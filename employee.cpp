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

void Employee::display(std::ostream & os) const
{
	os << "\nid: " << id << "\nname: " << name << "\naddress: " << address << "\ncity: " << city<<
		"\nstate: " << state << "\ncountry: " << country << "\nphone: " << phone << "\nsalary: " <<salary;
}

void Employee::write(std::ostream & os) const
{
	EmployeeRec outbuf;
	outbuf.id = id;
	outbuf.salary = salary;
	strncpy(outbuf.name, name.c_str(), 30)[30] = '\0';	//n-1 chars 11th position = terminating char
	strncpy(outbuf.address, address.c_str(), 25)[25] = '\0';
	strncpy(outbuf.city, city.c_str(), 20)[20] = '\0';
	strncpy(outbuf.state, state.c_str(), 20)[20] = '\0';
	strncpy(outbuf.country, country.c_str(), 20)[20] = '\0';
	strncpy(outbuf.phone, phone.c_str(), 20)[20] = '\0';
	
	os.write(reinterpret_cast<const char*>(&outbuf), sizeof outbuf);	//give address and how many need to be transferred to file

}

void Employee::store(std::iostream &ios) const
{
	EmployeeRec outbuf;
	outbuf.id = id;
	outbuf.salary = salary;
	strncpy(outbuf.name, name.c_str(), 30)[30] = '\0';	//n-1 chars 11th position = terminating char
	strncpy(outbuf.address, address.c_str(), 25)[25] = '\0';
	strncpy(outbuf.city, city.c_str(), 20)[20] = '\0';
	strncpy(outbuf.state, state.c_str(), 20)[20] = '\0';
	strncpy(outbuf.country, country.c_str(), 20)[20] = '\0';
	strncpy(outbuf.phone, phone.c_str(), 20)[20] = '\0';

	ios.write(reinterpret_cast<const char*>(&outbuf), sizeof outbuf);	//give address and how many need to be transferred to file

}

void Employee::toXML(std::ostream &os) const
{
	os << "<Employee>\n" << "\t<id>" << id << "</id>\n" << "\t<name>" << name << "</name>\n" << "\t<address>" << address << "</address>\n" <<
		"\t<city>" << city << "</city>\n" << "\t<state>" << state << "</state>\n" << "\t<country>" << country << "</country>\n" << "\t<salary>" <<
		salary << "</salary>\n" << "</Employee>\n";

}

Employee * Employee::read(std::istream &is)
{
	
	EmployeeRec inbuf;
	is.read(reinterpret_cast<char*>(&inbuf), sizeof inbuf);
	Employee* emp = new Employee();
	if (is) {
		emp->id = inbuf.id;
		emp->name = inbuf.name;
		emp->address = inbuf.address;
		emp->city = inbuf.city;
		emp->state = inbuf.state;
		emp->salary = inbuf.salary;
		emp->country = inbuf.country;
		emp->phone = inbuf.phone;
	}
	else
	{
		return nullptr;
	}
	return emp;
}

Employee * Employee::retrieve(std::istream &is, int search)
{
	while (is)
	{
		is.clear();
		EmployeeRec inbuf;
		is.read(reinterpret_cast<char*>(&inbuf), sizeof inbuf);
		Employee* emp = new Employee();
		if (is) {
			emp->id = inbuf.id;
			emp->name = inbuf.name;
			emp->address = inbuf.address;
			emp->city = inbuf.city;
			emp->state = inbuf.state;
			emp->salary = inbuf.salary;
			emp->country = inbuf.country;
			emp->phone = inbuf.phone;
		}
		if (emp->id == search)
		{
			return emp;
		}
	}
		
}

