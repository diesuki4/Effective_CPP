#include <iostream>

using namespace std;

/*
 * 소멸자 후 메모리가 해제될 때 비정적 멤버의 소멸자가 호출된다
 */

class AAA
{
    int num;

public:
    AAA(int num) : num(num) { cout << "AAA" << num << endl; }
    ~AAA()                  { cout << "~AAA" << num << endl; }
};

class BBB
{
    // 소멸자가 호출된다.
    AAA a;
    // delete 하지 않으면, 소멸자가 호출되지 않는다.
    AAA *pa;

public:
    /*
     * 생성자에서는 본문에서 멤버를 써야하기 때문에
     * 본문이 실행되기 전에
     *
     * 모든 멤버의 초기화가 이뤄져야 한다.
     * (객체의 경우 생성자가 호출)
     */
    BBB() : a(1), pa(new AAA(2)) { cout << "BBB" << endl; }

    ~BBB() { cout << "~BBB" << endl; }
    /*
     * 소멸자에서도 본문에서 멤버를 써야하기 때문에
     * 역순으로 본문이 실행된 후
     *
     * 모든 멤버의 소멸이 이뤄져야 한다.
     * (객체의 경우 소멸자가 호출)
     *
     * 스택에서 스택 프레임이 해제될 때 소멸자가 호출되고,
     * 힙에서 delete 연산이 수행될 때 소멸자가 호출되는 것처럼
     *
     * 실제 메모리에서 해제될 때
     * 비정적 멤버에 대해 소멸자가 호출된다.
     */

     /* 
     * 동적 할당된 메모리는 포인터에 저장되기 때문에
     * 포인터 타입에는 소멸자가 없다.
     *
     * 따라서, delete 하지 않으면
     * 실제 객체의 소멸자도 호출되지 않고 누수된다.
     * 
     * 가리키던 포인터가 사라질 뿐.
     */
};

int main(int argc, char* argv[])
{
    BBB bbb;

    return 0;
}
