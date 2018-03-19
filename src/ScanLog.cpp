#include "ScanLog.h"

void outputScanLog(const std::string & filePath, const Scan & s) {
    std::ofstream outputStream;
    outputStream.open(filePath);
    outputStream << "Port Scan\n";
    outputStream << s.getScanInfo();
    outputStream << s.generatePortLog();
    outputStream.close();
    
}   

