#pragma once
#include <utility>

class disjoint_set
{
private:
	int *parent;
	int *rank;

public:
	disjoint_set(int size) : parent(new int[size]{}), rank(new int[size]{})
	{
		for (int i = 0; i < size; ++i)
		{
			parent[i] = i;
		}
	}
	~disjoint_set()
	{
		delete[] parent;
		delete[] rank;
	}

	disjoint_set(const disjoint_set &) = delete;
	disjoint_set &operator=(const disjoint_set &) = delete;

	disjoint_set(disjoint_set &&) = delete;
	disjoint_set &operator=(disjoint_set &&) = delete;

	int find(int n)
	{
		if (n == parent[n])
			return n;
		return (parent[n] = find(parent[n]));
	}

	void unite(int x, int y)
	{
		x = find(x);
		y = find(y);

		if (x != y)
		{
			if (rank[x] < rank[y])
			{
				std::swap(x, y);
			}

			parent[y] = x;
			if (rank[x] == rank[y])
			{
				++rank[x];
			}
		}
	}
};