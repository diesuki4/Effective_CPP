#include <iostream>

using namespace std;

/*
 * 초기화 방식의 차이
 * 
 * https://eething.github.io/docs/Programming/cpp/cpp-initialization/
 */

class BBB
{
    int x;
    int y;

public:
    BBB(int x = 0, int y = 0) : x(x), y(y)   { cout << "BBB::생성자 " << x << endl; }
    BBB(const BBB& rhs) : x(rhs.x), y(rhs.y) { cout << "BBB::복사 생성자 " << x << endl; }

    BBB& operator= (const BBB& rhs)
    {
        cout << "BBB::복사 대입 연산자 " << rhs.x << endl;

        x = rhs.x;
        y = rhs.y;

        return *this;
    }
};

class DDD
{
    int x;
    bool b;

public:
    explicit DDD(int x = 0, bool b = false) : x(x), b(b) { cout << "DDD::생성자 " << x << endl; }
    DDD(const DDD& rhs) : x(rhs.x), b(rhs.b)             { cout << "DDD::복사 생성자 " << x << endl; }

    DDD& operator= (const DDD& rhs)
    {
        cout << "BBB::복사 대입 연산자 " << rhs.x << endl;

        x = rhs.x;
        b = rhs.b;

        return *this;
    }
};

void FuncBBB(BBB bbb) { return; }
void FuncDDD(DDD ddd) { return; }

int main(int argc, char* argv[])
{
    // 이건 bClass 객체 선언이 아니라,
    // BBB 객체를 반환하는 bClass 함수 선언으로 해석된다.
    BBB bClass();

    /*
     * 암시적 형 변환을 허용
     */

    BBB b = 1;
    BBB bb = {2};
    BBB bbb = BBB(3);
    BBB bbbb = BBB{4};
    BBB bbbbb{5};
    BBB bbbbbb(6);
    BBB bbbbbbb(BBB(BBB(BBB(7))));
    BBB bbbbbbbb(BBB{8});

    b = BBB(9);
    b = 10;

    FuncBBB(11);
    FuncBBB(BBB(12));
    FuncBBB(BBB{13});
    FuncBBB(b);

    /*
     * 암시적 형 변환을 허용하지 않음
     */

    // DDD d = 1;
    // DDD dd = {2};
    DDD ddd = DDD(3);
    DDD dddd = DDD{4};
    DDD ddddd{5};
    DDD dddddd(6);
    DDD ddddddd(DDD(DDD(DDD(7))));
    DDD dddddddd(DDD{8});

    // d = DDD(9);
    // d = 10;

    // FuncDDD(11);
    FuncDDD(DDD(12));
    FuncDDD(DDD{13});
    // FuncDDD(d);

    return 0;
}
