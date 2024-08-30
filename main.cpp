#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include <limits>
struct Contact {
    std::string name;
    std::string phoneNumber;
    std::string email;
};

const std::string CONTACTS_FILE = "contacts.csv";

struct User {
    std::string username;
    std::string password;
};
void contactManager(const std::string& username);
void displayContacts(const std::string& username);
void searchContact(const std::string& username);
void importContacts(const std::string& username);
void exportContacts(const std::string& username);
void deleteContact(const std::string& username);

void addContact(const std::string& username) {
    std::ofstream file(CONTACTS_FILE, std::ios::app);
    if (!file) {
        std::cout << "Error opening file for writing." << std::endl;
        return;
    }

    Contact contact;
    std::cout << "Enter contact name: ";
    std::getline(std::cin, contact.name);
    std::cout << "Enter contact phone number: ";
    std::getline(std::cin, contact.phoneNumber);
    std::cout << "Enter contact email: ";
    std::getline(std::cin, contact.email);

    file << username << "," << contact.name << "," << contact.phoneNumber << "," << contact.email << std::endl;

    file.close();
    std::cout << "Contact added successfully." << std::endl;
}

bool authenticateUser(const User& user) {
    std::ifstream file("users.txt");
    if (!file) {
        std::cout << "Error opening file for reading." << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername;
        std::string storedPassword;

        std::getline(ss, storedUsername, ',');
        std::getline(ss, storedPassword, ',');

        if (storedUsername == user.username && storedPassword == user.password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool registerUser() {
    std::string username;
    std::string password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    std::ofstream file("users.txt", std::ios::app);
    if (!file) {
        std::cout << "Error opening file for writing." << std::endl;
        return false;
    }

    file << username << "," << password << std::endl;
    file.close();

    return true;
}

void login() {
    std::string username;
    std::string password;

    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    User user{username, password};

    if (authenticateUser(user)) {
        std::cout << "Login successful." << std::endl;
        std::cout << "Welcome, " << username << "!" << std::endl;
        std::cout << std::endl;
        contactManager(username);
    } else {
        std::cout << "Invalid username or password." << std::endl;
        std::cout << std::endl;
    }
}

void contactManager(const std::string& username) {
    int choice;
    do {
        std::cout << "===== Contact Manager =====" << std::endl;
        std::cout << "1. Add Contact" << std::endl;
        std::cout << "2. Display Contacts" << std::endl;
        std::cout << "3. Search Contact" << std::endl;
        std::cout << "4. Import Contacts" << std::endl;
        std::cout << "5. Export Contacts" << std::endl;
        std::cout << "6. Delete Contact" << std::endl;
        std::cout << "7. Logout" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                addContact(username);
                break;
            case 2:
                displayContacts(username);
                break;
            case 3:
                searchContact(username);
                break;
            case 4:
                importContacts(username);
                break;
            case 5:
                exportContacts(username);
                break;
            case 6:
                deleteContact(username);
                break;
            case 7:
                std::cout << "Logging out." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;

    } while (choice != 7);
}

void displayContacts(const std::string& username) {
    std::ifstream file(CONTACTS_FILE);
    if (!file) {
        std::cout << "No contacts found." << std::endl;
        return;
    }

    std::string line;
    bool contactsFound = false;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername;
        std::string contactName;
        std::string phoneNumber;
        std::string email;

        std::getline(ss, storedUsername, ',');
        std::getline(ss, contactName, ',');
        std::getline(ss, phoneNumber, ',');
        std::getline(ss, email, ',');

        if (storedUsername == username) {
            std::cout << "Contact Name: " << contactName << std::endl;
            std::cout << "Phone Number: " << phoneNumber << std::endl;
            std::cout << "Email: " << email << std::endl;
            std::cout << std::endl;
            contactsFound = true;
        }
    }

    file.close();

    if (!contactsFound) {
        std::cout << "No contacts found for the user." << std::endl;
    }
}

void searchContact(const std::string& username) {
    std::ifstream file(CONTACTS_FILE);
    if (!file) {
        std::cout << "No contacts found." << std::endl;
        return;
    }

    std::string searchName;
    std::cout << "Enter the name to search: ";
    std::getline(std::cin, searchName);

    std::string line;
    bool contactFound = false;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername;
        std::string contactName;
        std::string phoneNumber;
        std::string email;

        std::getline(ss, storedUsername, ',');
        std::getline(ss, contactName, ',');
        std::getline(ss, phoneNumber, ',');
        std::getline(ss, email, ',');

        if (storedUsername == username && contactName == searchName) {
            std::cout << "Contact Name: " << contactName << std::endl;
            std::cout << "Phone Number: " << phoneNumber << std::endl;
            std::cout << "Email: " << email << std::endl;
            std::cout << std::endl;
            contactFound = true;
        }
    }

    file.close();

    if (!contactFound) {
        std::cout << "Contact not found." << std::endl;
    }
}

void importContacts(const std::string& username) {
    std::string filename;
    std::cout << "Enter the filename to import: ";
    std::getline(std::cin, filename);

    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file." << std::endl;
        return;
    }

    std::ofstream outFile(CONTACTS_FILE, std::ios::app);
    if (!outFile) {
        std::cout << "Error opening file for writing." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        outFile << username << "," << line << std::endl;
    }

    file.close();
    outFile.close();

    std::cout << "Contacts imported successfully." << std::endl;
}

