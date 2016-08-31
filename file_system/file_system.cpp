#include "file_system.hpp"

FileSystem::FileSystem()
{
  time(&this->creation);
  time(&this->modification);
  this->version = 0;
}

FileSystem::FileSystem(std::string name)
{
  this->name = name;
  time(&this->creation);
  time(&this->modification);
  this->version = 0;
}

FileSystem::FileSystem(std::string name, std::string data)
{
  this->name = name;
  this->data = data;
  time(&this->creation);
  time(&this->modification);
  this->version = 0;
}

void FileSystem::print_state()
{
  std::cout << "Printing" << std::endl;
  std::cout << "Name: " << this->name << std::endl;
  std::cout << "Data: " << this->data << std::endl;
  std::cout << "Childrens: " << this->children.size() << std::endl;
  std::cout << "Created: " << this->creation << std::endl;
  std::cout << "Last Modified: " << this->modification << std::endl;
  std::cout << "Version: " << this->version << std::endl;
}
