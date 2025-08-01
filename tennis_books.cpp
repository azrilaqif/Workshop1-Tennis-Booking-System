#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iomanip>
#include <stdlib.h>
#include <chrono>  
#include <thread>  
#include <conio.h>
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <regex>


using namespace std;
using namespace sql;

struct Court {
    int courtId;
    string courtName;
    string court_Location;
};
struct User {
    int userId;
    string username;
    string password;
};

// ---------------------------------------------------------MENUS----------------------------------------------------------- 
void main_menu()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                            WELCOME TO TENNIS BOOKING SYSTEM                          |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                1. Register New Customer                              |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                2. Register New Admin                                 |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                3. Customer Login                                     |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                4. Admin Login                                        |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                5. Exit                                               |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
}

void Menu_Admin()
{
    cout << "+=====================================================================================+" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "|                                WELCOME TO MENU ADMIN                                |" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "+=====================================================================================+" << endl;
    cout << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
}

void Menu_User()
{
    cout << "+=====================================================================================+" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "|                               WELCOME TO MENU CUSTOMER                              |" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "|                                                                                     |" << endl;
    cout << "+=====================================================================================+" << endl;
    cout << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
}

void menu_LoginUser()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                  CUSTOMER LOGIN MENU                                 |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}

// ------------------------------------------------------ LOGIN USER---------------------------------------------------------------- 
bool loginUser(Connection* con, string username, string password) {
    PreparedStatement* pstmt;
    ResultSet* res;
    char ch;

    string query = "SELECT * FROM customer WHERE username = ? AND password = ?";
    pstmt = con->prepareStatement(query);
    pstmt->setString(1, username);
    pstmt->setString(2, password);
    res = pstmt->executeQuery();

    bool success = res->next();

    delete res;
    delete pstmt;

    return success;

}

// ------------------------------------------------------REGISTER USER--------------------------------------------------------------- 
void menu_RegisterUser()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                CUSTOMER REGISTRATION                                 |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}

void registerUser(Connection* con) {
    PreparedStatement* pstmt = nullptr;
    ResultSet* res = nullptr;
    string username, email, phone_number, password, confirm_password;

    cout << "------------------------------" << endl;
    cout << "Enter username: ";
    cin.get();
    getline(cin, username);

    do {
        cout << "------------------------------" << endl;
        cout << "Enter admin email: ";

        getline(cin, email);

        // Validate email format
        size_t atPos = email.find('@');
        if (atPos == string::npos) {
            cout << "Invalid email format. Email must contain '@'. Please try again." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else {
            break;  // Valid email, exit the loop
        }
    } while (true);


    cout << "------------------------------" << endl;
    cout << "Enter your phone number (without -): ";

    getline(cin, phone_number);

    char ch;
    do {
        // Clear both password and confirm_password for a fresh start
        password = "";
        confirm_password = "";

        // Enter password
        cout << "------------------------------" << endl;
        cout << "Enter password: ";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!password.empty()) {
                    cout << "\b \b";
                    password.pop_back();
                }
            }
            else {
                cout << "*";
                password.push_back(ch);
            }
        }
        cout << endl;

        // Confirm password
        cout << "------------------------------" << endl;
        cout << "Confirm password: ";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!confirm_password.empty()) {
                    cout << "\b \b";
                    confirm_password.pop_back();
                }
            }
            else {
                cout << "*";
                confirm_password.push_back(ch);
            }
        }
        cout << endl;

        if (password != confirm_password) {

            cout << "Passwords do not match. Please try again." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } while (password != confirm_password);

    cout << "------------------------------" << endl;
    char confirmChoice;
    bool isValidChoice = false;

    do {
        cout << "Do you want to confirm your registration? (Y/N): ";
        cin >> confirmChoice;

        // Validate the input
        if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
            cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            isValidChoice = true;
        }

    } while (!isValidChoice);

    if (toupper(confirmChoice) != 'Y') {
        cout << "------------------------------" << endl;
        cout << "Registration canceled. Returning to the main menu." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        return;
    }

    // Check if user already exists
    string query = "SELECT * FROM customer WHERE username = ?";
    pstmt = con->prepareStatement(query);
    pstmt->setString(1, username);
    res = pstmt->executeQuery();
    system("cls");

    if (res->next()) {
        // User already exists
        cout << "**********************************************************************************" << endl;
        cout << "|              Customer already exists, Please enter another username.           |" << endl;
        cout << "**********************************************************************************" << endl;
        cout << "|                             1. Back to main menu                               |" << endl;
        cout << "|                             2. Create new registration                         |" << endl;
        cout << "==================================================================================" << endl;

        cout << "------------------------------" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;
        system("cls");

        if (choice == 1) {
            delete pstmt;
            delete res;
            return;
        }
        else if (choice == 2) {
            // Create a new registration
            delete pstmt;
            delete res;
            registerUser(con);
            return;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
            delete pstmt;
            delete res;
            return;
        }
    }
    else {
        // Insert new user into the database
        query = "INSERT INTO customer (username, email, phone_number, password) VALUES (?, ?, ?, ?)";
        pstmt = con->prepareStatement(query);
        pstmt->setString(1, username);
        pstmt->setString(2, email);
        pstmt->setString(3, phone_number);
        pstmt->setString(4, password);
        pstmt->execute();

        delete pstmt;
        cout << "------------------------------" << endl;
        cout << "Customer registered successfully!" << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
    }

    delete res;
}


// --------------------------------------------------REGISTER ADMIN-------------------------------------------------------------- 
void menu_RegisterAdmin()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                              REGISTER ADMIN ACCOUNT                                  |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}


void registerAdmin(Connection* con) {
    string newUsername, newPassword, newEmail, newPhoneNumber, confirm_password;
    string adminPassword = "admin123";  // Fixed password for admin registration
    string enteredPassword;

    cout << "------------------------------------------------------------" << endl;
    cout << "Enter the admin registration password to register new admin: ";
    

    // Masking the input using push_back
    char ch;
    while ((ch = _getch()) != 13) { // 13 is the ASCII code for Enter
        if (ch == 8 && !enteredPassword.empty()) { // 8 is the ASCII code for Backspace
            cout << "\b \b"; // Move the cursor back, print a space, move the cursor back again
            enteredPassword.pop_back();
            
        }
        else if (ch != 8) {
            cout << '*';
            enteredPassword.push_back(ch);
            
        }
    }

    if (enteredPassword != adminPassword) {
        cout << endl;
        cout << "------------------------------" << endl;
        cout << "Incorrect admin registration password. Admin registration canceled." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        return;
    }

    cout << endl;
    cout << "------------------------------" << endl;
    cout << "Enter admin username: ";
    cin.get();
    getline(cin, newUsername);

    do {
        cout << "------------------------------" << endl;
        cout << "Enter admin email: ";

        getline(cin, newEmail);

        // Validate email format
        size_t atPos = newEmail.find('@');
        if (atPos == string::npos) {
            cout << "Invalid email format. Email must contain '@'. Please try again." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        else {
            break;  // Valid email, exit the loop
        }
    } while (true);

    cout << "------------------------------" << endl;
    cout << "Enter admin phone number: ";

    getline(cin, newPhoneNumber);

    do {
        // Enter admin password
        cout << "------------------------------" << endl;
        cout << "Enter admin password: ";
        newPassword = "";
        char ch;
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!newPassword.empty()) {
                    cout << "\b \b";
                    newPassword.pop_back();
                }
            }
            else {
                cout << "*";
                newPassword.push_back(ch);
            }
        }
        cout << endl;

        // Confirm admin password
        cout << "------------------------------" << endl;
        cout << "Confirm admin password: ";
        confirm_password = "";
        while ((ch = _getch()) != '\r') {
            if (ch == '\b') {
                if (!confirm_password.empty()) {
                    cout << "\b \b";
                    confirm_password.pop_back();
                }
            }
            else {
                cout << "*";
                confirm_password.push_back(ch);
            }
        }
        cout << endl;

        if (newPassword != confirm_password) {
            cout << "Passwords do not match. Please try again." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    } while (newPassword != confirm_password);

    // Ask the user to confirm registration
    cout << "------------------------------" << endl;

    char confirmChoice;
    bool isValidChoice = false;

    do {
        cout << "Do you want to confirm your registration? (Y/N): ";
        cin >> confirmChoice;

        // Validate the input
        if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
            cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            isValidChoice = true;
        }

    } while (!isValidChoice);

    if (toupper(confirmChoice) != 'Y') {
        cout << "------------------------------" << endl;
        cout << "Registration canceled. Returning to the main menu." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        return;
    }

    try {
        // Check if admin already exists
        string query = "SELECT * FROM admin WHERE username = ?";
        PreparedStatement* pstmt = con->prepareStatement(query);
        pstmt->setString(1, newUsername);
        ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            // Admin already exists
            cout << "------------------------------" << endl;
            cout << "Admin already exists. Registration Failed." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
        }
        else {
            // Create a Statement
            Statement* stmt = con->createStatement();

            // Execute the query to insert admin data into the table
            stmt->execute("INSERT INTO admin (username, password, email, phone_number) VALUES ('" + newUsername + "', '" + newPassword + "', '" + newEmail + "', '" + newPhoneNumber + "')");

            cout << "------------------------------" << endl;
            cout << "Admin registration successful!" << endl;

            // Clean up
            delete stmt;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
        }

        // Clean up
        delete pstmt;
        delete res;
    }
    catch (SQLException) {
        cout << "------------------------------" << endl;
        cout << "Error occurred during admin registration." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
    }
}



// --------------------------------------------------------LOGIN ADMIN------------------------------------------------------------- 
bool loginAdmin(Connection* con, const string& username, const string& password) {
    try {
        PreparedStatement* pstmt;
        ResultSet* res;

        // Prepare SQL statement
        pstmt = con->prepareStatement("SELECT * FROM admin WHERE username = ? AND password = ?");
        pstmt->setString(1, username);
        pstmt->setString(2, password);
        res = pstmt->executeQuery();

        // Check if the admin exists in the database
        if (res->next())
        {
            delete res;
            delete pstmt;
            return true;  // Admin exists, login successful
        }

        delete res;
        delete pstmt;
        system("cls");
    }
    catch (SQLException& e) {
        cerr << "SQL error: " << e.what() << endl;

    }

    return false;  // Admin not found or error occurred
}

// -----------------------------------------------------VIEW USER BOOKING (CUSTOMER)---------------------------------------------- 
void viewUserBookings(Connection* con, const string& username) {
    PreparedStatement* pstmt;
    ResultSet* res;

    // Query to retrieve user bookings
    string userBookingsQuery = "SELECT BookingID, court_name, courtLocation, timeSlot, fee, booking_date FROM booking WHERE username = ?";
    pstmt = con->prepareStatement(userBookingsQuery);
    pstmt->setString(1, username);
    res = pstmt->executeQuery();

    // Display user bookings
    cout << "+================================================================================================+" << endl;
    cout << "|                                         YOUR BOOKINGS                                          |" << endl;
    cout << "+================================================================================================+" << endl;

    // Display headers
    cout << setw(15) << "Booking ID" << setw(20) << "Court" << setw(20) << "Location" << setw(15) << "Time Slot" << setw(10) << "Fee" << setw(15) << "Booking Date" << endl;
    cout << "+------------------------------------------------------------------------------------------------+" << endl;

    // Display booking details
    while (res->next()) {
        int bookingID = res->getInt("BookingID");
        string courtName = res->getString("court_name");
        string courtLocation = res->getString("courtLocation");
        int timeSlot = res->getInt("timeSlot");
        double fee = res->getDouble("fee");
        string bookingDate = res->getString("booking_date");

        // Display booking information
        cout << setw(15) << bookingID << setw(20) << courtName << setw(20) << courtLocation << setw(15) << timeSlot << setw(10) << fee << setw(15) << bookingDate << endl;
    }


    cout << "+------------------------------------------------------------------------------------------------+" << endl;

    // Cleanup
    delete res;
    delete pstmt;

    cout << "Press Enter to go back to the Customer Menu...";
    cin.ignore();
    cin.get();
    system("cls");
}


// -------------------------------------------------VIEW USER BOOKINGS (ADMIN)------------------------------------------------- 
void View_User()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                  VIEW CUSTOMER BOOKINGS                              |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}

void displayBookingRecord(const ResultSet* res) {
    int bookingID = res->getInt("BookingID");
    string username = res->getString("username");
    string court_name = res->getString("court_name");
    string court_location = res->getString("courtLocation");
    int time_slot = res->getInt("timeSlot");
    double price = res->getDouble("fee");
    string booking_date = res->getString("booking_date"); // Fetch booking date

    cout << "Booking ID: " << bookingID << " | ";
    cout << "Username: " << username << " | ";
    cout << "Court Name: " << court_name << " | ";
    cout << "Court Location: " << court_location << " | " << endl;
    cout << "Booking Date: " << booking_date << " | "; // Print booking date
    cout << "Time: " << time_slot << " AM - " << (time_slot + 1) << " AM | ";
    cout << "Price: RM " << price << endl;
}

