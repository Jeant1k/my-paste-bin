#include "../include/database.hpp"

Database::Database(const std::string &host, int port, const std::string &user, const std::string &password, const std::string &dbname) {
    try {
        std::string connURL = "host=" + host + " port=" + std::to_string(port) + " user=" + user + " password=" + password + " dbname=" + dbname;
        conn = std::make_shared<pqxx::connection>(connURL);
        if (conn->is_open()) {
            spdlog::info("Connected to database");
        } else {
            throw std::runtime_error("Cannot open database connection");
        }
    } catch (const std::exception &e) {
        spdlog::error("Database connection error: {}", e.what());
        throw;
    }
}
 
std::string Database::getUniqueNumber() {
    try {
        pqxx::work w(*conn);
        pqxx::result r = w.exec("SELECT nextval('unique_number_seq')");
        w.commit();
        if (!r.empty()) {
            spdlog::info("Fetched unique number from database: {}", r[0][0].as<std::string>());
            return r[0][0].as<std::string>();
        } else {
            throw std::runtime_error("No unique number fetched");
        }
    } catch (const std::exception &e) {
        spdlog::error("Error fetching unique number: {}", e.what());
        throw;
    }
}