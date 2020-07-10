#pragma once

#include <map>
#include <string>

namespace synthesis {

struct Element
{
  std::string name;
  std::map<std::string, std::string> properties;
  Element(const char* name)
    : name(name)
  {}
};

}
