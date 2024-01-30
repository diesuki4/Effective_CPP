#include <iostream>

using namespace std;

/*
 * 예외적으로 비가상 함수를 재정의하는 경우
 * 
 * CRTP (기묘한 재귀 템플릿 패턴, Curiously Recurring Template Pattern)
 */

/* 템플릿 메소드 패턴 (Template Method Pattern)
 * 
 * CRTP 를 왜 쓰는지 알기 위해, 우선 템플릿 메소드 패턴을 살펴본다.
 * 
 * 부모에 가상 함수 호출들로 구성된 비가상 인터페이스 뼈대를 만들고,
 * 각 가상 함수의 세부 구현은 자식들에서 오버라이드하는 설계 방식.
 * 
 * 이름과 달리 C++ 템플릿과는 하등 관련이 없다.
 *
 * NVI (Non-Virtual Interface) 관용구라고도 한다. */
class Person
{
public:
    // 부모의 Non-virtual 공개 인터페이스에서는
    void doDay()
    {
        // 로직만 구성하고 (가상 함수 호출로 인한 동적 바인딩 비용 발생)
        morning();
        afternoon();
        evening();
        night();
    }

// virtual 비공개 세부 구현은 자식들이 오버라이드 하도록 한다.
private:
    virtual void morning()   = 0;
    virtual void afternoon() = 0;
    virtual void evening()   = 0;
    virtual void night()     = 0;
};

class Student : public Person
{
private:
    void morning()   override { cout << "학교 가기 싫다."     << endl; }
    void afternoon() override { cout << "공부하기 싫다."      << endl; }
    void evening()   override { cout << "학원 가기 싫다."     << endl; }
    void night()     override { cout << "내일 학교 가기 싫다." << endl << endl; }
};

class Worker : public Person
{
private:
    void morning()   override { cout << "회사 가기 싫다."     << endl; }
    void afternoon() override { cout << "일하기 싫다."        << endl; }
    void evening()   override { cout << "야근하기 싫다."      << endl; }
    void night()     override { cout << "내일 회사 가기 싫다." << endl << endl; }
};

// ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ

/* CRTP
 *
 * 부모를 상속받을 때 템플릿을 이용해 부모에 자신의 타입을 전달해,
 * 정적 바인딩을 통해 런타임 비용을 줄이는 기법
 *
 * 템플릿 메소드 패턴에서 동적 바인딩 비용을 줄이고 싶을 때 사용할 수 있다.
 * 
 * 정적 바인딩을 해야 하기 때문에 가상 함수 오버라이드가 아닌,
 * 비가상 함수 재정의를 활용한다.
 *
 * 함수 오버로딩, 템플릿 등 컴파일 타임에 결정되는
 * 정적 다형성(Static Polymorphism) 의 응용이다. */
template <typename DERIVED>
class PersonT
{
private:
    // 자식 클래스 객체로 변환하는 함수
    DERIVED& derived()             { return static_cast<DERIVED&>(*this);       }
    const DERIVED& derived() const { return static_cast<const DERIVED&>(*this); }

public:
    void doDay()
    {
        // 이제 모든 함수는 비가상 함수이기 때문에, 빌드 시에 정적 바인딩 된다.
        derived().morning();
        derived().afternoon();
        derived().evening();
        derived().night();
    }

public:
    // 자식에서 재정의해야 할 것들을 명시할 뿐, 아무 동작도 하지 않는다.
    // 비가상 함수는 = 0 처럼 순수 함수로 선언 불가.
    void morning()   {}
    void afternoon() {}
    void evening()   {}
    void night()     {}
};

// 상속받을 때, 부모에 자신의 타입을 전달한다.
class StudentT : public PersonT<StudentT>
{
// 부모에 명시된 비가상 함수들을 재정의
public:
    void morning()   { cout << "학교 가기 싫다."     << endl; }
    void afternoon() { cout << "공부하기 싫다."      << endl; }
    void evening()   { cout << "학원 가기 싫다."     << endl; }
    void night()     { cout << "내일 학교 가기 싫다." << endl << endl; }
};

class WorkerT : public PersonT<WorkerT>
{
// 부모 클래스에서 derived().morning(); 과 같이 호출되므로 public 이어야 한다.
public:
    void morning()   { cout << "회사 가기 싫다."     << endl; }
    void afternoon() { cout << "일하기 싫다."        << endl; }
    void evening()   { cout << "야근하기 싫다."      << endl; }
    void night()     { cout << "내일 회사 가기 싫다." << endl << endl; }
};

int main(int argc, char* argv[])
{
    Student().doDay();
    Worker().doDay();

    /* 결과는 같지만, CRTP 에서는 비가상 함수 재정의를 통해 정적 바인딩을 진행하고,
     * 세부 구현이 외부에 노출된다는 점이 다르다. */
    StudentT().doDay();
    WorkerT().doDay();

    return 0;
}
