#include <cstring>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <stdexcept>
#include "employee.h"
#include <vector>
#include <memory>
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


using namespace std;
int main(int argc, char* argv[])
{
	ifstream instr(argv[1]);	//file 1 is good
	vector<unique_ptr<Employee> > v;
	try
	{
		Employee* p;
		while ((p = Employee::fromXML(instr)) != nullptr)
		{
			v.push_back(unique_ptr<Employee>(p));
		}

	}
	catch (exception& e) {
		cout << e.what() << endl;
	}
	instr.close();

	//for(const auto p:v)
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i]->display(cout);
		cout << endl;
	}
	fstream ofs{ "employee.bin", ios::out | ios::in | ios::binary | ios::trunc };
	for (const auto& x : v)
		x->write(ofs);

	ofs.flush();
	v.clear();
	ofs.clear();
	ofs.seekg(0, ios::beg);
	Employee* ptr;
	while ((ptr = Employee::read(ofs)) != nullptr)
	{
		v.push_back(unique_ptr<Employee>(ptr));
	}
	for (size_t i = 0; i < v.size(); ++i)
	{
		v[i]->toXML(cout);
		cout << endl;

		ofs.clear();
		ofs.seekg(0, ios::beg);
		int find = 12345;

		//if (!(std::ios::failbit))
		{
			while ((ptr = Employee::retrieve(ofs, find)) != nullptr)
			{
				cout << "Found";
				ptr->display(cout);
				cout << endl;
				ptr->salary = 150000;
				ptr->store(ofs);
				ofs.flush();
				ptr->display(cout);

			}
			ofs.clear();
			ofs.seekg(0, ios::beg);
			Employee* john = new Employee();
			if (john)
			{
				john->id = 1;
				john->salary = 15000;
				john->name = "John Higginson";
				john->address = "123 Street";
				john->city = "Provo";
				john->state = "UT";
				john->country = "USA";
				john->phone = "555-555-5555";
			}
			john->store(ofs);
			int user = 1;
			ofs.clear();
			ofs.seekg(0, ios::beg);
			while ((ptr = Employee::retrieve(ofs, user)) != nullptr)
			{
				ptr->display(cout);
				cout << endl;
			}
		}
		cin.get();

	}
}