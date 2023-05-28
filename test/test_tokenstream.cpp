#include <catch2/catch_test_macros.hpp>

#include "token.h"

SCENARIO("Token stream has input") {
  token_stream ts("AB ");
  WHEN("Input read") {
    THEN("First character is A") {
      auto c = ts.get_char();
      REQUIRE(c == 'A');
      c = ts.get_char();
      REQUIRE(c == 'B');
      c = ts.get_char();
      REQUIRE(c == ' ');
      REQUIRE(ts == false);
      c = ts.get_char();
      REQUIRE(c == '\0');
    }
  }
  WHEN("Input is read and put back") {
    auto c = ts.get_char();
    REQUIRE(c == 'A');
    ts.put_char();
    THEN("It is read again") {
      auto d = ts.get_char();
      REQUIRE(d == 'A');
    }
  }
  WHEN("More is put back than was taken out") {
    auto c = ts.get_char();
    REQUIRE(c == 'A');
    ts.put_char();
    ts.put_char();
    THEN("Input starts at the beginning of the stream") {
      auto d = ts.get_char();
      REQUIRE(d == 'A');
    }
  }
}