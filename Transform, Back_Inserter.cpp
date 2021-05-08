#include <vector>
#include <algorithm>
#include <functional>
#include <iostream>

using std::vector;
using std::function;
using std::transform;
using std::back_inserter;
using std::cout;
using std::endl;

typedef function<double(double)> Func;

vector<Func> funcs = {
	[](double x) {return x - 1; }
};

vector<Func> inversefuncs = {
	[](double x) {return x + 1; }
};

template<typename A, typename B, typename C>
function<C(A)> compose(function<C(B)> g, function<B(A)> f) // C(A)�̴ϱ� f, g�� ���� ĸ���� (�Լ��� ���� ĸ��) ���ڷ� A�� �ް�, g(f(x)) ����� �����ϴ� ���� �Լ��� ���� ����.
{
	return [f, g](A x) {return g(f(x)); };
};

auto 
main(void) -> int
{
	vector<Func> composedfunc;
	double num = 1;
	transform(begin(inversefuncs), end(inversefuncs), begin(funcs), back_inserter(composedfunc), compose<double, double, double>);
	/*
	template<class InputIt1, class InputIt2,
		class OutputIt, class BinaryOperation>
	OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
			OutputIt d_first, BinaryOperation binary_op)
	{
		while (first1 != last1) {
			*d_first++ = binary_op(*first1++, *first2++);
		}
		return d_first;
	}
	*/
	// ���� �ڵ带 ����, first1++�� first2++�� ���ÿ� �Ѵ�. �׷��� first1�� first2�� ���ڸ� ����� �Ѵ�. ���� first1 > first2��� ������ ����.

	/* 
	template <class _Container>
	_NODISCARD _CONSTEXPR20 back_insert_iterator<_Container> back_inserter(_Container & _Cont) noexcept {
		// return a back_insert_iterator
		return back_insert_iterator<_Container>(_Cont);
	}
	*/

	/*
	_CONSTEXPR20 back_insert_iterator& operator=(typename _Container::value_type && _Val) {
		container->push_back(_STD move(_Val));
		return *this;
	}
	*/
	// ������ back_inserter�� ����ϸ� back_insert_iterator�� ���� ���ڷ� ���� container���� push_back�� ���ش�. �� �� push_back�� �̵� push back, �⺻ push back 2������ �ִ�.

	for (auto iter : composedfunc)
	{
		std::cout << iter(num) << std::endl;
	}
	return 0;
}