void viewBookings(Connection* con) {
    Statement* stmt;
    ResultSet* res;

    while (true) {
        // Display all booking records
        stmt = con->createStatement();
        res = stmt->executeQuery("SELECT * FROM booking");

        cout << "Pending Bookings waiting to be Approved:" << endl;
        cout << "+=========================================================================================================================+" << endl;

        while (res->next()) {
            displayBookingRecord(res);
            cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }

        delete res;
        delete stmt;

        cout << endl;
        cout << "+*************************************************************************************+" << endl;
        cout << "|                            Search pending bookings by:                              |" << endl;
        cout << "+*************************************************************************************+" << endl;
        cout << "|                                    1. Court                                         |" << endl;
        cout << "|                                    2. Username                                      |" << endl;
        cout << "|                                    3. Date                                          |" << endl;
        cout << "|                                    4. Back                                          |" << endl;
        cout << "+=====================================================================================+" << endl;
        cout << "Enter your choice: ";

        int searchOption;

        // Input validation for integer
        while (true) {
            cin >> searchOption;

            if (cin.fail()) {
                cout << "Error: Invalid input. Please enter a valid integer." << endl;
                cin.clear(); // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discarding invalid input
                cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
                cout << "Enter your choice: ";
            }
            else {
                break;
            }
        }

        system("cls");

        if (searchOption == 1 || searchOption == 2 || searchOption == 3) {
            string searchField;
            if (searchOption == 1) {
                searchField = "court_name";
            }
            else if (searchOption == 2) {
                searchField = "username";
            }
            else {
                searchField = "booking_date";
            }

            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "Enter the " << searchField << ": ";
            string searchValue;
            cin.ignore();
            getline(cin, searchValue);

            stmt = con->createStatement();
            string query;
            if (searchOption == 3) {
                query = "SELECT * FROM booking WHERE DATE(" + searchField + ") = '" + searchValue + "'";
            }
            else {
                query = "SELECT * FROM booking WHERE " + searchField + " = '" + searchValue + "'";
            }
            res = stmt->executeQuery(query);

            cout << "Search Results:" << endl;
            cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;

            while (res->next()) {
                displayBookingRecord(res);
                cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
            }

            delete res;
            delete stmt;

            cout << "Do you want to search again? (1: No, 2: Yes): ";


            int searchAgain;

            while (true) {
                cin >> searchAgain;
                system("cls");

                if (cin.fail()) {
                    cout << "Error: Invalid input. Please enter 1 or 2." << endl;
                    cin.clear(); // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discarding invalid input
                    cout << "Enter your choice: ";
                }
                else if (searchAgain == 1 || searchAgain == 2) {
                    if (searchAgain == 2) {
                        break; // Exit the loop if the user chooses not to search again
                        system("cls");
                    }
                    else {
                        // Continue searching
                        return;
                    }
                }
                else {
                    cout << "Invalid option. Please enter 1 or 2." << endl;
                    cout << "Enter your choice: ";
                }
            }
        }
        else if (searchOption == 4) {
            break; // Exit the loop if the user chooses to go back
            system("cls");
        }
        else {
            cout << "Invalid option. Exiting..." << endl;
            break; // Exit the loop in case of an invalid option
            system("cls");
        }
    }
}




// ------------------------------------------------BOOKING A COURT (CUSTOMER)------------------------------------------------ 


void book_Court()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                   COURT BOOKINGS                                     |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}

bool isValidDate(const string& date) {
    // Use regular expression to check if the entered date follows the format
    regex dateRegex("\\d{4}-\\d{2}-\\d{2}");

    if (!regex_match(date, dateRegex)) {
        return false;
    }

    // Extract year, month, and day from the date string using sscanf
    int year, month, day;
    if (sscanf_s(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3) {
        return false; // Failed to extract components
    }

    // Check for valid month range (1 to 12)
    if (month < 1 || month > 12) {
        return false;
    }

    // Check for valid day range based on the month
    switch (month) {
    case 2: // February
        // Check for leap year
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            return day >= 1 && day <= 29;
        }
        else {
            return day >= 1 && day <= 28;
        }
        break;
    case 4: case 6: case 9: case 11: // April, June, September, November
        return day >= 1 && day <= 30;
    default: // All other months
        return day >= 1 && day <= 31;
    }
}


void bookCourt(Connection* con, string username) {
    Statement* stmt;
    ResultSet* res;
    int time_slot;

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM court");

    cout << "+=====================================================================================+" << endl;
    cout << "|                                   Court Listing:                                    |" << endl;
    cout << "+=====================================================================================+" << endl;

    vector<string> courtNames;

    // Store court names in a vector
    while (res->next()) {
        string courtName = res->getString("court_name") + " - " + res->getString("courtLocation");
        courtNames.push_back(courtName);
    }

    // Display court names in a single column with aligned numbers
    for (size_t i = 0; i < courtNames.size(); ++i) {
        cout << "|  " << setw(9) << i + 1 << ")" << setw(38) << courtNames[i] << setw(36) << " |" << endl;
    }

    cout << "+=====================================================================================+" << endl;
    cout << "Please enter the court number to book (0 to cancel): ";

    int courtNumberChoice;
    while (true) {
        cin >> courtNumberChoice;

        if (cin.fail()) {
            cout << "Error: Invalid input. Please enter a valid integer." << endl;
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "----------------------------------------------------- " << endl;
            cout << "Please enter the court number to book (0 to cancel): ";
        }
        else {
            break;
        }
    }
    system("cls");

    bool courtExists = false;
    string court_name;

    if (courtNumberChoice > 0 && courtNumberChoice <= 20) {
        res->beforeFirst();

        for (int i = 1; i <= courtNumberChoice; i++) {
            if (!res->next()) {
                // The specified court number doesn't exist
                cout << "------------------------------" << endl;
                cout << "Error: Court number " << courtNumberChoice << " does not exist." << endl;
                delete res;
                delete stmt;
                return;
            }
        }

        court_name = res->getString("court_name");
        courtExists = true;
    }
    else if (courtNumberChoice == 0) {
        // User chose to cancel
        delete res;
        delete stmt;
        return;
    }
    else {
        // Invalid court number choice
        cout << "Error: Invalid court number choice." << endl;
        delete res;
        delete stmt;
        return;
    }

    if (courtExists) {
        cout << "+*************************************************************************************+" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "|                                 Available Time Slots:                               |" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "+*************************************************************************************+" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "|                                 a. 6 AM - 7 AM                                      |" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "|                                 b. 7 AM - 8 AM                                      |" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "|                                 c. 8 AM - 9 AM                                      |" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "|                                 d. 9 AM - 10 AM                                     |" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "|                                 e. 10 AM - 11 AM                                    |" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "|                                 f. 11 AM - 12 PM                                    |" << endl;
        cout << "|                                                                                     |" << endl;
        cout << "+=====================================================================================+" << endl;
        cout << endl;

        cout << "------------------------------" << endl;
        cout << "Choose the time slot to book (a - f): ";
        char optionChar;
        cin >> optionChar;
        system("cls");

        if (cin.fail() || cin.peek() != '\n' || (optionChar < 'a' || optionChar > 'f')) {
            cout << "------------------------------" << endl;
            cout << "Error: Invalid input. Please enter a single character (a - f)." << endl;
            cout << "Press any key to go back to the court booking menu...";
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cin.get();
            system("cls");
            bookCourt(con, username);
        }
        else {
            time_slot = optionChar - 'a' + 1;

            int originalTimeSlot = time_slot;
            string timeSlotDescription;

            switch (time_slot) {
            case 1:
                time_slot = 6;
                timeSlotDescription = "6 AM - 7 AM";
                break;
            case 2:
                time_slot = 7;
                timeSlotDescription = "7 AM - 8 AM";
                break;
            case 3:
                time_slot = 8;
                timeSlotDescription = "8 AM - 9 AM";
                break;
            case 4:
                time_slot = 9;
                timeSlotDescription = "9 AM - 10 AM";
                break;
            case 5:
                time_slot = 10;
                timeSlotDescription = "10 AM - 11 AM";
                break;
            case 6:
                time_slot = 11;
                timeSlotDescription = "11 AM - 12 PM";
                break;
            }


            // Prompt for the booking date
            cout << "+-------------------------------------------------------------------------------------+" << endl;
            cout << "|                            Enter the Date for Booking:                              |" << endl;
            cout << "+-------------------------------------------------------------------------------------+" << endl;

            string bookingDate;
            bool validFormat = false;

            // Keep prompting until a valid date format is entered
            while (!validFormat) {
                cout << "Please enter the date in (YYYY-MM-DD) format: ";
                cin >> bookingDate;

                if (isValidDate(bookingDate)) {
                    validFormat = true;
                }
                else {
                    cout << "Error: Invalid date. Please enter a valid date." << endl;
                }
            }


            char confirmChoice;
            bool isValidChoice = false;

            do {
                cout << "Do you want to confirm your booking? (Y/N): ";;
                cin >> confirmChoice;

                // Validate the input
                if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
                    cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else {
                    isValidChoice = true;
                }

            } while (!isValidChoice);

            if (toupper(confirmChoice) != 'Y') {
                cout << "------------------------------" << endl;
                cout << "Booking canceled. Returning to the main menu." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                system("cls");
                return;
            }

            // Check for existing bookings on the specified date and time slot
            string checkQuery = "SELECT * FROM booking WHERE court_name = ? AND timeSlot = ? AND booking_date = ?";
            PreparedStatement* checkStmt = con->prepareStatement(checkQuery);
            checkStmt->setString(1, court_name);
            checkStmt->setInt(2, time_slot);
            checkStmt->setString(3, bookingDate);
            ResultSet* checkRes = checkStmt->executeQuery();

            if (checkRes->next())
            {
                cout << "+*************************************************************************************+" << endl;
                cout << "|       The court at this date and hour is already booked. Please choose another.      |" << endl;
                cout << "+*************************************************************************************+" << endl;
                cout << "|                         1. Go back to the court booking menu                        |" << endl;
                cout << "|                         2. Select another court and time                            |" << endl;
                cout << "+=====================================================================================+" << endl;

                cout << "------------------------------" << endl;
                cout << "Enter your choice: ";
                int option;
                cin >> option;

                if (option == 1) {
                    delete checkRes;
                    delete checkStmt;
                    delete res;
                    delete stmt;
                    return;
                }
                else if (option == 2) {
                    delete checkRes;
                    delete checkStmt;
                    system("cls");
                    bookCourt(con, username);
                    return;
                }
                else {
                    cout << "Invalid option. Booking failed!" << endl;
                    delete checkRes;
                    delete checkStmt;
                    delete res;
                    delete stmt;
                    return;
                }
            }
            else {
                string courtLocationQuery = "SELECT courtLocation FROM court WHERE court_name = ?";
                PreparedStatement* courtLocationStmt = con->prepareStatement(courtLocationQuery);
                courtLocationStmt->setString(1, court_name);
                ResultSet* courtLocationRes = courtLocationStmt->executeQuery();


                if (courtLocationRes->next()) {
                    string court_location = courtLocationRes->getString("courtLocation");
                    double price = 15.0;
                    string query = "INSERT INTO booking (username, court_name, courtLocation, timeSlot, fee, booking_date) VALUES (?, ?, ?, ?, ?, ?)";
                    PreparedStatement* pstmt = con->prepareStatement(query);
                    pstmt->setString(1, username);
                    pstmt->setString(2, court_name);
                    pstmt->setString(3, court_location);
                    pstmt->setInt(4, time_slot);
                    pstmt->setDouble(5, price); // Assuming the price is RM 15 for 1 hour
                    pstmt->setString(6, bookingDate);
                    pstmt->execute();

                    delete pstmt;
                    delete courtLocationRes;
                    delete courtLocationStmt;



                    cout << "+*************************************************************************************+" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                Booking was successful!                              |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "+*************************************************************************************+" << endl;
                    cout << "                                                                                       " << endl;
                    cout << "                                 Username: " << username << endl;
                    cout << "                                                                                       " << endl;
                    cout << "                                 Court: " << court_name << endl;
                    cout << "                                                                                       " << endl;
                    cout << "                                 Court Location: " << court_location << endl;
                    cout << "                                                                                       " << endl;
                    cout << "                                 Booking Time:  " << timeSlotDescription << endl;
                    cout << "                                                                                       " << endl;
                    cout << "                                 Booking Date:  " << bookingDate << endl;
                    cout << "                                                                                       " << endl;
                    cout << "                                 Price: RM " << price << endl;
                    cout << "                                                                                       " << endl;
                    cout << "+=====================================================================================+" << endl;

                    // Ask the user if they want to book another court
                    int xy = 0;
                    while (xy == 0) {
                        cout << "Do you want to book another court (y/n)? : ";

                        char option;
                        cin >> option;

                        if (option == 'y' || option == 'Y') {
                            xy = 1;
                            delete res;
                            delete stmt;
                            system("cls");
                            bookCourt(con, username);
                        }
                        else if (option == 'n' || option == 'N') {
                            xy = 1;
                            delete res;
                            delete stmt;
                            system("cls");

                        }
                        else {
                            system("cls");
                            cout << "Invalid Input !" << endl;
                        }
                    }
                }
                else {
                    cout << "------------------------------" << endl;
                    cout << "Error retrieving court location. Booking failed!" << endl;
                    delete courtLocationRes;
                    delete courtLocationStmt;
                    delete checkRes;
                    delete checkStmt;
                    delete res;
                    delete stmt;
                    return;
                }
            }
        }
    }
    else {
        cout << "Invalid court number. Please choose a valid court!" << endl;
        cout << "---------------------------------------------------------" << endl;
        int xy = 0;
        while (xy == 0) {
            cout << "Do you want to book another court (y/n)? : ";

            char option;
            cin >> option;

            if (option == 'y' || option == 'Y') {
                xy = 1;
                delete res;
                delete stmt;
                bookCourt(con, username);
            }
            else if (option == 'n' || option == 'N') {
                xy = 1;
                delete res;
                delete stmt;
                system("cls");
                menu_LoginUser();
            }
            else {
                system("cls");
                cout << "Invalid Input !" << endl;
            }
        }
    }
}


