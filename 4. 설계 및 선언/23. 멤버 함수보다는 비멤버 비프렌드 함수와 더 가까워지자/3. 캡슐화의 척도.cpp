/*
 * https://drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197
 * https://stackoverflow.com/questions/5989734/effective-c-item-23-prefer-non-member-non-friend-functions-to-member-functions
 */
#include <iostream>

using namespace std;

/*
 * 캡슐화의 척도
 * 
 * 변경으로 인해 얼마나 많은 코드 깨짐이 발생하는가?
 * 
 * 코드 깨짐이 덜 발생한다는 것은
 * 외부 사용자 코드에 영향을 덜 받아(Robustness)
 * 유연하게 수정이 가능(Flexibility)하다는 것이다.
 * 
 * 스콧은 이 코드 깨짐의 정도를 캡슐화의 척도로 사용한다.
 */

struct Point
{
    int X, Y;
};

/*
 * PointMoreEncapsulated 는 Point 에서
 * 데이터 멤버가 변경되는 것으로 발생하는
 * 코드 깨짐보다는 덜 하기 때문에
 * 
 * 더 캡슐화되었다고 할 수 있다.
 */
class PointMoreEncapsulated
{
    /*
     * 하지만, 완전히 캡슐화되었다고는 하기 어렵다.
     *
     * 데이터 멤버를 변경할 수는 있어도
     * 멤버 함수가 깨지는 건 어떻게 할 수 없기 때문이다.
     */

    /*
     * 따라서, 스콧은 캡슐화의 척도가 되는
     * 코드 깨짐의 기준을
     * 
     * <영향 받을 가능성이 있는 함수의 개수>
     * 로 정의한다.
     * 
     * private 데이터 멤버에 접근할 수 있는 건
     * 모두 함수 뿐이기 때문이다.
     * 
     * 현재 X, Y 로 인해 깨질 가능성이 있는 함수 개수는 5개다.
     */
    int X, Y;

    /*
     * friend 선언은
     * 코드 깨짐 가능성이 있는 함수를 추가하므로
     * 캡슐화를 저해시킨다.
     * 
     * (캡슐화를 위반하는 것이 아니다.)
     */
    friend class PointUtility;

public:
    int getX() const { return X; }
    int getY() const { return Y; }
    void setX(int newX) { X = newX; }
    void setY(int newY) { Y = newY; }
};

class PointUtility
{
public:
    void processPoint(Point& p)
    {
        int x = p.X, y = p.Y;

        cout << x << " " << y << endl;
    }
};

/*
 * 따라서, 간단히 멤버 함수의 개수를 통해
 * 캡슐화 정도를 파악할 수도 있다.
 * 
 * 모든 멤버 함수는 데이터 멤버를
 * 최소 1개 이상 활용할 것이기 때문이다.
 * (데이터 멤버를 쓰지 않는 함수를 멤버 함수로 만들 필요가..?)
 * 
 * 그래서 멤버 함수의 개수가 3개인 B보다는
 * 2개인 A가 더 캡슐화되었다고도 할 수 있다.
 */
class A
{
    int data;

public:
    void memberFunction1();
    void memberFunction2();
};

class B
{
    int data;

public:
    void memberFunction1();
    void memberFunction2();
    void memberFunction3();
};

int main(int argc, char* argv[])
{

    return 0;
}
