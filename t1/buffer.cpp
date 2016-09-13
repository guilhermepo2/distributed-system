#include <iostream>
#include <vector>

std::vector<std::string> split(const char * str, char c = ' ')
{
  std::vector<std::string> result;

  do
    {
      const char * begin = str;

      while(*str != c && *str)
	str++;

      result.push_back(std::string(begin,str));
      
    }while(0 != *str++);

  return result;
}

int main()
{
  std::string post_example = "POST /obladi/oblada HTTP/1.1\nHost: 127.0.0.1\nContent-length: 10\n\n123456789\n\n";
  
  std::vector<std::string> vetorzinho = split(post_example.c_str());

  std::cout << vetorzinho[0] << std::endl;
  
  return 0;
}
