#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int n, k, ans;
    cin >> n >> k;
    int * a = new int[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    int i = 0;
    while (i + k <= n)
    {
        ans = *min_element(a + i, a + k + i);
        printf("%d",ans);
        printf("%s", "\n");
        i++;
    }
    return 0;
}