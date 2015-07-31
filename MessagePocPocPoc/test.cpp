#include "test.h"

#include <iostream>

int test()
{
    MessageDispatcher dispatcher;
    Foo f(&dispatcher);
    Bar b(&dispatcher);
    cout << "test" << endl;
    f.foo();
    b.bar();
    return 0;
}

