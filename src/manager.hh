#pragma once
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <sqlite3.h>
#include <termios.h>

#include "pwutils.hh"

class PasswordManager {
  private:
    sqlite3* database;
    std::string databasePath;
    std::string decryptionKey;
  public:
    // Big Five
    PasswordManager(); // Constructor
    ~PasswordManager(); // Destructor
    PasswordManager(const PasswordManager& other); // Copy constructor
    PasswordManager(PasswordManager&& other); // Move constructor
    PasswordManager& operator=(const PasswordManager& other); // Copy assignment operator
    // Database methods
    void openDatabase(const std::string& newDatabasePath);
    void newDatabase(const std::string& newDatabasePath);
    void setupDatabase();
    void closeDatabase();
    void authenticate();
    // Credentials methods
    void addCredentials(const std::string& username, const std::string& password);
    void editCredentials(const std::string& username, const std::string& newPassword);
    void deleteCredentials(const std::string& username);
    void retrievePassword(const std::string& username);
    // Menus
    void run();
    void databaseMenu();
    void credentialsMenu();
}; 