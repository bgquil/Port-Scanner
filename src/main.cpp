#include <iostream>
#include <getopt.h>
#include "PortEntry.h"
#include "Scan.h"
#include "ErrorMessages.h"
#include "ParseHelper.h"

int main(int argc, char **argv) {
    std::string providedTarget;
    std::string providedPort;
    if (argc < 3) {
        printUsageError();
        return 2; 
    } 

    int option;
    bool verbose;
    int tFlag = 0;  
    int pFlag = 0;
    while ((option = getopt(argc, argv, "t:p:v")) != -1) {
        switch (option) {
            case 't':
                if (tFlag) {
                    printUsageError();
                    return 1;
                }
                else {
                tFlag++;
                providedTarget = optarg;
                }
                break;
            case 'p':
                if (pFlag) {
                    printUsageError();
                    return 1;
                }
                else {
                pFlag++;
                providedPort = optarg;
                }
                break;
            case 'v':
                verbose = true;
        }
    }

    if (tFlag == 1 && pFlag == 1) {
        Scan s(providedTarget, verbose);
        if (s.addressOK()) {
            parsePorts(providedPort, &s);
            s.printPorts();
            return 0;
        } 
        else {
            addressError();        
            return 1;
        }
    }

    return 1;
}
