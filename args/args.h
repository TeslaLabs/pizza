#ifndef ARGS_ARGS_H
#define ARGS_ARGS_H

#include <string>

class Args {
  int argc_;
  char** args_;

public:
  Args(int argc, char** argv);
  bool Has(const std::string& arg_name) const;
  bool Get(const std::string& arg_name, int index, std::string* value) const;
};

#endif
