#include "manager.hh"

/*
################################################################################
# Big Five
################################################################################
*/

// Constructor
PasswordManager::PasswordManager():
    database{nullptr} {}

// Destructor
PasswordManager::~PasswordManager() {}

// Copy constructor
PasswordManager::PasswordManager(const PasswordManager& other):
    database{other.database} {}

// Move constructor
PasswordManager::PasswordManager(PasswordManager&& other):
    database{other.database} {
    other.database = nullptr;
}

// Copy assignment operator
PasswordManager& PasswordManager::operator=(const PasswordManager& other) {
    if (this != &other) {
        this->database = other.database;
    }
    return *this;
}

/*
################################################################################
# Database methods
################################################################################
*/

void PasswordManager::openDatabase(const std::string& newDatabasePath) {
    if (this->database) sqlite3_close(this->database);
    
}

void PasswordManager::newDatabase(const std::string& newDatabasePath) {
    sqlite3* newDatabase;
    if (sqlite3_open(newDatabasePath.c_str(), &newDatabase)) 
        std::cerr << "Failed to create new database: " << sqlite3_errmsg(newDatabase) << std::endl;
    else {
        std::cout << "Successfully created new database: " << newDatabasePath << std::endl;
        this->databasePath = newDatabasePath;
        setupDatabase();
    }
}

void PasswordManager::setupDatabase() {
    const char* sqlCreateTable = R"(
        CREATE TABLE IF NOT EXISTS PASSWORDS (
            ID INTEGER PRIMARY KEY AUTOINCREMENT,
            USERNAME TEXT NOT NULL,
            PASSWORD TEXT NOT NULL,
            PLATFORM TEXT NOT NULL
        );
    )";
    char* errorMessage = nullptr;
    if (sqlite3_exec(this->database, sqlCreateTable, nullptr, nullptr, &errorMessage) != SQLITE_OK) {
        std::cerr << "SQL error: " << errorMessage << std::endl;
        sqlite3_free(errorMessage);
    } else
        std::cout << "Database setup completed.\n";
    std::string salt = generateSalt();
    std::string keyHash = hashPassword(decryptionKey, salt);
    std::string sqlInsertKey = "INSERT INTO KEYS (SALT, HASH) VALUES (?, ?);";
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(this->database, sqlInsertKey.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        std::cerr << "SQL error: " << sqlite3_errmsg(this->database) << std::endl;
    else {
        sqlite3_bind_text(stmt, 1, salt.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, keyHash.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) != SQLITE_DONE) 
            std::cerr << "SQL error" << sqlite3_errmsg(this->database) << std::endl;
        sqlite3_finalize(stmt);
    }
}

void PasswordManager::closeDatabase() {

}

void PasswordManager::authenticate() {
    for (int attempts = 0; attempts < 3; ++attempts) {
        std::cout << "Enter decryption key: ";
        std::cin >> this->decryptionKey;
        
    }
}

/*
################################################################################
# Credentials methods
################################################################################
*/

/*
################################################################################
# Menus
################################################################################
*/

// Main menu
void PasswordManager::run() {
    while (true) {
        int option;
        std::cout << "Enter a number:\n";
        std::cout << "[1] Open database\n";
        std::cout << "[2] Create new database\n";
        std::cout << "[3] Delete database" << std::endl;
        std::cin >> option;
        switch (option) {
            case 1:
                while (true) {
                    std::cout << "Specify a database (must be appended with .db)" << std::endl;
                    std::string filepath;
                    std::cin >> filepath;
                    if (std::filesystem::exists(filepath)) {

                    }
                }
                break;
            case 2:
                std::string newDatabasePath;
                std::cout << "Enter the path of the new password database: ";
                std::cin >> newDatabasePath;
                newDatabase(newDatabasePath);
                break;
            case 3:
                std::string databaseToDelete;
                std::cout << "Enter the path of the database to delete: "; 
                std::cin >> databaseToDelete;
        }
    }
}

// Database menu
void PasswordManager::databaseMenu() {
    while (true) {
        int option;
        std::cout << "Enter a number:\n";
        std::cout << "[1] View saved credentials\n";
        std::cout << "[2] Modify credentials\n";
        std::cout << "[3] Generate new password\n";
        std::cout << "[4] Backup database\n";
        std::cout << "[5] Wipe database\n";
        std::cout << "[6] Change database\n";
        std::cout << "[7] Change database password\n";
        std::cout << "[8] Exit program" << std::endl;
        std::cout << "> ";
        std::cin.clear();
        std::cin >> option;
        switch (option) {
            case 1:
                this->showCredentials();
                break;
            case 2:
                credentialsMenu();
                break;
            default:
                std::cout << "Invalid option" << std::endl;
                break;
        }
    }
}

// Credentials menu
void PasswordManager::credentialsMenu() {
    while (true) {
        int option;
        std::cout << "Enter a number:\n";
        std::cout << "[1] Add new credentials\n";
        std::cout << "[2] Edit existing credentials\n";
        std::cout << "[3] Delete credentials\n";
        std::cout << "[4] Return to main menu\n";
        std::cout << "> ";
        std::cin >> option;
        switch (option) {
            case 1:
                addCredentials();
                break;
            case 2:
                editCredentials();
                break;
            case 3:
                deleteCredentials();
                break;
            case 4:
                return;
            default:
                std::cout << "Invalid option\n";
                break;
        }
    }
}