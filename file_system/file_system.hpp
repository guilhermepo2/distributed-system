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
  std::vector<FileSystem> children;
  
public:
  FileSystem();
  FileSystem(std::string name);
  FileSystem(std::string name, std::string data);

  void setName(std::string name);
  void setData(std::string data);
  void addChild(FileSystem child);
  void removeChild(FileSystem child);
  std::string get_name();
  std::string get_data();
  FileSystem get_children(int pos);

  void print_state();
};
