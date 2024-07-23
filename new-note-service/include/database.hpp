#pragma once

#include <pqxx/pqxx>
#include <string>
#include <memory>
#include <stdexcept>
#include <spdlog/spdlog.h>

class Database {
public:
    Database(const std::string &host, int port, const std::string &user, const std::string &password, const std::string &dbname);
    std::string storeUrl(const std::string &hash, const std::string &url);

private:
    std::shared_ptr<pqxx::connection> conn;
};

