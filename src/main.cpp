#include "concurrentqueue.h"
#include "destination.h"
#include "configparser.h"
#include "token.h"
#include "filedestinationclosure.h"
#include "missingfileclosure.h"
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>

#include <fileapi.h>

using std::cout;
using std::cerr;
using std::endl;
using std::find;
using std::ifstream;
using std::ostringstream;
using std::string;
using std::filesystem::file_size;
using std::filesystem::path;
using std::filesystem::recursive_directory_iterator;
using namespace std::chrono;
using std::vector;
using std::chrono::duration;
using std::chrono::system_clock;

#define _BV(bit) (1 << (bit))

ConcurrentQueue<copyCommand> commands;
ConcurrentQueue<string> logQueue;

void loadFiles(path s, std::function<void(path, path)> closure) {
    for (auto e: recursive_directory_iterator(s)) {

        path p(e);

        if (std::filesystem::is_regular_file(p)) {
            auto root = get_destination(p);
            closure(p, root);
        }
    }
}

void read_configuration(path configfile) {
    string extension;
    string destination;
    ifstream in(configfile.c_str());

    string content((std::istreambuf_iterator<char>(in)), (std::istreambuf_iterator<char>()));
    in.close();

    Parser configparser;
    auto filemap = configparser.Parse(content);
    for (auto p: filemap) {
        if (p.second == "IGNORE") {
            add_destination(p.first, IGNORE_EXTENSION);
        } else {
            add_destination(p.first, p.second);
        }
    }

}

void log_message(string msg) {
    logQueue.push(msg);
}

void printLog(std::stop_token stoken) {
    while(true) {
        try {
            auto msg = logQueue.frontAndPop();
            cerr << msg << endl;
        } catch(std::out_of_range e) {
            if (stoken.stop_requested()) return;
            std::this_thread::sleep_for(500ms);
        }
    }
}

string find_start_path() {
    auto drives = GetLogicalDrives();

    for (int i = 0; i < 26; ++i) {
        DWORD mask = _BV(i);
        if (drives & mask) {
            ostringstream d;
            d << (char) ('A' + i) << ":\\DCIM";
            if (std::filesystem::exists(d.str())) {
                return d.str();
            }
        }
    }

    return ".";
}

void copyFile() {
    try {
        string verb;
        while(true) {
            auto cmd = commands.frontAndPop();
            auto parentpath = cmd.destination.parent_path();
            if (!std::filesystem::exists(parentpath)) {
                log_message("Creating folder " + parentpath.string());
                std::filesystem::create_directories(parentpath);
            }
            if (std::filesystem::exists(cmd.destination)) {
                verb = "Replacing ";
                std::filesystem::remove(cmd.destination);
            } else {
                verb = "Copying ";
            }
            log_message(verb + cmd.source.string() + " to " + cmd.destination.string());
            std::filesystem::copy(cmd.source, cmd.destination);
        }
    } catch(std::out_of_range e) {

    } catch(std::filesystem::filesystem_error e) {
        log_message(e.what());
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
    } else {
        startpath = find_start_path();
    }
    log_message("Unloading from " + startpath);

    {
        vector<string> missingExtensions;
        missingfileclosure missing(&missingExtensions);
        loadFiles(startpath, missing);

        if (!missingExtensions.empty()) {
            cerr << "Missing destinations for the following extensions:" << endl;
            for (auto f: missingExtensions) {
                cerr << f << endl;
            }
            return EXIT_FAILURE;
        }
    }

    filedestinationclosure files(&commands);
    loadFiles(startpath, files);

    std::jthread t1{copyFile};
    std::jthread t2{copyFile};
    std::jthread t3{copyFile};
    std::jthread t4{copyFile};

    std::jthread logThread{printLog};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    logThread.request_stop();
    logThread.join();

    return EXIT_SUCCESS;
}