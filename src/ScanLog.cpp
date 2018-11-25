#include "ScanLog.h"

void outputScanLog(const std::string & filePath, const Scan & s) {
    std::ofstream outputStream;
    outputStream.open(filePath);
    outputStream << "Port Scan\n";
    outputStream << s.getScanInfo();
    outputStream << s.generatePortLog();
    outputStream.close();
    
}   


std::string generateScanInfo() const {

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


std::string generatePortLog() const {
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

