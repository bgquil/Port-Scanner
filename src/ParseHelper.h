
#ifndef PARSEHEPLER_H_
#define PARSEHELPER_H_

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
#endif /* PARSERHELPER_H_ */
