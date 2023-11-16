#include<cstdio>
#include<iostream>
#include<stack>
using namespace std;
stack<int> st;
int main()
{
	int n;
	cin >> n;
	int a[100], ans[100];
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = n; i >= 1; i--) {
		while (!st.empty() && a[st.top()] <= a[i]) {
			st.pop();
		}
		ans[i] = st.empty() ? 0 : st.top();
		st.push(i);
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
	return 0;
}