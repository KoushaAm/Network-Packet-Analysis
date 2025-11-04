#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include <string.h> 
#include "packet.hpp"


class Display {
    public:
        Display();
        ~Display();

        void printPacket(Packet & pkt);

        void printStats(int tcp, int udp, int icmp, int other, long totalBytes);
};

#endif
