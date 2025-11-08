#include "packet.hpp"
#include <iostream>
#include <netinet/if_ether.h>  
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>

// how the data should be broken down: 
// datalink --> Ethernet --> IP --> (TCP/UDP/ICMP)

void Packet::parse(const u_char* data, size_t length) {
    if (length < sizeof(struct ether_header)) {
        std::cerr << "Packet too short for Ethernet header\n";
        return;
    }
    this->length = length;

    parseEthernet(data);
}

void Packet::parseEthernet(const u_char* data) {
    // Ethernet parsing logic
    // 7 bytes preampble + 1 byte SFD + 6 bytes dest MAC 
    // + 6 bytes src MAC + 2 bytes type + payload (upto 1500 bytes) + 4 bytes CRC
    const struct ether_header* ethHeader = (struct ether_header*)data;

    // get the type field to determine the next protocol
    uint16_t etherType = ntohs(ethHeader->ether_type);

    if (etherType == ETHERTYPE_IP) {
        this->protocol = "IPv4";
        parseIP(data + sizeof(struct ether_header));
    } else if (etherType == ETHERTYPE_IPV6) {
        this->protocol = "IPv6";
    } else {
        this->protocol = "Other";
    }
    
}

void Packet::parseIP(const u_char* data) {
    // data is now pointing to the IP header
    // struct ip defined in <netinet/ip.h>
    const struct ip* ipHeader = (struct ip*)data;

    uint8_t protocol = ipHeader->ip_p;

    // ipHeader->ip_hl * 4: length of the ip header in bytes
    // data + ipHeader->ip_hl * 4: pointer to the next protocol header 
    // (grabs the payload after IP header that is TCP/UDP/ICMP header)
    if (protocol == IPPROTO_TCP) {
        this->protocol = "TCP";
        parseTCP(data + ipHeader->ip_hl * 4);
    } else if (protocol == IPPROTO_UDP) {
        this->protocol = "UDP";
        parseUDP(data + ipHeader->ip_hl * 4);
    } else if (protocol == IPPROTO_ICMP) {
        this->protocol = "ICMP";
        parseICMP(data + ipHeader->ip_hl * 4);
    } else {
        this->protocol = "Other";
    }


}

void Packet::parseTCP(const u_char* data) {
    // TCP parsing logic
    // struct tcp defined in <netinet/tcp.h>
    const struct tcphdr* tcpHeader = (struct tcphdr*)data;

    this->srcPort = ntohs(tcpHeader->th_sport);
    this->dstPort = ntohs(tcpHeader->th_dport);

}

void Packet::parseUDP(const u_char* data) {
    // UDP parsing logic
    const struct udphdr* udpHeader = (struct udphdr*)data;
    this->srcPort = ntohs(udpHeader->uh_sport);
    this->dstPort = ntohs(udpHeader->uh_dport);

}

void Packet::parseICMP(const u_char* data) {
    // ICMP parsing logic
    const struct icmphdr* icmpHeader = (struct icmphdr*)data;
    // ICMP does not have ports, so we leave srcPort and dstPort as 0
    this->srcPort = 0; 
    this->dstPort = 0;
}