// ------------------------------------------------CANCEL COURT BOOKINGS (CUSTOMER)------------------------------------------------ 
void cancelCourtBooking(Connection* con, const string& username) {
    Statement* stmt;
    ResultSet* res;

    // Step 1: List Customer's Bookings
    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT BookingID, court_name, courtLocation, timeSlot, fee, booking_date FROM booking WHERE username = '" + username + "' AND status = 'active'");

    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                               CANCEL COURT BOOKINGS                                  |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;

    int bookingCount = 0;

    while (res->next()) {
        int BookingID = res->getInt("BookingID");
        string court_name = res->getString("court_name");
        string court_location = res->getString("courtLocation");
        int time_slot = res->getInt("timeSlot");
        double fee = res->getDouble("fee");
        string booking_date = res->getString("booking_date");

        cout << "Booking ID: " << BookingID << endl;
        cout << "Court: " << court_name << " (" << court_location << ")" << endl;
        cout << "Time: " << time_slot << " AM - " << (time_slot + 1) << " AM" << endl;
        cout << "Date: " << booking_date << endl;
        cout << "Fee: RM " << fee << endl;
        cout << "-----------------------------------------------------------------------------------" << endl;

        bookingCount++;
    }

    delete res;
    delete stmt;

    if (bookingCount == 0) {
        cout << "------------------------------" << endl;
        cout << "You have no active court bookings to cancel." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        return;
    }

    // Step 2: Prompt for Booking Cancellation
    int selectedBookingId;
    cout << "------------------------------" << endl;
    cout << "Enter the Booking ID to confirm cancellation (0 to cancel): ";
    cin >> selectedBookingId;

    if (selectedBookingId == 0) {
        cout << "------------------------------" << endl;
        cout << "Booking cancellation cancelled. Please try again..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("cls");
        return; // Exit the function
    }

    cout << "------------------------------" << endl;
    cout << "Are you sure you want to cancel booking ID " << selectedBookingId << "? (Y/N): ";
    char confirmation;
    cin >> confirmation;

    if (confirmation != 'Y' && confirmation != 'y') {
        cout << "------------------------------" << endl;
        cout << "Booking cancellation cancelled. Please try again..." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        system("cls");
        return; // Exit the function
    }

    // Step 3: Update the Status to 'cancelled'
    PreparedStatement* updateStatusStmt = con->prepareStatement("UPDATE booking SET status = 'cancelled' WHERE BookingID = ?");
    updateStatusStmt->setInt(1, selectedBookingId);

    if (updateStatusStmt->executeUpdate() > 0) {
        // Step 4: Move the Booking Record to CanceledBookings Table
        PreparedStatement* moveStmt = con->prepareStatement("INSERT INTO CanceledBookings (BookingID, username, court_name, courtLocation, timeSlot, fee, booking_date, status) SELECT BookingID, username, court_name, courtLocation, timeSlot, fee, booking_date, 'cancelled' FROM booking WHERE BookingID = ?");
        moveStmt->setInt(1, selectedBookingId);

        if (moveStmt->executeUpdate() > 0) {
            // Step 5: Delete the Booking Record from the booking Table
            PreparedStatement* deleteStmt = con->prepareStatement("DELETE FROM booking WHERE BookingID = ?");
            deleteStmt->setInt(1, selectedBookingId);
            deleteStmt->execute();

            cout << "------------------------------" << endl;
            cout << "Booking ID " << selectedBookingId << " has been successfully cancelled." << endl;
        }
        else {
            cout << "------------------------------" << endl;
            cout << "Failed to move the booking to CanceledBookings table. Booking cancellation failed. Please retry." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
            system("cls");
        }

        delete moveStmt;
    }
    else {
        cout << "------------------------------" << endl;
        cout << "Booking ID does not exist. Booking cancellation failed." << endl;
    }

    delete updateStatusStmt;

    cout << "------------------------------" << endl;
    cout << "Press Enter to go back to the Customer Menu...";
    cin.ignore();
    cin.get();
    system("cls");

}





// --------------------------------------------MANAGE COURT (ADMIN)----------------------------------------------------------- 
void Manage_Court()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                    MANAGE COURT                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}

void addCourt(Connection* con) {
    PreparedStatement* pstmt;
    ResultSet* res;


    string courtName, courtLocation;
    cout << "------------------------------" << endl;
    cout << "Enter court name: ";
    cin.ignore();
    getline(cin, courtName);

    cout << "------------------------------" << endl;
    cout << "Enter court location: ";
    getline(cin, courtLocation);

    // Check if the user wants to cancel the operation
    cout << "------------------------------" << endl;
    char confirmChoice;
    bool isValidChoice = false;

    do {
        cout << "Do you confirm to add this court? (Y/N): ";
        cin >> confirmChoice;

        // Validate the input
        if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
            cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            isValidChoice = true;
        }

    } while (!isValidChoice);

    if (toupper(confirmChoice) != 'Y') {
        cout << "------------------------------" << endl;
        cout << "Court add failed. Returning to the main menu." << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        system("cls");
        return;

    }



    // Check if the court already exists
    string checkQuery = "SELECT COUNT(*) FROM court WHERE court_name = ? AND courtLocation = ?";
    pstmt = con->prepareStatement(checkQuery);
    pstmt->setString(1, courtName);
    pstmt->setString(2, courtLocation);
    res = pstmt->executeQuery();

    int count = 0;
    if (res->next()) {
        count = res->getInt(1);
    }

    if (count > 0) {
        cout << "------------------------------" << endl;
        cout << "Court already exists. Cannot add duplicate court." << endl;

        // Offer options to go back to the menu or add another court
        cout << "+*************************************************************************************+" << endl;
        cout << "|                                    1. Go back to Admin Menu                         |" << endl;
        cout << "|                                    2. Add another court                             |" << endl;
        cout << "+*************************************************************************************+" << endl;

        cout << "------------------------------" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 2) {
            // Add another court
            addCourt(con);
        }
        else {
            cout << "------------------------------" << endl;
            cout << "Returning to the menu." << endl;
            system("cls");
        }
    }
    else {

        // Add the court to the court
        string insertQuery = "INSERT INTO court (court_name, courtLocation) VALUES (?, ?)";
        pstmt = con->prepareStatement(insertQuery);
        pstmt->setString(1, courtName);
        pstmt->setString(2, courtLocation);
        pstmt->execute();

        system("cls");
        cout << "------------------------------" << endl;
        cout << "Court added successfully!" << endl;


        // Offer options to go back to the menu or add another court
        cout << "+*************************************************************************************+" << endl;
        cout << "|                                    1. Go back to menu                               |" << endl;
        cout << "|                                    2. Add another court                             |" << endl;
        cout << "+*************************************************************************************+" << endl;
        cout << "------------------------------" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 2) {
            addCourt(con);
        }
        else {
            cout << "------------------------------" << endl;
            cout << "Returning to the menu." << endl;
            system("cls");
        }
    }

    delete res;
    delete pstmt;
}


void updateCourt(Connection* con) {
    PreparedStatement* pstmt;
    ResultSet* resCheck = nullptr, * resUpdate = nullptr;

    Statement* stmt = con->createStatement();
    ResultSet* res = stmt->executeQuery("SELECT * FROM court");

    cout << "Court Listing:" << endl;
    cout << "------------------------" << endl;
    while (res->next()) {
        cout << res->getString("court_name") << " - " << res->getString("courtLocation") << endl;
    }

    cout << "------------------------" << endl;
    cout << "Enter court name to update (0 to cancel): ";
    string court_name;
    cin.ignore();
    getline(cin, court_name);

    if (court_name != "0") {
        cout << "------------------------------" << endl;
        cout << "Enter court location to update: ";
        string court_location;
        getline(cin, court_location);

        // Check if the court exists
        string checkQuery = "SELECT * FROM court WHERE court_name = ? AND courtLocation = ?";
        pstmt = con->prepareStatement(checkQuery);
        pstmt->setString(1, court_name);
        pstmt->setString(2, court_location);
        resCheck = pstmt->executeQuery();

        if (resCheck->next()) {
            // Court exists, allow updating

            // Get new information
            string newCourtName, newCourtLocation;
            cout << "------------------------------" << endl;
            cout << "Enter new court name: ";
            getline(cin, newCourtName);

            cout << "------------------------------" << endl;
            cout << "Enter new court location: ";
            getline(cin, newCourtLocation);

            char confirmChoice;
            bool isValidChoice = false;

            do {
                cout << "Do you confirm to update this court? (Y/N): ";
                cin >> confirmChoice;

                // Validate the input
                if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
                    cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                else {
                    isValidChoice = true;
                }

            } while (!isValidChoice);

            if (toupper(confirmChoice) != 'Y') {
                cout << "------------------------------" << endl;
                cout << "Court update failed. Returning to the main menu." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                system("cls");
                return;
            }

            // Check if the new court name already exists
            string checkNewNameQuery = "SELECT COUNT(*) FROM court WHERE court_name = ? AND courtLocation = ?";
            pstmt = con->prepareStatement(checkNewNameQuery);
            pstmt->setString(1, newCourtName);
            pstmt->setString(2, newCourtLocation);
            ResultSet* resNewName = pstmt->executeQuery();
            int countNewName = 0;
            if (resNewName->next()) {
                countNewName = resNewName->getInt(1);
            }

            if (countNewName > 0) {
                cout << "------------------------------" << endl;
                cout << "Error: The new court name is already in use. Cannot update." << endl;
            }
            else {
                // Update the court information

                string updateQuery = "UPDATE court SET court_name = ?, courtLocation = ? WHERE court_name = ? AND courtLocation = ?";
                pstmt = con->prepareStatement(updateQuery);
                pstmt->setString(1, newCourtName);
                pstmt->setString(2, newCourtLocation);
                pstmt->setString(3, court_name);
                pstmt->setString(4, court_location);
                resUpdate = pstmt->executeQuery();

                cout << "------------------------------" << endl;
                cout << "Court updated successfully!" << endl;
            }

            delete resNewName;
        }
        else {
            cout << "------------------------------" << endl;
            cout << "Court does not exist. Cannot update." << endl;
        }

        delete resUpdate;
        delete pstmt;
    }

    delete resCheck;
    delete res;
    delete stmt;

    // Offer options to go back to the menu or update another court
    cout << "+*************************************************************************************+" << endl;
    cout << "|                                    1. Go back to menu                               |" << endl;
    cout << "|                                    2. Update another court                          |" << endl;
    cout << "+*************************************************************************************+" << endl;
    cout << "------------------------------" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    system("cls");

    if (choice == 1) {
        // Go back to the menu
        return;
    }
    else if (choice == 2) {
        // Update another court
        updateCourt(con);
    }
    else {
        cout << "------------------------------" << endl;
        cout << "Invalid choice. Going back to the menu." << endl;
        return;
    }
}



// ------------------------------------------------PAYMENT APPROVAL (ADMIN)-------------------------------------------------- 
void Approval_payment()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                      APPROVE PAYMENTS                                |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
}


