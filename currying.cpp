#include <functional>
#include <iostream>

template<typename Func, typename ... Args>
auto
curry(Func func, Args... args)
{
	return [=](auto... lastparam)
	{
		return func(args..., lastparam...);
	};
}

int
areaOfRectangle(int length, int width)
{
	return (length * width);
}

int
volumeOfRectangular(int length, int width, int height)
{
	return length * width * height;
}

auto
main(void) -> int
{
	auto area = curry(areaOfRectangle, 1);
	auto volume = curry(volumeOfRectangular, 1, 2);

	for (int i = 0; i <= 5; ++i)
		std::cout << "AREA " << area(i) << std::endl;
	for (int i = 0; i <= 5; ++i)
		std::cout << "VOLUME " << volume(i) << std::endl;
	return 0;
}