#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

/*
 * 클래스 설계는 타입 설계와 똑같이 취급하자
 */

/*
 * 새로운 클래스를 정의하는 것은
 * 새로운 타입을 정의하는 것과 같다.
 * 
 * 함수와 연산자의 오버로드,
 * 메모리 할당 및 해제,
 * 초기화 및 종료 작업
 * 을 모두 정의해야 한다.
 * 
 * 또한 문법이 자연스럽고,
 * 직관적이며,
 * 효율적인 구현이 1가지 이상 있어야 한다.
 */

class OtherClass;

// 0 ~ 100 사이 값을 갖는 정수
class MyInt
{
    int* pNum;

    static const int MIN = 0;
    static const int MAX = 100;

public:
    // 1. 객체 생성 및 소멸은 어떻게 이뤄져야 하는가?
    MyInt(int num) : pNum(new int) { SetNum(num); }

    void* operator new   (size_t size)  { return new char[size]; }
    void* operator new[] (size_t size)  { return new char[size]; }
    void  operator delete   (void* adr) { delete[] adr; }
    void  operator delete[] (void* adr) { delete[] adr; }

    ~MyInt() { delete pNum; }

    // 2. 값 타입으로 전달(Call by Value, 복사 생성자) 되는 경우 어떤 의미를 줄 것인가?
    MyInt(const MyInt& rhs) : pNum(new int(*rhs.pNum)) { }

    // 3. 초기화와 대입은 어떻게 달라야 하는가?
    MyInt& operator= (const MyInt& rhs)
    {
        int* pOrig = pNum;

        pNum = new int(*rhs.pNum);

        delete pOrig;

        return *this;
    }
    
    /*
     * 4. 적법한 값에 대한 제약은 무엇으로 잡을 것인가?
     * 
     * 생성자, 대입 연산자, 각종 Setter 함수는 불변속성에 많이 좌우된다.
     */
    void SetNum(int num)
    {
        *pNum = min(max(MIN, num), MAX);
    }

    /*
     * 5. 상속 계통망에 맞출 것인가?
     * 
     * 상속을 고려했다면 가상 함수, 가상 소멸자에
     * 대한 고려도 필요하다.
     */
    virtual void DoSomething() { return; }

    /*
     * 6. 어떤 종류의 타입 변환을 허용할 것인가?
     */

    // string -> MyInt 암시적 변환 비허용
    explicit MyInt(string& s) : pNum(new int) { SetNum(stoi(s)); }

    // MyInt -> string 암시적 변환 허용
    operator string() { return to_string(*pNum); }

    /*
     * 7. 어떤 연산자와 함수를 두어야 의미가 있을까?
     */
    const MyInt operator+ (const MyInt& rhs) { return MyInt(*pNum + *rhs.pNum); }

    /*
     * 8. 표준 함수 중 어떤 것을 허용하지 말 것인가?
     * 
     * 복사를 금지하기 위한 복사 함수의 private 선언 등
     */

    /*
     * 9. 멤버에 대한 접근 권한을 어느 쪽에 줄 것인가?
     */
private:
    bool bInternalData = true;

    friend OtherClass;

    /*
     * 10. 선언되지 않은 인터페이스로 무엇을 둘 것인가?
     * 
     * 보장할 것들이 어떤 것들인지에 대한 질문
     * 
     * 수행 성능, 예외 안전성, 자원 관리 등이 이에 속한다.
     */

    /*
     * 11. 얼마나 일반적인가?
     * 
     * 때에 따라서는 클래스 템플릿으로 정의해야 할 수도 있다.
     */

    /*
     * 12. 정말로 꼭 필요한가?
     * 
     * 기존 클래스에 대해 기능 몇 개가 아쉬워서
     * 자식 클래스를 새로 만들 바에는
     * 
     * 차라리 비멤버 함수나 템플릿을 몇 개 더 정의하는 게 낫다.
     */
};

class OtherClass { };

int main(int argc, char* argv[])
{

    return 0;
}
