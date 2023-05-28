#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using std::string;

enum token_type { ARROW, END_OF_INPUT, EXTENSION, IGNORE, STRING, UNKNOWN };

class token {
public:
  token_type type;
  string value;
};

class token_stream {

public:
  token_stream(string src);

  char get_char();
  void put_char();
  operator bool() const;

private:
  unsigned point;
  string buffer;
};

token_stream &operator>>(token_stream &lhs, token &rhs);

#endif