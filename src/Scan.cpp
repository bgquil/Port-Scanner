#include "Scan.h"


Scan::Scan(const std::string address, const bool verbose) {
    this->address = address;
    this->verbose = verbose;
    this->numOpen = 0;
    this->numClosed = 0;
    this->startTime = std::chrono::system_clock::now();
}

Scan::~Scan(){ 
    //std::cout << "Destructor Called" << std::endl;
}


void Scan::addPort(const int port) {
    if(!this->portMap.count(port)){
        PortEntry p(port);
        bool isOpen = probe(port);
        p.setStatus(isOpen);
        if (isOpen) {
            this-numOpen++;
        }
        else {
            this->numClosed++;
        }
        this->portMap.insert(std::make_pair(port, p)); 
    }
}

void Scan::printPorts() {
    this->endTime = std::chrono::system_clock::now();
    this->elapsedTime = endTime-startTime;
    std::cout << getScanInfo() << std::endl;
    for (auto element : this->portMap)  {
        if (this->verbose) {     
            std::cout << element.second.statusString() << std::endl;
        }
        else if (element.second.getStatus() == true) { 
            std::cout << element.second.statusString() << std::endl;
        }
    }
    if (this->numOpen == 0) {
        std::cout << "No open ports found or host isn't up" << std::endl;
    }
}

std::string Scan::getScanInfo() const {
    std::time_t start = std::chrono::system_clock::to_time_t(startTime);
    std::stringstream ss; 
    ss << "Target Address: ";
    ss << this->address; 
    ss << "\tStart Time: ";
    ss << ctime(&start);
    ss << "\nTime Elapsed: "; 
    ss << elapsedTime.count(); 
    ss << "s";
    ss << "\nPorts Open: "; 
    ss << std::to_string(this->numOpen); 
    ss << "\nPorts Closed: "; 
    ss << std::to_string(this-> numClosed);
    ss <<  "\n";
    return ss.str();
}

std::string Scan::generatePortLog() const {
    std::stringstream ss; 
    if (this->numOpen == 0) {
    ss << "No open ports found or host isn't up\n";
    }
    ss << "\n";
    for (auto element : this->portMap)  {
        ss << element.second.statusString() << "\n";
    }
    return ss.str();
}

bool Scan::addressOK() const {
    return inet_addr(address.c_str()) != -1;
}

bool Scan::probe(const int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0); 
    if (sock == -1) {
        std::cout << "Couldn't create socket" << std::endl; 
    }

    server.sin_addr.s_addr = inet_addr(address.c_str());
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

