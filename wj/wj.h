class weatherJournal{
	private:
		int size;    //number of days
		int * date;  //   format: 20211011
		double * temp;
	public:

		// constructors-----------------------
		weatherJournal(){
			date = new int[1];
			temp = new double[1];
			size = 0;
		}
		weatherJournal(const char* n);
		weatherJournal(const weatherJournal& other);
		weatherJournal(int size2, int* date2, double* temp2);
		//---------------------------------------
		int getdate(int i){
			if(i<size){
				return date[i];
			}
			return 0;
		}
		double gettemp(int i){
			if(i<size){
				return temp[i];
			}
			return 0;
		}
		int getsize(){
			return size;
		}
		//------------------------------------
		weatherJournal& operator=(const weatherJournal& other);
		weatherJournal& operator=(double temperature);
		weatherJournal operator+(const weatherJournal& other) const;
		weatherJournal& operator+=(const weatherJournal& other);
		bool operator==(const weatherJournal& other) const;
		bool operator!=(const weatherJournal& other) const;
		//add_new_element
		weatherJournal& operator()(int year, int month, int day);
		//delete element
		void delete_temp(int year, int month, int day);
		//out and from data to data
		friend std::ostream& operator<<(std::ostream& out, const weatherJournal& wj);
		friend std::ostream& outdtd(std::ostream& out, const weatherJournal& wj, int start_day, int start_month, int start_year, int finish_day, int finish_month, int finish_year);
		
		// destruct (not empty)--------------
		~weatherJournal();
};
