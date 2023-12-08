#include "Lox.h"

#include "Scanner.h"
#include "Token.h"
#include "TokenType.h"

#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

namespace LoxInterpreter {

std::string
Lox::readAllBytes(std::string const &path)
{
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error("Unable to open file: " + path);
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

void
Lox::runFile(std::string const &path)
{
  std::string bytes = Lox::readAllBytes(path);
  run(bytes);
}

void
Lox::runPrompt()
{
  for (;;) {
    std::string line;
    std::cout << ">: ";
    if (!std::getline(std::cin, line)) {
      // check of EOF
      if (std::cin.eof()) {
        break;
      } else {
        // some other error
        std::cerr << "\nError reading input." << std::endl;
        break;
      }
    }

    Lox::run(line);
  }
}

void
Lox::run(std::string const &source)
{
  std::unique_ptr<Scanner> scanner = std::make_unique<Scanner>(source);
  std::vector<Token> tokens = scanner->scanTokens();

  for (auto const &token : tokens) {
    std::cout << token << std::endl;
  }
}

void
Lox::error(int line, std::string const &message)
{
  Lox::report(line, "", message);
}

void
Lox::report(int line, std::string const &where, std::string const &message)
{
  std::cerr << "[line " << line << "] Error" << where << ": " << message;
}

}  // namespace LoxInterpreter
