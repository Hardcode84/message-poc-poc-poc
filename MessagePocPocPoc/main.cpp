#include <iostream>

#include "msg/messagehandler.h"
#include "msg/messagedispatcher.h"

#include "kukarek.h"
#include "pocpocpoc.h"

using namespace std;

class Foo : public MessageHandler
{
public:
    Foo(MessageDispatcher* dispatcher):
        MessageHandler(dispatcher)
    {
        using namespace std::placeholders;
        subscribe<Kukarek>(bind(&Foo::kukarek, this, _1));
    }

    void foo()
    {
        sendMessage(PocPocPoc{5});
    }

    void kukarek(const Kukarek& k)
    {
        cout << "Foo Kukarek " << k.i << endl;
    }
};

class Bar : public MessageHandler
{
public:
    Bar(MessageDispatcher* dispatcher):
        MessageHandler(dispatcher)
    {
        using namespace std::placeholders;
        subscribe<PocPocPoc>(bind(&Bar::pocpocpoc, this, _1));
        subscribe<Kukarek>(bind(&Bar::kukarek, this, _1));
    }

    void bar()
    {
        sendMessage(Kukarek{42});
    }

    void kukarek(const Kukarek& k)
    {
        cout << "Bar Kukarek " << k.i << endl;
    }

    void pocpocpoc(const PocPocPoc& p)
    {
        cout << "Bar PocPocPoc " << p.j << endl;
    }
};

int main()
{
    MessageDispatcher dispatcher;
    Foo f(&dispatcher);
    Bar b(&dispatcher);
    cout << "Hello World!" << endl;
    f.foo();
    b.bar();
    return 0;
}

