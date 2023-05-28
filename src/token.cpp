#include "token.h"

#include <cctype>
#include <string>

using std::string;

token_stream::token_stream(string src) : buffer(src), point(0) {}

char token_stream::get_char() {
  if (*this) {
    auto tmp = point;
    point += 1;
    return buffer[tmp];
  }
  return '\0';
}

void token_stream::put_char() {
  if (point > 0)
    point--;
}

token_stream::operator bool() const { return point < buffer.size(); }

token_stream &operator>>(token_stream &lhs, token &rhs) {

  if (lhs) {
    string work;
    const char SINGLEQUOTE = '\'';
    const char DOUBLEQUOTE = '\"';
    const char SPACES = '\0';
    char token_end = SPACES;

    rhs.type = UNKNOWN;
    rhs.value = "";

    for (auto c = lhs.get_char(); lhs && c != token_end; c = lhs.get_char()) {

      if (rhs.type == UNKNOWN) {
        while (std::isspace(c))
          c = lhs.get_char();
        switch (c) {
        case '.':
          rhs.type = EXTENSION;
          work += c;
          break;
        case SINGLEQUOTE:
          token_end = SINGLEQUOTE;
          rhs.type = STRING;
          break;
        case DOUBLEQUOTE:
          token_end = DOUBLEQUOTE;
          rhs.type = STRING;
          break;
        default:
          rhs.type = STRING;
          work += c;
        }
      } else {
        if (token_end == SPACES) {
          if (std::isspace(c)) {
            break;
          }
        }
        work += c;
      }
    }
    if (work == "->") {
      rhs.type = ARROW;
    }
    rhs.value = work;
  }
  return lhs;
}