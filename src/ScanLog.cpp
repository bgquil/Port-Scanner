#include "ScanLog.h"




ScanLog::ScanLog(Scan * scan, const bool verbose) {
    std::cout << "ScanLog created" << std::endl;
    this->scan = scan;
    this->verbose = verbose;
}

ScanLog::~ScanLog() {
    std::cout << "Desctructor Called:" << this << std::endl;
}

std::string ScanLog::getScanLog() const{
    return "";

}

std::string ScanLog::generateScanInfo() const {
    /*
    std::stringstream ss; 
    ss << "Target Address: ";
    ss << scan->address; 
    ss << "\tStart Time: ";
    ss << ctime(&start);
    ss << "\nTime Elapsed: "; 
    ss << elapsedTime.count(); 
    ss << "s";
    ss << "\nPorts Open: "; 
    ss << std::to_string(scan->numOpen); 
    ss << "\nPorts Closed: "; 
    ss << std::to_string(scan-> numClosed);
    ss <<  "\n";
    return ss.str();
    */

}


std::string ScanLog::generatePortLog() const {
    std::stringstream ss; 
    /*
    if (this->numOpen == 0) {
    ss << "No open ports found or host isn't up\n";
    }
    ss << "\n";
    for (auto element : this->portMap)  {
        ss << element.second.statusString() << "\n";
    }
    */
    return ss.str();
}


void outputScanLog(const std::string & filePath, const Scan & s) {
    std::ofstream outputStream;
    outputStream.open(filePath);
    outputStream << "Port Scan\n";
    outputStream << s.getScanInfo();
    outputStream << s.generatePortLog();
    outputStream.close();
    
}   
