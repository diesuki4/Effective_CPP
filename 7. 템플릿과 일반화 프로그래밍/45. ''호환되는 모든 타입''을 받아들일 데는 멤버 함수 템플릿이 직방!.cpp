#include <iostream>
#include <type_traits>

using namespace std;

/*
 * "호환되는 모든 타입"을 받아들일 데는 멤버 함수 템플릿이 직방!
 */

class Base {};
class Derived : public Base {};

/* 클래스 템플릿이기 때문에 (C++98 에서 직접 만들어 썼던) 스마트 포인터는,
 * 상속 관계에 상관 없이 기본적으로 형 변환이 불가능했다. */
template <typename T>
class SmartPtr
{
    T* p;

public:
    SmartPtr(T* pMem = nullptr) : p(pMem) {}
};

/* C++11 스마트 포인터에서는 상속 관계가 있으면 알아서 형 변환이 되던데..?
 * 이건 템플릿이 상속 관계를 파악해 처리해주기 때문이 아니다. */
template <typename T>
class AutoPtr
{
    T* p;

public:
    AutoPtr(T* pMem = nullptr) : p(pMem) {}

    /* 호환되는 모든 타입을 받아들이기 위해
     * 멤버 함수 템플릿으로 생성자를 계속 찍어내고 있기 때문에 가능.
     *
     * 이렇게 템플릿을 통해 다른 타입의 객체로부터 생성하도록 하는 복사 생성자를
     * 일반화 복사 생성자(Generalized Copy Constructor) 라고 한다. */
    template <class U>
    AutoPtr(const AutoPtr<U>& _Other) : p(_Other.get()) {}

    T* get() const { return p }
};

template <typename T>
class SharedPtr
{
    T* p;

public:
    SharedPtr(T* pMem = nullptr) : p(pMem) {}

    /* 실제로는 타입 특질을 이용해 좀 더 모던하게 구현되어 있다.
     *
     * 일반화 복사 생성자가 있어도 기본 복사 생성자는 추가된다.
     * 컴파일러는 일반화 복사 생성자만 보고는 복사 생성자가 있다고 판단하지 않는다는 것. */
    template <class U, enable_if_t<_SP_convertible<U, T>::value, bool> = true>
    SharedPtr(const SharedPtr<U>& _Other) {}
};

int main(int argc, char* argv[])
{
    SmartPtr<Derived> smd;
    // SmartPtr<Base> smb(smd);

    AutoPtr<Derived> apd;
    AutoPtr<Base> apb(apd);

    SharedPtr<Derived> spd;
    SharedPtr<Base> spb(spd);

    return 0;
}
