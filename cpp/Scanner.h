#pragma once

#include "Token.h"
#include "TokenType.h"

#include <string>
#include <unordered_map>
#include <vector>

namespace LoxInterpreter {

class Scanner {
 public:
  explicit Scanner(std::string const &source) : source(source)
  {
    this->start = this->current = 0;
    this->line = 1;

    this->keywords = {
        {"and", TokenType::AND},
        {"class", TokenType::CLASS},
        {"else", TokenType::ELSE},
        {"false", TokenType::FALSE},
        {"for", TokenType::FOR},
        {"fun", TokenType::FUN},
        {"if", TokenType::IF},
        {"nil", TokenType::NIL},
        {"or", TokenType::OR},
        {"print", TokenType::PRINT},
        {"return", TokenType::RETURN},
        {"super", TokenType::SUPER},
        {"this", TokenType::THIS},
        {"true", TokenType::TRUE},
        {"var", TokenType::VAR},
        {"while", TokenType::WHILE}};
  }

  std::vector<Token> scanTokens();

 private:
  // States.
  std::unordered_map<std::string, TokenType> keywords;
  std::string source;
  std::vector<Token> tokens;
  int start;
  int current;
  int line;

  // Methods.
  bool isAtEnd();
  bool isAlpha(char c);
  bool isDigit(char c);
  bool isAlphaNumeric(char c);

  void scanToken();
  char peek();
  char peekNext();
  char advance();
  bool match(char expected);
  void addToken(TokenType type, LiteralType const &literal);
  void string();
  void number();
  void identifier();
};

}  // namespace LoxInterpreter
