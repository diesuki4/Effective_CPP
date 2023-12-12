#include <iostream>

using namespace std;

/*
 * 멤버 함수 체이닝
 */

class Calc
{
    int m_Value = 0;

public:
    void Add(int value) { m_Value += value; }
    void Sub(int value) { m_Value -= value; }
    void Mul(int value) { m_Value *= value; }

    int GetValue() { return m_Value; }
};

class ChainedCalc
{
    int m_Value = 0;

public:
    // 특정 값을 반환해야 하는 상황이 아닐 때,
    // 객체의 레퍼런스를 반환하면
    //
    // 멤버 함수 체이닝을 적용할 수 있다.
    ChainedCalc& Add(int value) { m_Value += value; return *this; }
    ChainedCalc& Sub(int value) { m_Value -= value; return *this; }
    ChainedCalc& Mul(int value) { m_Value *= value; return *this; }

    int GetValue() { return m_Value; }
};

int main(int argc, char* argv[])
{
    Calc calc;

    calc.Add(5);
    calc.Sub(3);
    calc.Mul(4);

    cout << calc.GetValue() << endl;

    ChainedCalc chainedCalc;

    // 연쇄적으로 멤버 함수를 실행시킬 수 있다.
    chainedCalc.Add(5).Sub(3).Mul(4);

    cout << chainedCalc.GetValue() << endl;

    return 0;
}
