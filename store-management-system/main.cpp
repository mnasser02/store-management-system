#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Store.h"
#include "Customer.h"
#include "Employee.h"
#include "Dealer.h"
#include "User.h"
#include <algorithm>

const std::string DEALER_PASSWORD = "abc123";
const std::string EMPLOYEE_PASSWORD = "ab12";

std::string read_product_name() {
	std::string name;
	std::cin.ignore();
	std::getline(std::cin, name);
	name.erase(name.find_last_not_of(" \n\r\t") + 1);//right trim white characters
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	return name;
}

int main() {
	int choice = 0;
	std::string username = "", email = "", password = "";

	std::cout << "Create Account: " << std::endl;
	std::cout << "Username: ";
	std::cin >> username;
	do {
		std::cout << "Email: ";
		std::cin >> email;
	} while (!User::is_email_valid(email));
	do {
		std::cout << "Password: ";
		std::cin >> password;
	} while (!User::is_password_valid(password));
	
	User curr_user(email, password, username);
	std::cout << "Choose Your Role: " << std::endl
		<< "1. Dealer" << std::endl
		<< "2. Employee" << std::endl
		<< "3. Customer" << std::endl
		<< "(1/2/3): ";
	std::cin >> choice;

	std::ifstream fin("./products.txt");
	std::vector<Product> products;
	while (fin.peek() != EOF) {
		std::string tmp[3];
		for (int i = 0; i < 3; i++) {
			std::getline(fin, tmp[i]);
		}
		std::string name = tmp[0];
		int price = stoi(tmp[1]), quantity = stoi(tmp[2]);
		products.push_back(Product(name, price, quantity));
	}
	
	Store tech_store("Nasser's Computers and Electronics", products);
	//tech_store.display();
	if (choice == 1) {
		std::string password;
		do {
			std::cout << "Dealer's Password: " << std::endl; 
			std::cin >> password;
		} while (password != DEALER_PASSWORD);

		Dealer mahdi_dealer(curr_user, "12-11-2010", 550);
		std::cout << "Welcome to your store, " << mahdi_dealer.username() << std::endl;
		std::cout << "Available Actions: " << std::endl;
		while (true) {
			std::cout << "1. Add a product" << std::endl
				<< "2. Remove a product" << std::endl
				<< "3. Edit a product" << std::endl
				<< "4. Display all products" << std::endl
				<< "5. Exit" << std::endl
				<< "(1/2/3/4/5): ";
			int dealer_choice = 0;
			std::cin >> dealer_choice;
			if (dealer_choice == 1) {
				std::string name;
				int price, quantity;
				std::cout << "Name of product: ";
				name = read_product_name();
				std::cout << "Price of product: ";
				std::cin >> price;
				std::cout << "Quantity of product: ";
				std::cin >> quantity;
				Product product(name, price, quantity);
				tech_store.add_product(product);
			}
			else if (dealer_choice == 2) {
				std::string name;
				std::cout << "Name of product to remove: ";
				name = read_product_name();
				tech_store.remove_product(Product(name));
			}
			else if (dealer_choice == 3) {
				std::string name;
				std::cout << "Name of product to edit: ";
				name = read_product_name();
				tech_store.edit_product(name);
			}
			else if (dealer_choice == 4) {
				tech_store.display();
			}
			else if (dealer_choice == 5) {
				return 0;
			}
			std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
			std::cout << std::endl;
		}
	}
	else if (choice == 2) {
		std::string password;
		do {
			std::cout << "Employee's Password: " << std::endl;
			std::cin >> password;
		} while (password != EMPLOYEE_PASSWORD);

		Employee mahdi_employee(curr_user, 40, "10-10-2017", "71/453692");
		std::cout << mahdi_employee.username() << " started his work hours" << std::endl;
		std::cout << "Available Actions: " << std::endl;
		while (true) {
			std::cout << "1. Edit a product" << std::endl
				<< "2. Display all products" << std::endl
				<< "3. Exit" << std::endl
				<< "(1/2/3): ";
			int employee_choice = 0;
			std::cin >> employee_choice;
			if (employee_choice == 1) {
				std::string name;
				std::cout << "Name of product to edit: ";
				name = read_product_name();
				tech_store.edit_product(name);
			}
			else if (employee_choice == 2) {
				tech_store.display();
			}
			else if (employee_choice == 3) {
				return 0;
			}
			std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
			std::cout << std::endl;
		}
	}
	else if (choice == 3) {
		Customer mahdi_customer(curr_user);
		std::cout << "Welcome to our lovely store, " << mahdi_customer.username() << "!" << std::endl;
		std::cout << "Available Actions: " << std::endl;
		while (true) {
			std::cout << "1. Purchase a product" << std::endl
				<< "2. View cart" << std::endl
				<< "3. Display available products" << std::endl
				<< "4. Exit" << std::endl
				<< "(1/2/3/4): ";
			int customer_choice = 0;
			std::cin >> customer_choice;
			if (customer_choice == 1) {
				std::string name;
				std::cout << "Name of product to purchase: ";
				name = read_product_name();
				bool exists = tech_store.store_contains(Product(name));
				if (exists) {
					Product product_purchased = tech_store.get_product(name);
					mahdi_customer.add_product(product_purchased);
					std::cout << "product addeed to card" << std::endl
						<< "new bill: " << mahdi_customer.bill() << std::endl;
				}
				else {
					std::cout << "product not available" << std::endl;
				}
			}
			else if (customer_choice == 2) {
				Store cart("", mahdi_customer.cart());
				cart.customer_display();
				std::cout << "===========" << std::endl
					<< "Total: " << mahdi_customer.bill() << std::endl
					<< "===========" << std::endl;
			}
			else if (customer_choice == 3) {
				tech_store.customer_display();
			}
			else if (customer_choice == 4) {
				return 0;
			}
			std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
			std::cout << std::endl;
		}
	}
	return 0;
}