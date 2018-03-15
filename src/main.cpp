#include <iostream>
#include <getopt.h>
#include "PortEntry.h"
#include "Scan.h"


void printUsageError() { 
    std::cout << "Usage: main -t <Target Address> -p <Port range>" << std::endl;
}

void printRangeErrorInfo() {
    std::cout << "-p <Port range> [0 <= start port < end port <= 65535]" << std::endl;
}

void addressError() {
    std::cout << "Target Address Error: There was an error parsing the provided address." << std::endl;
}

template<typename Out>
void splitHelper(const std::string &s, Out result) {
    char delim = ','; 
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;    
    } 
}

std::vector<std::string> split(const std::string &rawPortArguments) {
    std::vector<std::string> portArgVector;
    splitHelper(rawPortArguments, std::back_inserter(portArgVector));
    return portArgVector;
}


int parseRange(const std::string range, Scan * const s) {
    std::string::size_type rangeSep = range.find('-');
    std::string startStr = range.substr(0, rangeSep);
    std::string endStr = range.substr(rangeSep+1, range.length());

    try {
        int start = stoi(startStr);
        int end = stoi(endStr);

        if (start >= 0 && start < 65335 && start < end && end > 0 && end <= 65535) {
            for (int i = start; i <= end; i++) {
                    s->addPort(i);
            } 
        }
        else {
            printUsageError();
            printRangeErrorInfo();
            exit(2);
        }
    } catch (std::invalid_argument& e) {
        printUsageError();
        return 2; 
    }
}

int parsePorts(const std::string portArgument, Scan * const s)  { 
    //split port arguments
    std::vector<std::string> ports =  split(portArgument);
    //parse each argument, checking for range or single port
    for (int i = 0; i < ports.size(); i++) {     
        std::string portString = ports[i];
        if (portString.find("-") != std::string::npos) {
            parseRange(ports[i], s);    
        }
        else { 
            try {
                int parsedPort =  stol(ports[i]);
                s->addPort(parsedPort);   
            } catch (std::invalid_argument& e) {
                printUsageError();
                return 2;
            }
        }
    } 
}

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
            default:
                printUsageError(); 
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
