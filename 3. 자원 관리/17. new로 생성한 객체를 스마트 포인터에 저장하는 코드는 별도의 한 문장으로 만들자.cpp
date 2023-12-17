#include <iostream>

using namespace std;

/*
 * new로 생성한 객체를 스마트 포인터에 저장하는 코드는 별도의 한 문장으로 만들자
 */

class Widget { };
// 우선순위를 반환하는 함수
int priority() { return 1; }
// 우선순위에 따라 위젯을 처리하는 함수
void processWidget(shared_ptr<Widget> pw, int priority) { return; }

int main(int argc, char* argv[])
{
    /*
     * shared_ptr 의 생성자는 explicit 선언되어 있어서
     * 암시적 변환을 허용하지 않는다.
     * 
     * processWidget(new Widget, priority());
     */
    processWidget(shared_ptr<Widget>(new Widget), priority());
    
    /*
     * 위 문장은 사실 자원 관리 객체를 쓰는데도
     * 자원 누출 가능성이 있다.
     * 
     * 컴파일러는 함수 호출 코드를 만들기 전에,
     * 우선 인자를 평가(Evaluate) 하는 단계를 거친다.
     * 
     * 위는 사실 세 동작으로 나뉜다.
     * 1. priority() 호출
     * 2. new Widget
     * 3. shared_ptr 생성자 호출
     * 
     * 그런데 Java, C# 등과 달리
     * 각각이 실행되는 순서는 컴파일러마다 다르다.
     * (2 이후 3 이라는 순서 제외)
     * 
     * 만약 다음과 같은 순서에서
     * 1. new Widget
     * 2. priority() 호출
     * 3. shared_prt 생성자 호출
     * 
     * 이미 Widget 을 동적 할당했는데,
     * priority() 호출에서 예외가 발생한다면
     * 자원 누출이 발생한다.
     */

    /*
     * 문제의 원인은 중간예 예외가 끼어들어
     * 자원관리 객체 생성 시 
     * 자원을 획득하지 않았기 때문이다.
     *
     * 해결하는 방법은
     * 자원 획득 즉시 초기화라는 RAII 법칙을
     * 컴파일러가 깨지 못 하도록
     * 
     * 객체를 스마트 포인터에 담는 코드를
     * 별도 문장으로 빼면 된다.
     */
    shared_ptr<Widget> pw(new Widget);
    processWidget(pw, priority());

    return 0;
}
