#include "messagehandler.h"

#include <cassert>

#include "messagedispatcher.h"

MessageHandler::MessageHandler(MessageDispatcher *dispatcher):
    mDispatcher(dispatcher)
{
    assert(nullptr != mDispatcher);
    mDispatcher->registerHandler(this);
}

MessageHandler::MessageHandler(MessageHandler* parent):
    mDispatcher(parent->mDispatcher)
{
    assert(nullptr != mDispatcher);
    mDispatcher->registerHandler(this);
}

MessageHandler::~MessageHandler()
{
    mDispatcher->unregisterHandler(this);
}

void MessageHandler::sendMessagePtr(unsigned id, const void *ptr)
{
    mDispatcher->sendMessagePtr(id, ptr);
}

void MessageHandler::subscribePtr(unsigned id, CallBase* c)
{
    mSubscribed.insert(id);
    mDispatcher->subscribe(this, id, c);
}

