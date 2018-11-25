#ifndef SCANLOG_H_
#define SCANLOG_H_

#include <iostream>
#include <fstream>
#include "Scan.h"


class ScanLog {
public:
    ScanLog(Scan * scan, const bool verbose);
    ~ScanLog();
    std::string getScanLog() const;
    std::string generateScanInfo() const;
    std::string generatePortLog() const;

private:
    Scan * scan;
    bool verbose;
};


void outputScanLog(const std::string & filePath, const Scan & s);

   
#endif /* SCANLOG_H_ */
