#include <iostream>

using namespace std;

/*
 * explicit 생성자를 적극 활용하자.
 */

class BBB
{
    int x;
    int y;

public:
    BBB(int x = 0, int y = 0) : x(x), y(y) { }
};

class DDD
{
    int x;
    bool b;

public:
    /*
     * explicit 선언은
     * 암시적 형 변환을 허용하지 않는다.
     * 
     * ddd = 1;
     * 안 된다.
     * 
     * 프로그래머가 예상치 못한 형 변환을 막아준다.
     * 
     * 암시적 형 변환을 허용할 뚜렷한 이유가 없는 한
     * explicit 생성자를 적극 활용하는 게 좋다.
     */
    explicit DDD(int x = 0, bool b = false) : x(x), b(b) { }
};

void FuncBBB(BBB bbb) { return; }
void FuncDDD(DDD ddd) { return; }

int main(int argc, char* argv[])
{
    BBB bbb;
    // 암시적 형 변환
    // bbb = BBB(1);
    bbb = 1;
    // FuncBBB(BBB(2));
    FuncBBB(2);

    DDD ddd;
    // 암시적 형 변환을 허용하지 않는다.
    // ddd = 1;
    // FuncDDD(2);

    return 0;
}