void approvePayments(Connection* con) {

    Statement* stmt;
    ResultSet* res;

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT BookingID, username, court_name, courtLocation, timeSlot, fee, booking_date FROM booking WHERE status = 'active'");

    cout << "Pending Payments:" << endl;
    cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
    while (res->next()) {
        int BookingID = res->getInt("BookingID");
        string username = res->getString("username");
        string court_name = res->getString("court_name");
        string court_location = res->getString("courtLocation");
        int time_slot = res->getInt("timeSlot");
        double price = res->getDouble("fee");
        string booking_date = res->getString("booking_date");

        cout << "Booking ID: " << BookingID << " |";
        cout << " Username: " << username << " |";
        cout << " Court: " << court_name << " (" << court_location << ")" << " |";
        cout << " Time: " << time_slot << " AM - " << (time_slot + 1) << " AM" << " |";
        cout << " Date: " << booking_date << " |";
        cout << " Price: RM " << price << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;

    }

    int selectedBookingId;
    bool validInput = false;

    do {
        cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Enter the Booking ID to approve (0 to cancel): ";
        cin >> selectedBookingId;

        if (selectedBookingId == 0) {
            cout << "Returning back to menu." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            delete res;
            delete stmt;
            return; // Return from the approvePayments() function
        }

        // Check if the entered Booking ID is valid
        res->beforeFirst(); // Reset the ResultSet to the beginning
        while (res->next()) {
            if (res->getInt("BookingID") == selectedBookingId) {
                validInput = true;
                break;
            }
        }

        if (!validInput) {
            cout << "---------" << endl;
            cout << "Booking ID not found. Please enter a valid Booking ID." << endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }



    } while (!validInput);



    bool found = false;
    res->beforeFirst();
    while (res->next()) {
        int BookingID = res->getInt("BookingID");
        if (BookingID == selectedBookingId) {
            found = true;
            string username = res->getString("username");
            string court_name = res->getString("court_name");
            string court_location = res->getString("courtLocation");
            int time_slot = res->getInt("timeSlot");
            double price = res->getDouble("fee");
            string booking_date = res->getString("booking_date");

            cout << "+*************************************************************************************+" << endl;
            cout << "|                                                                                     |" << endl;
            cout << "|                                    SELECTED BOOKING :                               |" << endl;
            cout << "|                                                                                     |" << endl;
            cout << "+*************************************************************************************+" << endl;
            cout << "                                                                                       " << endl;
            cout << "                                    Booking ID: " << BookingID << endl;
            cout << "                                                                                       " << endl;
            cout << "                                    Username: " << username << endl;
            cout << "                                                                                       " << endl;
            cout << "                                    Court: " << court_name << " (" << court_location << ")" << endl;
            cout << "                                                                                       " << endl;
            cout << "                                    Time: " << time_slot << " AM - " << (time_slot + 1) << " AM" << endl;
            cout << "                                                                                       " << endl;
            cout << "                                    Date: " << booking_date << endl;
            cout << "                                                                                       " << endl;
            cout << "                                    Price: RM " << price << endl;
            cout << "                                                                                       " << endl;
            cout << "+=====================================================================================+" << endl;

            cout << "------------------------------" << endl;
            cout << "Approve payment for this booking? (1 for Approve, 0 for Disapprove): ";
            char choice;
            cin >> choice;
            system("cls");

            if (choice == '1')
            {
                double payment_amount = price;
                string approved = "1";

                // Insert the payment details into transaction
                string insertQuery = "INSERT INTO transaction (BookingID, username, court_name, courtLocation, payment_amount, approval, booking_date) VALUES (?, ?, ?, ?, ?, ?, ?)";
                PreparedStatement* insertStmt = con->prepareStatement(insertQuery);
                insertStmt->setInt(1, BookingID);
                insertStmt->setString(2, username);
                insertStmt->setString(3, court_name);
                insertStmt->setString(4, court_location);
                insertStmt->setDouble(5, payment_amount);
                insertStmt->setString(6, approved);
                insertStmt->setString(7, booking_date);
                insertStmt->execute();
                delete insertStmt;

                string userBookingHistoryQuery = "INSERT INTO user_booking_history (BookingID, username, court_name, courtLocation, payment_amount, approval, booking_date) VALUES (?, ?, ?, ?, ?, ?, ?)";
                PreparedStatement* userBookingHistoryStmt = con->prepareStatement(userBookingHistoryQuery);
                userBookingHistoryStmt->setInt(1, BookingID);
                userBookingHistoryStmt->setString(2, username);
                userBookingHistoryStmt->setString(3, court_name);
                userBookingHistoryStmt->setString(4, court_location);
                userBookingHistoryStmt->setDouble(5, payment_amount);
                userBookingHistoryStmt->setString(6, approved);
                userBookingHistoryStmt->setString(7, booking_date);
                userBookingHistoryStmt->execute();
                delete userBookingHistoryStmt;

                string paymentHistoryQuery = "INSERT INTO payment_history (BookingID, username, court_name, courtLocation, timeSlot, payment_amount, approval, booking_date) VALUES (?, ?, ?, ?, ?, ?, ?, ?)";
                PreparedStatement* paymentHistoryStmt = con->prepareStatement(paymentHistoryQuery);
                paymentHistoryStmt->setInt(1, BookingID);
                paymentHistoryStmt->setString(2, username);
                paymentHistoryStmt->setString(3, court_name);
                paymentHistoryStmt->setString(4, court_location);
                paymentHistoryStmt->setInt(5, time_slot);
                paymentHistoryStmt->setDouble(6, payment_amount);
                paymentHistoryStmt->setString(7, approved);
                paymentHistoryStmt->setString(8, booking_date);
                paymentHistoryStmt->execute();
                delete paymentHistoryStmt;


                // Retrieve and display the approved payment record from payment_table
                stmt = con->createStatement();
                string paymentQuery = "SELECT * FROM transaction WHERE BookingID = ?";
                PreparedStatement* paymentStmt = con->prepareStatement(paymentQuery);
                paymentStmt->setInt(1, BookingID);
                res = paymentStmt->executeQuery();

                cout << "Approved Payment Record:" << endl;
                cout << "-----------------------------------------------------------------------------------------------------------------------" << endl;
                while (res->next()) {
                    int payment_id = res->getInt("transaction_ID");
                    double payment_amount = res->getDouble("payment_amount");
                    string approved = res->getString("approval");
                    string booking_date = res->getString("booking_date");

                    cout << "Transaction ID: " << payment_id << endl;
                    cout << "Booking ID: " << BookingID << endl;
                    cout << "Username: " << username << endl;
                    cout << "Court Name: " << court_name << endl;
                    cout << "Court Location: " << court_location << endl;
                    cout << "Time slot: " << time_slot << endl;
                    cout << "Booking Date: " << booking_date << endl;
                    cout << "Payment Amount: RM " << payment_amount << endl;
                    cout << "Approved: " << approved << endl;
                    cout << endl;
                }

                string deleteQuery = "DELETE FROM booking WHERE BookingID = ? ";
                PreparedStatement* deleteStmt = con->prepareStatement(deleteQuery);
                deleteStmt->setInt(1, BookingID);
                deleteStmt->execute();
                delete deleteStmt;

                cout << "+*************************************************************************************+" << endl;
                cout << "|                                  Choose an option:                                  |" << endl;
                cout << "+*************************************************************************************+" << endl;
                cout << "|                           1. Go back to Admin Main Menu                             |" << endl;
                cout << "|                           2. Approve another payment                                |" << endl;
                cout << "+=====================================================================================+" << endl;
                cout << "------------------------------" << endl;
                cout << "Enter your choice: ";
                int option;
                cin >> option;
                system("cls");

                if (option == 1) {
                    cout << "Returning to Admin Main Menu..." << endl;
                    delete res;
                    delete stmt;
                    return;
                }
                else if (option == 2) {
                    approvePayments(con);
                    break;
                }
                else {
                    cout << "Invalid choice. Press Enter to return to Admin Main Menu..." << endl;

                    cin.ignore();
                    cin.get();
                    delete res;
                    delete stmt;

                    return; // Return from the approvePayments() function
                }
            }
            else if (choice == '0') {
                cout << "------------------------------" << endl;
                cout << "Payment not approved." << endl;
                cout << "Press Enter to return to Admin Main Menu..." << endl;
                cin.ignore();
                cin.get();
                delete res;
                delete stmt;

                return; // Return from the approvePayments() function
            }
            else {
                cout << "------------------------------" << endl;
                cout << "Invalid choice. Please enter '1' or '0'." << endl;
                cout << "Enter to Return to Admin Main Menu..." << endl;
                cin.ignore();
                cin.get();
                delete res;
                delete stmt;

                return; // Return from the approvePayments() function
            }
        }
    }

    if (!found) {
        cout << "----------------------------------------------------------" << endl;
        cout << "Invalid Booking ID. Press Enter to return to Admin Menu..." << endl;
        cin.ignore();  // Ignore any remaining characters in the input buffer
        cin.get();     // Wait for Enter key press
        delete res;
        delete stmt;
        return;
    }

    delete res;
    delete stmt;

}



// -------------------------------------------------DISPLAY CUSTOMERS---------------------------------------------------------------- 
void displayUsers(Connection* con) {
    Statement* stmt;
    ResultSet* res;

    // Query to retrieve all users
    string userQuery = "SELECT username FROM customer";
    stmt = con->createStatement();
    res = stmt->executeQuery(userQuery);

    cout << " +***********************************************************************************************************+" << endl;
    cout << " |                                                List of Customers                                          |" << endl;
    cout << " +***********************************************************************************************************+" << endl;

    vector<string> usernames;

    // Store usernames in a vector
    while (res->next()) {
        string username = res->getString("username");
        usernames.push_back(username);
    }

    // Display usernames in a 5x5 grid
    int count = 0;
    for (size_t i = 0; i < usernames.size(); ++i) {
        if (count % 5 == 0) {
            cout << " | ";
        }
        cout << setw(5) << i + 1 << ")" << setw(15) << usernames[i];
        count++;
        if (count % 5 == 0) {
            cout << " |" << endl;
        }
    }

    // Fill the remaining cells with empty space if needed
    while (count % 5 != 0) {
        cout << setw(20) << " ";
        count++;
    }

    cout << endl << endl;

    delete res;
    delete stmt;
}


// -------------------------------------------------DISPLAY COURTS----------------------------------------------------------------- 
void displayCourts(Connection* con) {
    Statement* stmt;
    ResultSet* res;

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM court");

    cout << "+======================================================================================+" << endl;
    cout << "|                                   Available Courts                                   |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << "|                            Court Name    ||   Court Location                         |" << endl;
    cout << "+======================================================================================+" << endl;

    while (res->next()) {

        cout << "|  " << setw(34) << res->getString("court_name") << "      |";
        cout << "|  " << setw(11) << res->getString("courtLocation") << "                             |" << endl;
    }

    cout << "+======================================================================================+" << endl;

    delete res;
    delete stmt;

    // Wait for the user to press Enter
    cout << "------------------------------" << endl;
    cout << "Press Enter to return to the Customer Menu...";
    cin.ignore();
    cin.get(); // Wait for Enter
    system("cls");
}


// ---------------------------------------------------DISPLAY BOOKED COURTS------------------------------------------------------ 
void displayBookedCourts(Connection* con) {
    Statement* stmt;
    ResultSet* res;

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT * FROM court");

    cout << "+============================================================================+" << endl;
    cout << "|                        Booked Courts and Time Slots                        |" << endl;
    cout << "+============================================================================+" << endl;

    while (res->next()) {
        string court_name = res->getString("court_name");
        string court_location = res->getString("courtLocation");

        // Retrieve booked time slots and dates for the current court
        PreparedStatement* bookedSlotsStmt = con->prepareStatement("SELECT DISTINCT booking_date FROM booking WHERE court_name = ?");
        bookedSlotsStmt->setString(1, court_name);
        ResultSet* bookedDatesRes = bookedSlotsStmt->executeQuery();

        // Display court information
        cout << "               Court Name: " << court_name << "      | Court Location: " << court_location << endl;


        // Display booked time slots and dates
        while (bookedDatesRes->next()) {
            string bookingDate = bookedDatesRes->getString("booking_date");

            // Retrieve time slots for the current date
            PreparedStatement* timeSlotsStmt = con->prepareStatement("SELECT timeSlot FROM booking WHERE court_name = ? AND booking_date = ?");
            timeSlotsStmt->setString(1, court_name);
            timeSlotsStmt->setString(2, bookingDate);
            ResultSet* timeSlotsRes = timeSlotsStmt->executeQuery();

            // Display date and time slots
            cout << "               Booking Date: " << bookingDate << " | Time Slots: ";

            while (timeSlotsRes->next()) {
                cout << timeSlotsRes->getInt("timeSlot") << ",";
            }

            cout << endl;

            delete timeSlotsRes;
            delete timeSlotsStmt;
        }

        cout << "+----------------------------------------------------------------------------+" << endl;

        delete bookedDatesRes;
        delete bookedSlotsStmt;
    }

    delete res;
    delete stmt;

    // Wait for the user to press Enter
    cout << "Press Enter to return to the Customer menu...";
    cin.ignore();
    cin.get(); // Wait for Enter
    system("cls");
}






