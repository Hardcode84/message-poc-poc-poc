#include "messagecommon.h"

#include <cassert>
#include <unordered_map>

namespace
{
unsigned IdCounter = 0;

unsigned generateMessageId()
{
    return IdCounter++;
}

}

unsigned getStrMessageId(const char* str)
{
    assert(nullptr != str);
    static std::unordered_map<std::string, unsigned> idMap;
    auto it = idMap.find(str);
    if(it != idMap.end())
    {
        return it->second;
    }
    const auto id = generateMessageId();
    auto res = idMap.insert(std::make_pair(str,id));
    assert(res.second);
    return id;
}
