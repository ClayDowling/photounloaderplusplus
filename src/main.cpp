#include "concurrentqueue.h"
#include "destination.h"
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::filesystem::file_size;
using std::filesystem::path;
using std::filesystem::recursive_directory_iterator;
using namespace std::chrono;
using std::chrono::duration;
using std::chrono::system_clock;

ConcurrentQueue<copyCommand> files;

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
      if (root != NOPATH) {
        v.destination = root / datestamp / p.filename();
        files.push(v);
      }
    }
  }
}

int main(int argc, const char *argv[]) {

  path homedir = getenv("USERPROFILE");
  path configfile = homedir / ".photounloader";

  cout << "Reading from " << configfile.string() << endl;

  {
    string extension;
    string destination;
    ifstream in(configfile.c_str());
    while (in) {
      extension = "";
      destination = "";
      in >> extension >> destination;
      if (extension != "" && destination != "") {
        add_destination(extension, destination);
      }
    }
  }

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

  return EXIT_SUCCESS;
}