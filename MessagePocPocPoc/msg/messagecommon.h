#ifndef MESSAGECOMMON_H
#define MESSAGECOMMON_H

unsigned getStrMessageId(const char* str);

template<typename T>
struct message_info;

#define DECLARE_MESSAGE(msg) \
static const int _messageId##msg = getStrMessageId(#msg); \
template<> \
struct message_info<msg> \
{ \
    static unsigned getId() \
    { \
        return _messageId##msg; \
    } \
};

template<typename T>
unsigned getMessageId()
{
    return message_info<T>::getId();
}
#endif // MESSAGECOMMON_H
