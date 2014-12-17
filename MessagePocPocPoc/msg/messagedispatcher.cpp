#include "messagedispatcher.h"

#include "messagehandler.h"

#include <cassert>

MessageDispatcher::MessageDispatcher()
{

}

MessageDispatcher::~MessageDispatcher()
{
    assert(mHandlers.empty());
}

void MessageDispatcher::registerHandler(MessageHandler* handler)
{
    auto res = mHandlers.insert(handler);
    assert(res.second);
}

void MessageDispatcher::unregisterHandler(MessageHandler* handler)
{
    assert(nullptr != handler);
    for(auto id : handler->mSubscribed)
    {
        mSubscribers[id].subs.erase(handler);
    }
    auto res = mHandlers.erase(handler);
    assert(0 != res);
}

void MessageDispatcher::sendMessagePtr(unsigned id, const void *ptr)
{
    if(id >= mSubscribers.size()) return;
    for(const auto& h : mSubscribers[id].subs)
    {
        h.second->call(ptr);
    }
}

void MessageDispatcher::subscribe(MessageHandler *handler,
                                  unsigned id,
                                  MessageHandler::CallBase* c)
{
    std::unique_ptr<MessageHandler::CallBase> ptr(c);
    assert(nullptr != handler);
    assert(mHandlers.find(handler) != mHandlers.end());
    if(mSubscribers.size() <= id)
    {
        mSubscribers.resize(id + 1);
    }
    mSubscribers[id].subs.insert(std::make_pair(handler, std::move(ptr)));
}

