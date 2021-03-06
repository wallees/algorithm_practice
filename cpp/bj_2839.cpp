/* 백준 2839, 설탕 배달 : https://www.acmicpc.net/problem/2839 */

#include <iostream>
using namespace std;

// 사탕가게에 배달해야 하는 설탕량의 범위가 3이상 5000이하이므로
// 최대치 5000을 MAX 값으로 잡아줍니다.
#define MAX 5000

/*
 문제 해결방법으로 DP(Dynamic Programming)를 사용하였습니다.
 1. dp[] : 설탕량을 담을 수 있는 dp 배열입니다.
 2. basket[] : 설탕봉지는 3kg, 5kg로 구성되어 있다는 것을 의미합니다.
 */
int dp[MAX + 1];
int basket[2] = {3, 5};

/*
 Dynamic Programming은 '이전 값'을 이용하여 '현재 값'을 도출하는 방법입니다.
 순서대로 규칙에 맞는 값을 만들어가는 방법으로 마지막 결과 값을 생성하게 됩니다.
 
 18kg을 만들어봅시다.
 0kg는 없는 값이라고 생각할 수 있으므로 pass
 1,2kg는 최소 설탕봉지인 3kg 미만이기 때문에 만들 수 없는 값이라고 생각합니다.
 dp[1], dp[2]에는 최대값을 넣어주면 되겠죠.
 
 이제 순서대로 진행해봅시다.
 - 3kg : 3 * 1 -> 1
 - 4kg : 3 * 1 + 1 * 1 -> 1kg이 없으므로 만들 수 없음
 - 5kg : 5 * 1 -> 1
 - 6kg : 3 * 2 -> 2
 - 7kg : 만들 수 없음 (3 또는 5로 정확하게 떨어지지 않는 값)
 - 8kg : dp[8 - 5] = dp[3] = 1 / dp[8 - 3] = dp[5] = 1
 결국 dp[3] + 5kg 한개를 하던 dp[5] + 3kg 한개를 하던 2개로 동일하겠죠?
 - 9kg : 3kg * 3 -> 3
 ....
 
 이런식으로 현재 값에서 3kg 혹은 5kg 이전의 값의 최소 값에서 1개를 추가하는 경우를 비교하면서,
 현재의 최소 값을 만들어갑니다. 결국 최소 값에서 결과를 만들어가니까 최소가 되겠죠?
 
 그러면 확인하기 전 초기 값은 어떻게 해야할까요?
 최대값을 넣어주면 최소값이 만들어지면 어쨋든 그 값보다는 적어지게 되므로 계산이 가능하겠죠?
 */
int main(void)
{
    int total;  // 만들고자 하는 설탕의 무게를 입력받습니다.
    cin>>total;
    
    // 0kg는 0으로 (왜냐하면 3kg는 0 + 3 , 5kg는 0 + 5로 비교할거거든요)
    // 1kg, 2kg는 3과 5로 만들 수 없으므로 MAX 값을 넣어줍니다.
    dp[0] = 0;
    dp[1] = MAX;
    dp[2] = MAX;

    // 3kg부터 차례대로 Dynamic Programming을 적용해봅시다.
    for(int i=3; i<=total; i++) {
        // 초기에는 MAX 값으로 세팅해줍니다.
        // 값이 제대로 만들어질때만 변경해주면 되니까요.
        dp[i] = MAX;
        
        // basket. 즉 3kg, 5kg을 번갈아가면서 확인해봅니다.
        // basket[0] = 3kg, basket[1] = 5kg
        for(int j=0; j<2; j++) {
            /*
             사실 if문으로 하지 않고 dp[0]부터 dp[5]까지 미리 세팅할 수도 있습니다.
             dp[3] = 1, dp[4] = MAX, dp[5] = 1
             */
            
            // basket에서 비교할 값보다 i가 큰 경우에만 dp를 비교합니다.
            // 현재 dp[i]에서 3 또는 5를 더하기 이전 값(최소값이겠죠)에서 +1한 경우를 비교합니다.
            // 그래서 더 작은 최소 값을 dp[i]의 값으로 바꿔주면 되죠.
            if(i >= basket[j]) {
                dp[i] = min(dp[i], dp[i - basket[j]] + 1);
            }
        }
    }
    // 만약 MAX 값 이상이 나왔다면, 3kg와 5kg로 만들 수 없다는 의미겠죠? MAX에서 계속 +1이 되니까요.
    // MAX 값 이상이 아니라면, 정상적으로 만들어진 값이라는 의미입니다.
    if(dp[total] >= MAX)    cout<<"-1"<<endl;
    else                    cout<<dp[total]<<endl;
    return 0;
}
