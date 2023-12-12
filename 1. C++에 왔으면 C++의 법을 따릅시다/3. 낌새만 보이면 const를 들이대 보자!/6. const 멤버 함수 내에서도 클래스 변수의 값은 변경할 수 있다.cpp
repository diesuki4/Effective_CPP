#include <iostream>

using namespace std;

/*
 * const 멤버 함수 내에서도
 * 클래스 변수의 값은 변경할 수 있다
 */

class TextBlock
{
    string text;
    static int nCallCount;

public:
    TextBlock(string text) : text(text) { }

    /*
     * 클래스 변수는 객체의 맴버가 아니기 때문
     */
    void Show() const
    {
        cout << "호출 횟수: " << ++nCallCount << ", " << text << endl;
    }
};

int TextBlock::nCallCount = 0;

int main(int argc, char* argv[])
{
    const TextBlock cTextBlock("HelloWorld!");

    cTextBlock.Show();
    cTextBlock.Show();
    cTextBlock.Show();

    return 0;
}
