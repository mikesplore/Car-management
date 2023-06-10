#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <termios.h>
#include <limits>
#include <ctime>
#include <cstdlib>

struct Car {
    std::string model;
    std::string make;
    std::string id;
    int year;
};

std::map<std::string, std::string> users;

void saveUserDetails() {
    std::ofstream outFile("user_details.txt");

    if (outFile.is_open()) {
        for (const auto& user : users) {
            outFile << user.first << " " << user.second << std::endl;
        }
        outFile.close();
    } else {
        std::cout << "Error opening file for writing user details." << std::endl;
    }
}

void loadUserDetails() {
    std::ifstream inFile("user_details.txt");

    if (inFile.is_open()) {
        std::string username, password;
        while (inFile >> username >> password) {
            users[username] = password;
        }
        inFile.close();
    } else {
        std::cout << "No existing user details found." << std::endl;
    }
}

void registerUser() {
    std::string username, password;
    std::cout << "          Enter username: ";
    std::cin >> username;

    if (users.count(username) > 0) {
        std::cout << "          Username already exists. Please choose a different username.\n";
        return;
    }

    std::cout << "          Enter password: ";
    std::cin >> password;

    users[username] = password;
    std::cout << "          Registration successful!\n";

    saveUserDetails();  // Save user details to file
}

std::string getPasswordInput() {
    std::string password;

    struct termios oldSettings, newSettings;
    tcgetattr(fileno(stdin), &oldSettings); // Get the current terminal settings
    newSettings = oldSettings;
    newSettings.c_lflag &= ~(ECHO); // Turn off echoing of characters
    tcsetattr(fileno(stdin), TCSANOW, &newSettings); // Apply new terminal settings

    std::getline(std::cin, password); // Read password without echoing characters

    tcsetattr(fileno(stdin), TCSANOW, &oldSettings); // Restore original terminal settings

    return password;
}

bool loginUser() {
    std::string username, password;
    std::cout << "          Enter username: ";
    std::cin >> username;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Consume the newline character

    loadUserDetails(); // Load user details from file

    if (users.count(username) == 0) {
        std::cout << "          Username not found. Please register first.\n";
        return false;
    }

    std::cout << "          Enter password: ";
    password = getPasswordInput();

    if (users[username] != password) {
        std::cout << "          Incorrect password. Login failed.\n";
        return false;
    }

    std::cout << "          Login successful!\n";
    return true;
}

void registerCar() {
    std::string model, make, id;
    int year;

    // Get car information from the user
    std::cout << "          Enter the car Model: ";
    std::getline(std::cin, model);

    std::cout << "          Enter the car Make: ";
    std::getline(std::cin, make);

    std::cout << "          Enter the car ID: ";
    std::getline(std::cin, id);

    std::cout << "          Enter the Manufacture year: ";
    std::cin >> year;
    std::cin.ignore(); // Ignore the newline character in the input buffer

    // Open the file in append mode
    std::ofstream file("cars.txt", std::ios::app);

    // Check if the file was opened successfully
    if (file.is_open()) {
        // Write car information to the file
        file << model << "          " << make << "          " << id << "       " << year << "\n";
        file.close();

        std::cout << "\n          Car registered successfully!\n";
    } else {
        std::cout << "          Error opening the file. Car registration failed.\n";
    }
}

void viewCar() {
    std::ifstream file("cars.txt");
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }

        file.close();
    } else {
        std::cout << "          Error opening the file. Unable to view registered cars.\n";
    }
}

void deleteCar() {
    std::string id;
    std::vector<Car> cars;

    // Get car ID to delete
    std::cout << "          Enter the car ID to delete: ";
    std::getline(std::cin, id);

    std::ifstream file("cars.txt");

    if (file.is_open()) {
        std::string line;
        bool carFound = false; // Flag to track if the car ID was found

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string model, make, carId;
            int year;
            if (iss >> model >> make >> carId >> year) {
                if (carId != id) {
                    // Car record does not match the ID, add it to the vector
                    Car car;
                    car.model = model;
                    car.make = make;
                    car.id = carId;
                    car.year = year;
                    cars.push_back(car);
                } else {
                    carFound = true; // Car ID found
                }
            }
        }
        file.close();

        if (carFound) {
            std::ofstream outFile("cars.txt", std::ios::trunc); // Open the file in truncation mode

            if (outFile.is_open()) {
                // Write the updated car records to the file
                for (const Car& car : cars) {
                    outFile << car.model << "          " << car.make << "          " << car.id << "       " << car.year << "\n";
                }
                outFile.close();
                std::cout << "\n          Car deleted successfully!\n";
            } else {
                std::cout << "          Error opening the file. Car deletion failed.\n";
            }
        } else {
            std::cout << "\n          Car ID not found. Deletion failed.\n";
        }
    } else {
        std::cout << "          Error opening the file. Car deletion failed.\n";
    }
}



