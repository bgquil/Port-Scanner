#include "ScanLog.h"


ScanLog::ScanLog(const std::string address, const std::set<int> ports, const bool verbose) {
    this->scanner =  new Scan(address);
    this->verbose = verbose;
    this->portSet = ports;
}

ScanLog::~ScanLog() {
    std::cout << "ScanLog Destructor Called:" << this << std::endl;
    delete scanner;
}

void ScanLog::startScan() {
    if (this->scanner->addressOK()) {
        this->startTime = std::chrono::system_clock::now();
        for (auto e : this->portSet) {
            this->addPort(e);
        }
    }
    this->endTime = std::chrono::system_clock::now();
    this->elapsedTime = endTime-startTime;
}

void ScanLog::addPort(const int port) {
    if(!this->portMap.count(port)){
        PortEntry p(port);
        bool isOpen = this->scanner->probe(port);
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


std::string ScanLog::getScanLog() const{
    return "";

}

// Generate Metadata about a scan
std::string ScanLog::generateScanInfo() const {
    std::time_t start = std::chrono::system_clock::to_time_t(startTime);
    std::stringstream ss; 
    ss << "Target Address: ";
    ss << this->address; 
    ss << "\tStart Time: ";
    ss << ctime(&start);
    ss << "\nTime Elapsed: "; 
    ss << this->elapsedTime.count(); 
    ss << "s";
    ss << "\nPorts Open: "; 
    ss << std::to_string(this->numOpen); 
    ss << "\nPorts Closed: "; 
    ss << std::to_string(this->numClosed);
    ss <<  "\n";

    return ss.str();

}

std::string ScanLog::generatePortLog(const bool verbose) const {
    std::stringstream ss; 
    if (this->numOpen == 0) {
        ss << "No open ports found or host isn't up\n";
    }
    else {
        for (auto element : this->portMap)  {
            if (this->verbose) {     
                ss << element.second.statusString() << "\n";
            }
            else if (element.second.getStatus() == true) { 
                ss << element.second.statusString() << "\n";
            }
        }
    }
    return ss.str();
}

void ScanLog::writeScanLog(const std::string & filePath) {
/*
    std::ofstream outputStream;
    outputStream.open(filePath);
    outputStream << "Port Scan\n";
    outputStream << s.getScanInfo();
    outputStream << s.generatePortLog();
    outputStream.close();
*/
}   
