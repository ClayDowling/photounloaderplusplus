#include "destination.h"

#include <filesystem>
#include <string>
#include <cstring>
#include <map>

using std::string;
using std::map;
using std::filesystem::path;

map<string, path> filepaths;

string toUpper(string src) {
    string dst = "";
    for(auto a : src) {
        if (isalpha(a)) {
            dst += toupper(a);
        } else {
            dst += a;
        }
    }
    return dst;
}


void add_destination(string extension, path destination) {    
    filepaths[toUpper(extension)] = destination;
}

path get_destination(path source) {
    string ext = toUpper(source.extension().string());
    return filepaths[ext];
}