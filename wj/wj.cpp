#include <iostream>
#include "wj.h"
#include <string>
#include <fstream>
#include <stdio.h>

using namespace std;

//construct____________________________________________________

weatherJournal::weatherJournal(const char* n){
	ifstream f(n);
	int cnt = -7;
	if(!f){
		cerr << "NOT OPENED" << endl;
		exit(1);
	}
	while(f){
		string str;
		getline(f, str);
//		cout<<str<<endl;
		cnt++;
	}
	f.close();
	size = cnt/8;
	date = new int[size+1];
	temp = new double[size+1];
	int day, month, year;

	ifstream g(n);
	if(!g){
		cerr << "NOT OPENED" << endl;
		exit(1);
	}
	cnt = 0;
	char s;
	while(g){
		string str;
		getline(g, str);
		//cout << str << endl;
		if(cnt>=8 && cnt%8 == 0){
			sscanf(str.c_str(), "%c%d.%d.%d %c%c:%c%c%c;%c%lf%c", &s, &day, &month, &year, &s, &s, &s, &s, &s, &s, &(temp[size-(cnt/8)]), &s);
			date[size-(cnt/8)] = year*10000 + month*100 + day;
		}
		cnt++;
	}
	g.close();
/*	int i;
	for(i=0;i<size;i++){
		cout<< date[i] << "  " << temp[i] <<endl;
	}
	cout<< size <<endl;
*/
}


//construct_copy_______________________________________________OK
weatherJournal::weatherJournal(const weatherJournal& other){
	int i;
	size = other.size;
	date = new int[size+1];
	temp = new double[size+1];
	for(i=0; i<size; i++){
		date[i] = other.date[i];
	}
	for(i=0; i<size; i++){
		temp[i] = other.temp[i];
	}
}
//construct for + operator__________________________________________
weatherJournal::weatherJournal(int size2, int* date2, double* temp2){
	size = size2;
	date = date2;
	temp = temp2;
}

//operator=___________________________________________________OK
weatherJournal& weatherJournal::operator=(const weatherJournal& other){
	if(date) delete[] date;
	if(temp) delete[] temp;
	date = nullptr;
	temp = nullptr;
	size = other.size;
	int i;
	if(other.date){
		date = new int[size + 1];
		for(i=0; i<size; i++){
			date[i] = other.date[i];
		}
	}
	if(other.temp){
		temp = new double[size + 1];
		for(i=0; i<size; i++){
			temp[i] = other.temp[i];
		}
	}
	return *this;
}

// = for weatherJournal(year, month, day) = temperature
weatherJournal& weatherJournal::operator=(double temperature){
	int i, k=0;
	int d=0;
	double t=0;
	if(temperature < -273){
		int * date1 = new int[size+1];
		double* temp1 = new double[size+1];
		for(i=0;i<size;i++){
			date1[i] = date[i];
			temp1[i] = temp[i];
		}
		if(date) delete[] date;
		if(temp) delete[] temp;
		date = nullptr;
		temp = nullptr;

		date = new int[size + 1];
		for(i=0; i<size; i++){
			date[i] = date1[i];
		}
		temp = new double[size + 1];
		for(i=0; i<size; i++){
			temp[i] = temp1[i];
		}
		delete []date1;
		delete []temp1;
		return *this;
	} else{
		temp[size] = temperature;
		if(date[size-1]<date[size]){

		}else {
			if(date[0]>date[size]){
				for(i=0;i<size;i++){
					d = date[i];
					date[i] = date[size];
					date[size] = d;
					t = temp[i];
					temp[i] = temp[size];
					temp[size] = t;
				}
			} else{
				int cnt=0;
				for(i=0;i<size-1;i++){
					if(date[size] >date[i] && date[size] < date[i+1] && cnt==0){
						for(k=i+1;k<size;k++){
							d = date[k];
							date[k] = date[size];
							date[size] = d;
							t = temp[k];
							temp[k] = temp[size];
							temp[size] = t;
						}
						cnt = 1;
					}
				}
			}
		}
		size+=1;
		return *this;
	}
}

//operator==___________________________________________________OK
bool weatherJournal::operator==(const weatherJournal& other) const{
	int i=0;
	if(size == other.size && date[0] == other.date[0] && date[size-1] == other.date[other.size-1]){
		for(i=0; i < size; i++){
			if(temp[i] > other.temp[i] || temp[i] < other.temp[i]) return false;
		}
		return true;
	}
	return false;
//		cout<<"Different beginning!"<<endl;
//	std::cout<<"Different sizes!"<<std:endl;
}

