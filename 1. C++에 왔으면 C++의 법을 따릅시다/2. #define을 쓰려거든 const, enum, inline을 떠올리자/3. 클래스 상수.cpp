#include <iostream>

using namespace std;

/*
 * 클래스 상수
 */

class GamePlayer
{
    /*
     * 상수의 Scope 를 클래스로 한정하고자 할 때는
     * 사본 개수가 1개로 고정되도록
     * 클래스 상수로 만들면 된다.
     *
     * #define 에 비해 캡슐화된다는 장점도 있다.
     */

    // 이것은 선언이다.
    static const int NumTurns = 5;
    int scores[NumTurns];
};

/*
 * 클래스 상수의 주소를 구할 경우
 * 정의가 필요하다.
 *
 * 클래스 상수의 초깃값은 선언할 때 초기화되기 때문에
 * 정의에는 초깃값이 오지 않는다.
 */
const int GamePlayer::NumTurns;

int main(int argc, char* argv[])
{


    return 0;
}