// -------------------------------------------VIEW USER BOOKINGS HISTORY/REPORT (ADMIN)------------------------------------------- 
void viewUserBookingHistory(Connection* con) {
    displayUsers(con);  // Display the list of users

    string username;

    // Get the username from the admin
    cout << "Enter the username to view booking history: ";
    cin.ignore();
    getline(cin, username);
    system("cls");

    PreparedStatement* pstmt;
    ResultSet* res;

    // Query to retrieve user booking history from the updated user_booking_history table
    string bookingHistoryQuery = "SELECT * FROM user_booking_history WHERE username = ?";
    pstmt = con->prepareStatement(bookingHistoryQuery);
    pstmt->setString(1, username);
    res = pstmt->executeQuery();

    // Check if the result set is empty
    if (!res->next()) {
        cout << "Error: No booking history found for user '" << username << "'." << endl;
        delete res;
        delete pstmt;

        cout << "Press Enter to go back to the Admin Menu...";
        cin.ignore();
        cin.get();
        system("cls");

        return;
    }

    cout << "+=====================================================================================================================================+" << endl;
    cout << "                                                    Customer Booking History for " << username << "                                                   " << endl;
    cout << "+=====================================================================================================================================+" << endl;
    cout << " " << setw(15) << "UserBookingID" << "|" << setw(15) << "BookingID" << "|" << setw(15) << "Username" << "|" << setw(10) << "Court" << "|" << setw(18) << "Court Location" << "|" << setw(18) << "Payment Amount" << "|" << setw(10) << "Approval" << "|" << setw(20) << "Booking Date" << " " << endl;
    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;

    // Reset cursor before fetching data
    res->beforeFirst();

    // Display user booking history from updated user_booking_history table
    while (res->next()) {
        int userBookingID = res->getInt("UserBookingID");
        int bookingID = res->getInt("BookingID");
        string courtName = res->getString("court_name");
        string courtLocation = res->getString("courtLocation");
        double paymentAmount = res->getDouble("payment_amount");
        string approval = res->getString("approval");
        string bookingDate = res->getString("booking_date");

        cout << " " << setw(15) << userBookingID << "|" << setw(15) << bookingID << "|" << setw(15) << username << "|" << setw(10) << courtName << "|" << setw(18) << courtLocation << "|" << setw(18) << paymentAmount << "|" << setw(10) << approval << "|" << setw(20) << bookingDate << " " << endl;
    }

    cout << "+-------------------------------------------------------------------------------------------------------------------------------------+" << endl;

    delete res;
    delete pstmt;

    cout << "Press Enter to go back to the Admin Menu...";
    cin.ignore();
    cin.get();
    system("cls");

    return;
}




// ----------------------------------------------VIEW USER PAYMENT HISTORY/REPORT (ADMIN)---------------------------------------- 
void viewPaymentHistory(Connection* con) {
    displayUsers(con);  // Display the list of users

    string username;

    // Get the username from the admin
    cout << "Enter the username to view payment history: ";
    cin.ignore();
    getline(cin, username);
    system("cls");

    PreparedStatement* pstmt;
    ResultSet* res;

    // Query to retrieve user payment history from payment_history table
    string paymentHistoryQuery = "SELECT * FROM payment_history WHERE username = ?";
    pstmt = con->prepareStatement(paymentHistoryQuery);
    pstmt->setString(1, username);
    res = pstmt->executeQuery();

    // Check if the result set is empty
    if (!res->next()) {
        cout << "Error: No payment history to print found for user '" << username << "'." << endl;
        delete res;
        delete pstmt;

        cout << "Press Enter to go back to the Admin Menu...";
        cin.ignore();
        cin.get();
        system("cls");

        return;
    }

    cout << "+==================================================================================================================================================================+" << endl;
    cout << "                                                                     Payment History for " << username << "                                                           " << endl;
    cout << "+==================================================================================================================================================================+" << endl;
    cout << " " << setw(15) << "UserPaymentID" << "|" << setw(15) << "BookingID" << "|" << setw(15) << "Username" << "|" << setw(15) << "Court Name" << "|" << setw(15) << "Court Location" << "|"
        << setw(15) << "Time Slot" << "|" << setw(15) << "Amount" << "|" << setw(20) << "Approval" << "|" << setw(20) << "Booking Date" << " " << endl;
    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;

    // Reset cursor before fetching data
    res->beforeFirst();

    // Display user payment history from payment_history table
    while (res->next()) {
        int UserPaymentID = res->getInt("userPaymentID");
        int bookingID = res->getInt("BookingID");
        string username = res->getString("username");
        string courtName = res->getString("court_name");
        string courtLocation = res->getString("courtLocation");
        string timeSlot = res->getString("timeSlot");
        double amount = res->getDouble("payment_amount");
        string approval = res->getString("approval");
        string bookingDate = res->getString("booking_date");

        cout << " " << setw(15) << UserPaymentID << "|" << setw(15) << bookingID << "|" << setw(15) << username << "|" << setw(15) << courtName << "|" << setw(15) << courtLocation << "|"
            << setw(15) << timeSlot << "|" << setw(15) << amount << "|" << setw(20) << approval << "|" << setw(20) << bookingDate << " " << endl;
    }

    cout << "+------------------------------------------------------------------------------------------------------------------------------------------------------------------+" << endl;

    delete res;
    delete pstmt;

    // Pause to allow the user to read the report
    cout << "Press Enter to go back to the Admin Menu...";
    cin.ignore();
    cin.get();
    system("cls");

    return;
}



// ------------------------------------------UPDATE ACCOUNTS USER INFORMATION (CUSTOMER)-------------------------------------- 

