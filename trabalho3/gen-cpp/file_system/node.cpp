#include "node.hpp"

Node::Node()
{
  time(&this->creation);
  time(&this->modification);
  this->version = 0;
}

Node::Node(std::string name)
{
  this->name = name;
  time(&this->creation);
  time(&this->modification);
  this->version = 0;
}

Node::Node(std::string name, std::string data)
{
  this->name = name;
  this->data = data;
  time(&this->creation);
  time(&this->modification);
  this->version = 0;
}

void Node::modify()
{
  time(&this->modification);
  this->version++;
}

void Node::set_name(std::string name)
{
  this->name = name;
}

void Node::set_data(std::string data)
{
  this->data = data;
}

void Node::add_child(Node * child)
{
  this->children.push_back(child);
}

void Node::remove_child(Node * child)
{
  for(int i = 0; i < this->children.size(); i++)
    {
      if(this->children[i]->get_name() == child->get_name())
	{
	  this->children.erase(this->children.begin() + i);
	}
    }
}

int Node::get_version()
{
  return this->version;
}

std::string Node::get_name()
{
  return this->name;
}

std::string Node::get_data()
{
  return this->data;
}

Node * Node::get_child(int pos)
{
  return this->children[pos];
}

Node * Node::get_child_by_name(std::string name)
{
  for(int i = 0; i < this->children.size(); i++)
    {
      if(this->children[i]->name == name)
	{
	  return this->children[i];
	}
    }
  return NULL;
}

void Node::print_state(bool print_children)
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
	  this->children[i]->print_state(print_children);
	}
    }

}

time_t Node::get_creation()
{
  return this->creation;
}

time_t Node::get_modification()
{
  return this->modification;
}

int Node::get_size()
{
  return this->children.size();
}

std::vector<Node*> Node::get_children()
{
  for(int i = 0; i < children.size(); i++)
  {
    std::cout << "Filho " << i << ": " << this->children[i]->get_name() << std::endl;
  }

  return this->children;
}

int Node::get_child_count()
{
  return this->children.size();
}
