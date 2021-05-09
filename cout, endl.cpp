#include <cstdio>
namespace std
{
	class ostream
	{
	public:
		ostream& flush(void)
		{
			return *this; // ���� ���۸� ���� �ִٰ� ����.
		}

		ostream& put(char c)
		{
			printf("%c", c);
			return *this;
		}

		ostream& operator<<(int value)
		{
			printf("%d", value); // ���۸� ��� System Call�� �ϴ°�ó�� �����ϰ� �ϴ°ź���, ���� ���� �ľ��ϱ� ���� �̷��� �����ϰ� �ۼ��߽��ϴ�.
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
	std::cout << "���" << std::endl << "�̰� �ǳ�!!" << std::endl << "WOW";
	return 0;
}