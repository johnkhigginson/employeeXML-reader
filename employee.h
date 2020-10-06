#include <string>
#include <iostream>
#include <limits>
#include <vector>


class Employee
{

	struct EmployeeRec
	{
		int id;
		char name[31];
		char address[26]{};
		char city[21]{};
		char state[21]{};
		char country[21]{};
		char phone[21]{};
		double salary = 0.0;

		bool hasEmploy = false;
		bool hasEmployEND = false;
		bool hasId = false;
		bool hasIdEND = false;
		bool hasName = false;
		bool hasNameEND = false;
		bool hasAdd = false;
		bool hasAddEND = false;
		bool hasCity = false;
		bool hasCityEND = false;
		bool hasState = false;
		bool hasStateEND = false;
		bool hasCountry = false;
		bool hasCountryEND = false;
		bool hasPhone = false;
		bool hasPhoneEND = false;
		bool hasSal = false;
		bool hasSalEND = false;
		bool isReady = false;
	};
public:
	void display(std::ostream&) const;  // Write a readableEmployee representation to a stream
	void write(std::ostream&) const;    // Write a fixed-length record to current file position
	void store(std::iostream&) const;   // Overwrite (or append) record in (to) file
	void toXML(std::ostream&) const;    // Write XML record for Employee
	static Employee* read(std::istream&);   // Read record from current file position
	static Employee* retrieve(std::istream&, int); // Search file for record by id
	static Employee* fromXML(std::istream&);      // Read the XML record from a stream
	Employee() = default;

	Employee(int id, const std::string& name, const std::string& address, const std::string& city,
		const std::string& state, const std::string& country, const std::string& phone, double salary);

	~Employee();

	int id = 0;
	std::string name, address, city, state, country, phone;
	double salary = 0;


};
