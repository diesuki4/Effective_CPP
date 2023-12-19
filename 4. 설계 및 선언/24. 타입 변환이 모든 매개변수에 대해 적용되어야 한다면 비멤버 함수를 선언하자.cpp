#include <iostream>

using namespace std;

/*
 * 타입 변환이 모든 매개변수에 대해 적용되어야 한다면 비멤버 함수를 선언하자
 */

class MyInt
{
    int num;

public:
    /*
     * 생성자를 explicit 선언하면
     * 암시적 형 변환이 불가하므로,
     * 
     * result = mi1 * 10 같이 사용할 수 없다.
     */
    MyInt(int num = 0) : num(num) { }

    int getNum() const { return num; }

    const MyInt operator* (const MyInt& rhs) const
    {
        return MyInt(num * rhs.num);
    }
};

/*
 * 10 + mi
 * mi + 10
 * 
 * 처럼 형 변환이 두 피연산자 모두에 적용되어야 한다면
 * 
 * 비멤버 함수로 선언하는 것이 좋다.
 * 
 * 이때 이 함수는 클래스의 public 멤버 함수만으로도 구현이 가능하므로
 * 쓸데없이 friend 선언을 해, 캡슐화를 저해할 필요가 없다.
 */
const MyInt operator + (const MyInt& lhs, const MyInt& rhs)
{
    return MyInt(lhs.getNum() * rhs.getNum());
}

int main(int argc, char* argv[])
{
    MyInt mi1(2), mi2(4);

    MyInt result = mi1 * mi2;

    // result = mi1 * MyInt(10)
    // result = mi1.operator*(MyInt(10))
    result = mi1 * 10;

    // 불가
    // result = 10 * mi1;

    // 가능
    result = 10 + mi1;

    return 0;
}
