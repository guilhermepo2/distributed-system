#include <iostream>

int main(int argc, char * argv[])
{
  int port;
  if(argc < 2)
    {
      std::cout << "You must enter the port when executing the code" << std::endl;
      exit(0);
    }
  port = atoi(argv[1]);
  if(port <= 1024)
    {
      std::cout << "You can't use ports under 1024, sorry." << std::endl;
      exit(0);
    }
  
  
  return 0;
}
