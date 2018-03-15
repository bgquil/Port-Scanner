#include "Scan.h"


Scan::Scan(const std::string address, const bool verbose) {
    this->address = address;
    this->verbose = verbose;
    this->numOpen = 0;
}

Scan::~Scan(){ 
    //std::cout << "Destructor Called" << std::endl;
}


void Scan::addPort(const int port) {
    if(!this->portMap.count(port)){
        PortEntry p(port);
        bool isOpen = probe(port);
        p.setStatus(isOpen);
        if (isOpen) this-numOpen++;
        this->portMap.insert(std::make_pair(port, p)); 
    }
}

void Scan::printPorts() {
    for (auto element : this->portMap)  {
        if (this->verbose) {     
            std::cout << element.second.statusString() << std::endl;
        }
        else if (element.second.getStatus() == true) { 
            std::cout << element.second.statusString() << std::endl;
        }
    }
    if (this->numOpen == 0) {
        std::cout << "No open ports found" << std::endl;
    }
}

bool Scan::addressOK() {
    return inet_addr(address.c_str()) != -1;
}

bool Scan::probe(const int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock == -1) {
        std::cout << "Couldn't create socket" << std::endl; 
    }
 
    // for dns lookup 
    if (inet_addr(address.c_str()) == -1) {
        std::cout << "Bad target address" << std::endl;
    }
    else {
        // for ip
        server.sin_addr.s_addr = inet_addr(address.c_str());
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    // Attempt TCP connection
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
        //std::cout << port << ": Closed" << std::endl;
    } 
    else {
        //std::cout << port << ": Open" << std::endl;
        return true;
    }
    shutdown(sock, 2);
    close(sock); // unistd
    return false;
}





