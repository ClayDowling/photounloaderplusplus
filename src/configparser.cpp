#include "configparser.h"

map<string, string> Parser::Parse(string contents) {

  map<string, string> config;
  token_stream ts(contents);
  token t;
  string extension;

  while (ts) {
    ts >> t;
    switch (t.type) {
    case EXTENSION:
      extension = t.value;
      break;
    case STRING:
      config[extension] = t.value;
      extension = "";
      break;
    }
  }

  return config;
}

const char *parse_exception::what() const noexcept { return message; }