bool isCarIdValid(const std::string& id, const std::vector<Car>& cars) {
    for (const Car& car : cars) {
        if (car.id == id) {
            return true; // Car ID is valid
        }
    }
    return false; // Car ID is not valid
}

void sellCar() {
    std::string id;
    std::vector<Car> cars;

    // Get car ID to sell
    std::cout << "          Enter the car ID to sell: ";
    std::getline(std::cin, id);

    std::ifstream file("cars.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string model, make, carId;
            int year;
            if (iss >> model >> make >> carId >> year) {
                Car car;
                car.model = model;
                car.make = make;
                car.id = carId;
                car.year = year;
                cars.push_back(car);
            }
        }
        file.close();

        if (!isCarIdValid(id, cars)) {
            std::cout << "          Invalid car ID. Car sale failed.\n";
            return;
        }

        std::ofstream soldFile("sold_cars.txt", std::ios::app);
        if (soldFile.is_open()) {
            for (auto it = cars.begin(); it != cars.end(); ++it) {
                if (it->id == id) {
                    soldFile << it->model << "          " << it->make << "          " << it->id << "       " << it->year << "\n";
                    cars.erase(it);
                    break;
                }
            }
            soldFile.close();

            std::ofstream outFile("cars.txt", std::ios::trunc); // Open the file in truncation mode
            if (outFile.is_open()) {
                // Write the updated car records to the file
                for (const Car& car : cars) {
                    outFile << car.model << "          " << car.make << "          " << car.id << "       " << car.year << "\n";
                }
                outFile.close();
                
            } else {
                std::cout << "          Error opening the file. Car sale failed.\n";
                return;
            }
        } else {
            std::cout << "          Error opening the sold cars file. Car sale record could not be saved.\n";
            return;
        }
    } else {
        std::cout << "          Error opening the file. Car sale failed.\n";
        return;
    }

    // Complete the transaction
    std::string buyerName;
    double amount;

    // Get buyer's name
    std::cout << "          Enter the buyer's name: ";
    std::getline(std::cin, buyerName);

    // Get purchase amount
    std::cout << "          Enter the purchase amount: ";
    std::cin >> amount;
    std::cin.ignore(); // Ignore the newline character

    // Generate auto-generated date of purchase
    std::time_t currentTime = std::time(nullptr);
    std::tm* currentDate = std::localtime(&currentTime);
    char buffer[80];
    std::strftime(buffer, 80, "%Y-%m-%d", currentDate);

    // Generate receipt
    std::ofstream receiptFile("receipt.txt");
    if (receiptFile.is_open()) {
        receiptFile << "Date of Purchase: " << buffer << "\n";
        receiptFile << "Car ID: " << id << "\n";
        receiptFile << "Buyer's Name: " << buyerName << "\n";
        receiptFile << "Purchase Amount: " << amount << "\n";
        receiptFile.close();

        // Print successful selling message
        std::cout << "\n          Car sold successfully!\n";

        // Print receipt to the console
        std::cout<<"\n";
        std::cout<<"Here is the receipt\n";
        std::cout<<"----------------------------\n";
        std::cout<<"   MIKE CAR LIMITED\n";
        std::cout<<"\n";
        std::ifstream printReceiptFile("receipt.txt");
        if (printReceiptFile.is_open()) {
            std::string line;
            while (std::getline(printReceiptFile, line)) {
                std::cout << line << "\n";
            }
            printReceiptFile.close();
            
        std::cout<<"-----------------------------\n";  
        std::cout<<"Thank you for shopping with us! :)\n";  
                    } else {
            std::cout << "          Error opening the receipt file for printing.\n";
        }
    } else {
        std::cout << "          Error opening the receipt file. Receipt generation failed.\n";
    }
}


void displaySoldCars() {
    std::ifstream file("sold_cars.txt");

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream iss(line);
            std::string model, make, id;
            int year;
            if (iss >> model >> make >> id >> year) {
                std::cout << "-------------------------------\n";
                std::cout << "Model: " << model << std::endl;
                std::cout << "Make: " << make << std::endl;
                std::cout << "ID: " << id << std::endl;
                std::cout << "Year: " << year << std::endl;
                std::cout << "-------------------------------\n";
                std::cout << std::endl;
            }
        }
        file.close();
    } else {
        std::cout << "          Error opening the file. Could not display sold cars.\n";
    }
}



