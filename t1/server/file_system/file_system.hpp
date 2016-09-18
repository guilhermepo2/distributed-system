#ifndef FILESYSTEM
#define FILESYSTEM

#include "node.hpp"
#include "../common/tokenizer.hpp"
#include <vector>

class FileSystem
{
private:
  Node * root = NULL;
  FileSystem() {}
  static FileSystem * s_instance;
  
public:
  static FileSystem *instance();
  Node * getRoot();
  Node * insert(std::string url, std::string content);
  Node * remove(std::string url);
  Node * edit(std::string url, std::string content);
  Node * search(std::string url);
  Node * searchParent(std::string url);

  void printFS();
};

#endif
