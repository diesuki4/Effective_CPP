/*
 * https://stackoverflow.com/questions/59985569/should-i-use-a-barrier-while-accessing-statically-initialized-variable#answer-59986089
 */
#include <iostream>

using namespace std;

/*
 * static 변수의 레퍼런스 반환 시 성능
 */

struct Class
{
    int data;

    Class() : data(5) { }
};

/* 전역 변수는 프로그램 실행 시에 한꺼번에 초기화된다. */
Class a;

/* 레퍼런스가 값 타입보다 항상
 * 반환 비용이 적은 것은 아니다.
 *
 * 현재 Class 객체의 크기는 4바이트지만,
 *
 * x64 시스템에서는
 * 레퍼런스는 오히려 8바이트가 된다. */
Class& getClass()
{
    /* 기본 타입 static 변수는
     * 프로그램 실행 시에 초기화되지만,
     *
     * 기본 타입이 아닌 구조체, 클래스 등은
     * 처음 이 문장에 도달했을 때만 초기화된다.
     *
     * 그래서, 첫 실행인지 확인하는
     * 보이지 않는 로직이 들어가기 때문에
     *
     * 코드 양도 커지고 추가 비용도 발생한다. */

    //         이미 초기화됐는지 확인
    //         cmp     byte ptr [$guard variable for c], 0
    //         jne     .LBB_4
    // 
    //         멀티스레드 환경에서 한 스레드만 초기화를 진행하기 위한 락
    //         lea     rdi, byte ptr [$guard variable for c]
    //         call    guard_acquire()
    //         cmp     eax, 0
    //         je      .LBB_4
    // 
    //         생성자 호출 후 락 해제
    //         lea     rdi, byte ptr [$a]
    //         call    AAA::AAA()
    //         lea     rdi, byte ptr [$guard variable for c]
    //         call    guard_release()
    // 
    // .LBB_4  함수 로직
    //         mov     dword ptr [rip + square()::a], 9
    //         ...
    // 
    //         static 변수 초기화 중 예외 발생 시 Stack Unwinding 을 위한 코드
    //         lea     rdi, byte ptr [$guard variable for c]
    //         call    guard_abort()
    //         lea     rdi, dword ptr [rbp - 8]
    //         call    unwind_resume()
    static Class c;

    /*
     * 또한, static 변수가 존재하는 함수에
     * inline 최적화를 적용하지 않는 컴파일러도 있다.
     */

    return c;
}

int main(int argc, char* argv[])
{
    Class& c = getClass();

    /*
     * 레퍼런스는 실제로는 컴파일러에 의해
     * 포인터로 번역된다.
     *
     * 따라서, 역참조 비용이 따른다.
     */
    cout << c.data << endl;

    return 0;
}
