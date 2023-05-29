#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "token.h"
#include <filesystem>
#include <map>
#include <string>


using std::map;
using std::string;
using std::filesystem::path;

class Parser {

public:
  map<string, path> Parse(string contents);

private:
  string buffer;
};

#endif