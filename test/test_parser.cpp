#include <catch2/catch_test_macros.hpp>
#include <iostream>

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
  WHEN("Extension is ignored") {
    THEN("path returned is IGNORE") {
      Parser p;
      auto actual = p.Parse(".jpg IGNORE");
      REQUIRE(actual[".jpg"] == "IGNORE");
    }
  }
}

SCENARIO("Invalid config file") {
  WHEN("Directory does not have preceeding extension") {
    THEN("Parser throws exception") {
      Parser p;

      REQUIRE_THROWS_AS(p.Parse("Z:\\Videos"), parse_exception);
    }
  }
  WHEN("Input ends after extension") {
    THEN("Parse throws exception") {
      Parser p;
      REQUIRE_THROWS_AS(p.Parse(".jpg"), parse_exception);
    }
  }
  WHEN("Extension follows another extension") {
    THEN("Parse throws an exception") {
      Parser p;
      REQUIRE_THROWS_AS(p.Parse(".jpg .mp4 Z:\\Photos"), parse_exception);
    }
  }
}