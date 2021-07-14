#include <string>

enum class Currency {
	EUR,
	YEN,
	USD
};

struct MonetaryValue {
	int value;
	Currency currency;
};

struct Employee {
	// employee data
};

class EmployeePaymentCalculator {
public:
	// Accounting
	MonetaryValue calculatePay();
};

class EmployeeReportGenerator {
public:
	// HR
	std::string generateReport();
};

class EmployeeRepository {
public:
	// DB Admin
	void saveToDb(Employee emp);
	static Employee findById(int id);
};

class DieselEngine {
	void start();
};

class PetrolEngine {
	void start();
};

template <typename Engine>
class Car : private Engine {
	void start() {
		Engine::start();
	}
};

