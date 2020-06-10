#include<iostream>
#include<string>
using namespace std;

const int MAX_DIGIT = 10;

char DecToFT(unsigned int num)
{
	char FT[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
		'E', 'F', 'G' };

	return FT[num];
}

int FTToDec(const char ch)
{
	char FT[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
		'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
		'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
		'E', 'F', 'G' };

	for (size_t i = 0; i < 43; i++)
	{
		if (ch == FT[i])
		{
			return i;
		}
	}
	
}


int main()
{
	cout << "r is 43" << endl;

	while (true)
	{
		cout << "Which mode?" << endl;

		int mode = 0, value = 0;

		string result;

		cin >> mode;

		switch (mode)
		{
		case 0:

			cout << "Value?" << endl;
			cin >> value;

			do
			{
				result = DecToFT(value % 43) + result;
				value /= 43;

			} while (value > 0);

			cout << "Result:" << result << endl;

			break;

		case 1:
			char FTnumber[MAX_DIGIT + 1];
			double sum = 0;

			cout << "Value?" << endl;
			cin >> FTnumber;

			int power = strlen(FTnumber) - 1;
			int base = 0;

			for (size_t i = 0; i < strlen(FTnumber); i++, power--)
			{
				base = FTToDec(FTnumber[i]);
				sum += base * pow(43, power);					
			}

			cout << "Result:" << sum << endl;

			break;

		}
	}


	system("pause");
	return 0;

}