Employee * Employee::fromXML(std::istream & is)
{
	std::string input;
	EmployeeRec empbuf;
	while (is >> input)
	{
		if (input == "<Employee>")
		{
			empbuf.hasEmploy = true;
		}
		if (input == "/id>")
		{
			empbuf.hasIdEND = true;
		}
		if (input == "/name>")
		{
			empbuf.hasNameEND = true;
		}
		if (input == "/address>")
		{
			empbuf.hasAddEND = true;
		}
		if (input == "/city>")
		{
			empbuf.hasCityEND = true;
		}
		if (input == "/state>")
		{
			empbuf.hasStateEND = true;
		}
		if (input == "/country>")
		{
			empbuf.hasCountryEND = true;
		}
		if (input == "/phone>")
		{
			empbuf.hasPhoneEND = true;
		}
		if (input == "/salary>")
		{
			empbuf.hasSalEND = true;
		}
	/*	if (input != "<Employee>" && input != "/id>" && input != "/name>" && input != "/address>" && input != "/city>" &&
			input != "/state>" && input != "/country>" && input != "/phone>" && input != "/salary>")
		{
			is.setstate(std::ios::failbit);
			try {
				throw std::runtime_error("Invalid file!");
			}
			catch (std::exception &e) {
				std::cout << "Invalid file! " << e.what() << "\n";
			}
			return 0;
			
		}*/
		std::getline(is, input, '<');
		std::getline(is, input, '>');
		if (input == "/Employee")
		{
			empbuf.hasEmployEND = true;
		}

		if (input == "id")
		{
			empbuf.hasId = true;
			std::getline(is, input, '<');
			empbuf.id = stoi(input);
			
		}
		if (input == "name")
		{
			empbuf.hasName = true;
			std::getline(is, input, '<');
			strcpy(empbuf.name, input.c_str());
		}
		if (input == "salary")
		{
			empbuf.hasSal = true;
			std::getline(is, input, '<');
			empbuf.salary = stod(input);
		}
		if (input == "address")
		{
			empbuf.hasAdd = true;
			std::getline(is, input, '<');
			strcpy(empbuf.address, input.c_str());
		}
		if (input == "city")
		{
			empbuf.hasName = true;
			std::getline(is, input, '<');
			strcpy(empbuf.city, input.c_str());
		}
		if (input == "state")
		{
			empbuf.hasName = true;
			std::getline(is, input, '<');
			strcpy(empbuf.state, input.c_str());
		}
		if (input == "country")
		{
			empbuf.hasName = true;
			std::getline(is, input, '<');
			strcpy(empbuf.country, input.c_str());
		}
		if (input == "phone")
		{
			empbuf.hasName = true;
			std::getline(is, input, '<');
			strcpy(empbuf.phone, input.c_str());
		}
		if (empbuf.hasEmploy == true && empbuf.hasEmployEND == true)
		{
			empbuf.isReady = true;
			break;
		}
		/*if ((empbuf.hasName == false && empbuf.hasNameEND == false) || (empbuf.hasCity == true && empbuf.hasCityEND==false)||(empbuf.hasEmploy == true && empbuf.hasEmployEND == false)||
			(empbuf.hasEmploy == false && empbuf.hasEmployEND == false))
		{
			is.setstate(std::ios::failbit);
			try {
				throw std::runtime_error("Invalid file!");
			}
			catch (std::exception &e) {
				std::cout << "Invalid file! " << e.what() << "\n";
			}
			return 0;
		}*/
	}
	if (input == "")
	{
		return nullptr;
	}
	
	Employee* emp = new Employee();
	if (empbuf.isReady = true) {
		emp->id = empbuf.id;
		emp->name = empbuf.name;
		emp->address = empbuf.address;
		emp->city = empbuf.city;
		emp->state = empbuf.state;
		emp->country = empbuf.country;
		emp->phone = empbuf.phone;
		emp->salary = empbuf.salary;
	}
	return emp;

}

Employee::Employee(int id, const std::string & name="", const std::string & address="", const std::string & city = "",
	const std::string & state = "", const std::string & country = "", const std::string & phone = "", double salary=0.0) : name(name)
{
	this->id = id;
	this->salary = salary;
}

Employee::~Employee()
{
}