#include <chrono>
#include <iostream>
#include <filesystem>

#include <fileapi.h>

using std::filesystem::recursive_directory_iterator;
using std::filesystem::path;
using std::cout;
using std::endl;
using std::time_t;
using namespace std::chrono;
using std::chrono::system_clock;
using std::chrono::duration;

#define _BV(bit) (1 << (bit))

int main(int argc, char** argv) {


    // auto drives = GetLogicalDrives();

    // for(int i = 0; i < 26; ++i) {
    //     DWORD mask = _BV(i);
    //     if (drives & mask) {
    //         cout << (char)('A' + i) << ":" << endl;
    //     }
    // }

    for(auto e : recursive_directory_iterator(".")) {
        const auto lastwrite = std::filesystem::last_write_time(e);
        const auto systemTime = std::chrono::file_clock::to_sys(lastwrite); 

        const std::chrono::year_month_day ymd(floor<days>(systemTime));

        int y = (int)ymd.year();
        unsigned m = (unsigned)ymd.month();
        unsigned d = (unsigned)ymd.day();

        path p(e);

        cout << p << ": " << y << "-" << m << "-" << d ;
        if (std::filesystem::is_regular_file(p)) {
            cout << "  EXTENSION: " << p.extension() << " FILENAME: " << p.stem();
        }
        cout << endl;
    }

}