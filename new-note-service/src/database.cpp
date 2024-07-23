#include "../include/database.hpp"

Database::Database(const std::string &host, int port, const std::string &user, const std::string &password, const std::string &dbname) {
    try {
        std::string connURL = "host=" + host + " port=" + std::to_string(port) + " user=" + user + " password=" + password + " dbname=" + dbname;
        spdlog::info("Connecting to database... URL: " + connURL);
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
 
std::string Database::storeUrl(const std::string& hash, const std::string& url) {
    try {
        pqxx::work w(*conn);
        w.exec0("INSERT INTO notes (hash, url) VALUES (" + w.quote(hash) + ", " + w.quote(url) + ")");
        w.commit();
        spdlog::info("url: {} and hash: {} have been added to the database", url, hash);
        return hash;
    } catch (const std::exception &e) {
        spdlog::error("Error storing URL in database: {}", e.what());
        throw;
    }
}