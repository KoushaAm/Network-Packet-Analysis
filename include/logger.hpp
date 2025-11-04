#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <string>
#include "packet.hpp"

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {


public:
    std::string filename;
    bool rewriteCSV; 

    Logger(const std::string & filename, bool rewriteCSV = false);
    ~Logger();

    void logPacket(const Packet & pkt);
    void logStats(int tcp, int udp, int icmp, int other, long totalBytes);
    void log(LogLevel level, const std::string & message);

};

#endif














