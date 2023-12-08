#pragma once

#include "Token.h"
#include "TokenType.h"

#include <iostream>
#include <string>
#include <variant>

namespace LoxInterpreter {

using LiteralType = std::variant<std::monostate, double, std::string>;

class Token {
 public:
  Token(TokenType type, std::string const &lexeme, LiteralType const &literal, int line)
      : type(type), lexeme(lexeme), literal(literal), line(line)
  {
  }

  friend std::ostream &operator<<(std::ostream &os, Token const &token);

 private:
  TokenType type;
  std::string lexeme;
  LiteralType literal;
  int line;

  std::string LiteralToString() const;
};

}  // namespace LoxInterpreter
