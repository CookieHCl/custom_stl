#include "queue.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
	iostream::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	string s;

	my_queue<int> q;
	for (cin >> n; n--;)
	{
		cin >> s;
		if (s == "push")
		{
			cin >> k;
			q.push(k);
		}
		else if (s == "pop")
		{
			cout << (q.empty() ? -1 : q.pop().value()) << '\n';
		}
		else if (s == "size")
		{
			cout << q.size() << '\n';
		}
		else if (s == "empty")
		{
			cout << q.empty() << '\n';
		}
		else if (s == "front")
		{
			cout << (q.empty() ? -1 : q.front()) << '\n';
		}
		else if (s == "back")
		{
			cout << (q.empty() ? -1 : q.back()) << '\n';
		}
	}
	return 0;
}