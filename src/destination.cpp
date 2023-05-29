#include "destination.h"

#include <cstring>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>

using std::map;
using std::string;
using std::filesystem::path;

map<string, path> filepaths;
path NOPATH;
path IGNORE_EXTENSION("NULL:");

string toUpper(string src) {
  string dst = "";
  for (auto a : src) {
    if (isalpha(a)) {
      dst += toupper(a);
    } else {
      dst += a;
    }
  }
  return dst;
}

void add_destination(string extension, path destination) {
  string actual = toUpper(extension);
  filepaths[actual] = destination;
}

path get_destination(path source) {
  string ext = toUpper(source.extension().string());
  if (filepaths.contains(ext)) {
    return filepaths[ext];
  }
  return NOPATH;
}