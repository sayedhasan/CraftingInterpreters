#pragma once

#include <string>

namespace LoxInterpreter {

class Lox {
 public:
  static std::string readAllBytes(std::string const &path);
  static void runFile(std::string const &path);
  static void runPrompt(void);
  static void run(std::string const &source);
  static void error(int line, std::string const &message);
  static void report(int line, std::string const &where, std::string const &message);
};

}  // namespace LoxInterpreter
