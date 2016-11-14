#include "tokenizer.hpp"

namespace Tokenizer
{
  std::vector<std::string> split(const char * str, char c)
  {
    std::vector<std::string> result;
    
    do
      {
	const char * begin = str;
	
	while((*str != c && *str != '\n') && *str)
	  str++;
	
	result.push_back(std::string(begin,str));
	
      }while(0 != *str++);
    
    return result;
  }
}
