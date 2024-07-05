#include "manager.hh"

PasswordManager::PasswordManager(const std::string& databaseName, bool createNew):
    database{nullptr} {
    if (createNew) {
        int rc = sqlite3_open(databaseName.c_str(), &database);
        if (rc) {
            std::cerr << "Error opening SQLite database: " << sqlite3_errmsg(database) << std::endl;
        }
    }
}

PasswordManager::~PasswordManager() {
    sqlite3_close(database);
}