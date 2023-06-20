//
// Created by Clay on 6/20/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include "missingfileclosure.h"
#include "destination.h"

using std::find;

SCENARIO("missingFileClosure") {
    missingfileclosure c;
    WHEN("destination is NOPATH") {
        c("/tmp/myfile.jpg", NOPATH);
        c("/tmp/yourfile.raw", NOPATH);
        THEN("Extension is added to missing extensions") {
            REQUIRE(find(c.missingeExtensions.begin(), c.missingeExtensions.end(), ".jpg") != c.missingeExtensions.end());
            REQUIRE(find(c.missingeExtensions.begin(), c.missingeExtensions.end(), ".raw") != c.missingeExtensions.end());
        }
    }
    WHEN("destination is a directory") {
        c("/tmp/myfile.jpg", "Z:\\Photos");
        THEN("Extension is not found in missing extensions") {
            REQUIRE(find(c.missingeExtensions.begin(), c.missingeExtensions.end(), ".jpg") == c.missingeExtensions.end());
        }
    }
}