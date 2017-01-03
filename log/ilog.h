#ifndef LOG_ILOG_H
#define LOG_ILOG_H

#include <string>

class ILog {
public:
  virtual void Message(const std::string& message) const = 0;
  virtual void Error(const std::string& message) const = 0;
};

#endif
