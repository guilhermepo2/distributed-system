#ifndef TOKENIZER
#define TOKENIZER

#include <vector>
#include <iostream>

namespace Tokenizer
{
  std::vector<std::string> split(const char * str, char c = ' ');
}

#endif
