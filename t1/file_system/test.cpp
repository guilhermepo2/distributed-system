#include "file_system.hpp"

int main()
{
  FileSystem my_fs("FileSystem Root", "Just the Root");
  my_fs.add_child(new FileSystem("FileSystem Child", "First Child"));
  my_fs.add_child(new FileSystem("FileSystem Child 2", "Second Child"));

  my_fs.get_child(0)->add_child(new FileSystem("FileSystem Child Child", "yup"));

  my_fs.print_state(true);
  return 0;
}
