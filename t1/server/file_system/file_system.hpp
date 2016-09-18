#ifndef FILESYSTEM
#define FILESYSTEM

#include "node.hpp"
#include "../common/tokenizer.hpp"
#include <vector>

class FileSystem
{
private:
  Node * root = NULL;
  
public:
  FileSystem() {}
  Node * getRoot();
  Node * insert(std::string url);
  Node * remove(std::string url);
  Node * edit(std::string url, std::string content);
  Node * search(std::string url);
};

#endif
