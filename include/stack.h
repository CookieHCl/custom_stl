#pragma once
#include "vector.h"
#include <optional>

template <typename T>
class my_stack
{
private:
	my_vector<T> container{};

public:
	void push(T x)
	{
		container.push_back(x);
	}

	std::optional<T> pop()
	{
		if (empty())
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

	std::optional<T> top()
	{
		if (empty())
		{
			return std::nullopt;
		}

		return container.back();
	}
};