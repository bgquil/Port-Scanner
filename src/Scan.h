
#ifndef SCAN_H_
#define SCAN_H_

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>


class Scan {
public:
    Scan(const std::string address);
    ~Scan();
    bool addressOK() const;
    void setupServer(); 
    bool probe(const int port);

private:
    std::string address;
    struct timeval timeLimit;
    int sock;
    struct sockaddr_in server;
};
#endif /* SCAN_H_ */