void exportContacts(const std::string& username) {
    std::string filename;
    std::cout << "Enter the filename to export: ";
    std::getline(std::cin, filename);

    std::ifstream file(CONTACTS_FILE);
    if (!file) {
        std::cout << "No contacts found." << std::endl;
        return;
    }

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cout << "Error opening file for writing." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername;
        std::string contactName;
        std::string phoneNumber;
        std::string email;

        std::getline(ss, storedUsername, ',');
        std::getline(ss, contactName, ',');
        std::getline(ss, phoneNumber, ',');
        std::getline(ss, email, ',');

        if (storedUsername == username) {
            outFile << contactName << "," << phoneNumber << "," << email << std::endl;
        }
    }

    file.close();
    outFile.close();

    std::cout << "Contacts exported successfully." << std::endl;
}

void deleteContact(const std::string& username) {
    std::ifstream file(CONTACTS_FILE);
    if (!file) {
        std::cout << "No contacts found." << std::endl;
        return;
    }

    std::string deleteName;
    std::cout << "Enter the name to delete: ";
    std::getline(std::cin, deleteName);

    std::string line;
    std::vector<std::string> tempLines;
    bool contactFound = false;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string storedUsername;
        std::string contactName;
        std::string phoneNumber;
        std::string email;

        std::getline(ss, storedUsername, ',');
        std::getline(ss, contactName, ',');
        std::getline(ss, phoneNumber, ',');
        std::getline(ss, email, ',');

        if (storedUsername == username && contactName != deleteName) {
            tempLines.push_back(line);
        } else if (storedUsername == username && contactName == deleteName) {
            contactFound = true;
        }
    }

    file.close();

    if (!contactFound) {
        std::cout << "Contact not found." << std::endl;
        return;
    }

    std::ofstream outFile(CONTACTS_FILE);
    if (!outFile) {
        std::cout << "Error opening file for writing." << std::endl;
        return;
    }

    for (const auto& tempLine : tempLines) {
        outFile << tempLine << std::endl;
    }

    outFile.close();

    std::cout << "Contact deleted successfully." << std::endl;
}

int main() {
    int choice;
    do {
        std::cout << "===== Contact Manager =====" << std::endl;
        std::cout << "1. Register" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                if (registerUser()) {
                    std::cout << "Registration successful." << std::endl;
                } else {
                    std::cout << "Registration failed." << std::endl;
                }
                std::cout << std::endl;
                break;
            case 2:
                login();
                break;
            case 3:
                std::cout << "Exiting." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;

    } while (choice != 3);

    return 0;
}
