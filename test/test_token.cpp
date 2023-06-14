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
    ts >> t;
    AND_THEN("type is STRING") { REQUIRE(t.type == STRING); }
    AND_THEN("value is Z:\\\"large\" files") {
      REQUIRE(t.value == "Z:\\\"large\" files");
    }
    ts >> t;
    AND_THEN("type is IGNORE") { REQUIRE(t.type == IGNORE); }
    AND_THEN("value is IGNORE") { REQUIRE(t.value == "IGNORE"); }
    ts >> t;
    AND_THEN("type is END_OF_INPUT") { REQUIRE(t.type == END_OF_INPUT); }
    AND_THEN("value is empty string") { REQUIRE(t.value == ""); }
  }
}

SCENARIO("Input buffer does not end with a newline") {
  token_stream ts(".jpg");
  WHEN("Token is read") {
    token t;
    ts >> t;
    THEN("Type should be EXTENSION") { REQUIRE(t.type == EXTENSION); }
    AND_THEN("Full value of token is read") { REQUIRE(t.value == ".jpg"); }
  }
}

SCENARIO("Multi-token input ends with IGNORE") {
  WHEN("IGNORE is not followed by whitepspace") {
    token_stream ts(".jpg IGNORE");
    THEN("Final token is IGNORE") {
      token t;
      ts >> t;
      REQUIRE(t.type == EXTENSION);
      ts >> t;
      REQUIRE(t.type == IGNORE);
      REQUIRE(t.value == "IGNORE");
    }
  }
}