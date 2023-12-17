#include <iostream>

using namespace std;

/*
 * 객체 슬라이싱(복사손실, Object slicing) 문제와 가상 함수 테이블 포인터
 */

class Base
{
    int baseNum;

public:
    Base(int baseNum) : baseNum(baseNum) { cout << "Base::생성자 " << baseNum << endl; }

    /*
     * 복사 생성자와 복사 대입 연산자는
     * 가상 함수 테이블 포인터(vptr) 를 복사하지 않는다.
     *
     * 같은 타입의 객체끼리는 동일한 vftbl 을 가리키므로
     * 복사할 필요가 없다.
     * 
     * 가상 함수 테이블에는 가상 함수 뿐만 아니라,
     * 일반 함수도 올라가 있다.
     * 
     * 따라서, 부모-자식 상속 관계에서는
     * vptr 을 복사하면 안 된다.
     *
     * 자식의 함수들로 초기화 혹은 생성되지도 않았을
     * 자식 부분의 조작을 허용하는 건 말이 안 되기 때문.
     */

    Base(const Base& rhs) : baseNum(rhs.baseNum)
    {
        cout << "Base::복사 생성자" << endl;
    }

    Base& operator= (const Base& rhs)
    {
        cout << "Base::복사 대입 연산자" << endl;

        baseNum = rhs.baseNum;
        return *this;
    }

    virtual void Show() const { cout << "baseNum = " << baseNum << endl; }

    virtual ~Base() { cout << "Base::소멸자 " << baseNum << endl; }
};

class Derived : public Base
{
    int derivedNum;

public:
    Derived(int baseNum, int derivedNum) : Base(baseNum), derivedNum(derivedNum) { cout << "Derived::생성자 " << derivedNum << endl; }

    Derived(const Derived& rhs) : Base(rhs), derivedNum(rhs.derivedNum)
    {
        cout << "Derived::복사 생성자" << endl;
    }

    Derived& operator= (const Derived& rhs)
    {
        cout << "Derived::복사 대입 연산자" << endl;

        Base::operator=(rhs);

        derivedNum = rhs.derivedNum;
        return *this;
    }

    virtual void Show() const override { cout << "derivedNum = " << derivedNum << endl; }

    ~Derived() { cout << "Derived::소멸자 " << derivedNum << endl; }
};

/*
 * 자식 객체를 값 타입의 부모로 받게 되면
 * 부모의 복사 생성자가 호출된다.
 * 
 * 이때, 자식 부분이 복사되지 않는
 * 객체 슬라이싱(복사손실, Object slicing) 문제가 발생한다.
 * 
 * 또한, 새로운 객체가 복사 생성됨으로 인해
 * 그 객체는 부모의 vptr 을 갖게 된다.
 */
void BaseFunc(Base base)
{
    base.Show();
}

/*
 * 자식 객체를 부모의 포인터로 받아도
 * 복사와는 관련이 없으므로
 * 
 * 자식의 기존 vptr, 멤버를 유지한다.
 */
void BaseFuncPtr(Base* pBase)
{
    pBase->Show();
}

/*
 * 자식 객체를 부모의 레퍼런스로 받아도
 * 복사와는 관련이 없으므로
 *
 * 자식의 기존 vptr, 멤버를 유지한다.
 */
void BaseFuncRef(Base& rBase)
{
    rBase.Show();
}

int main(int argc, char* argv[])
{
    Derived d(1, 2);

    BaseFunc(d);
    BaseFuncPtr(&d);
    BaseFuncRef(d);

    return 0;
}
