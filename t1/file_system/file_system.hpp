#include <iostream>
#include <vector>
#include <time.h>

class FileSystem
{
private:
  //metadata
  time_t creation;
  time_t modification;
  int version;
  //data
  std::string name;
  std::string data;
  std::vector<FileSystem*> children;
  
public:
  FileSystem();
  FileSystem(std::string name);
  FileSystem(std::string name, std::string data);

  void set_name(std::string name);
  void set_data(std::string data);
  void add_child(FileSystem * child);
  std::string get_name();
  std::string get_data();
  FileSystem * get_child(int pos);
  FileSystem * get_child_by_name(std::string name);

  void print_state(bool print_children = false);
};
