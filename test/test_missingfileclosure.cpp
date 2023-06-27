//
// Created by Clay on 6/20/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <algorithm>
#include <ranges>
#include "missingfileclosure.h"
#include "destination.h"

using std::find;
using std::count;

SCENARIO("missingFileClosure") {
    vector<string> missingExtensions;
    missingfileclosure c(&missingExtensions);
    WHEN("destination is NOPATH") {
        c("/tmp/myfile.jpg", NOPATH);
        c("/tmp/yourfile.raw", NOPATH);
        THEN("Extension is added to missing extensions") {
            REQUIRE(find(missingExtensions.begin(), missingExtensions.end(), ".jpg") != missingExtensions.end());
            REQUIRE(find(missingExtensions.begin(), missingExtensions.end(), ".raw") != missingExtensions.end());
        }
    }
    WHEN("extension with NOPATH destination is found twice") {
        c("/tmp/first.jpg", NOPATH);
        c("/tmp/second.jpg", NOPATH);
        THEN("extension only appears in list once") {
            auto x = missingExtensions | std::views::filter([](string n){ return n == ".jpg"; }) ;
            REQUIRE(std::ranges::distance(x) == 1);
        }
    }
    WHEN("extension is an empty string") {
        c("/tmp/myfile", NOPATH);
        THEN("Extension is not found in the list") {
            REQUIRE(
                    std::ranges::distance(missingExtensions | std::views::filter([](string n){ return n == ""; })) == 0
                    );
        }
    }
    WHEN("destination is a directory") {
        c("/tmp/myfile.jpg", "Z:\\Photos");
        THEN("Extension is not found in missing extensions") {
            REQUIRE(find(missingExtensions.begin(), missingExtensions.end(), ".jpg") == missingExtensions.end());
        }
    }
}