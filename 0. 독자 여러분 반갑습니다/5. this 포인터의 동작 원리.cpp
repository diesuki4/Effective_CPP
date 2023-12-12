#include <iostream>

using namespace std;

/*
 * this 포인터의 동작 원리
 */

class Simple
{
    int m_ID;
    int copy_ID;

    /*
     * this 포인터는 클래스나 객체의 멤버가 아니다.
     *
     * 멤버 함수 호출 시 첫 번째 인자로
     * 암시적으로 전달되는 주소 값이다.
     */

public:
    // 컴파일러에 의해 다음과 같이 변환된다.

    // 스택 혹은 힙에 객체의 메모리가 할당된 직후 생성자가 호출되므로,
    // 생성자에서도 객체의 주소를 받을 수 있다.
    // Simple(Simple* const this, int id) : m_ID(id), copy_ID(this->m_ID) { }
    Simple(int id) : m_ID(id), copy_ID(m_ID) { }

    // void SetID(Simple* const this, int id) { this->m_ID = id; }
    // this-> 내부 값은 변경할 수 있지만,
    // this = nullptr; 은 불가
    void SetID(int id) { m_ID = id; }

    // int GetID(Simple* const this) { return this->m_ID; }
    int GetID() { return m_ID; }

    // 멤버 변수와 동일한 이름의 인자는 변환되지 않는다.
    // void ShowTwo(Simple* const this, int id) { cout << id << endl; }
    void ShowTwo(int id) { cout << id << endl; }

    // static 클래스 함수 내에서는
    // 객체의 멤버 변수, this 포인터 같은
    //
    // non-static 값을 사용할 수 없다.
    // 
    // static void ShowID() { cout << m_ID << endl; }
    // static void ShowID() { cout << this->m_ID << endl; }
};

int main(int argc, char* argv[])
{
    // 컴파일러에 의해 자동으로 변환된다.

    // Simple simple(객체의 주소, 1);
    Simple simple(1);

    // simple.SetID(&simple, 2);
    simple.SetID(2);

    // int id = simple.GetID(&simple);
    int id = simple.GetID();

    return 0;
}
