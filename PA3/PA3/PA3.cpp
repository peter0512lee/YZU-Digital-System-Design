#include "Header.h"

int main()
{
	string t;
	while (getline(cin, t, '\n'))
	{
		fstream fin(t + ".kiss", ios::in);

		SR sr(fin);
		sr.print_origin();
		sr.execute();
		cout << "After State Reduction:" << endl;
		sr.print_afterSR();

		fin.close();
	}
	system("pause");
	return 0;
}