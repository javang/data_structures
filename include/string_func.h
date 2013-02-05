
#include "base_types.h"
#include <string>
#include <sstream>

#ifndef STRING_FUNC_H
#define STRING_FUNC_H

Strings split(const String &s, const char delimiter) {
  std::istringstream ss(s);
  String item;
  Strings words;
  while(std::getline(ss, item, delimiter)) {
    if(! item.empty()) words.push_back(item);
  }
  return words;
}

#endif
