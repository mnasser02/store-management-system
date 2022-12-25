#include <iostream>
#include <string>
#include <fstream>
#include "Customer.h"
#include "User.h"


const std::string DEALER_PASSWORD = "abc123";
const std::string EMPLOYEE_PASSWORD = "ab12";

void invalid_input() {
	std::cin.clear();
	std::cin.ignore(100, '\n');
	std::cout << std::endl << "invalid input!" << std::endl;
}
void edit_product(const User &curr_user) {
	std::string name;
	std::cout << "Number of product to edit: ";
	int p;
	std::cin >> p;
	if (!std::cin) {
		invalid_input();
		return;
	}
	if (p < 1 || p > User::products_number()) {
		std::cout << "product not found" << std::endl;
		return;
	}
	std::cout << "1. Increase quantity" << std::endl
		<< "2. Decrease quantity" << std::endl
		<< "3. Change price" << std::endl
		<< "(1/2/3): ";
	int edit_choice, change;
	std::cin >> edit_choice;
	if (!std::cin) {
		invalid_input();
		return;
	}
	if (edit_choice == 1) {
		std::cout << "increase by: ";
		std::cin >> change;
	}
	else if (edit_choice == 2) {
		std::cout << "decrease by: ";
		std::cin >> change;
	}
	else if (edit_choice == 3) {
		std::cout << "new price: ";
		std::cin >> change;
	}
	else {
		return;
	}
	if (!std::cin || change < 0) {
		invalid_input();
		return;
	}
	curr_user.edit_product("products.txt", p, edit_choice, change);
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
	
	while (true) {
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(100, '\n');
		}
		std::cout << "Choose Your Role: " << std::endl
			<< "1. Dealer" << std::endl
			<< "2. Employee" << std::endl
			<< "3. Customer" << std::endl
			<< "(1/2/3): ";
		std::cin >> choice;
		std::cout << std::endl;
		User::set_products_number("products.txt");
		if (choice == 1) {
			std::string password;
			do {
				std::cout << "Dealer's Password: ";
				std::cin >> password;
				std::cout << std::endl;
			} while (password != DEALER_PASSWORD);
			User curr_user(email, password, "dealer", username);
			std::cout << "Welcome to your store, " << curr_user.username() << std::endl << std::endl;
			std::cout << "Available Actions: " << std::endl;
			while (true) {
				if (!std::cin) {
					std::cin.clear();
					std::cin.ignore(100, '\n');
				}
				std::cout << "1. Display available products" << std::endl
					<< "2. Add a product" << std::endl
					<< "3. Edit a product" << std::endl
					<< "4. Remove a product" << std::endl
					<< "5. Exit" << std::endl
					<< "(1/2/3/4/5): ";
				int dealer_choice = 0;
				std::cin >> dealer_choice;
				std::cout << std::endl;
				std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
				if (dealer_choice == 1) {
					curr_user.view_products("products.txt");
				}
				else if (dealer_choice == 2) {
					std::string name;
					int price, quantity;
					std::cout << "Name of product: ";
					std::cin.ignore();
					getline(std::cin, name);
					if (name == "") {
						invalid_input();
						std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
						continue;
					}
					std::cout << "Price of product: ";
					std::cin >> price;
					if (!std::cin || price < 0) {
						invalid_input();
						std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
						continue;
					}
					std::cout << "Quantity of product: ";
					std::cin >> quantity;
					if (!std::cin || quantity < 0) {
						invalid_input();
						std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
						continue;
					}
					Product product(name, price, quantity);
					curr_user.add_product("products.txt", product);
				}
				else if (dealer_choice == 3) {
					edit_product(curr_user);
				}
				else if (dealer_choice == 4) {
					std::string name;
					std::cout << "Number of product to remove: ";
					int p;
					std::cin >> p;
					if (!std::cin || p < 1) {
						invalid_input();
						continue;
					}
					curr_user.remove_product("products.txt", p);
				}
				else if (dealer_choice == 5) {
					std::cout << "exiting...";
					return 0;
				}
				else {
					std::cout << "invalid choice" << std::endl;
				}
				std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
			}
		}
		else if (choice == 2) {
			std::string password;
			do {
				std::cout << "Employee's Password: ";
				std::cin >> password;
				std::cout << std::endl;
			} while (password != EMPLOYEE_PASSWORD);
			User curr_user(email, password, "employee", username);
			std::cout << curr_user.username() << " started his work hours" << std::endl << std::endl;
			std::cout << "Available Actions: " << std::endl;
			while (true) {
				if (!std::cin) {
					std::cin.clear();
					std::cin.ignore(100, '\n');
				}
				std::cout << "1. Display available products" << std::endl
					<< "2. Edit a product" << std::endl
					<< "3. Exit" << std::endl
					<< "(1/2/3): ";
				int employee_choice = 0;
				std::cin >> employee_choice;
				std::cout << std::endl;
				std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
				if (employee_choice == 1) {
					curr_user.view_products("products.txt");
				}
				else if (employee_choice == 2) {
					edit_product(curr_user);
				}
				else if (employee_choice == 3) {
					std::cout << "exiting...";
					return 0;
				}
				else {
					std::cout << "invalid choice" << std::endl;
				}
				std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
			}
		}
		else if (choice == 3) {
			User curr_user(email, password, "customer", username);
			Customer curr_customer(curr_user);
			std::cout << "Welcome to our lovely store, " << curr_customer.username() << "!" << std::endl << std::endl;
			std::cout << "Available Actions: " << std::endl;
			while (true) {
				if (!std::cin) {
					std::cin.clear();
					std::cin.ignore(100, '\n');
				}
				std::cout << "1. Display available products" << std::endl
					<< "2. Purchase a product" << std::endl
					<< "3. View cart" << std::endl
					<< "4. Remove from cart" << std::endl
					<< "5. Exit" << std::endl
					<< "(1/2/3/4/5): ";
				int customer_choice = 0;
				std::cin >> customer_choice;
				std::cout << std::endl;
				std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl;
				if (customer_choice == 1) {
					curr_customer.view_products("products.txt");
				}
				else if (customer_choice == 2) {
					std::string name;
					std::cout << "Number of product to purchase: ";
					int p;
					std::cin >> p;
					if (!std::cin || p < 1) {
						invalid_input();
						std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
						continue;
					}
					curr_customer.add_to_cart("products.txt", p);
				}
				else if (customer_choice == 3) {
					curr_customer.view_cart();
				}
				else if (customer_choice == 4) {
					std::cout << "Number of product(as viewed by the cart) to remove from cart: ";
					int i;
					std::cin >> i;
					if (!std::cin || i < 1) {
						invalid_input();
						std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
						continue;
					}
					std::cout << "quantity to remove: ";
					int q;
					std::cin >> q;
					if (!std::cin || q < 1) {
						invalid_input();
						std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
						continue;
					}
					curr_customer.remove_from_cart("products.txt", i, q);
				}
				else if (customer_choice == 5) {
					std::cout << "exiting...";
					return 0;
				}
				else {
					std::cout << "invalid choice" << std::endl;
				}
				std::cout << "+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-" << std::endl << std::endl;
			}
		}
		else {
			std::cout << "invalid choice" << std::endl << std::endl;
		}
	}
	return 0;
}