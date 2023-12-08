#include "Scanner.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "Lox.h"

namespace LoxInterpreter {

std::vector<Token>
Scanner::scanTokens()
{
  while (!this->isAtEnd()) {
    // We are at the beginning of the next lexeme.
    start = current;
    scanToken();
  }

  this->tokens.emplace_back(TokenType::EOF_, "", std::monostate{}, line);
  return this->tokens;
}

void
Scanner::scanToken()
{
  char const c = this->advance();
  switch (c) {
    case '(':
      addToken(TokenType::LEFT_PAREN, std::monostate{});
      break;
    case ')':
      addToken(TokenType::RIGHT_PAREN, std::monostate{});
      break;
    case '{':
      addToken(TokenType::LEFT_BRACE, std::monostate{});
      break;
    case '}':
      addToken(TokenType::RIGHT_BRACE, std::monostate{});
      break;
    case ',':
      addToken(TokenType::COMMA, std::monostate{});
      break;
    case '.':
      addToken(TokenType::DOT, std::monostate{});
      break;
    case '-':
      addToken(TokenType::MINUS, std::monostate{});
      break;
    case '+':
      addToken(TokenType::PLUS, std::monostate{});
      break;
    case ';':
      addToken(TokenType::SEMICOLON, std::monostate{});
      break;
    case '*':
      addToken(TokenType::STAR, std::monostate{});
      break;
    case '!':
      addToken(match('=') ? TokenType::BANG_EQUAL : TokenType::BANG, std::monostate{});
      break;
    case '=':
      addToken(match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL, std::monostate{});
      break;
    case '<':
      addToken(match('=') ? TokenType::LESS_EQUAL : TokenType::LESS, std::monostate{});
      break;
    case '>':
      addToken(match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER, std::monostate{});
      break;
    case '/':
      if (match('/')) {
        // A comment goes until the end of the line.
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(TokenType::SLASH, std::monostate{});
      }
      break;
    case ' ':
      break;
    case '\r':
      break;
    case '\t':
      break;
    case '\n':
      line++;
      break;
    case '"':
      string();
      break;

    default:
      if (isDigit(c)) {
        number();
      } else if (isAlpha(c)) {
        identifier();
      } else {
        Lox::error(line, "Unexpected character.");
      }
      break;
  }
}

bool
Scanner::isAtEnd()
{
  return this->current >= static_cast<int>(this->source.length());
}

bool
Scanner::isAlpha(char const c)
{
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

bool
Scanner::isDigit(char const c)
{
  return c >= '0' && c <= '9';
}

bool
Scanner::isAlphaNumeric(char const c)
{
  return this->isAlpha(c) || this->isDigit(c);
}

char
Scanner::peek()
{
  if (this->isAtEnd()) return '\0';
  return this->source[current];
}

char
Scanner::peekNext()
{
  if ((this->current + 1) >= static_cast<int>(this->source.length())) return '\0';
  return this->source[current + 1];
}

char
Scanner::advance()
{
  return this->source[current++];
}

bool
Scanner::match(char const expected)
{
  if (this->isAtEnd()) return false;
  if (this->source[current] != expected) return false;
  current++;
  return true;
}

void
Scanner::addToken(TokenType type, LiteralType const &literal)
{
  std::string text = this->source.substr(this->start, this->current - this->start);
  this->tokens.emplace_back(type, text, literal, line);
}

void
Scanner::string()
{
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line++;
    advance();
  }

  if (isAtEnd()) {
    Lox::error(line, "Unterminated string.");
    return;
  }

  // The closing '"'.
  advance();

  // Trim the surrounding quotes.
  std::string value = this->source.substr(this->start + 1, this->current - this->start - 2);
  this->addToken(TokenType::STRING, value);
}

void
Scanner::number()
{
  while (this->isDigit(this->peek())) this->advance();

  // Look for a fractional part.
  if (peek() == '.' && this->isDigit(this->peekNext())) {
    // Consume the "."
    advance();

    while (this->isDigit(this->peek())) advance();
  }

  std::string value = this->source.substr(this->start, this->current - this->start);
  this->addToken(TokenType::NUMBER, std::stod(value));
}

void
Scanner::identifier()
{
  while (this->isAlphaNumeric(peek())) advance();

  TokenType type;
  std::string text = this->source.substr(this->start, this->current - this->start);
  auto it = this->keywords.find(text);
  if (it != this->keywords.end()) {
    type = it->second;
  } else {
    type = TokenType::IDENTIFIER;
  }
  this->addToken(type, std::monostate{});
}

}  // namespace LoxInterpreter
