#include <bits/stdc++.h>
using namespace std;

#include "set.h"

int main()
{
	iostream::sync_with_stdio(0);
	cin.tie(0);

	my_set<int> s(true);

	int n, t, x;
	cin >> n;

	while (n--)
	{
		cin >> t >> x;
		if (t == 1)
		{
			s.insert(x);
		}
		else
		{
			int k = *(s.kth(x));
			s.erase_one(k);
			cout << k << '\n';
		}
	}

	return 0;
}