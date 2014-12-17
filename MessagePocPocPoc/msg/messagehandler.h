#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include <set>
#include <functional>
#include <memory>

class MessageDispatcher;

class MessageHandler
{
public:
    explicit MessageHandler(MessageDispatcher* dispatcher);
    explicit MessageHandler(MessageHandler* parent);
    virtual ~MessageHandler();

protected:
    template<typename T>
    void sendMessage(const T& msg)
    {
        const auto id = getMessageId(msg);
        sendMessagePtr(id, static_cast<const void*>(&msg));
    }
    template<typename MSG, typename F>
    void subscribe(const F& handler)
    {
        const auto id = getMessageId(*static_cast<const MSG*>(nullptr));
        std::unique_ptr<CallBase> c(new Call<MSG>(handler));
        subscribePtr(id, c.release());
    }

private:
    friend class MessageDispatcher;
    class CallBase
    {
    public:
        virtual ~CallBase() {}
        virtual void call(const void*)=0;
    };
    template<typename MSG>
    struct Call : public CallBase
    {
        const std::function<void(const MSG&)> fun;
    public:
        template<typename F>
        Call(const F& f):fun(f) {}
        virtual void call(const void* ptr)
        {
            fun(*static_cast<const MSG*>(ptr));
        }
    };

    MessageHandler(const MessageHandler&) = delete;
    MessageHandler& operator =(const MessageHandler&) = delete;
    MessageDispatcher* mDispatcher;
    std::set<unsigned> mSubscribed;

    void sendMessagePtr(unsigned id, const void* ptr);
    void subscribePtr(unsigned id, CallBase* c);
};

#endif // MESSAGEHANDLER_H
