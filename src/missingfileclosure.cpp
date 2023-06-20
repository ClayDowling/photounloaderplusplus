//
// Created by Clay on 6/20/2023.
//

#include "destination.h"
#include "missingfileclosure.h"

void missingfileclosure::operator()(path src, path dst) {
    if (dst == NOPATH) {
        missingeExtensions.push_back(src.extension().string());
    }
}