#include "final.h"
using namespace cv;
using namespace std;

int main()
{
	int number;
	while (true)
	{
		cout << "1: 3_1" << endl;
		cout << "2: 3_2" << endl;
		cout << "3: 3_3_1&2" << endl;
		cout << "4: 3_3_3" << endl;
		cout << "0: exit" << endl;
		cout << "Enter the question number to select output result:";
		cin >> number;

		if (number == 1)
			PUBG();
		else if (number == 2)
			sorting();
		/*else if (number == 3)
			HW3_3_1_2();
		else if (number == 4)
			HW3_3_3();*/
		else if (number == 0)
			break;
		else if (number < 0 or number > 4)
			cout << "Invaild number, please enter a number in the range of 1 ~ 4" << endl;
		cout << "========================================================================" << endl;
	}
	cout << "Exit Program" << endl;
	system("pause");

	return 0;
}