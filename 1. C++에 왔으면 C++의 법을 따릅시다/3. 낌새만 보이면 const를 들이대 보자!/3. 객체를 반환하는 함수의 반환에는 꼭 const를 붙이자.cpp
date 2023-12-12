#include <iostream>

using namespace std;

/*
 * 함수, 특히 객체를 반환하는 함수의 반환에는
 * 꼭 const 를 붙이자
 */

class Rational
{
    int data;

public:
    Rational(int data = 0) : data(data) { }

    Rational GetCopy()
    {
        return Rational(data);
    }

    // 반환된 임시 객체에 대입이 허용된다.
    friend Rational operator* (const Rational& lhs, const Rational& rhs)
    {
        return Rational(lhs.data * rhs.data);
    }

    // 반환된 임시 객체에 대입이 불가능해진다.
    friend const Rational operator+ (const Rational& lhs, const Rational& rhs)
    {
        return Rational(lhs.data + rhs.data);
    }

    operator bool () { return (data != 0); }
};

int main(int argc, char* argv[])
{
    Rational a(3), b(4), c;

    /*
     * operator* 반환 값에 const 선언을 하지 않으면
     * 다음과 같은 일이 벌어진다.
     */
    (a * b) = c;

    // GetCopy() 가 반환한 임시 객체에
    // c 가 대입되었다.
    a.GetCopy() = c;

    /*
     * c 가 대입된 (a * b) 의 임시 객체가
     * bool 타입으로 형 변환 되었다.
     */
    if (a * b = c) { ; }

    /*
     * const 객체를 반환해 방지할 수 있다.
     * 
     * (a + b) = c;
     * 
     * if (a + b = c) { ; }
     * 
     */

    return 0;
}
