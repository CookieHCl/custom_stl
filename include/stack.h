#pragma once
#include "vector.h"
#include <utility>
#include <concepts>
#include <optional>

template <typename T>
class my_stack
{
public:
	using size_type = typename my_vector<T>::size_type;

private:
	my_vector<T> container{};

public:
	template <typename U>
		requires std::convertible_to<U, T>
	void push(U &&x)
	{
		container.push_back(std::forward<U>(x));
	}

	std::optional<T> pop()
	{
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
		return container.back();
	}
	const T &top() const
	{
		return container.back();
	}
};