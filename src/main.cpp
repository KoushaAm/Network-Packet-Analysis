// main.cpp
#include <iostream>
#include <pcap.h>
#include "packet.hpp"


int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: sudo " << argv[0] << " <network_interface>\n";
        std::cerr << "Example: sudo " << argv[0] << " en0\n";
        return 1;
    }

    return 0;
}
