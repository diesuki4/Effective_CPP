#include <iostream>
#include "Date.h"
#include "Address.h"
#include "Person.h"

using namespace std;

/*
 * Pimpl 관용구
 */

int main(int argc, char* argv[])
{
    string s;
    Date d;
    Address a;

    // 이제 전방 선언을 통해 포인터를 사용하지 않아도 된다.
    Person p(s, d, a);

    return 0;
}
