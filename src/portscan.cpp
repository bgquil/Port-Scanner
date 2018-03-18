#include <iostream>
#include <getopt.h>
#include "Scan.h"
#include "ParseHelper.h"
#include "ScanLog.h"

void printUsage() { 
    std::cout << "Usage: portscan -t [TARGET ADDRESS] -p [PORTS, PORT RANGE] " << std::endl;
}


void addressError() {
    std::cout << "Target Address Error: There was an error parsing the provided address." << std::endl;
}

void printHelp() {
    printUsage();
    std::cout << "Perform a simple TCP port scan on a computer.\n" << std::endl;
    std::cout << " -h\t Show this help information" << std::endl;
    std::cout << " -o\t write the scan log to a file" << std::endl;
    std::cout << " -p\t comma separated ports or port ranges" << std::endl;
    std::cout << " -t\t target's IPv4 address" << std::endl;
    std::cout << " -v\t Show both open and closed ports, only show open without -v" << std::endl;
    std::cout << "\nExamples" << std::endl;
    std::cout << "\t portscan -t 192.168.1.1 -p 23,53,80" << std::endl;
    std::cout << "\t portscan -t 192.168.1.1 -p 53,80,100-500 -v" << std::endl;
}

int main(int argc, char **argv) {
    std::string providedTarget;
    std::string providedPort;
    std::string outputFilePath;

    int option;
    bool verbose;
    int tFlag = 0;  
    int pFlag = 0;
    int hFlag = 0;
    int oFlag = 0;
    while ((option = getopt(argc, argv, "t:p:vho:")) != -1) {
        switch (option) {
            case 't':
                if (tFlag) {
                    printUsage();
                    return 1;
                }
                else {
                tFlag++;
                providedTarget = optarg;
                }
                break;
            case 'p':
                if (pFlag) {
                    printUsage();
                    return 1;
                }
                else { pFlag++;
                providedPort = optarg;
                }
                break;
            case 'v':
                verbose = true;
                break;
            case 'h':
                hFlag++;
                break; 
            case 'o': {
                oFlag++;
                outputFilePath = optarg;
                break;
                }
            default:
                printUsage();
        }
    }
    if (hFlag || argc < 3 || ( tFlag < 1 || pFlag < 1)) {
        printHelp();
    }

    else if (tFlag == 1 && pFlag == 1) {
        Scan s(providedTarget, verbose);
        if (s.addressOK()) {
            parsePorts(providedPort, &s);
            s.printPorts();

        if (oFlag == 1) {
            outputScanLog(&outputFilePath, &s); 
        }
            
            return 0;
        } 
        else {
            addressError();        
            return 1;
        }
    }

    return 1;
}
