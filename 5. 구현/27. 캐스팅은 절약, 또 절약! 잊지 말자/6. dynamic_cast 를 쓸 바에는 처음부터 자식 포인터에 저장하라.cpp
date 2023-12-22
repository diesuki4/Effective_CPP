#include <iostream>
#include <vector>

using namespace std;

/*
 * dynamic_cast 를 쓸 바에는 처음부터 자식 포인터에 저장하라
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

    void blink()
    {
        cout << "SpecialWindow::blink()" << endl;
    }
};

int main(int argc, char* argv[])
{
    // 캐스팅이 필요 없도록
    using VPW = vector<shared_ptr<Window>>;
    VPW winPtrs;

    // 부모 객체와
    winPtrs.emplace_back(new Window);

    // 자식 객체를
    using VPSW = vector<shared_ptr<SpecialWindow>>;
    VPSW spWinPtrs;

    // 애초에 따로 저장했다.
    spWinPtrs.emplace_back(new SpecialWindow);
    spWinPtrs.emplace_back(new SpecialWindow);

    for (VPSW::iterator it = spWinPtrs.begin(); it != spWinPtrs.end(); ++it)
        // 이제 dynamic_cast 비용 없이 바로 호출할 수 있다.
        (*it)->blink();

    return 0;
}
