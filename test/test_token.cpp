#include <catch2/catch_test_macros.hpp>

#include "token.h"

SCENARIO("Valid input buffer") {
  token_stream ts(".mov -> Z:\\Video\n \"Z:\\Camera Photos\"\n\'Z:\\\"large\" "
                  "files'  IGNORE ");

  WHEN("Tokens are read") {
    token t;
    ts >> t;
    THEN("type is EXTENSION") { REQUIRE(t.type == EXTENSION); }
    AND_THEN("value is .mov") { REQUIRE(t.value == ".mov"); }
    ts >> t;
    AND_THEN("type is ARROW") { REQUIRE(t.type == ARROW); }
    AND_THEN("value is ->") { REQUIRE(t.value == "->"); }
    ts >> t;
    AND_THEN("type is STRING") { REQUIRE(t.type == STRING); }
    AND_THEN("value is Z:\\Video") { REQUIRE(t.value == "Z:\\Video"); }
    ts >> t;
    AND_THEN("type is STRING") { REQUIRE(t.type == STRING); }
    AND_THEN("value is Z:\\Camera Photos") {
      REQUIRE(t.value == "Z:\\Camera Photos");
    }
  }
}