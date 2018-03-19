
#ifndef PARSEHEPLER_H_
#define PARSEHELPER_H_
#include <iostream>
#include "Scan.h"

template<typename Out>
void splitHelper(const std::string &s, Out result);

std::vector<std::string> split(const std::string & rawPortArguments);

int parseRange(const std::string & range, Scan & s);

int parsePorts(const std::string & portArgument, Scan & s);

#endif /* PARSERHELPER_H_ */