//operator!=___________________________________________________OK
bool weatherJournal::operator!=(const weatherJournal& other) const{
	int i=0;
	if(size == other.size && date[0] == other.date[0] && date[size-1] == other.date[size-1]){
		for(i=0; i < size; i++){
			if(temp[i] > other.temp[i] || temp[i] < other.temp[i]) return true;
		}
		return false;
	}
	return true;
}

//operator+___________________________________________________
weatherJournal weatherJournal::operator+(const weatherJournal& other) const{
	int size1 = size+other.size;
	int* date1 = new int[size1+1];
	double* temp1 = new double[size1+1];
	int i;
	if(date[0] < other.date[0]){
		for(i=0;i<size1;i++){
			if(i<size){
				date1[i] = date[i];
				temp1[i] = temp[i];
			}
			else {
				date1[i] = other.date[i-size];
				temp1[i] = other.temp[i-size];
			}
		}
	}
	else {
		for(i=0;i<size1;i++){
			if(i<other.size){
				date1[i] = other.date[i];
				temp1[i] = other.temp[i];
			}
			else {
				date1[i] = date[i-size];
				temp1[i] = temp[i-size];
			}
		}
	}
	return weatherJournal(size1, date1, temp1);
}

//operator+=___________________________________________________
weatherJournal& weatherJournal::operator+=(const weatherJournal& other){
	*this = (*this+other);
	return *this;
}

//add_new_element___________________________________________________
weatherJournal& weatherJournal::operator()(int year, int month, int day){
//no size change here
	int * date1 = new int[size+2];
	double* temp1 = new double[size+2];

	int add_date = year*10000+month*100+day;
	date1[size] = add_date;
	int i;
	for(i=0;i<size;i++){
		date1[i] = date[i];
		temp1[i] = temp[i];
	}
	if(date) delete[] date;
	if(temp) delete[] temp;
	date = nullptr;
	temp = nullptr;

	date = new int[size + 2];
	for(i=0; i<size+1; i++){
		date[i] = date1[i];
	}
	temp = new double[size + 2];
	for(i=0; i<size; i++){
		temp[i] = temp1[i];
	}
	delete [] temp1;
	delete [] date1;
	return *this;
}

//delete_element___________________________________________________
void weatherJournal::delete_temp(int year, int month, int day){
	int i;
	int data = year*10000+month*100+day;
	for(i = 0;i<size;i++){
		if(data == date[i]){
			size -= 1;
			int k;
			for(k=0;k<size;k++){
				if(k>=i){
					date[k] = date[k+1];
					temp[k] = temp[k+1];
				}
			}
			return;
		}
	}
	cout<< "This date is missing" <<endl;
}

//out___________________________________________________
std::ostream& operator<<(std::ostream& out, const weatherJournal& wj){
	int i;
	out<< "date     temperature"<<endl;
	for(i=0;i<wj.size;i++){
		out<< wj.date[i]%100 <<"." << (wj.date[i]%10000)/100 <<"."<< wj.date[i]/10000 << "  " << wj.temp[i] <<endl;
	}
	return out;
}

//out_from_data_to_data___________________________________________________
std::ostream& outdtd(std::ostream& out, const weatherJournal& wj, int start_day,
int start_month, int start_year, int finish_day, int finish_month, int finish_year){
	
	int st_date = start_year*10000+start_month*100+start_day;
	int fn_date = finish_year*10000+finish_month*100+finish_day;
	
	if(st_date < wj.date[0] or fn_date > wj.date[wj.size-1] or st_date > fn_date){
		out<< "INCORRECT START OR FINISH" << endl;
	} else{
		int i;
		out<< "date     temperature"<<endl;
		for(i=0;i<wj.size;i++){
			
			if(wj.date[i] >= st_date && wj.date[i]<=fn_date){
				out<< wj.date[i]%100 <<"." << (wj.date[i]%10000)/100 <<"."<< wj.date[i]/10000 << "  " << wj.temp[i] <<endl;
			}
		}
	}
	return out;
}

//destruct_________________________________________________________
weatherJournal::~weatherJournal(){
	if(date) delete[] date;
	if(temp) delete[] temp;
}
