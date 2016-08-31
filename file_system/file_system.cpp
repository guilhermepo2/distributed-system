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

void FileSystem::set_name(std::string name)
{
  this->name = name;
}

void FileSystem::set_data(std::string data)
{
  this->data = data;
}

void FileSystem::add_child(FileSystem child)
{
  this->children.push_back(child);
}

std::string FileSystem::get_name()
{
  return this->name;
}

std::string FileSystem::get_data()
{
  return this->data;
}

FileSystem FileSystem::get_child(int pos)
{
  return this->children[pos];
}

void FileSystem::print_state(bool print_children)
{
  std::cout << "Printing" << std::endl;
  std::cout << "Name: " << this->name << std::endl;
  std::cout << "Data: " << this->data << std::endl;
  std::cout << "Childrens: " << this->children.size() << std::endl;
  std::cout << "Created: " << this->creation << std::endl;
  std::cout << "Last Modified: " << this->modification << std::endl;
  std::cout << "Version: " << this->version << std::endl;
  std::cout << std::endl;

  if(print_children)
    {
      for(int i = 0; i < this->children.size(); i++)
	{
	  this->children[i].print_state(print_children);
	}
    }
  
}