void goToLoginMenu() {
    cout << "Returning back to Login menu" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

void update_Account()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                            UPDATE CUSTOMER ACCOUNT INFORMATION                       |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;

}
void updateUser(Connection* con, const string& username, const string& newPassword) {
    try {
        // Retrieve customer details
        PreparedStatement* selectStmt = con->prepareStatement("SELECT * FROM customer WHERE username = ?");
        selectStmt->setString(1, username);
        ResultSet* res = selectStmt->executeQuery();

        if (!res->next()) {
            cout << "Error: Unable to retrieve customer details." << endl;
            delete selectStmt;
            return;
        }

        cout << "Customer Details:" << endl;
        cout << "---------------------------" << endl;
        cout << "Username: " << res->getString("username") << endl;
        cout << "Password: " << res->getString("password") << endl;
        cout << "Email: " << res->getString("email") << endl;
        cout << "Phone Number: " << res->getString("phone_number") << endl;
        cout << "---------------------------" << endl;

        delete res;
        delete selectStmt;

        int updateChoice;
        do {
            cout << "+**************************************************************************************+" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                Select what to update:                                |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "+**************************************************************************************+" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   1. Password                                        |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   2. Email                                           |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   3. Phone Number                                    |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   4. Username                                        |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   5. Back to Customer Menu                           |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "+======================================================================================+" << endl;

            cout << "Enter your choice: ";
            while (true) {
                cin >> updateChoice;

                if (cin.fail()) {
                    cout << "Error: Invalid input. Please enter a valid integer." << endl;
                    cin.clear(); // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "--------------------------------------------" << endl;
                    cout << "Enter your choice: ";
                }
                else {
                    break;
                }
            }

            switch (updateChoice) {
            case 1: {
                string newPassword;
                cout << "Enter new password: ";
                cin >> newPassword;

                char confirmChoice;
                bool isValidChoice = false;

                do {
                    cout << "Do you want to confirm your password? (Y/N): ";
                    cin >> confirmChoice;

                    // Validate the input
                    if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
                        cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else {
                        isValidChoice = true;
                    }

                } while (!isValidChoice);

                if (toupper(confirmChoice) != 'Y') {
                    cout << "------------------------------" << endl;
                    cout << "Password update canceled." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE customer SET password = ? WHERE username = ?");
                stmt->setString(1, newPassword);
                stmt->setString(2, username);
                stmt->executeUpdate();

                delete stmt;
                cout << "Password updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                break;

            }
            case 2: {
                string newEmail;

                do {
                    cout << "------------------------------" << endl;
                    cout << "Enter new email: ";

                    getline(cin, newEmail);

                    // Validate email format
                    size_t atPos = newEmail.find('@');
                    if (atPos == string::npos) {
                        cout << "Invalid email format. Email must contain '@'. Please try again." << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else {
                        break;  // Valid email, exit the loop
                    }
                } while (true);

                char confirmChoice;
                bool isValidChoice = false;

                do {
                    cout << "Do you want to confirm your email? (Y/N): ";
                    cin >> confirmChoice;

                    // Validate the input
                    if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
                        cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else {
                        isValidChoice = true;
                    }

                } while (!isValidChoice);

                if (toupper(confirmChoice) != 'Y') {
                    cout << "------------------------------" << endl;
                    cout << "Email update canceled." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE customer SET email = ? WHERE username = ?");
                stmt->setString(1, newEmail);
                stmt->setString(2, username);
                stmt->executeUpdate();
                delete stmt;
                cout << "Email updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                break;
            }
            case 3: {
                string newPhoneNumber;
                cout << "Enter new phone number: ";
                cin >> newPhoneNumber;

                char confirmChoice;
                bool isValidChoice = false;

                do {
                    cout << "Do you want to confirm your phone number? (Y/N): ";
                    cin >> confirmChoice;

                    // Validate the input
                    if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
                        cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else {
                        isValidChoice = true;
                    }

                } while (!isValidChoice);

                if (toupper(confirmChoice) != 'Y') {
                    cout << "------------------------------" << endl;
                    cout << "Phone number update canceled." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE customer SET phone_number = ? WHERE username = ?");
                stmt->setString(1, newPhoneNumber);
                stmt->setString(2, username);
                stmt->executeUpdate();
                delete stmt;
                cout << "Phone number updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                break;
            }
            case 4: {
                string newUsername;
                cout << "Enter new username: ";
                cin >> newUsername;

                char confirmChoice;
                bool isValidChoice = false;

                do {
                    cout << "Do you want to confirm your username? (Y/N): ";
                    cin >> confirmChoice;

                    // Validate the input
                    if (cin.fail() || (toupper(confirmChoice) != 'Y' && toupper(confirmChoice) != 'N')) {
                        cout << "Invalid input. Please enter 'Y' or 'N'." << endl;
                        cin.clear();
                        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                    else {
                        isValidChoice = true;
                    }

                } while (!isValidChoice);

                if (toupper(confirmChoice) != 'Y') {
                    cout << "------------------------------" << endl;
                    cout << "Username update canceled." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(2));

                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE customer SET username = ? WHERE username = ?");
                stmt->setString(1, newUsername);
                stmt->setString(2, username);
                stmt->executeUpdate();
                delete stmt;
                cout << "Username updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                cout << "IMPORTANT : Please re-login to your account after changing your username." << endl;
                cout << "------------------------------------" << endl;
                break;


            }
            case 5:
                cout << "Returning back to Customer menu" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                system("cls");
                return; // Go back to the customer menu

            default:
                cout << "Invalid choice. Nothing updated." << endl;
            }

            cout << "Do you want to update anything else? (1 for Yes, 0 for No): ";
            cin >> updateChoice;
            system("cls");

        } while (updateChoice == 1);


    }
    catch (SQLException& e) {
        cout << "User update failed: " << e.what() << endl;
        system("cls");
    }
}

// ---------------------------------------UPDATE ACCOUNTS ADMIN INFORMATION (ADMIN)---------------------------------------------- 
void update_Admin()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                            UPDATE ADMIN ACCOUNT INFORMATION                          |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;

}
void updateAdmin(Connection* con, const string& username, const string& newPassword)
{
    try {
        // Retrieve admin details
        PreparedStatement* selectStmt = con->prepareStatement("SELECT * FROM admin WHERE username = ?");
        selectStmt->setString(1, username);
        ResultSet* res = selectStmt->executeQuery();

        if (!res->next()) {
            cout << "Error: Unable to retrieve admin details." << endl;
            delete selectStmt;
            return;
        }

        cout << "Admin Details:" << endl;
        cout << "---------------------------" << endl;
        cout << "Username: " << res->getString("username") << endl;
        cout << "Password: " << res->getString("password") << endl;
        cout << "Email: " << res->getString("email") << endl;
        cout << "Phone Number: " << res->getString("phone_number") << endl;
        cout << "---------------------------" << endl;

        delete res;
        delete selectStmt;

        int updateChoice;
        do {
            cout << "+**************************************************************************************+" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                Select what to update:                                |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "+**************************************************************************************+" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   1. Password                                        |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   2. Email                                           |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   3. Phone Number                                    |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   4. Username                                        |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "|                                   5. Back to Admin Menu                              |" << endl;
            cout << "|                                                                                      |" << endl;
            cout << "+======================================================================================+" << endl;

            cout << "Enter your choice: ";
            while (true) {
                cin >> updateChoice;

                if (cin.fail()) {
                    cout << "Error: Invalid input. Please enter a valid integer." << endl;
                    cin.clear(); // Clear error flag
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                    cout << "--------------------------------------------" << endl;
                    cout << "Enter your choice: ";
                }
                else {
                    break;
                }
            }

            switch (updateChoice) {
            case 1: {
                string newPassword;
                cout << "Enter new password: ";
                cin >> newPassword;

                cout << "Do you want to confirm your changes? (y/n): ";
                char confirmBookingChoice;
                cin >> confirmBookingChoice;

                if (confirmBookingChoice != 'y' && confirmBookingChoice != 'Y') {
                    // User chose not to continue booking
                    cout << "------------------" << endl;
                    cout << "Update cancelled." << endl;
                    cout << "------------------" << endl;


                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE admin SET password = ? WHERE username = ?");
                stmt->setString(1, newPassword);
                stmt->setString(2, username);
                stmt->executeUpdate();
                delete stmt;
                cout << "Password updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                break;
                system("cls");
            }
            case 2: {
                string newEmail;
                do {
                    cout << "------------------------------" << endl;
                    cout << "Enter new email: ";

                    getline(cin, newEmail);

                    // Validate email format
                    size_t atPos = newEmail.find('@');
                    if (atPos == string::npos) {
                        cout << "Invalid email format. Email must contain '@'. Please try again." << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                    }
                    else {
                        break;  // Valid email, exit the loop
                    }
                } while (true);

                cout << "Do you want to confirm your changes? (y/n): ";
                char confirmBookingChoice;
                cin >> confirmBookingChoice;

                if (confirmBookingChoice != 'y' && confirmBookingChoice != 'Y') {
                    // User chose not to continue booking
                    cout << "------------------" << endl;
                    cout << "Update cancelled." << endl;
                    cout << "------------------" << endl;


                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE admin SET email = ? WHERE username = ?");
                stmt->setString(1, newEmail);
                stmt->setString(2, username);
                stmt->executeUpdate();
                delete stmt;
                cout << "Email updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                break;
                system("cls");
            }
            case 3: {
                string newPhoneNumber;
                cout << "Enter new phone number: ";
                cin >> newPhoneNumber;

                cout << "Do you want to confirm your changes? (y/n): ";
                char confirmBookingChoice;
                cin >> confirmBookingChoice;

                if (confirmBookingChoice != 'y' && confirmBookingChoice != 'Y') {
                    // User chose not to continue booking
                    cout << "------------------" << endl;
                    cout << "Update cancelled." << endl;
                    cout << "------------------" << endl;


                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE admin SET phone_number = ? WHERE username = ?");
                stmt->setString(1, newPhoneNumber);
                stmt->setString(2, username);
                stmt->executeUpdate();
                delete stmt;
                cout << "Phone number updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                break;
                system("cls");
            }
            case 4: {
                string newUsername;
                cout << "Enter new username: ";
                cin >> newUsername;

                cout << "Do you want to confirm your changes? (y/n): ";
                char confirmBookingChoice;
                cin >> confirmBookingChoice;

                if (confirmBookingChoice != 'y' && confirmBookingChoice != 'Y') {
                    // User chose not to continue booking
                    cout << "------------------" << endl;
                    cout << "Update cancelled." << endl;
                    cout << "------------------" << endl;


                    break;
                }

                PreparedStatement* stmt = con->prepareStatement("UPDATE admin SET username = ? WHERE username = ?");
                stmt->setString(1, newUsername);
                stmt->setString(2, username);
                stmt->executeUpdate();
                delete stmt;
                cout << "Username updated successfully!" << endl;
                cout << "------------------------------------" << endl;
                cout << "IMPORTANT : Please re-login to your account after changing your username." << endl;
                cout << "------------------------------------" << endl;
                break;
                system("cls");
            }
            case 5:
                cout << "Returning back to Admin menu..." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                system("cls");
                return; // Go back to the admin menu

            default:
                cout << "Invalid choice. Nothing updated." << endl;

            }

            cout << "Do you want to update anything else? (1 for Yes, 0 for No): ";
            cin >> updateChoice;
            system("cls");


        } while (updateChoice == 1);

        system("cls");

    }
    catch (SQLException& e) {
        cout << "Admin update failed: " << e.what() << endl;
        system("cls");
    }
}

// ----------------------------------------------DISPLAY USER TRANSACTIONS (CUSTOMER)------------------------------------------ 
void displayUserPaymentHistory(Connection* con, const string& username) {
    try {
        string query = "SELECT * FROM payment_history WHERE username = ?";
        PreparedStatement* pstmt = con->prepareStatement(query);
        pstmt->setString(1, username);

        ResultSet* res = pstmt->executeQuery();

        cout << "+=============================================================================================================+" << endl;
        cout << "                                    PAYMENT HISTORY FOR CUSTOMER: " << username << "                     " << endl;
        cout << "+=============================================================================================================+" << endl;

        // Check if the result set is empty
        if (!res->next()) {
            cout << "No payment history to print found for customer: " << username << endl;
            cout << "+--------------------------------------------+" << endl;
        }
        else {
            do {
                int userPaymentID = res->getInt("userPaymentID");
                int bookingID = res->getInt("BookingID");
                string courtName = res->getString("court_name");
                string courtLocation = res->getString("courtLocation");
                int time_slot = res->getInt("timeSlot");
                double paymentAmount = res->getDouble("payment_amount");
                string approval = res->getString("approval");
                string bookingDate = res->getString("booking_date");

                cout << " User Payment ID: " << userPaymentID << " |";
                cout << " Booking ID: " << bookingID << " |";
                cout << " Court Name: " << courtName << " |";
                cout << " Court Location: " << courtLocation << " |" << endl;
                cout << " Time slot: " << time_slot << " |";
                cout << " Payment Amount: RM " << paymentAmount << " |";
                cout << " Approval: " << approval << " |";
                cout << " Booking Date: " << bookingDate << endl;
                cout << "+-------------------------------------------------------------------------------------------------------------+" << endl;
            } while (res->next());
        }

        delete pstmt;
        delete res;

        cout << "Press Enter to go back to the menu...";
        cin.ignore(); // consume the newline character left in the input buffer
        cin.get();    // wait for the user to press Enter
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}



// ----------------------------------------------DISPLAY ALL APPROVED TRANSACTIONS (ADMIN)------------------------------------------ 
void displayAllTransactions(Connection* con) {
    int choice;
    string searchUsername;

    do {
        cout << "+==========================================+" << endl;
        cout << "|                                          |" << endl;
        cout << "|                                          |" << endl;
        cout << "|        DISPLAY ALL TRANSACTIONS MENU     |" << endl;
        cout << "|                                          |" << endl;
        cout << "|                                          |" << endl;
        cout << "+==========================================+" << endl;
        cout << "|                                          |" << endl;
        cout << "|        1. Display All Transactions       |" << endl;
        cout << "|                                          |" << endl;
        cout << "|        2. Search by Username             |" << endl;
        cout << "|                                          |" << endl;
        cout << "|        3. Back to Admin Menu             |" << endl;
        cout << "|                                          |" << endl;
        cout << "+==========================================+" << endl;
        cout << "Enter your choice: ";
        while (!(cin >> choice)) {
            // Handle the case where the user enters a non-integer
            cout << "Invalid input. Please enter a valid integer." << endl;
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "--------------------------------------------" << endl;
            cout << "Enter your choice: ";
        }
        system("cls");

        switch (choice) {
        case 1:
            // Display all transactions
            try {
                string query = "SELECT * FROM transaction";
                Statement* stmt = con->createStatement();
                ResultSet* res = stmt->executeQuery(query);

                cout << "+=====================================================================================+" << endl;
                cout << "|                        ALL APPROVED TRANSACTIONS IN THE DATABASE                    |" << endl;
                cout << "+=====================================================================================+" << endl;

                int rowCount = 0;
                const int rowsPerPage = 20;

                while (res->next()) {
                    int transactionID = res->getInt("transaction_ID");
                    int bookingID = res->getInt("BookingID");
                    string username = res->getString("username");
                    string court_name = res->getString("court_name");
                    string court_location = res->getString("courtLocation");
                    double paymentAmount = res->getDouble("payment_amount");
                    string approval = res->getString("approval");
                    string booking_date = res->getString("booking_date");

                    cout << " Transaction ID: " << transactionID << " |";
                    cout << " Booking ID: " << bookingID << " |";
                    cout << " Username: " << username << " |";
                    cout << " Court Name: " << court_name << endl;
                    cout << " Court Location: " << court_location << " |";
                    cout << " Payment Amount: RM " << paymentAmount << " |";
                    cout << " Approval: " << approval << " |";
                    cout << " Booking Date: " << booking_date << endl;
                    cout << "+-------------------------------------------------------------------------------------+" << endl;

                    rowCount++;

                    if (rowCount % rowsPerPage == 0) {
                        cout << "Press Enter to display the next " << rowsPerPage << " rows (0 to stop): ";
                        string userInput;
                        getline(cin, userInput);

                        if (!userInput.empty()) {
                            break; // Exit the loop if the user inputs anything
                        }
                    }
                }

                delete stmt;
                delete res;

                cout << "Press Enter to go back to the menu...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume the newline character
                cin.get();
                system("cls");
            }
            catch (sql::SQLException& e) {
                cout << "SQL Error: " << e.what() << endl;
            }
            break;


        case 2:
            displayUsers(con);
            // Search transactions by username
            cout << "Enter the username to search: ";
            cin >> searchUsername;
            system("cls");

            try {
                // Check if the username exists in the database
                string checkQuery = "SELECT COUNT(*) AS count FROM transaction WHERE username = ?";
                PreparedStatement* checkStmt = con->prepareStatement(checkQuery);
                checkStmt->setString(1, searchUsername);

                ResultSet* checkRes = checkStmt->executeQuery();
                checkRes->next();
                int userCount = checkRes->getInt("count");

                delete checkStmt;
                delete checkRes;

                if (userCount == 0) {
                    cout << "Username not found in the database. Please try again." << endl;
                    cout << "Press Enter to go back to the menu...";
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume the newline character
                    cin.get();
                    system("cls");
                    break;
                }

                // Continue with the original query to fetch transactions
                string query = "SELECT * FROM transaction WHERE username = ?";
                PreparedStatement* pstmt = con->prepareStatement(query);
                pstmt->setString(1, searchUsername);

                ResultSet* res = pstmt->executeQuery();

                cout << "+=====================================================================================+" << endl;
                cout << "            SEARCHED TRANSACTIONS FOR USERNAME: " << searchUsername << "                                " << endl;
                cout << "+=====================================================================================+" << endl;

                while (res->next()) {
                    int transactionID = res->getInt("transaction_ID");
                    int bookingID = res->getInt("BookingID");
                    double paymentAmount = res->getDouble("payment_amount");
                    string approval = res->getString("approval");
                    string court_name = res->getString("court_name");
                    string court_location = res->getString("courtLocation");
                    string booking_date = res->getString("booking_date");

                    cout << " Transaction ID: " << transactionID << " |";
                    cout << "  Booking ID: " << bookingID << " |";
                    cout << "  Payment Amount: RM " << paymentAmount << " |";
                    cout << "  Approval: " << approval << endl;
                    cout << " Court Name: " << court_name << " |";
                    cout << " Court Location: " << court_location << " |";
                    cout << " Booking Date: " << booking_date << endl;
                    cout << "+-------------------------------------------------------------------------------------+" << endl;
                }

                delete pstmt;
                delete res;

                cout << "Press Enter to go back to the menu...";
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // consume the newline character
                cin.get();
                system("cls");
            }
            catch (sql::SQLException& e) {
                cout << "SQL Error: " << e.what() << endl;
            }
            break;

        case 3:
            cout << "Returning to the main menu..." << endl;
            system("cls");
            break;

        default:
            cout << "                            Invalid choice. Please try again." << endl;
            cout << "----------------------------------------------------------------------------------------" << endl;
            break;
        }
    } while (choice != 3);
}



// ----------------------------------------------PRINT RECEIPT (USER)------------------------------------------ 
void printReceiptMenu()
{
    cout << "+=====================================================================================+" << endl;
    cout << "|                               DISPLAY YOUR RECEIPT                                  |" << endl;
    cout << "+=====================================================================================+" << endl;
}

void printReceipt(Connection* con, const string& username) {
    int userPaymentID;

    // Loop until a valid integer is entered
    while (true) {
        cout << "Enter your User Payment ID: ";

        // Check if the input is a valid integer
        if (cin >> userPaymentID) {
            break; // Exit the loop if a valid integer is entered
        }
        else {
            cout << "Error: Invalid input. Please enter a valid integer." << endl;
            cin.clear(); // Clear error flag
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        }
    }

    try {
        string query = "SELECT * FROM payment_history WHERE userPaymentID = ? AND username = ?";
        PreparedStatement* pstmt = con->prepareStatement(query);
        pstmt->setInt(1, userPaymentID);
        pstmt->setString(2, username);

        ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            // Fetch the payment details
            int bookingID = res->getInt("BookingID");
            string court_name = res->getString("court_name");
            string court_location = res->getString("courtLocation");
            int time_slot = res->getInt("timeSlot");
            double paymentAmount = res->getDouble("payment_amount");
            string approval = res->getString("approval");
            string bookingDate = res->getString("booking_date");

            // Print the receipt
            cout << "+*************************************************************************************+" << endl;
            cout << "|                                      RECEIPT                                        |" << endl;
            cout << "+*************************************************************************************+" << endl;
            cout << " User Payment ID: " << userPaymentID << endl;
            cout << " Booking ID: " << bookingID << endl;
            cout << " Username: " << username << endl;
            cout << " Court Name: " << court_name << endl;
            cout << " Court Location: " << court_location << endl;
            cout << " Time slot: " << time_slot << endl;
            cout << " Booking Date: " << bookingDate << endl;
            cout << " Payment Amount: RM " << paymentAmount << endl;
            cout << " Approval: " << approval << endl;
            cout << "+=====================================================================================+" << endl;

            char confirmation;
            cout << "Are you sure you want to print the receipt? (y/n): ";
            cin >> confirmation;

            // Check user confirmation
            if (confirmation != 'y' && confirmation != 'Y') {
                cout << "Printing canceled. Returning to the Customer Menu..." << endl;
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cin.get();
                system("cls");
                return;
            }

            // Delete the payment history data
            string deleteQuery = "DELETE FROM payment_history WHERE userPaymentID = ?";
            PreparedStatement* deleteStmt = con->prepareStatement(deleteQuery);
            deleteStmt->setInt(1, userPaymentID);
            deleteStmt->executeUpdate();
            delete deleteStmt;

            cout << "Your receipt has been successfully printed." << endl;
        }
        else {
            cout << "Error: User Payment ID not found or does not belong to the user." << endl;
        }

        delete pstmt;
        delete res;
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }

    // Pause to let the user view the receipt or error message before returning
    cout << "-----------------------------------------------------" << endl;
    cout << "Press Enter to go back to the Customer Menu... ";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.get();
    system("cls");
}





// --------------------------------------------CALCULATING CUSTOMER REVENUE (ADMIN)---------------------------------------------- 


void generateMonthlyRevenueReportByMonth(Connection* con, int year, int month) {
    try {
        string query = "SELECT court_name, SUM(payment_amount) AS monthly_revenue FROM transaction WHERE YEAR(booking_date) = ? AND MONTH(booking_date) = ? GROUP BY court_name";
        PreparedStatement* pstmt = con->prepareStatement(query);
        pstmt->setInt(1, year);
        pstmt->setInt(2, month);
        ResultSet* res = pstmt->executeQuery();

        double grandTotalRevenue = 0.0;

        cout << "+===========================================================================================+" << endl;
        cout << "                            MONTHLY REVENUE REPORT FOR " << month << "/" << year << "                          " << endl;
        cout << "+===========================================================================================+" << endl;

        while (res->next()) {
            string courtName = res->getString("court_name");
            double monthlyRevenue = res->getDouble("monthly_revenue");

            grandTotalRevenue += monthlyRevenue;

            cout << " Court Name: " << courtName << endl;
            cout << " Monthly Revenue: RM " << monthlyRevenue << endl;
            cout << "+-------------------------------------------------------------------------------------------+" << endl;
        }

        cout << " Grand Total Monthly Revenue: RM " << grandTotalRevenue << endl;
        cout << "+-------------------------------------------------------------------------------------------+" << endl;

        delete pstmt;
        delete res;

        cout << "Press Enter to go back to the menu...";
        cin.ignore(); // consume the newline character left in the input buffer
        cin.get();
        system("cls");
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}


void generateMonthlyRevenueReportByCourtMonth(Connection* con) {
    try {
        cout << "+===========================================================================================+" << endl;
        cout << "|                                     MONTHLY REVENUE REPORT                                |" << endl;
        cout << "+===========================================================================================+" << endl;
        // Ask the user to input the court name
        cout << "Enter Court Name: ";
        string inputCourtName;
        cin.get();
        getline(cin, inputCourtName);

        string query = "SELECT court_name, YEAR(booking_date) AS year, MONTH(booking_date) AS month, SUM(payment_amount) AS total_revenue FROM transaction WHERE court_name = ? GROUP BY court_name, year, month";
        PreparedStatement* pstmt = con->prepareStatement(query);
        pstmt->setString(1, inputCourtName); // Bind the input court name to the query

        ResultSet* res = pstmt->executeQuery();

        int rowCount = 0;
        double grandTotalRevenue = 0.0;

        cout << "+===========================================================================================+" << endl;
        cout << "                            MONTHLY REVENUE REPORT FOR " << setw(30) << left << inputCourtName << "              " << endl;
        cout << "+===========================================================================================+" << endl;
        cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
        cout << "| Court Name           | Year                 | Month                | Total Revenue (RM)   |" << endl;
        cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;

        if (res->next()) {
            do {
                string courtName = res->getString("court_name");
                int year = res->getInt("year");
                int month = res->getInt("month");
                double totalRevenue = res->getDouble("total_revenue");

                cout << "| " << setw(21) << left << courtName << "| " << setw(21) << left << year << "| " << setw(21) << left << month << "| " << setw(21) << left << totalRevenue << "|" << endl;

                rowCount++;
                grandTotalRevenue += totalRevenue;

                if (rowCount % 100 == 0 && !res->isLast()) {
                    cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                    cout << "| Court Name           | Year                 | Month                | Total Revenue (RM)   |" << endl;
                    cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                    // Repeat the court name for the next set of rows
                    cout << "| " << setw(21) << left << courtName;
                }
            } while (res->next());
        }

        if (rowCount == 0) {
            cout << "No data available for court: " << inputCourtName << endl;
        }
        else {
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
            cout << "                           Grand Total Revenue: RM " << grandTotalRevenue << endl;
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
        }

        delete pstmt;
        delete res;

        cout << "Press Enter to go back to the menu...";
        cin.ignore(); // consume the newline character left in the input buffer
        cin.get();
        system("cls");
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void generateMonthlyRevenueReport(Connection* con) {
    try {
        cout << "+===========================================================================================+" << endl;
        cout << "|                                     MONTHLY REVENUE REPORT                                |" << endl;
        cout << "+===========================================================================================+" << endl;
        string query = "SELECT court_name, YEAR(booking_date) AS year, MONTH(booking_date) AS month, SUM(payment_amount) AS total_revenue FROM transaction GROUP BY court_name, year, month";
        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(query);

        int rowCount = 0;
        double grandTotalRevenue = 0.0;
        string currentCourtName = "";
        int currentYear = -1; // Initialize with an invalid year

        cout << "+===========================================================================================+" << endl;
        cout << "|                                  MONTHLY REVENUE REPORT                                   |" << endl;
        cout << "+===========================================================================================+" << endl;
        cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
        cout << "| Court Name           | Year                 | Month                | Total Revenue (RM)   |" << endl;
        cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;

        while (res->next()) {
            string courtName = res->getString("court_name");
            int year = res->getInt("year");
            int month = res->getInt("month");
            double totalRevenue = res->getDouble("total_revenue");

            if (courtName != currentCourtName) {
                if (rowCount != 0) {
                    cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                }


                cout << "Press Enter to display the next row...";
                cin.ignore(); // consume the newline character left in the input buffer
                cin.get();
                cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                cout << "| " << setw(21) << left << courtName;
                currentCourtName = courtName;
                currentYear = -1; // Reset currentYear when court changes


            }
            else {
                cout << "| " << setw(21) << left << ""; // Empty string for the court name column
            }

            if (year != currentYear) {
                cout << "| " << setw(21) << left << year;
                currentYear = year;
            }
            else {
                cout << "| " << setw(21) << left << ""; // Empty string for the year column
            }

            cout << "| " << setw(21) << left << month << "| " << setw(21) << left << totalRevenue << "|" << endl;

            rowCount++;
            grandTotalRevenue += totalRevenue;

            if (rowCount % 100 == 100 && res->isLast() == false) {
                cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                cout << "| Court Name           | Year                 | Month                | Total Revenue (RM)   |" << endl;
                cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
            }
        }

        if (rowCount == 0) {
            cout << "No data available." << endl;
        }
        else {
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
            cout << "                           Grand Total Revenue: RM " << grandTotalRevenue << endl;
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
        }

        delete stmt;
        delete res;

        cout << "Press Enter to go back to the menu...";
        cin.ignore(); // consume the newline character left in the input buffer
        cin.get();
        system("cls");
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void generateWeeklyRevenueReport(Connection* con) {
    try {

        string query = "SELECT court_name, YEAR(booking_date) AS year, WEEK(booking_date) AS week, SUM(payment_amount) AS total_revenue FROM transaction GROUP BY court_name, year, week";
        Statement* stmt = con->createStatement();
        ResultSet* res = stmt->executeQuery(query);

        int rowCount = 0;
        double grandTotalRevenue = 0.0;
        string currentCourtName = "";
        int currentYear = -1;
        double currentCourtTotal = 0.0;

        cout << "+===========================================================================================+" << endl;
        cout << "|                                   WEEKLY REVENUE REPORT                                   |" << endl;
        cout << "+===========================================================================================+" << endl;
        cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
        cout << "| Court Name           | Year                 | Week                 | Total Revenue (RM)   |" << endl;
        cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;

        while (res->next()) {
            string courtName = res->getString("court_name");
            int year = res->getInt("year");
            int week = res->getInt("week");
            double totalRevenue = res->getDouble("total_revenue");

            if (courtName != currentCourtName) {
                if (rowCount != 0) {
                    cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                    cout << "| " << setw(21) << left << "Court Total" << "| " << setw(21) << left << "" << "| " << setw(21) << left << "" << "| " << setw(21) << left << currentCourtTotal << "|" << endl;
                    cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                }

                cout << "Press Enter to display the next row..." << endl;

                cin.ignore(); // consume the newline character left in the input buffer
                cin.get();
                cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
                cout << "| " << setw(21) << left << courtName;
                currentCourtName = courtName;
                currentYear = -1; // Reset currentYear when court changes
                currentCourtTotal = 0.0;


            }
            else {

                cout << "| " << setw(21) << left << ""; // Empty string for the court name column

            }

            if (year != currentYear) {
                cout << "| " << setw(21) << left << year;
                currentYear = year;
            }
            else {
                cout << "| " << setw(21) << left << ""; // Empty string for the year column
            }

            cout << "| " << setw(21) << left << week << "| " << setw(21) << left << totalRevenue << "|" << endl;

            rowCount++;
            currentCourtTotal += totalRevenue;
            grandTotalRevenue += totalRevenue;

            // Wait for user to press Enter before printing the next row

        }

        // Display the total for the last court
        if (rowCount != 0) {
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
            cout << "| " << setw(21) << left << "Court Total" << "| " << setw(21) << left << "" << "| " << setw(21) << left << "" << "| " << setw(21) << left << currentCourtTotal << "|" << endl;
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;


        }

        if (rowCount == 0) {
            cout << "No data available." << endl;
        }
        else {
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
            cout << "                           Grand Total Revenue: RM " << grandTotalRevenue << endl;
            cout << "+----------------------+----------------------+----------------------+----------------------+" << endl;
        }

        delete stmt;
        delete res;


    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}





void generateMonthlyReportByCourt(Connection* con, int year, int month, const std::string& courtName) {
    try {
        cout << "+===========================================================================================+" << endl;
        cout << "|                                     MONTHLY REVENUE REPORT                                |" << endl;
        cout << "+===========================================================================================+" << endl;
        string query = "SELECT DAY(booking_date) AS day, SUM(payment_amount) AS daily_revenue FROM transaction WHERE YEAR(booking_date) = ? AND MONTH(booking_date) = ? AND court_name = ? GROUP BY DAY(booking_date)";
        PreparedStatement* pstmt = con->prepareStatement(query);
        pstmt->setInt(1, year);
        pstmt->setInt(2, month);
        pstmt->setString(3, courtName);
        ResultSet* res = pstmt->executeQuery();

        double totalMonthlyRevenue = 0.0;

        cout << "+===========================================================================================+" << endl;
        cout << "                               MONTHLY REPORT FOR " << courtName << " - " << month << "/" << year << "                              " << endl;
        cout << "+===========================================================================================+" << endl;

        while (res->next()) {
            int day = res->getInt("day");
            double dailyRevenue = res->getDouble("daily_revenue");

            totalMonthlyRevenue += dailyRevenue;

            cout << " Day " << day << ": RM " << dailyRevenue << endl;
            cout << "+-------------------------------------------------------------------------------------------+" << endl;
        }

        cout << " Total Monthly Revenue for " << courtName << ": RM " << totalMonthlyRevenue << endl;
        cout << "+-------------------------------------------------------------------------------------------+" << endl;

        delete pstmt;
        delete res;

        cout << "Press Enter to go back to the menu...";
        cin.ignore(); // consume the newline character left in the input buffer
        cin.get();
        system("cls");
    }
    catch (sql::SQLException& e) {
        cout << "SQL Error: " << e.what() << endl;
    }
}

void Menu_Reports(Connection* con) {
    int choice;

    do {
        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "|                                                                             |" << endl;
        cout << "|                            Monthly Revenue Reports                          |" << endl;
        cout << "|                                                                             |" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "|                                                                             |" << endl;
        cout << "|             1. Generate Monthly Revenue Report for Court by Month           |" << endl;
        cout << "|                                                                             |" << endl;
        cout << "|             2. Generate Monthly Revenue Report for a Specific Court         |" << endl;
        cout << "|                                                                             |" << endl;
        cout << "|             3. Generate Monthly Revenue Report for a Every Court by Month   |" << endl;
        cout << "|                                                                             |" << endl;
        cout << "|             4. Generate Weekly Revenue Report for Each Court                |" << endl;
        cout << "|                                                                             |" << endl;
        cout << "|             5. Generate All Monthly Revenue Report for Court & Month        |" << endl;
        cout << "|                                                                             |" << endl;
        cout << "|             6. Back to Admin Menu                                           |" << endl;
        cout << "|                                                                             |" << endl;
        cout << "+-----------------------------------------------------------------------------+" << endl;
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 6) {
            cout << "Invalid input. Please choose 1 to 6." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter your choice: ";
        }

        system("cls");

        switch (choice) {
        case 1:
            generateMonthlyRevenueReportByCourtMonth(con);
            break;
        case 2:
        {
            cout << "+===========================================================================================+" << endl;
            cout << "|                                     MONTHLY REVENUE REPORT                                |" << endl;
            cout << "+===========================================================================================+" << endl;
            string courtName;
            int year, month;
            cout << "Enter Court Name: ";
            cin.get();
            getline(cin, courtName);
            cout << "Enter Year: ";
            cin >> year;
            cout << "Enter Month: ";
            cin >> month;
            generateMonthlyReportByCourt(con, year, month, courtName);
        }
        break;
        case 3:
        {
            cout << "+===========================================================================================+" << endl;
            cout << "|                                     MONTHLY REVENUE REPORT                                |" << endl;
            cout << "+===========================================================================================+" << endl;
            int month, year;
            cout << "Enter the month (1-12): ";
            cin >> month;
            cout << "Enter the year: ";
            cin >> year;
            generateMonthlyRevenueReportByMonth(con, year, month);
        }
        break;

        case 4:
        {
            generateWeeklyRevenueReport(con);
            break;
        }
        case 5:
        {
            generateMonthlyRevenueReport(con);
            break;
        }
        case 6:
            cout << "Returning to Admin Menu." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        if (choice != 6) {
            cout << "Press Enter to continue...";
            cin.ignore(); // consume the newline character left in the input buffer           
            system("cls");
        }
    } while (choice != 6);
}


// --------------------------------------------------------------------------------------------------------------------------- 
void Login_Admin()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                      LOGIN ADMIN                                     |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}

void Tennis_menu()
{
    cout << "+======================================================================================+" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                TENNIS BOOKING SYSTEM                                 |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "|                                                                                      |" << endl;
    cout << "+======================================================================================+" << endl;
    cout << endl;
}

// -----------------------------------------------INT MAIN------------------------------------------------------------- 
int main() {
    sql::mysql::MySQL_Driver* driver;
    Connection* con;

    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "");
    con->setSchema("tennis_books");

    string username, password;
    int choice;

    while (true) {
        main_menu();
        cout << "Enter your choice: ";

        do {
            if (!(cin >> choice) || choice < 1 || choice > 6) {
                cout << "Invalid input. Please choose 1 to 5." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                cout << "------------------------------------------------------------" << endl;
                cout << "Enter your choice: ";
            }
        } while (choice < 1 || choice > 6);

        system("cls");

        switch (choice) {
        case 1:
            menu_RegisterUser();
            registerUser(con);
            break;
        case 2:
            menu_RegisterAdmin();
            registerAdmin(con);
            break;
        case 3: {
            menu_LoginUser();
            string newUsername, newEmail, newPhoneNumber, newPassword;
            cout << "Enter your username: ";
            cin.get();
            getline(cin, username);
            cout << "Enter your password: ";
            string password = "";

            char ch;
            while (true) {
                ch = _getch();

                if (ch == 13) // Enter key ASCII value 
                    break;
                else if (ch == 8) { // Backspace key ASCII value
                    if (!password.empty()) {
                        cout << "\b \b";
                        password.pop_back();
                    }
                }
                else {
                    cout << '*';
                    password.push_back(ch);
                }
            }

            cout << endl;

            if (loginUser(con, username, password)) {
                cout << "----------------------------" << endl;
                cout << "Customer login successful!" << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                system("cls");

                while (true) {
                    Menu_User();
                    cout << "+=====================================================================================+" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                  MENU CUSTOMER                                      |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "+=====================================================================================+" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 1. Book a Court                                     |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 2. Cancel Booking                                   |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 3. View My Bookings                                 |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 4. Update Account                                   |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 5. View Available Courts                            |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 6. View Booked Courts                               |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 7. Check My Approved Bookings                       |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 8. Print Receipt                                    |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "|                                 9. Logout                                           |" << endl;
                    cout << "|                                                                                     |" << endl;
                    cout << "+=====================================================================================+" << endl;

                    cout << "Enter your choice: ";
                    do {
                        if (!(cin >> choice) || choice < 1 || choice > 10) {
                            cout << "Invalid input. Please choose 1 to 9." << endl;
                            cin.clear(); // Clear the error flag
                            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                            cout << "------------------------------------------------------------" << endl;
                            cout << "Enter your choice: ";
                        }
                    } while (choice < 1 || choice > 10);

                    system("cls");

                    switch (choice)
                    {
                    case 1:
                        book_Court();
                        bookCourt(con, username);
                        break;
                    case 2:
                        // Option to cancel booking
                        cancelCourtBooking(con, username);
                        break;

                    case 3:
                        cout << "                                     Viewing Your Bookings" << endl;
                        cout << "-------------------------------------------------------------------------------------------------" << endl;
                        viewUserBookings(con, username);
                        break;
                    case 4:
                    {
                        update_Account();
                        updateUser(con, username, password);
                        break;
                    }
                    case 5: {
                        displayCourts(con);
                        system("cls");
                        break;
                    }
                    case 6: {
                        displayBookedCourts(con);
                        system("cls");
                        break;
                    }
                    case 7: {
                        displayUserPaymentHistory(con, username);
                        system("cls");
                        break;
                    }
                    case 8: {
                        printReceiptMenu();
                        printReceipt(con, username);
                        system("cls");
                        break;
                    }
                    case 9:
                        cout << "Logging out..." << endl;
                        std::this_thread::sleep_for(std::chrono::seconds(1));
                        system("cls");
                        break;
                    default:
                        cout << "                            Invalid choice. Please try again." << endl;
                        cout << "----------------------------------------------------------------------------------------" << endl;
                        break;
                    }
                    if (choice == 9)
                        break;
                }
            }
            else {
                cout << "Invalid credentials. Customer login failed." << endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                system("cls");
            }
            break;
        }
        case 4:
            Login_Admin(); {
                cout << "Enter your username: ";
                cin.get();
                getline(cin, username);
                cout << "Enter your password: ";
                string password = "";
                char ch;

                while (true) {
                    ch = _getch();

                    if (ch == 13) // Enter key ASCII value 
                        break;
                    else if (ch == 8) { // Backspace key ASCII value
                        if (!password.empty()) {
                            cout << "\b \b";
                            password.pop_back();
                        }
                    }
                    else {
                        cout << '*';
                        password.push_back(ch);
                    }
                }

                cout << endl;


                if (loginAdmin(con, username, password)) {
                    cout << "------------------------------" << endl;
                    cout << "Admin login successful!" << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");

                    Menu_Admin();

                    while (true) {
                        cout << "+=====================================================================================+" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                 ADMIN MENU FUNCTIONS                                |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "+=====================================================================================+" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  1. View bookings                                   |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  2. Manage Courts                                   |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  3. Approve Payments                                |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  4. Customer Booking History                        |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  5. Customer Payment History                        |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  6. Update Admin Information                        |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  7. View Approved Transactions                      |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  8. Generate Report Revenue                         |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "|                                  9. Logout                                          |" << endl;
                        cout << "|                                                                                     |" << endl;
                        cout << "+=====================================================================================+" << endl;
                        cout << "Enter your choice: ";
                        do {
                            if (!(cin >> choice) || choice < 1 || choice > 10) {
                                cout << "Invalid input. Please choose 1 to 9." << endl;
                                cin.clear(); // Clear the error flag
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                cout << "------------------------------------------------------------" << endl;
                                cout << "Enter your choice: ";
                            }
                        } while (choice < 1 || choice > 10);
                        system("cls");

                        switch (choice)
                        {
                        case 1:
                            View_User();
                            viewBookings(con);
                            break;
                        case 2:
                            Manage_Court();
                            cout << "+======================================================================================+" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "|                                COURT MANAGEMENT MENU                                 |" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "+======================================================================================+" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "|                                    1. Add Court                                      |" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "|                                    2. Update Court                                   |" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "|                                    3. Back                                           |" << endl;
                            cout << "|                                                                                      |" << endl;
                            cout << "+======================================================================================+" << endl;
                            cout << "Enter your choice: ";
                            while (true) {
                                cin >> choice;

                                if (cin.fail()) {
                                    cout << "Error: Invalid input. Please enter a valid integer." << endl;
                                    cin.clear(); // Clear error flag
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                                    cout << "--------------------------------------------" << endl;
                                    cout << "Enter your choice: ";
                                }
                                else {
                                    break;
                                }
                            }
                            system("cls");

                            switch (choice)
                            {
                            case 1:
                                addCourt(con);
                                break;
                            case 2:
                                updateCourt(con);
                                break;
                            case 3:
                                break;

                            default:
                                cout << "Invalid input. Please enter (1-4). Returning back to the menu..." << endl;
                                break;
                            }
                            break;
                        case 3:
                            Approval_payment();
                            approvePayments(con);
                            system("cls");
                            break;
                        case 4:
                            cout << "                                            Customer Booking History                                            " << endl;
                            cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                            viewUserBookingHistory(con);
                            break;
                        case 5:
                            cout << "                                                Payment History                                            " << endl;
                            cout << "----------------------------------------------------------------------------------------------------------------" << endl;
                            viewPaymentHistory(con);
                            break;
                        case 6:
                            update_Admin();
                            updateAdmin(con, username, password);
                            break;
                        case 7:
                            displayAllTransactions(con);
                            break;
                        case 8:
                            Menu_Reports(con);  // Add this line to display the menu for reports
                            break;

                        case 9:
                            cout << "Logging out..." << endl;
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            system("cls");
                            break;
                        default:
                            cout << "                            Invalid choice. Please try again." << endl;
                            cout << "----------------------------------------------------------------------------------------" << endl;
                            break;
                        }
                        if (choice == 9)
                            break;
                    }
                }
                else
                {
                    cout << "Invalid credentials. Admin login failed." << endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    system("cls");
                }
                break;
            }
        case 5:
            cout << "Exiting..." << endl;
            delete con;
            return 0;

        default:
            cout << "                            Invalid choice. Please try again." << endl;
            cout << "----------------------------------------------------------------------------------------" << endl;
            break;
        }
    }


    delete con;
    return 0;
}