#include <iostream>

using namespace std;

/*
 * 기본 복사 생성자 생성이 거부되는 2가지 경우
 * 
 * 이때는 직접 복사 생성자를 정의해주어야 한다.
 */

class AAA
{
private:
    /*
     * 1. 복사 생성자가 private 인 멤버를 가진 경우
     *
     * 기본 복사 생성자는
     * 멤버의 복사 생성자도 자동으로 호출하는데,
     *
     * private 이라서 접근할 수 없기 때문
     */
    AAA(const AAA& rhs) { }

public:
    AAA() { }
};

class Base
{
private:
    /*
     * 2. 복사 생성자가 private 인 클래스를 상속 받은 경우
     * 
     * 기본 복사 생성자는
     * 부모의 복사 생성자도 자동으로 호출하는데,
     * 
     * private 이라서 접근할 수 없기 때문
     */
    Base(const Base& rhs) { }

public:
    Base() { }
};

class Derived : public Base
{
    string& name;
    AAA aaa;
    const int num;

public:
    Derived(string& name, const AAA& aaa, const int num) : name(name), num(num)
    {
        this->aaa = aaa;
    }

    Derived(const Derived& rhs) : name(rhs.name), num(rhs.num)
    /* 
     * private 이므로 호출 불가
     * 
     * , Base(rhs), aaa(rhs.aaa)
     */
    { }

    void Show() { cout << "Name = " << name << ", Num = " << num << endl; }
};

int main(int argc, char* argv[])
{
    string s("String");
    AAA a;

    Derived obj1(s, a, 1), obj2(obj1);

    obj1.Show();
    obj2.Show();

    return 0;
}
