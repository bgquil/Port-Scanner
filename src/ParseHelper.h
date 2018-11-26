
#ifndef PARSEHEPLER_H_
#define PARSEHELPER_H_
#include <iostream>
#include <set>
#include <vector>
#include <sstream>

template<typename Out>
void splitHelper(const std::string &s, Out result);

std::vector<std::string> split(const std::string & rawPortArguments);

int parseRange(const std::string & range, std::set<int> & s);

std::set<int> parsePorts(const std::string & portArgument);

#endif /* PARSERHELPER_H_ */
