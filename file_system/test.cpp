#include "file_system.hpp"

int main()
{
  FileSystem fs("sample name", "sample data");
  fs.print_state();
  return 0;
}
