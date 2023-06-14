#include "concurrentqueue.h"
#include "destination.h"
#include "configparser.h"
#include "token.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::find;
using std::ifstream;
using std::string;
using std::filesystem::file_size;
using std::filesystem::path;
using std::filesystem::recursive_directory_iterator;
using namespace std::chrono;
using std::vector;
using std::chrono::duration;
using std::chrono::system_clock;

ConcurrentQueue<copyCommand> files;
vector<string> missingDirectories;

void loadFiles(path s) {
  for (auto e : recursive_directory_iterator(s)) {
    char datestamp[12];
    const auto lastwrite = std::filesystem::last_write_time(e);
    const auto systemTime = std::chrono::file_clock::to_sys(lastwrite);

    path p(e);

    if (std::filesystem::is_regular_file(p)) {
      copyCommand v;
      v.source = p;
      v.size = file_size(p);

      const std::chrono::year_month_day ymd(floor<days>(systemTime));

      int y = (int)ymd.year();
      unsigned m = (unsigned)ymd.month();
      unsigned d = (unsigned)ymd.day();

      snprintf(datestamp, sizeof(datestamp), "%4.4d-%2.2d-%2.2d", y, m, d);

      auto root = get_destination(p);
      if (root == NOPATH) {
        if (find(missingDirectories.begin(), missingDirectories.end(),
                 p.extension().string()) == missingDirectories.end()) {
          missingDirectories.push_back(p.extension().string());
        }
      } else {
        v.destination = root / datestamp / p.filename();
        files.push(v);
      }
    }
  }
}

void read_configuration(path configfile) {
  string extension;
  string destination;
  ifstream in(configfile.c_str());

  string content((std::istreambuf_iterator<char>(in)),
                 (std::istreambuf_iterator<char>()));
  in.close();

  Parser configparser;
  auto filemap = configparser.Parse(content);
  for(auto p: filemap) {
      if (p.second == "IGNORE") {
          add_destination(p.first, IGNORE_EXTENSION);
      } else {
          add_destination(p.first, p.second);
      }
  }

}

int main(int argc, const char *argv[]) {

  path homedir = getenv("USERPROFILE");
  path configfile = homedir / ".photounloader";

  cout << "Reading from " << configfile.string() << endl;
  read_configuration(configfile);

  string startpath = ".";
  if (argc > 1) {
    startpath = argv[1];
  }
  loadFiles(startpath);

  try {
    for (auto d = files.frontAndPop();; d = files.frontAndPop()) {
      cout << d.destination.string() << endl;
    }
  } catch (std::out_of_range e) {
    cout << "List complete." << endl;
  }

  if (!missingDirectories.empty()) {
    cout << "Missing extensions:" << endl;
    for (auto m : missingDirectories) {
      cout << m << endl;
    }
  }

  return EXIT_SUCCESS;
}