#include "priority_queue.h"
#include <bits/stdc++.h>
using namespace std;

int main()
{
	iostream::sync_with_stdio(0);
	cin.tie(0);

	int n, k;
	my_priority_queue<int> pq;

	for (cin >> n; n--;)
	{
		cin >> k;
		if (k)
		{
			pq.push(k);
		}
		else if (pq.empty())
		{
			cout << "0\n";
		}
		else
		{
			cout << pq.top() << '\n';
			pq.pop();
		}
	}
	return 0;
}