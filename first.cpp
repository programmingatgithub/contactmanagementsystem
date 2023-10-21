#include <iostream>
#include <vector>
#include <string>

class Contact {
public:
    Contact(const std::string& name, const std::string& phoneNumber)
        : name(name), phoneNumber(phoneNumber) {}

    virtual void display() const {
        std::cout << "Name: " << name << ", Phone Number: " << phoneNumber << std::endl;
    }

    const std::string& getName() const {
        return name;
    }

private:
    std::string name;
    std::string phoneNumber;
};

class PersonalContact : public Contact {
public:
    PersonalContact(const std::string& name, const std::string& phoneNumber, const std::string& address)
        : Contact(name, phoneNumber), address(address) {}

    void display() const override {
        Contact::display();
        std::cout << "Address: " << address << std::endl;
    }

private:
    std::string address;
};

class BusinessContact : public Contact {
public:
    BusinessContact(const std::string& name, const std::string& phoneNumber, const std::string& company)
        : Contact(name, phoneNumber), company(company) {}

    void display() const override {
        Contact::display();
        std::cout << "Company: " << company << std::endl;
    }

private:
    std::string company;
};

int main() {
    std::vector<Contact*> contacts;

    while (true) {
        std::cout << "Contact Management System\n";
        std::cout << "1. Add Personal Contact\n";
        std::cout << "2. Add Business Contact\n";
        std::cout << "3. Display Contacts\n";
        std::cout << "4. Search Contacts\n";
        std::cout << "5. Delete Contact\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, phoneNumber, address;
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter phone number: ";
                std::cin >> phoneNumber;
                std::cout << "Enter address: ";
                std::cin >> address;
                contacts.push_back(new PersonalContact(name, phoneNumber, address));
                break;
            }

            case 2: {
                std::string name, phoneNumber, company;
                std::cout << "Enter name: ";
                std::cin >> name;
                std::cout << "Enter phone number: ";
                std::cin >> phoneNumber;
                std::cout << "Enter company: ";
                std::cin >> company;
                contacts.push_back(new BusinessContact(name, phoneNumber, company));
                break;
            }

            case 3:
                std::cout << "Contacts:\n";
                for (const Contact* contact : contacts) {
                    contact->display();
                }
                break;

            case 4: {
                std::string searchName;
                std::cout << "Enter name to search: ";
                std::cin >> searchName;
                bool found = false;
                for (const Contact* contact : contacts) {
                    if (contact->getName() == searchName) {
                        contact->display();
                        found = true;
                    }
                }
                if (!found) {
                    std::cout << "Contact not found.\n";
                }
                break;
            }

            case 5: {
                std::string deleteName;
                std::cout << "Enter name to delete: ";
                std::cin >> deleteName;
                for (auto it = contacts.begin(); it != contacts.end(); ++it) {
                    if ((*it)->getName() == deleteName) {
                        delete *it; // Deallocate memory
                        contacts.erase(it);
                        std::cout << "Contact deleted.\n";
                        break;
                    }
                }
                break;
            }

            case 6:
                // Clean up and exit
                for (Contact* contact : contacts) {
                    delete contact;
                }
                return 0;

            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
