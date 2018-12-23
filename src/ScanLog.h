#ifndef SCANLOG_H_
#define SCANLOG_H_

#include "Scan.h"
#include "PortEntry.h"

#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <chrono>
#include <ctime>
#include <memory>

class ScanLog {
public:
    ScanLog(const std::string addr, const std::set<int> port) : 
        address(addr), portSet(port), scanner(new Scan(addr))
    {};
    //ScanLog(const std::string address, const std::set<int>, const bool verbose);
    ~ScanLog();
    void addPort(const int);
    void startScan();
    std::string printScanLog() const;
    std::string generateScanInfo() const;
    std::string generatePortLog(const bool verbose) const;
    std::string getScanLog() const;
    void writeScanLog(const std::string & filePath);

private:
    std::unique_ptr<Scan> scanner;
    std::string address;
    std::set<int> portSet;
    std::map<int, PortEntry>  portMap;
    std::chrono::system_clock::time_point startTime;
    std::chrono::system_clock::time_point endTime;
    std::chrono::duration<double> elapsedTime;
    int numOpen = 0;
    int numClosed = 0;
};

   
#endif /* SCANLOG_H_ */
