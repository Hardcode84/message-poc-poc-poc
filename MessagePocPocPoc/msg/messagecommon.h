#ifndef MESSAGECOMMON_H
#define MESSAGECOMMON_H

unsigned generateMessageId();

#define DECLARE_MESSAGE(msg) \
unsigned getMessageId(const msg&);

#define REGISTER_MESSAGE(msg) \
unsigned getMessageId(const msg&) \
{ \
    static unsigned id = generateMessageId(); \
    return id; \
}

#endif // MESSAGECOMMON_H
