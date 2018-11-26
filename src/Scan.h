
#ifndef SCAN_H_
#define SCAN_H_

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <fcntl.h>
#include "PortEntry.h"


class Scan {
public:
    Scan(const std::string address, const bool verbose);
    ~Scan();
    bool addressOK() const;
    void addPort(const int port);
    bool probe(const int port);
    void printPorts();
    void startScan();
    std::string getScanInfo() const;
    std::string generatePortLog() const;
    std::string getAddress();
    int getNumOpen();
    int getNumClosed();
    std::chrono::duration<double> getElapsedTime();
    

private:
    std::string address;
    std::map<int, PortEntry> portMap;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    std::chrono::duration<double> elapsedTime;
    bool verbose;
    int numOpen;
    int numClosed;
    int sock;
    struct sockaddr_in server;
};
#endif /* SCAN_H_ */
