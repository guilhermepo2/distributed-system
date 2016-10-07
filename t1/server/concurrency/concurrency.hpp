#ifndef CONCURRENCY_HEADER
#define CONCURRENCY_HEADER

#include <iostream>
#include <vector>

struct operation
{
  std::string verb;
  std::string path_to_file;
};
typedef struct operation operation;

bool check(operation to_perform);
void performed(operation performed);

#endif
