#include <iostream>
#include "file_system.hpp"

int main()
{
  
  std::cout << "======================================="  << std::endl;
  //FileSystem * fs = new FileSystem();
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Inserting /" << std::endl;
  FileSystem::instance()->insert("/", "my content");
  // nao insere isso acima
  std::cout << "======================================="  << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Inserting /obladi" << std::endl;
  FileSystem::instance()->insert("/obladi", "obladi");
  std::cout << "======================================="  << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Inserting /obladi" << std::endl;
  FileSystem::instance()->insert("/obladi", "obladi2");
  std::cout << "======================================="  << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Inserting /obladi/obladum" << std::endl;
  FileSystem::instance()->insert("/obladi/obladum", "obladum");
  std::cout << "======================================="  << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Inserting /obladi/oblada" << std::endl;
  FileSystem::instance()->insert("/obladi/oblada", "oblada");
  std::cout << "======================================="  << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Inserting /obladi/oblada/obladola" << std::endl;
  FileSystem::instance()->insert("/obladi/oblada/obladola", "obladola");
  std::cout << "======================================="  << std::endl;
  
  std::cout << "======================================="  << std::endl;
  std::cout << "Searching obladola" << std::endl;
  Node * x = FileSystem::instance()->search("/obladi/oblada/obladola");
  x-> print_state();
  std::cout << "======================================="  << std::endl;

  std::cout << "======================================="  << std::endl;
  std::cout << "Searching oblada" << std::endl;
  x = FileSystem::instance()->search("/obladi/oblada");
  x-> print_state();
  std::cout << "======================================="  << std::endl;

  std::cout << "======================================="  << std::endl;
  std::cout << "Editing oblada" << std::endl;
  FileSystem::instance()->edit("/obladi/oblada", "edited content");
  std::cout << "======================================="  << std::endl;

  std::cout << "======================================="  << std::endl;
  std::cout << "Editing obladoka" << std::endl;
  FileSystem::instance()->edit("/obladi/obladoka", "edited content again");
  std::cout << "======================================="  << std::endl;

  std::cout << "======================================="  << std::endl;
  std::cout << "Searching root 10 times" << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "Root: " << FileSystem::instance()->getRoot() << std::endl;
  std::cout << "======================================="  << std::endl;

  

  
  
  std::cout << std::endl;

  std::cout << "PRINTANDO\n" << std::endl;
  FileSystem::instance()->printFS();

  return 0;
}
