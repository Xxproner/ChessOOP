#include "pieces.h"

bool except::operator ==(const char* ex) const {
    size_t num; num = strlen(this->what()) < strlen(ex) ? strlen(ex) : strlen(this->what());
    if (strncmp(this->what(), ex, num) == 0)
        return true;
    else
        return false;
}