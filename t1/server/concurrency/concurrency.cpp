#include "concurrency.hpp"

std::vector<operation> operationVector;

bool check(operation to_perform)
{
  bool on_file_already = false;
  for(int i = 0; i < operationVector.size(); i++)
    {
      if(operationVector[i].path_to_file == to_perform.path_to_file)
	on_file_already = true;
    }

  if(((on_file_already && (to_perform.verb == "GET" || to_perform.verb == "HEAD"))
      || (!on_file_already)))
    {
      operationVector.push_back(to_perform);
      return true;
    }
  else
    {
      return false;
    }
}

void performed(operation performed)
{
  for(int i = 0; i < operationVector.size(); i++)
    {
      if(performed.verb == operationVector[i].verb &&
	 performed.path_to_file == operationVector[i].path_to_file)
	{
	  if(i > 0)
	    operationVector.erase(operationVector.begin()+(i-1));
	  else
	    operationVector.erase(operationVector.begin());
	}
    }
}
