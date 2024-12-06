#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

#include <string>
#include <queue>
#include <unordered_map>

// Employee class to hold employee details
class Employee {
public:
    std::string name;
    int waiting_time;    // Days employee has waited for the book
    int retaining_time;  // Days employee has kept the book

    // Constructor to initialize the employee's name
    Employee(const std::string& _name);

    // To adjust waiting time and retaining time when priorities change
    void updateTimes(int waiting, int retaining);

    // Priority comparator for the queue
    bool operator<(const Employee& other) const;
};

// Book class to manage book circulation
class Book {
public:
    std::string title;
    std::string circulation_start_date;
    std::string circulation_end_date;
    bool is_archived;
    std::queue<Employee*> circulation_queue;

    // Constructor to initialize the book's title and circulation start date
    Book(const std::string& _title, const std::string& _start_date);

    // Function to circulate the book to an employee
    void circulateBook(Employee* employee);

    // Function to pass the book to the next employee in the queue
    void passOnBook();

    // Display the book's circulation queue and its archived status
    void displayStatus();
};

// Library class to manage books and employees
class Library {
public:
    std::unordered_map<std::string, Book*> books;    // Mapping book title to its details
    std::unordered_map<std::string, Employee*> employees;  // Mapping employee name to their details

    // Add an employee to the library system
    void addEmployee(const std::string& name);

    // Add a book to the library system
    void addBook(const std::string& title, const std::string& start_date);

    // Circulate a book to an employee
    void circulateBook(const std::string& book_title, const std::string& employee_name);

    // Pass the book to the next employee
    void passOnBook(const std::string& book_title);

    // Display status of the books and their circulation
    void displayBooksStatus();
};

#endif // LIBRARYSYSTEM_H
