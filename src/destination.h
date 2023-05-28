#ifndef DESTINATION_H
#define DESTINATION_H

#include <chrono>
#include <filesystem>
#include <string>

using std::string;
using std::filesystem::path;

struct copyCommand {
  path source;
  std::chrono::time_point<std::chrono::system_clock> filetime;
  path destination;
  unsigned long size;
};

extern path NOPATH;

void add_destination(string extension, path destination);
path get_destination(path source);

#endif