
#ifndef PORTENTRY_H_
#define PORTENTRY_H_

#include <sstream>

class PortEntry {
public:
    PortEntry(): portNumber(-1), status(false) {};
    PortEntry(const int portNumber); 
    PortEntry(const int portNumber, const bool status); 
    std::string statusString();
    void setStatus(const bool status);
    bool getStatus();
    
private:
    int portNumber;
    bool status;
}; 

#endif /* PORTENTRY_H_ */
