#ifndef ARGS_ARGS_H
#define ARGS_ARGS_H

#include <string>

class Args {
  int argc_;
  char** args_;

public:
  Args(int argc, char** argv);
  bool Has(const std::string& arg_name, int* index);
  char* operator[](int index);
};

#endif
