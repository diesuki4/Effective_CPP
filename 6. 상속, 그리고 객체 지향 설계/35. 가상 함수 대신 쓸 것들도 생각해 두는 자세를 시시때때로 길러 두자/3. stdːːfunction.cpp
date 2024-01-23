#include <iostream>
#include <functional>

using namespace std;

/*
 * std::function
 * 
 * 함수 프로토타입이 완전히 일치해야 하는 함수 포인터와 달리,
 * 
 * 반환 값과 매개변수가 호환되는(형 변환이 가능한) 함수를 담을 수 있다.
 */

class Base { };
class Derived : public Base { };

short BaseFunc(Base& a)
{
    return 10;
}

double DerivedFunc(Derived& a)
{
    return 10;
}

int main(int argc, char* argv[])
{
    // 자식으로 뭘 하겠다는 function 에 부모를 다루는 함수는 넣을 수 있지만
    function<int(Derived&)> f1 = BaseFunc;

    /* 부모로 뭘 하겠다는 function 에 자식을 다루는 함수를 넣을 수는 없다.
    function<int(Base&)> f2 = DerivedFunc; */ 

    return 0;
}
