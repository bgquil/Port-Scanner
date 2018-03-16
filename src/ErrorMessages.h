#ifndef ERRORMESSAGES_H_
#define ERRORMESSAGES_H_

void printUsageError() { 
    std::cout << "Usage: main -t <Target Address> -p <Port range> -v <Verbose: show Open and Closed ports>" << std::endl;
}

void printRangeErrorInfo() {
    std::cout << "-p <Port range> [0 <= start port < end port <= 65535]" << std::endl;
}

void addressError() {
    std::cout << "Target Address Error: There was an error parsing the provided address." << std::endl;
}
    
#endif /* ERRORMESSAGES_H_ */
