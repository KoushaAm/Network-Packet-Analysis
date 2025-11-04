#include "display.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Display::Display() {
    // Constructor
}

Display::~Display() {
    // Destructor
    
}

void Display::printPacket(Packet & pkt) {
    string color;
    if (pkt.protocol == "TCP") color = "\033[32m"; // green
    else if (pkt.protocol == "UDP") color = "\033[34m"; // blue
    else if (pkt.protocol == "ICMP") color = "\033[33m"; // yellow
    else color = "\033[37m"; // white 

    cout << color
         << "----------------------------------------\n"
         << "🌐 Protocol: " << pkt.protocol << "\n"
         << "📍 Src IP: " << pkt.srcIP << " | Src Port: " << pkt.srcPort << "\n"
         << "📍 Dst IP: " << pkt.dstIP << " | Dst Port: " << pkt.dstPort << "\n"
         << "📦 Length: " << pkt.length << " bytes\n"
         << "🕒 Timestamp: " << pkt.timestamp << "\n"
         << "----------------------------------------\n"
         << "\033[0m"; 
}

void Display::printStats(int tcp, int udp, int icmp, int other, long totalBytes) {
    std::cout << "\n📊 Stats: "
              << "TCP: " << tcp << " | "
              << "UDP: " << udp << " | "
              << "ICMP: " << icmp << " | "
              << "Other: " << other
              << " | Total Bytes: " << totalBytes << "\n";
}

