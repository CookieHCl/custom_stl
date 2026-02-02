#include <bits/stdc++.h>
using namespace std;

#include "set.h"

int main()
{
	iostream::sync_with_stdio(0);
	cin.tie(0);

	int n, m, i = 0;
	string s;
	my_set<string> us, sets;

	for (cin >> n >> m; i < n; ++i)
	{
		cin >> s;
		us.insert(s);
	}
	for (i = 0; i < m; ++i)
	{
		cin >> s;
		if (us.find(s))
		{
			sets.insert(s);
		}
	}

	cout << sets.size() << '\n';
	sets.iterate([](string x)
				 { cout << x << '\n'; });
	return 0;
}