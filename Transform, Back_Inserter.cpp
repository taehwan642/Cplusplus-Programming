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
function<C(A)> compose(function<C(B)> g, function<B(A)> f) // C(A)이니까 f, g의 값을 캡쳐해 (함수의 본문 캡쳐) 인자로 A를 받고, g(f(x)) 결과를 도출하는 람다 함수를 새로 제작.
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
	// 위에 코드를 보면, first1++와 first2++를 동시에 한다. 그래서 first1과 first2의 숫자를 맞춰야 한다. 만약 first1 > first2라면 오류가 난다.

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
	// 저렇게 back_inserter를 사용하면 back_insert_iterator를 통해 인자로 넣은 container에게 push_back를 해준다. 이 때 push_back은 이동 push back, 기본 push back 2가지가 있다.

	for (auto iter : composedfunc)
	{
		std::cout << iter(num) << std::endl;
	}
	return 0;
}