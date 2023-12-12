#include <iostream>

/*
 * 전처리기는 모든 ASPECT_RATIO 를 1.653으로 밀어버리고
 * 컴파일러에게 전달하기 때문에
 * 
 * 컴파일러는 ASPECT_RATIO 의 존재를 모른다.
 * 
 * 따라서 디버깅 심볼을 만들 수도 없다.
 * 
 * 소스 코드엔 분명히 ASPECT_RATIO 라고 되어 있는데,
 * 컴파일 에러에서는 1.653 이 보이게 돼
 * 디버깅도 쉽지 않다.
 * 
 * 특히, 내가 선언한 매크로가 아니라면
 * 어디에 있는지 알 방법도 없다.
 */
#define ASPECT_RATIO 1.653

using namespace std;

/*
 * 가급적 전처리기보다는 컴파일러를 더 가까이 하자
 */

/*
 * #define 보다는 const 상수를 사용하자.
 *
 * 컴파일러가 존재를 알 수 있고
 * 디버깅 심볼도 만들 수 있다.
 *
 * #define 의 경우 1.653 의 사본이 등장 횟수만큼 생기는 반면,
 * const 상수는 AspectRatio 1개면 충분하기 때문에
 *
 * 최종 코드의 크기도 작아진다.
 */
const double AspectRatio = 1.653;

int main(int argc, char* argv[])
{


    return 0;
}
