#include "messagecommon.h"

namespace
{
unsigned IdCounter = 0;
}

unsigned generateMessageId()
{
    return IdCounter++;
}
