#ifndef NODE
#define NODE

#include <iostream>
#include <vector>
#include <time.h>

class Node
{
private:
  //metadata
  time_t creation;
  time_t modification;
  int version;
  //data
  std::string name;
  std::string data;
  std::vector<Node*> children;
  
public:

  Node();
  Node(std::string name);
  Node(std::string name, std::string data);

  void set_name(std::string name);
  void set_data(std::string data);
  void add_child(Node * child);
  std::string get_name();
  std::string get_data();
  int get_version();
  int get_size();
  time_t get_creation();
  time_t get_modification();
  Node * get_child(int pos);
  Node * get_child_by_name(std::string name);

  void print_state(bool print_children = false);
};

#endif
