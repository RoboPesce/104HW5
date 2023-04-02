#ifndef DICTENG_H
#define DICTENG_H

#ifndef RECCHECK
#include <set>
#include <string>
#endif

//extern const std::set<std::string> dictWords; 
const std::set<std::string>& readDictWords(std::string filename);

#endif