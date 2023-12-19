/*
 * https://drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197
 * https://stackoverflow.com/questions/5989734/effective-c-item-23-prefer-non-member-non-friend-functions-to-member-functions
 */
#include <iostream>

using namespace std;

/*
 * 캡슐화란
 * 
 * 완벽히 수행해야 하는 목적이 아니라,
 * 유연성(Flexibility) 과 견고성(영향을 받지 않는 성질, Robustness) 을 확보하기 위한 수단이다.
 * 
 * 그렇기에 딱히 바람직하다고 할만 한 게 없다.
 * 
 * 외부 사용자들이 public 멤버 함수들을 어떻게 사용하는지에 영향 받지 않고(견고성),
 * 클래스 내부를 유연하게 수정(유연성)할 수 있어야 한다.
 */

struct Point
{
    /*
     * 변수의 이름이 바뀌었다면?
     * 사용자 측의 코드가 깨진다.
     * 
     * X, Y 값을 DB 에서 가져와야 한다면?
     * 변수 선언을 함수로 바꿔야 한다.
     * 
     * 이런 상황을 캡슐화가 잘 되지 않아(Uncapsulated)
     * 변동에 유연하지 않다(Not flexible) 고 한다.
     * 
     * public 하게 외부에 노출되었다는 것은
     * 사용자가 이 멤버를 쓰고 있다는 걸 가정하므로,
     * 
     * 사용자의 코드를 깨트리지 않기 위해서는
     * 데이터 멤버를 수정하기가 매우 어렵다는 뜻이다.
     * 
     * 그래서 캡슐화가 필요한 것이다.
     */
    int X, Y;
};

/*
 * 좀 더 유연성을 확보해 캡슐화된 클래스
 */
class PointMoreEncapsulated
{
    // 이제 변수 이름을 유연하게 수정할 수 있다.
    int X, Y;

public:
    // 이제 X, Y 값을 DB 에서 가져올 수도 있다.
    int getX() const { return X; }
    int getY() const { return Y; }
    void setX(int newX) { X = newX; }
    void setY(int newY) { Y = newY; }
};

int main(int argc, char* argv[])
{

    return 0;
}
