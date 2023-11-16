#include <iostream>
#include <deque>

using namespace std;

const int N = 1e6 + 10;

int n, k;
int a[N];
deque<int> q;

int main()
{
    cin >> n >> k;
    for (int i = 0; i < n; i ++ ) cin >> a[i];

    for (int i = 0; i < n; i ++ )
    {
        if (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] >= a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k - 1) cout << a[q.front()] << ' ';
    }
    cout << endl;

    q.clear();
    
    for (int i = 0; i < n; i ++ )
    {
        if (!q.empty() && q.front() <= i - k) q.pop_front();
        while (!q.empty() && a[q.back()] <= a[i]) q.pop_back();
        q.push_back(i);
        if (i >= k - 1) cout << a[q.front()] << ' ';
    }
    cout << endl;

    return 0;
}