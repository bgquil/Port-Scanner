#include "Scan.h"


Scan::Scan(const std::string address) {
    this->address = address;
}

Scan::~Scan(){ 
    //std::cout << "Scan Destructor Called:" << this << std::endl;
}

bool Scan::addressOK() const {
    return inet_addr(address.c_str()) != -1;
}

bool Scan::probe(const int port) {
    struct timeval timeLimit;
    fd_set fdset;

    // .05 second connection timeout
    timeLimit.tv_sec = 0;
    timeLimit.tv_usec = 50000;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(address.c_str());
    server.sin_port = htons(port);

    sock = socket(AF_INET, SOCK_STREAM, 0); 

    if (sock == -1) {
        std::cout << "Error: couldn't create socket" << std::endl; 
        return false;
    }
    else {

        // set to nonblocking mode
        fcntl(sock, F_SETFL, O_NONBLOCK);

        FD_ZERO(&fdset);
        FD_SET(sock, &fdset);

        connect(sock, (struct sockaddr *) &server, sizeof(server));

        if (select(sock + 1, NULL, &fdset, NULL, &timeLimit) == 1) {
            int so_error = -1;
            socklen_t len = sizeof(so_error);
            getsockopt(sock, SOL_SOCKET, SO_ERROR, &so_error, &len);

            if (so_error == 0) {
                // port open
                shutdown(sock, 2);
                close(sock); // unistd
                return true;
            }
        }
        // closed
        shutdown(sock, 2);
        close(sock); // unistd
        return false;
    }
}

