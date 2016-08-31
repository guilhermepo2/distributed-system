#include "file_system.hpp"

int main()
{
  FileSystem my_fs("FileSystem Root", "Just the Root");
  my_fs.add_child(FileSystem("FileSystem Child", "First Child"));
  my_fs.add_child(FileSystem("FileSystem Child 2", "Second Child"));

  FileSystem auxiliary_fs = my_fs.get_child(0);
  auxiliary_fs.add_child(FileSystem("FileSystem Child Child", "Who Cares"));
  
  my_fs.print_state(true);
  return 0;
}
