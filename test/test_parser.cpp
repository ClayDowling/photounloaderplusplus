#include <catch2/catch_test_macros.hpp>

#include "configparser.h"

SCENARIO("Valid config file") {
  WHEN("File ends with whitespace") {
    string content(".mp4 -> Z:\\Videos\n");
    THEN("Parser returns all mappings") {
      Parser p;

      auto actual = p.Parse(content);

      REQUIRE(actual.size() == 1);

      string dest = actual[".mp4"];
      REQUIRE(dest == "Z:\\Videos");
    }
  }
  WHEN("File does not end with whitespace") {
    string content(".jpg -> Z:\\Videos\n.dng -> Z:\\Photos");
    THEN("Parser returns all mappings") {
      Parser p;
      auto actual = p.Parse(content);
      REQUIRE(actual.size() == 2);

      string jpeg = actual[".jpg"];
      string raw = actual[".dng"];

      REQUIRE(jpeg == "Z:\\Videos");
      REQUIRE(raw == "Z:\\Photos");
    }
  }
}