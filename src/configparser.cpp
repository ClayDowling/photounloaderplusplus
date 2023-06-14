#include "configparser.h"
#include <iostream>
#include <sstream>

using std::ostringstream;

map<string, string> Parser::Parse(string contents) {

  map<string, string> config;
  token_stream ts(contents);
  token t;
  string extension;

  while (ts) {
    ts >> t;
    switch (t.type) {
    case EXTENSION:
      if (extension != "") {
        ostringstream ss;
        ss << "Extension " << extension << " active when new extension "
           << t.value << " received";
        throw parse_exception(ss.str());
      }
      extension = t.value;
      break;
    case STRING:
      if (extension == "") {
        ostringstream ss;
        ss << "Destination " << t.value << " without associated extension";

        throw parse_exception(ss.str());
      }
      config[extension] = t.value;
      extension = "";
      break;
    case IGNORE:
      config[extension] = "IGNORE";
      extension = "";
      break;
    }
  }
  if (extension != "") {
    ostringstream ss;
    ss << "Extension " << extension << " without destination";
    throw parse_exception(ss.str());
  }

  return config;
}

const char *parse_exception::what() const noexcept { return message; }
