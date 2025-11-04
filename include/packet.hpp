// packet.hpp
#ifndef PACKET_HPP
#define PACKET_HPP

#include <string>
#include <cstdint>
#include <pcap.h>

class Packet {
public:
    // fields
    std::string srcIP;
    std::string dstIP;
    uint16_t srcPort = 0;
    uint16_t dstPort = 0;
    std::string protocol;
    uint32_t length = 0;
    std::string timestamp;

    // constructor
    void parse(const u_char* data, size_t length);

private:
    // helper parsers for different layers
    void parseEthernet(const u_char* data);
    void parseIP(const u_char* data);
    void parseTCP(const u_char* data);
    void parseUDP(const u_char* data);
    void parseICMP(const u_char* data);
    
};

#endif 
