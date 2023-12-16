#include <iostream>

using namespace std;

/*
 * 기본 복사 생성자와 기본 복사 대입 연산자의 작동 방식 차이
 */

class AAA
{
public:
    AAA() { cout << "AAA::생성자" << endl; }

    AAA(const AAA& rhs) {  cout << "AAA::복사 생성자" << endl; }

    AAA& operator= (const AAA& rhs) { cout << "AAA::복사 대입 연산자" << endl; return *this; }
};

class BBB
{
    AAA aaa;
    int data;

public:
    /*
     * 기본 생성자
     */
    BBB() { }

    /*
     * 기본 복사 생성자
     * 
     * 객체 멤버에 대해서도 복사 생성자가 호출된다.
     */
    BBB(const BBB& rhs) : aaa(rhs.aaa), data(rhs.data) { }

    /*
     * 기본 복사 대입 연산자
     * 
     * 객체 멤버에 대해서도 복사 대입 연산자가 호출된다.
     */
    BBB& operator= (const BBB& rhs) { aaa = rhs.aaa; data = rhs.data; return *this; }

    /*
     * 기본 소멸자
     */
    ~BBB() { }
};

int main(int argc, char* argv[])
{
    BBB b1;

    BBB b2(b1);

    b1 = b2;

    return 0;
}
