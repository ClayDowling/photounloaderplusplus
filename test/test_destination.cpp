#include <catch2/catch_test_macros.hpp>

#include "destination.h"
#include <filesystem>


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
        REQUIRE(imagedest.string().rfind("Z:\\Raw Photo", 0) == 0);
      }

      THEN("Photo files with different extension case are put in photo path") {
        auto imagedest = get_destination(imagefilecaps);
        REQUIRE(imagedest.string().rfind("Z:\\Raw Photo", 0) == 0);
      }

      THEN("Video files are put in video path") {
        auto videodest = get_destination(videofile);
        REQUIRE(videodest.string().rfind("Z:\\Raw Video", 0) == 0);
      }
      THEN("Video files with different extension case are put in video path") {
        auto videodest = get_destination(videofilecaps);
        REQUIRE(videodest.string().rfind("Z:\\Raw Video", 0) == 0);
      }
    }

    WHEN("File extension is not in list") {
      path imagefile("E:\\DCIM\\myphoto.bmp");

      THEN("NOPATH value is returned") {
        auto imagedst = get_destination(imagefile);
        REQUIRE(imagedst == NOPATH);
      }
    }
  }
}