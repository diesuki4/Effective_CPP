#include <iostream>

using namespace std;

/*
 * 캐스트 연산자가 입맛 당기는 상황이라면 뭔가 꼬여가는 징조다
 */

class Window
{
public:
    virtual void onResize()
    {
        cout << reinterpret_cast<int*>(this) << " Window::onResize()" << endl;
    }

    virtual void onClick()
    {
        cout << reinterpret_cast<int*>(this) << " Window::onClick()" << endl;
    }

    virtual ~Window() { }
};

class SpecialWindow : public Window
{
public:
    virtual void onResize() override
    {
        // *this 에서 객체 사본이 만들어진다.
        static_cast<Window>(*this).onResize();

        cout << reinterpret_cast<int*>(this) << " SpecialWindow::onResize()" << endl << endl;
    }

    virtual void onClick() override
    {
        // 그냥 컴파일러에게 부모 함수를 호출하라고 명시하면 된다.
        Window::onClick();

        cout << reinterpret_cast<int*>(this) << " SpecialWindow::onClick()" << endl << endl;
    }
};

int main(int argc, char* argv[])
{
    SpecialWindow sw;

    /*
     * 잘 작동은 하는데, 두 함수는 실제로는 다른 객체에서 실행된다.
     */
    sw.onResize();

    /*
     * 이제 두 함수는 동일한 객체에서 실행된다.
     */
    sw.onClick();

    return 0;
}
