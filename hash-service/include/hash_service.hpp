#pragma once

#include <string>
#include <memory>
#include <sw/redis++/redis++.h>
#include <thread>
#include <chrono>
#include <sw/redis++/redis++.h>
#include <openssl/rand.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cppcodec/base64_rfc4648.hpp>
#include <stdexcept>

#include "../include/database.hpp"

class HashService {
public:
    HashService(Database &db, const std::string &redis_host, int redis_port);
    std::string getHash();

private:
    Database &db;
    std::shared_ptr<sw::redis::Redis> redis;
    std::string redis_host;
    int redis_port;

    void generateHashes();
    std::string generateBase64Hash();
};
