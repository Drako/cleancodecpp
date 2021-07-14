#include <string>

class MonetaryValue;

class Employee {
public:
	MonetaryValue calculatePay();
	void saveToDb();
	std::string generateReport();
};
