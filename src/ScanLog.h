#ifndef SCANLOG_H_
#define SCANLOG_H_

#include "Scan.h"

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <chrono>
#include <ctime>

class ScanLog {
public:
    ScanLog(const std::string address, const std::set<int>, const bool verbose);
    ~ScanLog();
    void addPort(const int);
    void startScan();
    std::string printScanLog() const;
    std::string generateScanInfo() const;
    std::string generatePortLog(const bool verbose) const;
    std::string getScanLog() const;
    void writeScanLog(const std::string & filePath);

private:
    Scan * scanner;
    bool verbose = false;
    std::string address;
    std::set<int> portSet;
    std::map<int, PortEntry>  portMap;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    std::chrono::duration<double> elapsedTime;
    int numOpen = 0;
    int numClosed = 0;
};


//void outputScanLog(const std::string & filePath, const Scan & s);

   
#endif /* SCANLOG_H_ */
