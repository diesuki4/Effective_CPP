#include <iostream>

using namespace std;

/*
 * 함수에서 객체를 반환할 때 레퍼런스를 반환하려고 들지 마라
 */
 
class MyInt
{
     int n;

public:
    MyInt(int n = 0) : n(n) { cout << "MyInt::생성자 " << n << endl; }

    /*
     * 곱셈의 결과를 레퍼런스로 반환하면 더 효율적이지 않을까?
     * 그 전에 그게 가능할까?
     * 
     * 함수에서 새로운 객체를 만드는 방법은 2가지 뿐이다.
     * 1. 스택에 지역 객체로 생성한다.
     * 2. 힙에 동적 할당한다.
     */

    /* 우선 1번처럼 스택에 할당하고 그 레퍼런스를 반환하면,
     * 
     * const MyInt& operator* (const MyInt& rhs)
     * {
     *     MyInt mi(n * rhs.n);
     *     return mi;
     * }
     * 
     * 함수가 종료되자마자 레퍼런스는
     * 해제된 스택 프레임을 참조하게 된다.
     */ 

    /* 2번처럼 힙에 동적 할당하고 역참조를 레퍼런스로 반환하면,
     * 
     * const MyInt& operator* (const MyInt& rhs)
     * {
     *     return *new MyInt(n * rhs.n);
     * }
     * 
     * 매 호출마다 사용자가 delete 를 고려해야 한다.
     * 
     * w = x * y * z 같은 상황에서는 delete 를 호출할 수도 없다.
     */

    /*
     * 다른 발상으로 정적 객체를 활용하면?
     * 
     * const MyInt& operator* (const MyInt& rhs)
     * {
     *    static MyInt mi;
     *
     *    mi.n = n * rhs.n;
     *
     *    return mi;
     * }
     * 
     * (a * b) == (c * d) 는 항상 참을 반환하게 될 것이다.
     */

    /*
     * 따라서, 팩토리 함수에서 다형성을 유지해야 하는 등 특수한 경우가 아니라면
     * (자식 객체를 값 타입의 부모로 반환하면, 다형성이 사라지므로)
     * 
     * 새로운 객체의 반환은
     * 레퍼런스 반환이나 동적 할당을 고민하지 말고,
     * 그냥 값 타입으로 반환하자.
     * 
     * 특히, 아래와 같이 객체를 바로 생성해 반환하는 경우
     * 복사 생성되는 객체에 대해 RVO 가 일어난다.
     */
    const MyInt operator* (const MyInt& rhs) { return MyInt(n * rhs.n); }
    
    bool operator== (const MyInt& rhs) { return (n == rhs.n); }

    ~MyInt() { cout << "MyInt::소멸자 " << n << endl; }
};

int main(int argc, char* argv[])
{
    MyInt mi1(2), mi2(4);

    MyInt mi3 = mi1 * mi2;

    return 0;
}
