//
// Created by Clay on 6/20/2023.
//

#ifndef PHOTOUNLOADER_MISSINGFILECLOSURE_H
#define PHOTOUNLOADER_MISSINGFILECLOSURE_H

#include <filesystem>
#include <vector>
#include <string>

using std::filesystem::path;
using std::vector;
using std::string;

class missingfileclosure {

public:
    vector<string> missingeExtensions;

    void operator()(path src, path dst);
};


#endif //PHOTOUNLOADER_MISSINGFILECLOSURE_H
