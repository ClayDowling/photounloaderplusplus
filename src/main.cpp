#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>

using std::cout;
using std::endl;
using std::ifstream;
using std::filesystem::path;
using std::string;

int main(int argc, const char* argv[]) {

    path homedir = getenv("USERPROFILE");
    path configfile = homedir / ".photounloader";

    cout << "Reading from " << configfile << endl;

    {
        string extension;
        string destination;
        ifstream in(configfile.c_str());
        while(in) {
            extension = "";
            destination = "";
            in >> extension >> destination;
            if (extension != "" && destination != "") {
                cout << extension << " -> " << destination << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}