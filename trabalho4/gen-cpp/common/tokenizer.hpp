#ifndef TOKENIZER
#define TOKENIZER

#include <vector>
#include <iostream>

namespace Tokenizer
{
  std::vector<std::string> split(const char * str, char c = ' ');
}

#endif

#ifndef DEV
#define DEV

#define DEBUG 0

#endif
