#pragma once
#include <string>

class Product
{
private:
	std::string name_;
	int price_, quantity_;
public:
	Product(const std::string&, int price = 0, int quantity = 0);

	std::string name() const;
	int price() const;
	int quantity() const;
	
	void set_name(const std::string&);
	void set_price(int);
	void set_quantity(int);

	void increase_quantity(int);
	void decrease_quantity(int);
	void display() const;
	void cart_display() const;
};

