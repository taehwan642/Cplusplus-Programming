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
	std::copy(std::begin(numbers), std::end(numbers), std::ostream_iterator<int>(std::cout, " ")); // Copy 함수로 벡터의 모든 요소를 복사해서 출력.
	std::cout << std::endl;
	/*
	template <class _InIt, class _OutIt>
	_CONSTEXPR20 _OutIt copy(_InIt _First, _InIt _Last, _OutIt _Dest) { // copy [_First, _Last) to [_Dest, ...)
		_Adl_verify_range(_First, _Last);
		const auto _UFirst = _Get_unwrapped(_First);
		const auto _ULast = _Get_unwrapped(_Last);
		const auto _UDest = _Get_unwrapped_n(_Dest, _Idl_distance<_InIt>(_UFirst, _ULast));
		_Seek_wrapped(_Dest, _Copy_unchecked(_UFirst, _ULast, _UDest)); // 여기서 _Copy_unchecked를 잘 보면
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
			*_Dest = *_First; // 이 부분에서 _Dest인자에 = _First의 값 (이때는 Iterator이다.)을 한다.
		}

		return _Dest;
	}
	*/

	/*
	* // ostream_iterator 안에 있는 연산자 재정의 부분을 보면, =는 << Val 후 << delim을 하는데 여기서 delim은 std::ostream_iterator<int>(std::cout, " ")에서 2번째 인자인 " "와 같다.
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
			if (_Pred(*_UFirst)) { // 여기서 함수의 리턴타입이 true라면
				*_UDest = *_UFirst; primes.push_back(_UFirst)와 같은 의미.
				++_UDest; // back_inserter의 재정의를 본다면 return *this이다. 의미는 같음.
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
	// remove_copy_if는 조건문이 !_Pred(*_UFirst), 즉 copy_if의 반대일 뿐이다.
	std::copy(std::begin(primes), std::end(primes), std::ostream_iterator<int>(std::cout, " "));
	return 0;
}