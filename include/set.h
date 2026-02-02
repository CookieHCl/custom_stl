#pragma once
#include <utility>
#include <random>
#include <concepts>

template <typename T>
class my_set
{
public:
	using size_type = int;

private:
	class Node
	{
	private:
		using rng_type = std::mt19937;
		static inline thread_local rng_type _rng{std::random_device{}()};

	public:
		T x;
		rng_type::result_type priority;

		Node *left;
		Node *right;
		size_type size;

		Node(const T &x) : x(x), priority(_rng()), left(nullptr), right(nullptr), size(1) {}
		Node(T &&x) noexcept : x(std::move(x)), priority(_rng()), left(nullptr), right(nullptr), size(1) {}
	};

	Node *_root = nullptr;
	bool _multi_mode;

	void _delete_node(Node *node)
	{
		if (node)
		{
			_delete_node(node->left);
			_delete_node(node->right);
			delete node;
		}
	}

	void _update_size(Node *node)
	{
		if (node)
		{
			node->size = 1;
			if (node->left)
			{
				node->size += node->left->size;
			}
			if (node->right)
			{
				node->size += node->right->size;
			}
		}
	}

	void _merge(Node *&root, Node *left, Node *right)
	{
		if (!left)
		{
			root = right;
		}
		else if (!right)
		{
			root = left;
		}
		else // left && right
		{
			if (left->priority > right->priority)
			{
				root = left;
				_merge(root->right, left->right, right);
			}
			else
			{
				root = right;
				_merge(root->left, left, right->left);
			}
		}

		_update_size(root);
	}

	// left <= cur < right
	void _split_l(const T &k, Node *cur, Node *&left, Node *&right)
	{
		if (!cur)
		{
			left = nullptr;
			right = nullptr;
			return;
		}

		if (cur->x <= k)
		{
			left = cur;
			_split_l(k, cur->right, cur->right, right);
		}
		else
		{
			right = cur;
			_split_l(k, cur->left, left, cur->left);
		}
		_update_size(cur);
	}

	// left < cur <= right
	void _split_r(const T &k, Node *cur, Node *&left, Node *&right)
	{
		if (!cur)
		{
			left = nullptr;
			right = nullptr;
			return;
		}

		if (cur->x < k)
		{
			left = cur;
			_split_r(k, cur->right, cur->right, right);
		}
		else
		{
			right = cur;
			_split_r(k, cur->left, left, cur->left);
		}
		_update_size(cur);
	}

	const Node *_find(const T &k, Node *cur) const
	{
		if (!cur)
		{
			return nullptr;
		}

		if (cur->x == k)
		{
			return cur;
		}
		else if (cur->x < k)
		{
			return _find(k, cur->right);
		}
		else // cur->x > k
		{
			return _find(k, cur->left);
		}
	}

	const Node *_find_kth(const size_type &k, Node *cur) const
	{
		if (!cur)
		{
			// C++23 std::unreachable();
			return nullptr;
		}

		size_type lsize = (cur->left) ? (cur->left->size) : 0;

		if (lsize + 1 == k)
		{
			return cur;
		}
		else if (lsize >= k)
		{
			return _find_kth(k, cur->left);
		}
		else
		{
			return _find_kth(k - lsize - 1, cur->right);
		}
	}

	void _erase_one(const T &k, Node *&cur)
	{
		if (!cur)
		{
			return;
		}

		if (cur->x == k)
		{
			Node *temp = cur;
			_merge(cur, cur->left, cur->right);

			delete temp;
		}
		else if (cur->x < k)
		{
			_erase_one(k, cur->right);
		}
		else // cur->x > k
		{
			_erase_one(k, cur->left);
		}
		_update_size(cur);
	}

	template <typename Func>
		requires std::regular_invocable<Func, T>
	void _iterate(Node *cur, const Func &f)
	{
		if (!cur)
		{
			return;
		}

		if (cur->left)
		{
			_iterate(cur->left, f);
		}
		f(cur->x);
		if (cur->right)
		{
			_iterate(cur->right, f);
		}
	}

	Node *_copy_tree(Node *tree)
	{
		if (!tree)
		{
			return nullptr;
		}

		Node *new_tree = new Node(tree->x);

		new_tree->left = _copy_tree(tree->left);
		new_tree->right = _copy_tree(tree->right);
		new_tree->priority = tree->priority;
		new_tree->size = tree->size;

		return new_tree;
	}

public:
	my_set(bool multi_mode = false) : _multi_mode(multi_mode) {}

	my_set(const my_set &other) : _root(_copy_tree(other._root)), _multi_mode(other._multi_mode) {}
	my_set(my_set &&other)
	{
		_root = other._root;
		_multi_mode = other._multi_mode;

		other._root = nullptr;
	}

	my_set &operator=(const my_set &other)
	{
		if (this != &other)
		{
			_delete_node(_root);

			_root = _copy_tree(other._root);
			_multi_mode = other._multi_mode;
		}

		return *this;
	}
	my_set &operator=(my_set &&other)
	{
		if (this != &other)
		{
			_delete_node(_root);

			_root = other._root;
			_multi_mode = other._multi_mode;
			other._root = nullptr;
		}

		return *this;
	}

	~my_set()
	{
		_delete_node(_root);
	}

	const T *find(const T &x) const
	{
		const Node *node = _find(x, _root);
		if (!node)
		{
			return nullptr;
		}
		return &(node->x);
	}

	// 1based; 1 <= n <= size()
	const T *kth(const size_type &n) const
	{
		if (n <= 0 || n > size())
		{
			return nullptr;
		}

		const Node *node = _find_kth(n, _root);
		return &(node->x);
	}

	template <typename U>
		requires std::convertible_to<U, T>
	void insert(U &&x)
	{
		if (!_multi_mode && find(x))
		{
			return;
		}

		Node *new_node = new Node(std::forward<U>(x));

		if (!_root)
		{
			_root = new_node;
		}
		else
		{
			Node *left = nullptr;
			Node *right = nullptr;
			_split_l(x, _root, left, right);

			_merge(_root, left, new_node);
			_merge(_root, _root, right);
		}
	}

	void erase_one(const T &x)
	{
		_erase_one(x, _root);
	}

	void erase(const T &x)
	{
		Node *left = nullptr;
		Node *same = nullptr;
		Node *right = nullptr;

		Node *temp = nullptr;

		_split_r(x, _root, left, temp);
		_split_l(x, temp, same, right);

		_merge(_root, left, right);
		_delete_node(same);
	}

	size_type size() const
	{
		if (_root == nullptr)
		{
			return 0;
		}
		return _root->size;
	}

	bool empty() const
	{
		return (_root == nullptr);
	}

	template <typename Func>
		requires std::regular_invocable<Func, T>
	void iterate(const Func &f)
	{
		_iterate(_root, f);
	}
};