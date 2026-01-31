#pragma once
#include "vector.h"
#include <optional>

class my_stack
{
private:
	my_vector container;

public:
	void push(int x)
	{
		container.push_back(x);
	}

	std::optional<int> pop()
	{
		if (this->empty())
		{
			return std::nullopt;
		}

		return container.pop_back();
	}

	int size()
	{
		return container.size();
	}

	bool empty()
	{
		return container.empty();
	}

	std::optional<int> top()
	{
		if (this->empty())
		{
			return std::nullopt;
		}

		return container.back();
	}
};