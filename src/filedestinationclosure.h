//
// Created by Clay on 6/20/2023.
//

#ifndef PHOTOUNLOADER_FILEDESTINATIONCLOSURE_H
#define PHOTOUNLOADER_FILEDESTINATIONCLOSURE_H

#include <filesystem>
#include <chrono>

#include "destination.h"
#include "concurrentqueue.h"

using std::filesystem::path;
using std::chrono::system_clock;

class filedestinationclosure {
public:
    ConcurrentQueue<copyCommand> *commands;

    filedestinationclosure(ConcurrentQueue<copyCommand>*);

    void operator()(path src, path dst);
};

string datestamp(std::chrono::time_point<system_clock> point);

#endif //PHOTOUNLOADER_FILEDESTINATIONCLOSURE_H
