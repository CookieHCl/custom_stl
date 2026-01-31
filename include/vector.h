#pragma once

class my_vector
{
private:
	int *_arr;
	int _size;
	int _capacity;

	static constexpr int INITIAL_CAP = 8;

	void reallocate()
	{
		int *old_arr = _arr;
		_arr = new int[_capacity * 2];

		for (int i = 0; i < _size; ++i)
		{
			_arr[i] = old_arr[i];
		}

		delete[] old_arr;
		_capacity *= 2;
	}

public:
	my_vector() : _arr(new int[INITIAL_CAP]), _size(0), _capacity(INITIAL_CAP)
	{
	}
	my_vector(int initial_size) : _arr(new int[initial_size]{}), _size(initial_size), _capacity(initial_size)
	{
	}

	void push_back(int x)
	{
		if (_size == _capacity)
		{
			reallocate();
		}

		_arr[_size] = x;
		++_size;
	}

	int pop_back()
	{
		--_size;
		return _arr[_size];
	}

	int size()
	{
		return _size;
	}

	bool empty()
	{
		return _size == 0;
	}

	int &operator[](int x)
	{
		return _arr[x];
	}

	int front()
	{
		return _arr[0];
	}
	int back()
	{
		return _arr[_size - 1];
	}

	int *begin()
	{
		return _arr;
	}
	int *end()
	{
		return _arr + _size;
	}
};