#include <iostream>
using namespace std;

class member {
protected:
	string name;
	int run;
	int jump;
	bool eliminated;
	int completed;
public:
	virtual void runn() {
		cout << "run" << endl;
		run = true;
	}
	virtual void jumpp() {
		cout << "jump" << endl;
		jump = true;
	}
	member(string n) :eliminated(false), completed(0), name(n) {}
	int getrun() {
		return run;
	}
	int getjump() {
		return jump;
	}
	string getname() {
		return name;
	}
	int getcompleted() {
		return completed;
	}
	bool geteliminated() {
		return eliminated;
	}
	void setcompleted(int v) {
		completed = v;
	}
	void setrun(int r) {
		run = r;
	}
	void setjump(int r) {
		jump = r;
	}
	void seteliminated(bool e) {
		eliminated = e;
	}
};

class human :public member {
public:
	human(string n) :member(n) {}
};

class cat :public member {
public:
	cat(string n) :member(n) {}
};

class robot :public member {
public:
	robot(string n) :member(n) {}
};

class impediment {
protected:
	int value;
public:
	impediment(int v) :value(v) {}
	virtual bool completed(member** begin, member** end) = 0;
};

class wall :public impediment {
public:
	wall(int v) : impediment(v) {}
	bool completed(member** begin, member** end) {
		for (member** start = begin; start != end;start++)
		{
			if ((*start)->geteliminated() == false) {
				int a;
				cout << "enter jump value: ";
				cin >> a;
				(*start)->setjump(a);
				if (value >= (*start)->getjump()) {
					cout << "member: " << (*start)->getname() << "\tgot eliminated at wall at the distance: " << (*start)->getjump() << "completions: " << (*start)->getcompleted() << endl;
					(*start)->seteliminated(true);
					return false;
				}
				cout << "member: " << (*start)->getname() << "\thas completed the wall: " << (*start)->getjump() << endl;
				int saver = (*start)->getcompleted();
				(*start)->setcompleted(++saver);
				return true;
			}
			return false;
		}

	}
};

class path :public impediment {
public:
	path(int v) : impediment(v) {}
	bool completed(member** begin, member** end) {
		for (member** start = begin; start != end;start++)
		{
			if ((*start)->geteliminated() == false) {
				int a;
				cout << "enter run value: ";
				cin >> a;
				(*start)->setrun(a);
				if (value >= (*start)->getrun()) {
					cout << "member: " << (*start)->getname() << "\tgot eliminated at path at the distance: " << (*start)->getrun() << "completions: " << (*start)->getcompleted() << endl;
					(*start)->seteliminated(true);
					return false;
				}
				cout << "member: " << (*start)->getname() << "\thas completed the path: " << (*start)->getrun() << endl;
				int saver = (*start)->getcompleted();
				(*start)->setcompleted(++saver);
				return true;
			}
			return false;
		}
	}
};

class client {
	member** marr;
	impediment** iarr;
public:
	client(member** m, impediment** i) :marr(m), iarr(i) {}
};


int main() {
	member* arr[3];
	arr[0] = new human("name");
	arr[1] = new cat("name1");
	arr[2] = new robot("name2");
	impediment* arr1[2];
	arr1[0] = new wall(100);
	arr1[1] = new path(100);
	client a(arr, arr1);
	for (impediment** start = arr1;start != arr1 + 2;start++)
	{
		for (member** start1 = arr; start1 != arr + 3;start1++)
		{
			(*start)->completed(start1, start1 + 3);
		}
	}
}