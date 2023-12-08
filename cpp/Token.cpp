#include "Token.h"

#include <iostream>
#include <string>
#include <type_traits>
#include <variant>

namespace LoxInterpreter {

std::string
Token::LiteralToString() const
{
  return std::visit(
      [](auto &&arg) -> std::string {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, std::monostate>) {
          return "";
        } else if constexpr (std::is_same_v<T, double>) {
          return std::to_string(arg);
        } else if constexpr (std::is_same_v<T, std::string>) {
          return arg;
        } else {
          return "unknown";
        }
      },
      this->literal);
}

// Implement the operator<<
std::ostream &
operator<<(std::ostream &os, Token const &token)
{
  return os << TokenTypeToString(token.type) << " " << token.lexeme << " " << token.LiteralToString();
}

}  // namespace LoxInterpreter
