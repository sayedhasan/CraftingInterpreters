#include "Lox.h"
#include "Scanner.h"
#include "Token.h"
#include "TokenType.h"

#include <cstdlib>
#include <iostream>
#include <stdexcept>

using namespace LoxInterpreter;

int
main(int argc, char *argv[])
{
  if (argc > 2) {
    std::cout << "Usage: jlox [script]" << std::endl;
    exit(1);
  } else if (argc == 2) {
    Lox::runFile(argv[1]);
  } else if (argc == 1) {
    Lox::runPrompt();
  }

  return 0;
}
