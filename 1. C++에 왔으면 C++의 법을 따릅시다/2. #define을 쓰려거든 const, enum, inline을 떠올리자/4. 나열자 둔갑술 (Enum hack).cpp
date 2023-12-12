#include <iostream>

using namespace std;

/*
 * 나열자 둔갑술 (Enum hack)
 */

class GamePlayer
{
    /*
     * 구형 컴파일러 중에 클래스 상수를
     * 선언 시에 초기화는 것을 허용하지 않는 경우도 있다.
     * 
     * static const int NumTurns;
     */
    
    /*
     * Enum 타입의 값은 int 위치에도 놓일 수 있다.
     * 
     * Enum 은 메모리를 만들지 않기 때문에,
     * 상수보다는 #define 과 유사하다.
     * #define 처럼 여러 복사본으로 인한 낭비도 없다.
     * 
     * 상수의 주소를 얻을 수는 있어도,
     * 매크로 상수나 Enum 의 주소를 얻을 수는 없다.
     * 
     * 따라서, 다른 사람이 내 정수 상수의 주소를 얻는 것이 싫다면
     * Enum hack 을 이용해 방지할 수 있다.
     */
    enum { NumTurns = 5 };

    int scores[NumTurns];
};

/*
 * 구형 컴파일러에서 오류가 난다면
 * 정의에서 초기화해야 한다.
 */
const int GamePlayer::NumTurns = 5;

int main(int argc, char* argv[])
{


    return 0;
}
