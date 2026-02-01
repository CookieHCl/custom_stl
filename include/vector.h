#pragma once
#include <utility>
#include <concepts>
#include <optional>

template <typename T>
class my_vector
{
public:
	using size_type = int;

private:
	T *_arr;
	size_type _size;
	size_type _capacity;

	static constexpr size_type INITIAL_CAP = 8;

	void _reallocate()
	{
		_reallocate(_capacity * 2);
	}
	void _reallocate(size_type new_size)
	{
		if (new_size <= _capacity)
		{
			return;
		}

		T *new_arr = new T[new_size];

		for (size_type i = 0; i < _size; ++i)
		{
			new_arr[i] = std::move(_arr[i]);
		}

		delete[] _arr;
		_arr = new_arr;
		_capacity = new_size;
	}

public:
	my_vector() : _arr(new T[INITIAL_CAP]), _size(0), _capacity(INITIAL_CAP)
	{
	}
	my_vector(size_type initial_size) : _arr(new T[initial_size]{}), _size(initial_size), _capacity(initial_size)
	{
	}

	friend void swap(my_vector &a, my_vector &b) noexcept
	{
		using std::swap;

		swap(a._arr, b._arr);
		swap(a._size, b._size);
		swap(a._capacity, b._capacity);
	}

	my_vector(const my_vector &other)
		: _arr(new T[other._capacity]), _size(other._size), _capacity(other._capacity)
	{
		for (size_type i = 0; i < _size; ++i)
		{
			_arr[i] = other._arr[i];
		}
	}
	my_vector(my_vector &&other) noexcept
		: _arr(nullptr), _size(0), _capacity(0)
	{
		swap(*this, other);
	}
	my_vector &operator=(my_vector other)
	{
		swap(*this, other);
		return *this;
	}

	~my_vector()
	{
		delete[] _arr;
	}

	template <typename U>
		requires std::convertible_to<U, T>
	void push_back(U &&x)
	{
		if (_size == _capacity)
		{
			_reallocate();
		}

		_arr[_size] = std::forward<U>(x);
		++_size;
	}

	std::optional<T> pop_back()
	{
		if (empty())
		{
			return std::nullopt;
		}

		--_size;
		return std::move(_arr[_size]);
	}

	size_type size() const
	{
		return _size;
	}

	bool empty() const
	{
		return _size == 0;
	}

	T &operator[](size_type x)
	{
		return _arr[x];
	}

	T &front()
	{
		return _arr[0];
	}
	T &back()
	{
		return _arr[_size - 1];
	}

	const T &operator[](size_type x) const
	{
		return _arr[x];
	}

	const T &front() const
	{
		return _arr[0];
	}
	const T &back() const
	{
		return _arr[_size - 1];
	}

	T *begin()
	{
		return _arr;
	}
	T *end()
	{
		return _arr + _size;
	}

	const T *begin() const
	{
		return _arr;
	}
	const T *end() const
	{
		return _arr + _size;
	}

	void resize(size_type new_size)
	{
		if (_size < new_size)
		{
			_reallocate(new_size);

			for (size_type i = _size; i < new_size; ++i)
			{
				_arr[i] = T{};
			}
		}

		_size = new_size;
	}
};