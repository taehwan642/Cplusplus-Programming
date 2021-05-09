#include <cstdio>
namespace std
{
	class ostream
	{
	public:
		ostream& flush(void)
		{
			return *this; // 츨력 버퍼를 비우고 있다고 가정.
		}

		ostream& put(char c)
		{
			printf("%c", c);
			return *this;
		}

		ostream& operator<<(int value)
		{
			printf("%d", value); // 버퍼를 잡고 System Call을 하는것처럼 복잡하게 하는거보다, 원리 먼저 파악하기 위해 이렇게 간단하게 작성했습니다.
			return *this;
		}

		ostream& operator<<(double value)
		{
			printf("%f", value);
			return *this;
		}

		ostream& operator<<(char value)
		{
			printf("%c", value);
			return *this;
		}

		ostream& operator<<(const char* value)
		{
			printf("%s", value);
			return *this;
		}

		ostream& operator<<(ostream&(*endl)(ostream&))
		{
			endl(*this);
			return *this;
		}

	private:

	};

	ostream cout;

	ostream& endl(ostream& os)
	{
		os.put('\n');
		os.flush();
		return os;
	}
}


int main(void)
{
	std::cout << "우왕" << std::endl << "이게 되네!!" << std::endl << "WOW";
	return 0;
}