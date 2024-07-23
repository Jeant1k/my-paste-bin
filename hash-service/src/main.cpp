#include <iostream>
#include <httplib.h>
#include <yaml-cpp/yaml.h>
#include <spdlog/spdlog.h>

#include "../include/hash_service.hpp"

std::string getEnvVar(const std::string &key) {
    const char *val = std::getenv(key.c_str());
    if (val == nullptr) {
        throw std::runtime_error("Environment variable " + key + " not set");
    }
    return std::string(val);
}

int main() {
    try {
        YAML::Node config = YAML::LoadFile("./config/config.yaml");
 
        std::string db_host = config["db"]["host"].as<std::string>();
        int db_port = config["db"]["port"].as<int>();
        std::string db_user = getEnvVar("DB_USER");
        std::string db_password = getEnvVar("DB_PASSWORD");
        std::string db_name = config["db"]["name"].as<std::string>();
        std::string redis_host = config["redis"]["host"].as<std::string>();
        int redis_port = config["redis"]["port"].as<int>();
 
        Database db(db_host, db_port, db_user, db_password, db_name);
        HashService hashService(db, redis_host, redis_port);
 
        httplib::Server svr;
 
        svr.Get("/hash", [&](const httplib::Request &req, httplib::Response &res) {
            spdlog::info("Received request for /hash");
            std::string hash = hashService.getHash();
            if (hash.empty()) {
                res.status = 500;
                res.set_content("No available hashes", "text/plain");
                spdlog::error("No available hashes");
            } else {
                res.set_content(hash, "text/plain");
                spdlog::info("Returning hash: {}", hash);
            }
        });
 
        spdlog::info("Starting server on port 8080");
        svr.listen("0.0.0.0", 8080);
    } catch (const std::exception &e) {
        spdlog::error("Error: {}", e.what());
        return 1;
    }
}