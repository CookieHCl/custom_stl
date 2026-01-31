#pragma once
#include "vector.h"
#include <optional>

template <typename T>
class my_queue
{
private:
	my_vector<T> container{};

	int _head = 0;

	void reallocate()
	{
		int s = size();
		for (int i = 0; i < s; ++i)
		{
			container[i] = container[_head + i];
		}

		container.resize(s);
		_head = 0;
	}

public:
	void push(T x)
	{
		if (_head > (container.size() + 1) / 2)
		{
			reallocate();
		}

		container.push_back(x);
	}

	std::optional<T> pop()
	{
		if (empty())
		{
			return std::nullopt;
		}

		return container[_head++];
	}

	int size()
	{
		return container.size() - _head;
	}

	bool empty()
	{
		return container.size() == _head;
	}

	std::optional<T> front()
	{
		if (empty())
		{
			return std::nullopt;
		}

		return container[_head];
	}

	std::optional<T> back()
	{
		if (empty())
		{
			return std::nullopt;
		}

		return container.back();
	}
};