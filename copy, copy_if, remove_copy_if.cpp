#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>

auto
main(void) -> int
{
	std::vector<int> numbers;
	for (int i = 0; i < 20; ++i)
		numbers.push_back(i);

	std::cout << "OG" << std::endl;
	std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout, " ")); // Copy �Լ��� ������ ��� ��Ҹ� �����ؼ� ���.
	std::cout << std::endl;
	/*
	template <class _InIt, class _OutIt>
	_CONSTEXPR20 _OutIt copy(_InIt _First, _InIt _Last, _OutIt _Dest) { // copy [_First, _Last) to [_Dest, ...)
		_Adl_verify_range(_First, _Last);
		const auto _UFirst = _Get_unwrapped(_First);
		const auto _ULast = _Get_unwrapped(_Last);
		const auto _UDest = _Get_unwrapped_n(_Dest, _Idl_distance<_InIt>(_UFirst, _ULast));
		_Seek_wrapped(_Dest, _Copy_unchecked(_UFirst, _ULast, _UDest)); // ���⼭ _Copy_unchecked�� �� ����
		return _Dest;
	}
	*/

	/*
	template <class _InIt, class _OutIt>
	_CONSTEXPR20 _OutIt _Copy_unchecked(_InIt _First, _InIt _Last, _OutIt _Dest) {
		// copy [_First, _Last) to [_Dest, ...)
		// note: _Copy_unchecked has callers other than the copy family
		if constexpr (_Ptr_copy_cat<_InIt, _OutIt>::_Trivially_copyable) {
#ifdef __cpp_lib_is_constant_evaluated
			if (!_STD is_constant_evaluated())
#endif // __cpp_lib_is_constant_evaluated
			{
				return _Copy_memmove(_First, _Last, _Dest);
			}
		}

		for (; _First != _Last; ++_Dest, (void) ++_First) {
			*_Dest = *_First; // �� �κп��� _Dest���ڿ� = _First�� �� (�̶��� Iterator�̴�.)�� �Ѵ�.
		}

		return _Dest;
	}
	*/

	/*
	* // ostream_iterator �ȿ� �ִ� ������ ������ �κ��� ����, =�� << Val �� << delim�� �ϴµ� ���⼭ delim�� std::ostream_iterator<int>(std::cout, " ")���� 2��° ������ " "�� ����.
	ostream_iterator& operator=(const _Ty& _Val) { // insert value into output stream, followed by delimiter
        *_Myostr << _Val;
        if (_Mydelim) {
            *_Myostr << _Mydelim;
        }

        return *this;
    }
	*/

	std::vector<int> primes;
	std::copy_if(std::begin(numbers), std::end(numbers), std::back_inserter(primes),
		[](int n)
		{
			if (n % 2 == 0)
				return true;
			return false;
		});

	/*
	template <class _InIt, class _OutIt, class _Pr>
	_CONSTEXPR20 _OutIt copy_if(_InIt _First, _InIt _Last, _OutIt _Dest, _Pr _Pred) { // copy each satisfying _Pred
		_Adl_verify_range(_First, _Last);
		auto _UFirst = _Get_unwrapped(_First);
		const auto _ULast = _Get_unwrapped(_Last);
		auto _UDest = _Get_unwrapped_unverified(_Dest);
		for (; _UFirst != _ULast; ++_UFirst) {
			if (_Pred(*_UFirst)) { // ���⼭ �Լ��� ����Ÿ���� true���
				*_UDest = *_UFirst; primes.push_back(_UFirst)�� ���� �ǹ�.
				++_UDest; // back_inserter�� �����Ǹ� ���ٸ� return *this�̴�. �ǹ̴� ����.
			}
		}

		_Seek_wrapped(_Dest, _UDest);
		return _Dest;
	}
	*/

	std::copy(std::begin(primes), std::end(primes), std::ostream_iterator<int>(std::cout, " "));
	std::cout << std::endl;
	primes.clear();
	std::remove_copy_if(std::begin(numbers), std::end(numbers), std::back_inserter(primes),
		[](int n)
		{
			if (n % 2 == 0)
				return true;
			return false;
		});
	// remove_copy_if�� ���ǹ��� !_Pred(*_UFirst), �� copy_if�� �ݴ��� ���̴�.
	std::copy(std::begin(primes), std::end(primes), std::ostream_iterator<int>(std::cout, " "));
	return 0;
}