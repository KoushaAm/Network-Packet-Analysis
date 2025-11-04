#include "sniffer.hpp"    
#include <iostream>
#include <cstring>   
#include <ctime>
#include <sstream>    
#include <iomanip>
#include "packet.hpp"
#include "display.hpp"
#include "logger.hpp"


using namespace std;

static Display display;
static Logger logger("packets.csv", true);


bool Sniffer::init() {
    handle = pcap_open_live(
        interfaceName.c_str(), // device
         BUFSIZ,  // snaplen
         1, // promiscuous mode (1 = capture all packets)
         1000, // read timeout in ms
         errbuf); // error buffer

    if (handle == nullptr) {
        cerr << "Could not open device " << interfaceName << ": " << errbuf << endl;
        return false; 
    }

    if (pcap_datalink(handle) != DLT_EN10MB) {
        cerr << "Device " << interfaceName << " does not provide Ethernet headers (not supported)\n";
        pcap_close(handle);
        return false; 
    }
    
    this->handle = handle;



    return true; 
}


Sniffer::~Sniffer() {
    if (handle) {
        pcap_close(handle);
        handle = nullptr;
        cout << "🚪 Closed pcap handle for " << interfaceName << endl;
    }
}

Sniffer::Sniffer(const string& interfaceName) {

    this->interfaceName = interfaceName;
    this->handle = nullptr;
    // initialize errbuf to zero
    memset(errbuf, 0, PCAP_ERRBUF_SIZE);
    init();
    
}

void Sniffer::startCapture() {
    if (!handle) {
        cerr<<"❌ Error: interface not initialized :("<<endl; 
        return; 
    }

    cout<< "📡 Starting capture on interface: " << interfaceName << endl;

    if(pcap_loop(this->handle, -1, this->packetHandler, nullptr)) {
        cerr << "❌ Error while capturing packets: " << pcap_geterr(handle) << endl;
    }

}

void Sniffer::packetHandler(u_char *args, const struct pcap_pkthdr *header, const u_char* bytes) {
    Packet pkt; 
    pkt.parse(bytes, header->len);

    // formatting time
    std::time_t now = std::time(nullptr);
    std::stringstream ts;
    ts << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S");
    pkt.timestamp = ts.str();

    display.printPacket(pkt);
    logger.logPacket(pkt);

}
