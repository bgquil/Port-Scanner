#include "ScanLog.h"

void outputScanLog(std::string *filePath, const Scan * const  s) {
    std::ofstream outputStream;
    outputStream.open("test393.txt");
    outputStream << s->getScanInfo();
    outputStream.close();
    
}   

