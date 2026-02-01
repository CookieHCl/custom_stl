#pragma once
#include "vector.h"
#include <utility>
#include <concepts>
#include <optional>

template <typename T>
class my_queue
{
public:
	using size_type = typename my_vector<T>::size_type;

private:
	my_vector<T> container{};

	size_type _head = 0;

	void _reallocate()
	{
		size_type s = size();
		for (size_type i = 0; i < s; ++i)
		{
			container[i] = std::move(container[_head + i]);
		}

		container.resize(s);
		_head = 0;
	}

public:
	template <typename U>
		requires std::convertible_to<U, T>
	void push(U &&x)
	{
		if (_head > (container.size() + 1) / 2)
		{
			_reallocate();
		}

		container.push_back(std::forward<U>(x));
	}

	std::optional<T> pop()
	{
		if (empty())
		{
			return std::nullopt;
		}

		return std::move(container[_head++]);
	}

	size_type size() const
	{
		return container.size() - _head;
	}

	bool empty() const
	{
		return container.size() == _head;
	}

	T &front()
	{
		return container[_head];
	}
	const T &front() const
	{
		return container[_head];
	}

	T &back()
	{
		return container.back();
	}
	const T &back() const
	{
		return container.back();
	}
};