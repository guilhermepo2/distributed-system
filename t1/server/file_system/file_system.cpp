#include "file_system.hpp"
#include "../common/tokenizer.hpp"

FileSystem * FileSystem::s_instance = NULL;

Node * FileSystem::getRoot()
{
  return this->root;
}

Node * FileSystem::insert(std::string url, std::string content)
{
#if DEBUG
  std::cout << "(insert function)" << std::endl;
#endif
  
  // get the parent of the url
  Node * parent = this->searchParent(url);
  
#if DEBUG
  std::cout << "(insert function) url: " << url << std::endl;
  std::cout << "(insert function) parent: " << parent << std::endl;
#endif
  
  // getting the node name
  std::vector<std::string> urlTokens = Tokenizer::split(url.c_str(), '/');
  if(urlTokens[urlTokens.size() - 1] == "") urlTokens.pop_back();
  std::string name = urlTokens[urlTokens.size() - 1];
  
#if DEBUG
  std::cout << "(insert function) name: " << name << std::endl;
#endif
  
  if(name.size() > 100)
    {
      name.erase(name.begin()+100, name.end());
    }
  
  // if doesnt give a name for the children somehow
  if(name == "")
    {
      return NULL;
    }
  
  if(parent == NULL)
    {
      #if DEBUG
      std::cout << "(insert function) parent is null" << std::endl;
      #endif
      
      if(this->root == NULL)
	{
#if DEBUG
	  std::cout << "(insert function) root is also null" << std::endl;
	  std::cout << "(insert function) root: " << this->root << std::endl;
#endif
	  this->root = new Node(name, content);

#if DEBUG
	  std::cout << "(insert function) root should not be null anymore" << std::endl;
	  std::cout << "(insert function) root: " << this->root << std::endl;
#endif
	  return this->root;
	}
      else
	{
	  // root is not null and im trying to insert there again
	  return NULL;
	}
    }
  
  Node * child = new Node(name, content);
  
  #if DEBUG
  std::cout << "parent: " << parent << std::endl;
  #endif

  // EVERYTHING OK, but... DOESN IT ALREADY EXIST?
  for(int i = 0; i < parent->get_child_count(); i++)
    {
      if(parent->get_child(i)->get_name() == child->get_name())
	{
	  // name already inserted, wont insert
	  return NULL;
	}
    }
  
  parent->add_child(child);

#if DEBUG
  std::cout << "returning" << std::endl;
#endif
  
  return child;
}
  
  Node * FileSystem::remove(std::string url)
  {
    Node * removed = this->search(url);

    if(removed == NULL)
      return NULL;
    
    if(removed->get_child_count() > 0)
      return NULL;

    Node * parent = this->searchParent(url);

    // root node
    if(parent == NULL)
      {
	this->root = NULL;
	delete removed;
	return removed;
      }

    // not root node
    parent->remove_child(removed);
    delete removed;
    return removed;
  }

Node * FileSystem::edit(std::string url, std::string content)
{
  Node * edit = this->search(url);

  if(edit == NULL)
    return NULL;

  edit->set_data(content);
  edit->modify();

  return edit;
}

Node * FileSystem::search(std::string url)
{
  #if DEBUG
  std::cout << "Root: " << this->root << std::endl;
  #endif
  
  if(this->root == NULL)
    return NULL;

  std::vector<std::string> urlTokens = Tokenizer::split(url.c_str(), '/');

  // treating / 
  if(urlTokens.size() == 2 && urlTokens[0] == "" && urlTokens[1] == "")
    return this->root;

  int i = 0;
  if(urlTokens[0] == "") i++;

  Node * search_node = this->root;
  
  if(search_node->get_name() != urlTokens[i])
    return NULL;
  i++;
  
  if(urlTokens[i] == "") i++;

  for(; (search_node != NULL && i < urlTokens.size()); i++)
    {
      if(urlTokens[i] != "")
	search_node = search_node->get_child_by_name(urlTokens[i]);
    }

  return search_node;
}

Node * FileSystem::searchParent(std::string url)
{
  #if DEBUG
  std::cout << "(search parent function)" << std::endl;
  std::cout << "root: " << this->root << std::endl;
  #endif
  
  if(this->root == NULL)
    return NULL;

#if DEBUG
  std::cout << "(search parent function) root not null null" << std::endl;
#endif

  std::vector<std::string> urlTokens = Tokenizer::split(url.c_str(), '/');
  
#if DEBUG
  std::cout << "Tokens:" << std::endl;
  for(int i = 0; i < urlTokens.size(); i++)
    {
      std::cout << "token " << i << ": " << urlTokens[i] << std::endl;
    }
#endif

  // removing the last from the url (because we want his parent)
  if(urlTokens[urlTokens.size() - 1] == "") urlTokens.pop_back();
  urlTokens.pop_back();

#if DEBUG
  std::cout << "Tokens without child:" << std::endl;
  for(int i = 0; i < urlTokens.size(); i++)
    {
      std::cout << "token " << i << ": " << urlTokens[i] << std::endl;
    }
#endif

  // treating / 
  if(urlTokens.size() == 0)
    return NULL;

  // treating trying to insert root again

  #if DEBUG
  std::cout << "(search parent function) performing search" << std::endl;
  #endif

  int i = 0;
  if(urlTokens[0] == "") i++;

  Node * search_node = this->root;


  #if DEBUG
  std::cout << "(search parent function) search node name: " << search_node->get_name() << std::endl;
  std::cout << "(search parent function) urlTokens[i]: " << urlTokens[i] << std::endl;
  #endif

  if(urlTokens.size() == 1)
    {
      // trying to insert root again
      return NULL;
    }

#if DEBUG
  std::cout << "(search parent function) url token " << i << ": " << urlTokens[i] << std::endl;
  std::cout << "(search parent function) url token size: " << urlTokens.size() << std::endl;
#endif
  
  i++;
  
  for(; (search_node != NULL && i < urlTokens.size()); i++)
    {
      search_node = search_node->get_child_by_name(urlTokens[i]);
    }

  return search_node;
    }

void FileSystem::printFS()
{
  this->root->print_state(true);
}

FileSystem *FileSystem::instance()
{
  if (!s_instance)
    s_instance = new FileSystem;

  return s_instance;
}
