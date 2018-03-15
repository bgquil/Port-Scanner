#include "PortEntry.h"

PortEntry::PortEntry(const int portNumber, const bool status) {
        this->portNumber = portNumber;
        this->status = status;
}

PortEntry::PortEntry(const int portNumber) {
    this->portNumber = portNumber;    
}

void PortEntry::setStatus(const bool status){
    this->status = status;
}

bool PortEntry::getStatus() {
    return this->status;
}

std::string PortEntry::statusString() {
    std::stringstream ss;
    ss << "Port: "; 
    ss << this->portNumber;
    ss << "\tStatus: "; 
    ss << (this->status ? "Open": "Closed");
    return ss.str();
}
