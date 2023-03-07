#define CHECK
#define ADD
#define OUTD
#include <iostream>
#include "wj.h"

using namespace std;

int main(){
	cout << "Enter file name (to construct wj1):" << endl;
	char a[200];
	cin >> a;
	weatherJournal wj1(a);   

#ifdef CHECK
#ifdef ADD

	weatherJournal wjsep("september.csv");
	weatherJournal wj3(wjsep);
	weatherJournal wj4 = wjsep;
	weatherJournal wj2020("2020.csv");
	
	//== and !=_______________________________________________
	cout << "Checking equality (wj1 and september 2021): ";
	if(wj1 == wjsep) cout << "equal" << endl;
	else cout<< "not equal" << endl;

	std::cout<< "_______________________________________________" << std::endl;

	//= and copy_______________________________
	std::cout << "Checking copy and =" << std::endl;
	if(wj3 == wjsep) std::cout << "wj3(wjsep) = wjsep - OK" << std::endl;
	else std::cout << "wj3(wjsep) != wjsep - error" << std::endl;
	
	if(wj4==wjsep) std::cout<< "wj4 = wjsep - OK" << std::endl;
	else std::cout << "wj4 != wjsep - error" << std::endl;

#ifdef OUTD

	std::cout<< "_______________________________________________" << std::endl;	
	//+ +=, cout and from data to data
	std::cout<< "CHECKING + +=" << std::endl;
	weatherJournal wj6 = wj2020+wjsep;
	std::cout << "wj2020 + wjsep" << std::endl;
	std::cout << wj6;

	int start_day, start_month, start_year;
	std::cout<< "from data to data:" << std::endl;
	std::cout<< "Start(dd mm yyyy): "<< std::endl;
	std::cin >> start_day >> start_month >> start_year;
	//std::cout << start_day << start_month << start_year << std::endl;
	int finish_day, finish_month, finish_year;	
	std::cout<< "Finish(dd mm yyyy): "<< std::endl;
	std::cin >> finish_day >> finish_month >> finish_year;
	
	outdtd(std::cout, wj6, start_day, start_month, start_year, finish_day, finish_month, finish_year);

#endif //OUTD

	cout<< "____________________________________________________" << endl;

#endif //ADD

	cout<< "operator()________________________________" << endl;
	cout<<wjsep;
	wjsep(2021, 10, 1) = 5.4;
	wjsep(2021, 8, 31) = 10;
	
	cout<< "ADDING 1.10.2021, 31.8.2021:_____________________________________" << endl;
	cout<< wjsep;

	cout<< "DELETE_OPERATOR____________________________________________________" <<endl;
	//DELETE_________________________________________________________________________
	wjsep.delete_temp(2021, 9, 30);
	wjsep.delete_temp(2021, 9, 15);
	wjsep.delete_temp(2021, 9, 1);
	
	wjsep(2021, 9, 15) = -30;
	
	cout << wjsep << "deleted and added 2021.09.15" << endl;

	cout << "Testing missing date (2.2.2020 is not september):" << endl;
	wjsep.delete_temp(2020, 2 , 2);

#endif // CHECK
	return 0;
}

