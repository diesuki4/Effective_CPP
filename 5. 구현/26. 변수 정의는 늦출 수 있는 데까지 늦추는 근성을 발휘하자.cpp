#include <iostream>

using namespace std;

/*
 * 변수 정의는 늦출 수 있는 데까지 늦추는 근성을 발휘하자
 */

void encrypt(string& s) { return; }

string encryptPassword(const string& password) throw(logic_error)
{
    static const int MinimumPasswordLength = 8;

    /*
     * encrypted 변수를 여기에 선언하면.
     * 
     * 길이가 8자 미만인 경우 객체가 쓰이지도 않았는데
     * 생성/소멸 비용만 발생하게 된다.
     * 
     * string encrypted;
     */

    if (password.length() < MinimumPasswordLength)
        throw logic_error("길이가 너무 짧습니다.");

    /*
     * 따라서, 실제로 필요할 때까지
     * 선언 시점을 늦추는 게 좋다.
     * 
     * 선언 때도 아래처럼
     * 
     * string encrypted;
     * encrypted = password;
     * 
     * 생성자 -> 복사 대입보다는
     *
     * 바로 복사 생성자로 생성하는 것이 효율적이다.
     * 
     * 실제로 변수를 사용할 때가 오기 전까지
     * 최대한 정의를 늦추라는 것이다.
     */
    string encrypted(password);

    encrypt(encrypted);

    return encrypted;
}

class Widget
{
    int data;

public:
    Widget(int data = 0) : data(data) { }
};

/*
 * 복사 대입 비용 < 생성/소멸 비용
 * 이라면 이 방식이 효율적이다.
 * 
 * w 의 scope 가 넓어져
 * 프로그램 이해도와 유지보수성이 안 좋아질 수 있다.
 */
void OutSideFunc(int n)
{
    // 생성 1회
    Widget w;

    for (int i = 0; i < n; ++i)
        // 복사 대입 n 회
        w = i;

    // 소멸 1회
}

/*
 * 복사 대입 비용 > 생성/소멸 비용
 * 이라면 이 방식이 효율적이다.
 * 
 * 성능에 큰 차이가 없다면
 * 이 방식이 더 선호된다.
 */
void InsideFunc(int n)
{
    for (int i = 0; i < n; ++i)
        // 생성 n 회
        Widget w(i);
        // 소멸 n 회
}

int main(int argc, char* argv[])
{
    string password = "ab12";
    string encrypted = encryptPassword(password);

    return 0;
}
