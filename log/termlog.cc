#include "termlog.h"
#include <color.h>

void TermLog::Message(const std::string& message) const {
    std::printf(PURPLE("%s") "\n", message.c_str());
}

void TermLog::Error(const std::string& message) const {
    std::printf(ERROR("%s") "\n", message.c_str());
}
