//
// Created by Clay on 6/20/2023.
//

#include <filesystem>
#include "filedestinationclosure.h"

using std::chrono::days;
using std::filesystem::last_write_time;

filedestinationclosure::filedestinationclosure(ConcurrentQueue<copyCommand>* c) {
    commands = c;
}


void filedestinationclosure::operator()(path src, path dst) {

    if (dst == IGNORE_EXTENSION) return;

    copyCommand cmd;
    cmd.source = src;

    auto root = get_destination(src);
    auto lastWrite = last_write_time(src);
    auto sysTime = std::chrono::file_clock::to_sys(lastWrite);

    copyCommand v;
    v.source = src;
    v.size = file_size(src);
    v.destination = root / datestamp(sysTime) / src.filename();
    commands->push(v);

}

string datestamp(std::chrono::time_point<system_clock> point) {
    char ds[12];
    const std::chrono::year_month_day ymd(floor<days>(point));

    int y = (int) ymd.year();
    unsigned m = (unsigned) ymd.month();
    unsigned d = (unsigned) ymd.day();

    snprintf(ds, sizeof(ds), "%4.4d-%2.2d-%2.2d", y, m, d);
    return ds;
}