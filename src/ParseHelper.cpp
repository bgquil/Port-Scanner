#include "ParseHelper.h"

void printRangeErrorInfo() {
    std::cout << "Error parsing provided port arguments." << std::endl;;
    std::cout << "-p <Port range> [0 <= start port < end port <= 65535] '-p 23-101'" << std::endl;
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

std::vector<std::string> split(const std::string & rawPortArguments) {
    std::vector<std::string> portArgVector;
    splitHelper(rawPortArguments, std::back_inserter(portArgVector));
    return portArgVector;
}


void parseRange(const std::string & range, std::set<int> & portSet) {
    std::string::size_type rangeSep = range.find('-');
    std::string startStr = range.substr(0, rangeSep);
    std::string endStr = range.substr(rangeSep+1, range.length());

    try {
        int start = stoi(startStr);
        int end = stoi(endStr);

        if (start >= 0 && start < 65335 && start < end && end > 0 && end <= 65535) {
            for (int i = start; i <= end; i++) {
                portSet.insert(i);
            } 
        }
        else {
            printRangeErrorInfo();
            exit(2);
        }
    } catch (std::invalid_argument& e) {
        printRangeErrorInfo();
    }
}

std::set<int> parsePorts(const std::string & portArgument)  { 
    std::set<int> portSet;
    //split port arguments
    std::vector<std::string> ports =  split(portArgument);
    //parse each argument, checking for range or single port
    for (int i = 0; i < ports.size(); i++) {     
        std::string portString = ports[i];
        if (portString.find("-") != std::string::npos) {
            parseRange(ports[i], portSet);    
        }
        else { 
            try {
                int parsedPort =  stol(ports[i]);
                portSet.insert(parsedPort);
            } catch (std::invalid_argument& e) {

            }
        }
    }

    return portSet;
}
