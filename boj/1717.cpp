#include "disjoint_set.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
	iostream::sync_with_stdio(0);
	cin.tie(0);

	int n, m, a, b, c;
	cin >> n >> m;
	disjoint_set ds(n + 1);

	while (m--)
	{
		cin >> a >> b >> c;

		if (a)
		{
			b = ds.find(b);
			c = ds.find(c);
			cout << (b == c ? "YES\n" : "NO\n");
		}
		else
		{
			ds.unite(b, c);
		}
	}
	return 0;
}