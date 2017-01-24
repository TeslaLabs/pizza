#include "args.h"
#include <string>

Args::Args(int argc, char** argv)
  : argc_ { argc },
    args_ { argv }
{}

bool Args::Has(const std::string& arg_name, int* out_index) {
  for (auto i = 0; i < argc_; ++i) {
    if (arg_name == args_[i]) {
      if (out_index) *out_index = i;
      return true;
    }
  }
  return false;
}

char* Args::operator[](int index) {
  return index > argc_ ? nullptr : args_[index];
}
