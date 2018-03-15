
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
#include "PortEntry.h"


class Scan {
public:
    Scan(const std::string address, const bool verbose);
    ~Scan();
    bool addressOK();
    void addPort(const int port);
    bool probe(const int port);
    void printPorts();
    void startScan();
    

private:
    std::string address;
    bool verbose;
    int numOpen;
    int sock;
    struct sockaddr_in server;
    std::vector<int> portVector;
    std::map<int, PortEntry> portMap;
};
#endif /* SCAN_H_ */
