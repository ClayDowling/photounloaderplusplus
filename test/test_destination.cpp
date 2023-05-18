#include <catch2/catch_test_macros.hpp>

#include <filesystem>
#include "destination.h"

using namespace std::filesystem;

SCENARIO("File destination mapping") {
    GIVEN("File extensions are initialized") {
        add_destination(".dng", "Z:\\Raw Photo");
        add_destination(".mov", "Z:\\Raw Video");

        WHEN("File extension is in list") {

            path imagefile("E:\\DCIM\\myphoto.dng");
            path imagefilecaps("F:\\DCIM\\myphoto.DNG");
            path videofile("E:\\DCIM\\myvideo.mov");
            path videofilecaps("E:\\DCIM\\myvideo.MoV");

            THEN("Photo files are put in photo path") {
                auto imagedest = get_destination(imagefile);
                REQUIRE( imagedest.string().rfind("Z:\\Raw Photo", 0) == 0);
            }

        }

    }
}