#include "file_system.hpp"
#include "../common/tokenizer.hpp"


Node * FileSystem::getRoot()
{
  return this->root;
}

Node * FileSystem::insert(std::string url)
{
  this->root = new Node("obladi", "conteudoooooo");
  
  return this->root;
}

Node * FileSystem::remove(std::string url)
{
  
  return NULL;
}

Node * FileSystem::edit(std::string url, std::string content)
{
  
  return NULL;
}

Node * FileSystem::search(std::string url)
{
  if(this->root == NULL)
    return NULL;

  if(url[0] == '/')
    return this->root;

  std::vector<std::string> urlTokens = Tokenizer::split(url.c_str(), '/');

  int i = 0;
  if(urlTokens[0] == "") i++;

  Node * search_node = this->root;
  if(search_node->get_name() != urlTokens[i])
    return NULL;
  i++;

  for(; (search_node != NULL && i < urlTokens.size()); i++)
    {
      search_node = search_node->get_child_by_name(urlTokens[i]);
    }

  return search_node;
}
