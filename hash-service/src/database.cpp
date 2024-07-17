#include <iostream>
#include <spdlog/spdlog.h>

#include "../include/database.hpp"

Database::Database(const std::string &host, int port, const std::string &user, const std::string &password, const std::string &dbname) {
    std::string connURL = "host=" + host + " port=" + std::to_string(port) + " user=" + user + " password=" + password + " dbname=" + dbname;
    spdlog::info("Connecting to database... URL: " + connURL);
    conn = std::make_shared<pqxx::connection>(connURL);
    spdlog::info("Connected to database");
}

std::string Database::getUniqueNumber() {
    pqxx::work w(*conn);
    pqxx::result r = w.exec("SELECT nextval('unique_number_seq')");
    w.commit();
    spdlog::info("Fetched unique number from database: {}", r[0][0].as<std::string>());
    return r[0][0].as<std::string>();
}