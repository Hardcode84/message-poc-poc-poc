#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <set>
#include <vector>
#include <map>
#include <memory>
#include <functional>

#include "messagehandler.h"

class MessageDispatcher
{
public:
    MessageDispatcher();
    virtual ~MessageDispatcher();

private:
    friend class MessageHandler;

    MessageDispatcher(const MessageDispatcher&) = delete;
    MessageDispatcher& operator =(const MessageDispatcher&) = delete;

    void registerHandler(MessageHandler* handler);
    void unregisterHandler(MessageHandler* handler);
    void sendMessagePtr(unsigned id, const void* ptr);
    void subscribe(MessageHandler* handler, unsigned id, MessageHandler::CallBase* c);

    std::set<MessageHandler*> mHandlers;

    struct SubscriberDesc
    {
        std::multimap<MessageHandler*,std::unique_ptr<MessageHandler::CallBase> > subs;
    };

    std::vector<SubscriberDesc> mSubscribers;
};

#endif // MESSAGEDISPATCHER_H
