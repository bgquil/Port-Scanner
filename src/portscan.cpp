
#include <iostream> 
#include <getopt.h>
#include "Scan.h"
#include "ParseHelper.h"
#include "ScanLog.h"
#include <set>

void printUsage() { 
    std::cout << "Usage: portscan -t [TARGET IPv4 ADDRESS] -p [PORTS, PORT RANGE] " << std::endl;
}


void addressError() {
    std::cout << "Target Address Error: There was an error parsing the provided address." << std::endl;
}

void printHelp() {
    printUsage();
    std::cout << "Perform a simple TCP port scan on a given host.\n\n" 
    << " -h\t show this help information\n" 
    << " -t\t target's IPv4 address\n"
    << " -p\t comma separated ports or port ranges\n"
    << " -o\t write the scan log to a file\n"
    << " -v\t show both open and closed ports, default show open only\n"
    << "\nExamples:\n"
    << "\t portscan -t 192.168.1.1 -p 23,53,80\n"
    << "\t portscan -t 192.168.1.1 -p 53,80,100-500 -v\n"
    << "\t portscan -t 192.168.1.103 -p 10-100 -o ~/scan.txt\n" << std::endl;
}

int main(int argc, char **argv) {
    std::string providedTarget;
    std::string providedPort;
    std::string outputFilePath;

    int option = 0;
    bool verboseFlag = false;;
    int targetFlag = 0;
    int portFlag = 0;
    int helpFlag = 0;
    int outputFlag = 0;

    while ((option = getopt(argc, argv, "t:p:vho:")) != -1) {
        switch (option) {
            case 't':
                if (targetFlag) {
                    printUsage();
                    return 1;
                }
                else {
                targetFlag++;
                providedTarget = optarg;
                }
                break;
            case 'p':
                if (portFlag) {
                    printUsage();
                    return 1;
                }
                else { 
                portFlag++;
                providedPort = optarg;
                }
                break;
            case 'v':
                verboseFlag = true;
                break;
            case 'h':
                helpFlag++;
                break; 
            case 'o': {
                outputFlag++;
                outputFilePath = optarg;
                break;
                }
            default:
                printUsage();
                return 1;            
        }
    }
    // print help if required scan options are not given 
    if (helpFlag || argc < 3 || ( targetFlag < 1 || portFlag < 1)) {
        printHelp();
    }
    else if (targetFlag == 1 && portFlag == 1) {
        std::set<int> portSet;
        portSet = parsePorts(providedPort);

        ScanLog log(providedTarget, portSet);

        try {
            std::cout << "Scan started.\n" << std::endl;
            log.startScan();

            std::cout << log.generateScanInfo() << std::endl;
            std::cout << log.generatePortLog(verboseFlag) << std::endl;

            if (outputFlag == 1) {
                log.writeScanLog(outputFilePath); 
            }
        }
        catch (std::invalid_argument& err) {
            addressError();        
            return 1;
        }

        return 0;
    }

    return 1;
}
