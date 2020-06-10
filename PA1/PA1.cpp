#include<iostream>
#include<string>
using namespace std;

const int MAX_DIGIT = 10;

string FTnumber;

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

bool input43()
{
	string number;
	cin >> number;

	for (size_t i = 0; i < number.size(); i++)
	{
		if ((number[i]<'0' || number[i]>'9') && (number[i]<'a' || number[i]>'z') && (number[i]<'A' || number[i]>'G'))
		{
			return false;
		}
		else 
		{
			FTnumber.push_back(number[i]);
		}

	}
	return true;
}

int main()
{

	cout << "r is 43" << endl;

	while (true)
	{	
		double sum = 0;
		int power = 0, base = 0;

		cout << "Which mode?" << endl;

		int mode = 0, value = 0;

		string result;

		cin >> mode;

		if (cin.good())
		{
			switch (mode)
			{
			case 0:

				cout << "Value?" << endl;
				cin >> value;

				if (!cin.good())
				{
					cout << "input error" << endl;
					cin.clear();
					cin.ignore(1000, '\n');
					break;
				}

				do
				{
					result = DecToFT(value % 43) + result;
					value /= 43;

				} while (value > 0);

				cout << "Result:" << result << endl;

				break;

			case 1:

				cout << "Value?" << endl;

				if (input43())
				{
					power = FTnumber.size() - 1;

					for (size_t i = 0; i < FTnumber.size(); i++, power--)
					{
						base = FTToDec(FTnumber[i]);
						sum += base * pow(43, power);
					}

					cout << "Result:" << sum << endl;

				}
				else
				{
					cout << "input error" << endl;
				}

				FTnumber.clear();
				
				break;
			default:				
				break;
			}
		}
		else 
		{
			cout << "input error" << endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
	}


	system("pause");
	return 0;

}