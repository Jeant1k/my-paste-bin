#pragma once

#include <pqxx/pqxx>
#include <string>
#include <memory>

class Database {
public:
    Database(const std::string &host, int port, const std::string &user, const std::string &password, const std::string &dbname);
    std::string getUniqueNumber();

private:
    std::shared_ptr<pqxx::connection> conn;
};
