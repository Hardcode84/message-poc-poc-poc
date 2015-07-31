#include <iostream>

#include "test.h"

int test();

int main()
{
    MessageDispatcher dispatcher;
    Foo f(&dispatcher);
    Bar b(&dispatcher);
    cout << "Hello World!" << endl;
    f.foo();
    b.bar();
    test();
    return 0;
}

