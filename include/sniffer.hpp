#ifndef SNIFFER_HPP
#define SNIFFER_HPP

// https://www.winpcap.org/docs/docs_412/html/incs_2pcap_8h_source.html
#include <pcap.h>
#include <string>


class Sniffer {
    public:
        // constructor
        Sniffer(const std::string& interface);
        // start capturing packets

        bool init();
        
        ~Sniffer(); // destructor to clean up pcap handle

        void startCapture();
        void stopCapture();

    private:
        pcap_t* handle; // pcap handle for capturing packets
        std::string interfaceName; // network interface name
        char errbuf[PCAP_ERRBUF_SIZE]; // error buffer

        // pcap_pkthdr: https://www.winpcap.org/docs/docs_412/html/structpcap__pkthdr.html
        // attributes: ts (timestamp), caplen (length of portion present), len (length of the packet)
        static void packetHandler(u_char *args, const struct pcap_pkthdr *header, const u_char* bytes);

};
#endif // SNIFFER_HPP


