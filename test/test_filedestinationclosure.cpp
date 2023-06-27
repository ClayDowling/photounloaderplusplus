//
// Created by Clay on 6/20/2023.
//

#include <catch2/catch_test_macros.hpp>
#include <filesystem>
#include <fstream>
#include "filedestinationclosure.h"

using std::filesystem::temp_directory_path;
using std::filesystem::remove;
using std::ofstream;
using std::endl;

SCENARIO("filedestinationclosure") {
    ConcurrentQueue<copyCommand> commands;
    filedestinationclosure dc(&commands);
    auto temp = temp_directory_path();
    string datepart = datestamp(std::chrono::system_clock::now());

    WHEN("Raw image is found") {
        path rawimage = temp / "myphoto.DNG";
        ofstream rf(rawimage.string());
        rf << "Placeholder" << endl;
        rf.close();
        THEN("Destination added in proper output folder with date") {
            dc(rawimage, "Z:\\rawphotos");
            auto actual = commands.frontAndPop();
            string expected = "Z:\\rawphotos\\" + datepart + "\\myphoto.DNG";
        }
        remove(rawimage.c_str());
    }

    WHEN("Ignored file is found") {
        path ignoredfile = temp / "notaphoto.GIF";
        ofstream ignored(ignoredfile);
        ignored << "Dont mind me" << endl;
        ignored.close();
        THEN("Destination is not added to copy commands") {
            dc(ignoredfile, IGNORE_EXTENSION);
            REQUIRE_THROWS( commands.frontAndPop() );
        }
        remove(ignoredfile.c_str());
    }

}