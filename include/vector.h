#pragma once
#include <utility>

template <typename T>
class my_vector
{
private:
	T *_arr;
	int _size;
	int _capacity;

	static constexpr int INITIAL_CAP = 8;

	void reallocate()
	{
		T *old_arr = _arr;
		_arr = new T[_capacity * 2];

		for (int i = 0; i < _size; ++i)
		{
			_arr[i] = old_arr[i];
		}

		delete[] old_arr;
		_capacity *= 2;
	}

public:
	my_vector() : _arr(new T[INITIAL_CAP]), _size(0), _capacity(INITIAL_CAP)
	{
	}
	my_vector(int initial_size) : _arr(new T[initial_size]{}), _size(initial_size), _capacity(initial_size)
	{
	}

	~my_vector()
	{
		delete[] _arr;
	}

	void push_back(T x)
	{
		if (_size == _capacity)
		{
			reallocate();
		}

		_arr[_size] = x;
		++_size;
	}

	T pop_back()
	{
		--_size;
		return std::move(_arr[_size]);
	}

	int size()
	{
		return _size;
	}

	bool empty()
	{
		return _size == 0;
	}

	T &operator[](int x)
	{
		return _arr[x];
	}

	T front()
	{
		return _arr[0];
	}
	T back()
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

	void resize(int new_size)
	{
		if (_size < new_size)
		{
			// TODO: 멍청하고 느린데 나중에 수정함
			while (_capacity >= new_size)
			{
				reallocate();
			}

			for (int i = _size; i < new_size; ++i)
			{
				_arr[i] = T{};
			}
		}

		_size = new_size;
	}
};