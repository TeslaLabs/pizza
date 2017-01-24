#include "args.h"
#include <string>

Args::Args(int argc, char** argv)
  : argc_ { argc },
    args_ { argv }
{}

bool Args::Has(const std::string& arg_name) {
  for (auto i = 0; i < argc_; ++i) {
    if (arg_name == args_[i]) return true;
  }
  return false;
}

bool Args::Get(const std::string& arg_name,
               int index,
               std::string* out_value) {
  for (auto i = 0; i < argc_; ++i) {
    if (arg_name == args_[i]) {
      if (i + index < argc_) {
        *out_value = std::string { args_[i + index] };
        return true;
      }
    }
  }
  return false;
}
