#include "bank_atm.h"
#include <iostream>

using namespace std;

using namespace BankATM;

int main()
{
	clear_screen();
	cout << "Tip: To test all features, select 'Bank' and log in as an 'admin' user & password '1111' .\n";
	cout << "To test ATM features, select 'ATM' and log in with account number 'a1111' & pin code 'b1111'.\n\n";

	Select_bank_OR_ATM();

	cout << endl;
	return 0;
}
