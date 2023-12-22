#include <iostream>
#include <vector>

using namespace std;

/*
 * dynamic_cast 를 통한 안전한 캐스팅
 */

class Window
{
public:
    virtual void onResize() { cout << "Window::onResize()" << endl; }

    virtual ~Window() { }
};

class SpecialWindow : public Window
{
public:
    virtual void onResize() override { cout << "SpecialWindow::onResize()" << endl; }

    /*
     * 자식 클래스 함수를 호출하고 싶은데
     * (가상 함수가 아니다.)
     */
    void blink()
    {
        cout << "SpecialWindow::blink()" << endl;
    }
};

int main(int argc, char* argv[])
{
    // 부모 클래스 포인터밖에 없을 경우
    using VPW = vector<shared_ptr<Window>>;
    VPW winPtrs;

    winPtrs.emplace_back(new SpecialWindow);
    winPtrs.emplace_back(new SpecialWindow);
    winPtrs.emplace_back(new Window);

    for (VPW::iterator it = winPtrs.begin(); it != winPtrs.end(); ++it)
        /*
         * dynamic_cast 를 통해 안전하게 캐스팅해
         * 자식 함수를 호출할 수 있다.
         * 
         * 실제 객체가 부모인 3번째에서는 nullptr 이 반환된다.
         */
        if (SpecialWindow* psw = dynamic_cast<SpecialWindow*>(it->get()))
            psw->blink();

    return 0;
}
