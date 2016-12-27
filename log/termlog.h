#ifndef LOGGER_TERMLOGGER_H
#define LOGGER_TERMLOGGER_H

#include <string>
#include "ilog.h"

class TermLog : public ILog {
public:
    virtual void Message(const std::string& message) const override;
    virtual void Error(const std::string& message) const override;
};

#endif
