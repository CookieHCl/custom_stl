#include "stack.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
	iostream::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	string s;
	my_stack<int> st;
	for (cin >> n; n--;)
	{
		cin >> s;
		if (s == "push")
		{
			cin >> k;
			st.push(k);
		}
		else if (s == "pop")
		{
			cout << (st.empty() ? -1 : st.pop().value()) << '\n';
		}
		else if (s == "size")
		{
			cout << st.size() << '\n';
		}
		else if (s == "empty")
		{
			cout << st.empty() << '\n';
		}
		else if (s == "top")
		{
			cout << (st.empty() ? -1 : st.top()) << '\n';
		}
	}

	return 0;
}