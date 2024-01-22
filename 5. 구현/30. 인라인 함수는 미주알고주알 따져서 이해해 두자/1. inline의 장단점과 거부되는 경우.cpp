#include <iostream>

using namespace std;

/*
 * inline의 장단점과 거부되는 경우
 * 
 * inline 함수는 요청이지 명령이 아니다.
 * 
 * 컴파일러는 최적화는 대체적으로
 * 함수 호출이 없는 코드들이 연속적으로 이어질 때 적용된다.
 * 
 * inline 함수는 본문이 변경되면, 무조건 다시 컴파일해야 한다.
 * 또, 스택 프레임이 존재하지 않기 때문에 콜 스택을 보며 디버깅하기가 어렵다.
 *
 * inline 함수는 오브젝트 코드의 크기를 증가시키므로
 * 코드 크기가 중요할 때는 남발해서는 안 된다.
 * 
 * 그래서 함수 템플릿에 inline 을 쓸 경우 특히 주의해야 한다.
 *
 * 또, 코드 크기 증가로 페이징 횟수가 늘어나고
 * 명령어 캐시 적중률이 떨어져 성능이 저하될 가능성도 있다.
 * 
 * 본문 길이가 매우 짧은 경우에는, 반대로
 * 오브젝트 코드의 크기를 줄이는 효과를 가져올 수도 있다.
 */

class Person
{
    int theAge;

public:
    /* 클래스 내부에 멤버 함수를 바로 정의하면
     * 암시적으로 inline 으로 지정된다.
     *
     * inline 함수는 헤더 파일에 들어가는 게 맞다.
     * 
     * 링크가 아닌, 컴파일 타임에 함수의 본문을 알아야
     * 코드를 끼워넣을 수 있기 때문. */
    int age() const { return theAge; }

    // 런타임에 함수가 정해지는 가상 함수는 inline화 되지 않는다.
    virtual void print() { cout << age << endl; }

    // 컴파일러가 보기에 복잡한 Loop, 재귀 함수가 들어있으면 inline화 하지 않는다.
    int sum(int n)
    {
        if (n == 0)
            return 0;

        return n + sum(n - 1);
    }
};

/* inline 과 별개로, 템플릿 역시 헤더파일에 들어가는 게 맞다.
 * 
 * 템플릿을 인스턴스화하려면,
 * 어떤 구조인지 컴파일러가 알아야 하기 때문. */
template <typename T>
void Func(T&& t)
{
    return;
}

inline int getNum() { return 5; }

int main(int argc, char* argv[])
{
    // inline화 된다.
    int num = getNum();

    /* inline 함수의 주소를 취하거나, 함수 포인터를 통해 호출하는 경우에도
     * inline화 되지 않는다. */
    int (*pf)() = getNum;
    num = pf();

    return 0;
}
