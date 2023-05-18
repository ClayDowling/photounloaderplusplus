#ifndef DESTINATION_H
#define DESTINATION_H

#include <filesystem>
#include <string>

using std::filesystem::path;
using std::string;

struct copyCommand {
    path source;
    path destination;
};

void add_destination(string extension, path destination);
path get_destination(path source);


#endif