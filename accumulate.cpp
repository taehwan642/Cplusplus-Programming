#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

auto
main(void) -> int
{
	std::vector<int> numbers = { 0,1,2,3,4 };
	auto foldl = std::accumulate(std::begin(numbers), std::end(numbers), 0,
		[](const int& val1, const int& val2)
		{
			std::cout << "val1 " << val1 << " val2 " << val2 << std::endl;
			return val1 + val2;
		});
	auto foldr = std::accumulate(std::rbegin(numbers), std::rend(numbers), 0,
		[](const int& val1, const int& val2)
		{
			std::cout << "val1 " << val1 << " val2 " << val2 << std::endl;
			return val1 + val2;
		});

	/*
	template <class _InIt, class _Ty, class _Fn>
	_NODISCARD _CONSTEXPR20 _Ty accumulate(const _InIt _First, const _InIt _Last, _Ty _Val, _Fn _Reduce_op) {
		// return noncommutative and nonassociative reduction of _Val and all in [_First, _Last), using _Reduce_op
		_Adl_verify_range(_First, _Last);
		auto _UFirst = _Get_unwrapped(_First);
		const auto _ULast = _Get_unwrapped(_Last);
		for (; _UFirst != _ULast; ++_UFirst) {
#if _HAS_CXX20
			_Val = _Reduce_op(_STD move(_Val), *_UFirst);
#else // ^^^ _HAS_CXX20 ^^^ // vvv !_HAS_CXX20 vvv
			_Val = _Reduce_op(_Val, *_UFirst); // �� �� _Val�� *_UFirst (�ʹݿ��� 0�� numbers�� begin iterator�� ���� �� 0�̴�.)�� ���ڷ� ���� �Լ��� 2�� �ִ´�. std::plus<int>�� �Լ� ��ü�̱⿡ �����ϴ�.
#endif // _HAS_CXX20
		}
		return _Val;
	}
	*/

	std::cout << foldl << " " << foldr << std::endl;

	return 0;
}