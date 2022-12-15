#pragma once
#include <string>
#include <unordered_set>

class Product
{
private:
	int idx_;
	std::string name_;
	int price_, quantity_;
public:
	Product(const std::string&, const int& price = 0, const int& quantity = 0, const int& id = -1);

	//getters
	int index() const;
	std::string name() const;
	int price() const;
	int quantity() const;
	//setters
	void set_index(int&);
	void set_name(const std::string&);
	void set_price(const int&);
	void set_quantity(const int&);

	void increase_quantity(const int&);
	void decrease_quantity(const int&);
	void display() const;
	void customer_display() const;
};

