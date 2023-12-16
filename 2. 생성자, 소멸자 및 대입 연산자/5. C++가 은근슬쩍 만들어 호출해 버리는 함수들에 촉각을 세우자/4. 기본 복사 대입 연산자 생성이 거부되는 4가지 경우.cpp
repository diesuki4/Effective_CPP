#include <iostream>

using namespace std;

/*
 * 기본 복사 대입 연산자 생성이 거부되는 4가지 경우
 * 
 * 이때는 직접 복사 대입 연산자를 정의해주어야 한다.
 */

class AAA
{
private:
    /*
     * 1. 복사 대입 연산자가 private 인 멤버를 가진 경우
     *
     * 기본 복사 대입 연산자는
     * 멤버의 복사 대입 연산자도 자동으로 호출하는데,
     *
     * private 이라서 접근할 수 없기 때문
     */
    AAA& operator= (const AAA& rhs) { }
};

class Base
{
private:
    /*
     * 2. 복사 대입 연산자가 private 인 클래스를 상속 받은 경우
     * 
     * 기본 복사 대입 연산자는
     * 부모의 복사 대입 연산자도 자동으로 호출하는데,
     * 
     * private 이라서 접근할 수 없기 때문
     */
    Base& operator= (const Base& rhs) { }
};

class Derived : public Base
{
    string& name;
    AAA aaa;
    const int num;

public:
    // string name 으로 받아도 컴파일 오류는 발생하지 않지만,
    // 생성자 종료 후 해제된 스택 프레임의 참조를 갖게 된다.
    Derived(string& name, const AAA& aaa, const int num) : name(name), aaa(aaa), num(num) { }

    Derived& operator= (const Derived& rhs)
    {
        /*
         * 3. 멤버 변수에 레퍼런스가 존재하는 경우
         *
         * 아래를 보면
         * 되는데? 뭐가 안 된다는 거지? 할 수 있지만
         * 그렇지 않다.
         *
         * 아래는 name 이 참조하는 공간에 rhs.name 의 값을 복사한 것 뿐이지,
         * rhs.name 이 참조하는 공간을 name 도 참조하도록 <대입한 것이 아니다.>
         * 
         * 향후 rhs 로 전달된 객체의 name 을 변경한다고 해도
         * 이 객체의 name 은 변경되어 출력되지 않을 것이다.
         */
        name = rhs.name;

        /*
         * 4. 상수 멤버가 존재하는 경우
         *
         * 상수 멤버에는 값을 대입할 수 없다.
         * 
         * num = rhs.num;
         * 
         */

        /*
         * private 이므로 호출 불가
         *
         * aaa = rhs.aaa;
         *
         */

         /*
         * private 이므로 호출 불가
         *
         * Base::operator=(rhs);
         *
         */

        return *this;
    }

    void Show() { cout << "Name = " << name << ", Num = " << num << endl; }
};

int main(int argc, char* argv[])
{
    string s1("String1"), s2("String2");
    AAA a1, a2;

    Derived obj1(s1, a1, 1), obj2(s2, a2, 2);
    obj1 = obj2;

    obj1.Show();
    obj2.Show();

    return 0;
}
