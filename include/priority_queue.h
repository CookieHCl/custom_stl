#pragma once
#include "vector.h"
#include <utility>
#include <concepts>
#include <optional>
#include <iostream>

template <typename T>
class my_priority_queue
{
public:
	using size_type = typename my_vector<T>::size_type;

private:
	my_vector<T> container{};

	static inline size_type parent(size_type n)
	{
		return (n - 1) / 2;
	}
	static inline size_type first_child(size_type n)
	{
		return 2 * n + 1;
	}
	static inline size_type second_child(size_type n)
	{
		return 2 * (n + 1);
	}

	void _push_heap()
	{
		using std::swap;

		size_type n = size() - 1;
		while (n != 0)
		{
			size_type par_n = parent(n);

			if (container[par_n] >= container[n])
			{
				break;
			}

			swap(container[par_n], container[n]);
			n = par_n;
		}
	}

	void _pop_heap()
	{
		using std::swap;
		swap(container.front(), container.back());

		size_type n = 0;
		size_type new_size = size() - 1;
		while (n < new_size)
		{
			size_type first_child_n = first_child(n);
			size_type second_child_n = second_child(n);

			if (second_child_n < new_size && container[second_child_n] > container[n] && container[second_child_n] > container[first_child_n])
			{
				swap(container[second_child_n], container[n]);
				n = second_child_n;
			}
			else if (first_child_n < new_size && container[first_child_n] > container[n])
			{
				swap(container[first_child_n], container[n]);
				n = first_child_n;
			}
			else
			{
				break;
			}
		}
	}

public:
	template <typename U>
		requires std::convertible_to<U, T>
	void push(U &&x)
	{
		container.push_back(std::forward<U>(x));
		_push_heap();
	}

	std::optional<T> pop()
	{
		if (empty())
		{
			return std::nullopt;
		}

		_pop_heap();
		return container.pop_back();
	}

	size_type size() const
	{
		return container.size();
	}

	bool empty() const
	{
		return container.empty();
	}

	T &top()
	{
		return container.front();
	}
	const T &top() const
	{
		return container.front();
	}
};
