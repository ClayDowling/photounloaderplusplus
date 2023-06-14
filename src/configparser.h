#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include "token.h"
#include <cstring>
#include <exception>
#include <map>
#include <string>

using std::exception;
using std::map;
using std::string;

class parse_exception : public exception {
private:
  const char *message;

public:
  parse_exception(const char *m) : message(strdup(m)){};
  parse_exception(string m) : message(strdup(m.c_str())){};

  virtual const char *what() const noexcept;
};

class Parser {

public:
  map<string, string> Parse(string contents);

private:
  string buffer;
};

#endif