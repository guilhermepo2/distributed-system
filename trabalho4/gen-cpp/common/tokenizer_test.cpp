#include "tokenizer.hpp"
#include <vector>
#include <string>

int main()
{
  std::string my_request = "GET /obladi/oblada HTTP/1.1";
  std::vector<std::string> tokens = Tokenizer::split(my_request.c_str(), ' ');

  std::cout << "Tokens" << std::endl;
  for(int i = 0; i < tokens.size(); i++)
    {
      std::cout << "Token " << i << ": " << tokens[i] << std::endl;
    }

  std::cout << "Splitting Token[1] in /" << std::endl;
  std::vector<std::string> url = Tokenizer::split(tokens[1].c_str(), '/');

  for(int i = 0; i < url.size(); i++)
    {
      std::cout << "Token " << i << ": " << url[i] << std::endl;
    }

  
  return 0;
}
