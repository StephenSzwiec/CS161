#include "KString.h"
using namespace std; 

int main()
{
	KString k1("Scott");
	KString k2;
	KString k3; 
	k2 = "Cast";
	k3 = k1 + k2; 
	cout << k3[6] << endl;
	k3[6] = 'K';
	cout << "Enter your name";
	cin >> k2;
	if (k1 == k2) {
		cout << "Same name" << endl;
	}
	if (k1 < k2) {
		cout << "First name less than" << endl;
	}
	if (k1 > k2) {
		cout << "First name greater than" << endl;
	}
	cout << k2 << " have a great day!" << endl;
	if (k1 == "Scott") {
		cout << "Nice Name" << endl;
	}
	cout << k1.getLength() << endl;
	
}
