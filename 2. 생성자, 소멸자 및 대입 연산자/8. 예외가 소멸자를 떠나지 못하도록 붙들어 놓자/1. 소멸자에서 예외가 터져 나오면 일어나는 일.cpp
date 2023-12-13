#include <iostream>
#include <vector>

using namespace std;

/*
 * 소멸자에서 예외가 터져 나오면 일어나는 일
 */

class Widget
{
    int num;

public:
    Widget(int num) : num(num) { }
    ~Widget() throw(int)
    {
        // 5번 객체 소멸에서 예외가 발생하도록 가정
        if (num == 5)
            throw num;

        cout << "Widget " << num << " 소멸" << endl;
    }
};

void Func()
{
    // int -> Widget 암시적 형 변환
    vector<Widget> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    /*
     * 10개 객체의 메모리 소멸 책임은 vector 에 있다.
     * 
     * 10개의 소멸자가 호출될 때 5번째에서 예외가 발생해
     * 도중에 끊기게 된다.
     * 
     * 결국, 메모리 누수가 발생하고 Undefined behavior 로 이어질 수 있다.
     */
}

int main(int argc, char* argv[])
{
    Func();

    return 0;
}
