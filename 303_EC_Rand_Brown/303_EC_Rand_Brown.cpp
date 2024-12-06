#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

// Employee class to hold employee details
class Employee {
public:
    std::string name;
    int waiting_time; // Days employee has waited for the book
    int retaining_time; // Days employee has kept the book

    Employee(const std::string& _name) : name(_name), waiting_time(0), retaining_time(0) {}

    // To adjust waiting time and retaining time when priorities change
    void updateTimes(int waiting, int retaining) {
        waiting_time = waiting;
        retaining_time = retaining;
    }

    // Priority comparator for the queue
    bool operator<(const Employee& other) const {
        return (waiting_time - retaining_time) < (other.waiting_time - other.retaining_time);
    }
};

// Book class to manage book circulation
class Book {
public:
    std::string title;
    std::string circulation_start_date;
    std::string circulation_end_date;
    bool is_archived;
    std::queue<Employee*> circulation_queue;

    Book(const std::string& _title, const std::string& _start_date)
        : title(_title), circulation_start_date(_start_date), is_archived(false) {}

    // Function to circulate the book to an employee
    void circulateBook(Employee* employee) {
        circulation_queue.push(employee);
    }

    // Function to pass the book to the next employee in the queue
    void passOnBook() {
        if (circulation_queue.empty()) {
            std::cout << "No employees left to pass the book to!" << std::endl;
            return;
        }

        // Employee who is passing on the book
        Employee* current_employee = circulation_queue.front();
        circulation_queue.pop();

        // Adjust retaining time for the current employee
        current_employee->retaining_time++;

        if (circulation_queue.empty()) {
            // Archive the book if it's the last employee
            is_archived = true;
            std::cout << "Book \"" << title << "\" archived after employee " << current_employee->name << " returns it." << std::endl;
        }
        else {
            // Employee who gets the book
            Employee* next_employee = circulation_queue.front();
            next_employee->waiting_time++;
            std::cout << "Employee " << current_employee->name << " passed the book to employee "
                << next_employee->name << "." << std::endl;
        }
    }

    // Display the book's circulation queue and its archived status
    void displayStatus() {
        std::cout << "Book: " << title << ", Archived: " << (is_archived ? "Yes" : "No") << std::endl;
        std::cout << "Employees in queue for the book: " << std::endl;
        std::queue<Employee*> temp_queue = circulation_queue;
        while (!temp_queue.empty()) {
            Employee* emp = temp_queue.front();
            temp_queue.pop();
            std::cout << "Employee: " << emp->name << ", Waiting time: " << emp->waiting_time
                << ", Retaining time: " << emp->retaining_time << std::endl;
        }
    }
};

// Library class to manage books and employees
class Library {
public:
    std::unordered_map<std::string, Book*> books; // Mapping book title to its details
    std::unordered_map<std::string, Employee*> employees; // Mapping employee name to their details

    // Add an employee to the library system
    void addEmployee(const std::string& name) {
        employees[name] = new Employee(name);
    }

    // Add a book to the library system
    void addBook(const std::string& title, const std::string& start_date) {
        books[title] = new Book(title, start_date);
    }

    // Circulate a book to an employee
    void circulateBook(const std::string& book_title, const std::string& employee_name) {
        if (books.find(book_title) == books.end()) {
            std::cout << "Book not found!" << std::endl;
            return;
        }
        if (employees.find(employee_name) == employees.end()) {
            std::cout << "Employee not found!" << std::endl;
            return;
        }

        Book* book = books[book_title];
        Employee* employee = employees[employee_name];
        book->circulateBook(employee);

        std::cout << "Employee " << employee_name << " is now reading the book \"" << book_title << "\"." << std::endl;
    }

    // Pass the book to the next employee
    void passOnBook(const std::string& book_title) {
        if (books.find(book_title) == books.end()) {
            std::cout << "Book not found!" << std::endl;
            return;
        }

        Book* book = books[book_title];
        book->passOnBook();
    }

    // Display status of the books and their circulation
    void displayBooksStatus() {
        for (auto& entry : books) {
            entry.second->displayStatus();
        }
    }
};

// Main function to demonstrate the library system
int main() {
    Library lib;

    // Add employees
    lib.addEmployee("Alice");
    lib.addEmployee("Bob");
    lib.addEmployee("Charlie");

    // Add books
    lib.addBook("C++ Programming", "2024-12-01");
    lib.addBook("Data Structures", "2024-12-01");

    // Circulate books to employees
    lib.circulateBook("C++ Programming", "Alice");
    lib.circulateBook("Data Structures", "Bob");

    // Display the status of books
    lib.displayBooksStatus();

    // Pass the book to the next employee
    lib.passOnBook("C++ Programming");
    lib.passOnBook("Data Structures");

    // Display the status again after passing the books
    lib.displayBooksStatus();

    // Archive the books
    lib.passOnBook("C++ Programming");
    lib.passOnBook("Data Structures");

    // Display final status
    lib.displayBooksStatus();

    return 0;
}
