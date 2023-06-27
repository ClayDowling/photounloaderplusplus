//
// Created by Clay on 6/20/2023.
//

#include <ranges>
#include "destination.h"
#include "missingfileclosure.h"

missingfileclosure::missingfileclosure(vector<std::string> *f) {
    missingeExtensions = f;
}

void missingfileclosure::operator()(path src, path dst) {
    if (dst == NOPATH) {
        string extension = src.extension().string();
        if (extension == "") return;
        if (std::ranges::distance(
                *missingeExtensions | std::views::filter(
                        [extension](string n){ return n == extension; })) == 0) {
            missingeExtensions->push_back(src.extension().string());
        }
    }
}