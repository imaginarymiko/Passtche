#pragma once
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

#include <sqlite3.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>

#include "generator.hh"
#include "pwutils.hh"

class PasswordManager {
  private:
    sqlite3* database;
  public:
    // Constructor/Destructor
    PasswordManager(const std::string& databaseName, bool createNew);
    ~PasswordManager();
    // Methods
    bool checkDatabase(const std::string& databaseName);
    void addCredentials(const std::string& username, const std::string& password);
    void editCredentials(const std::string& username, const std::string& newPassword);
    void deleteCredentials(const std::string& username);
    void retrievePassword(const std::string& username);
}; 