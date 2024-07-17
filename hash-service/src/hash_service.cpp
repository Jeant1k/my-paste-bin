#include <thread>
#include <chrono>
#include <sw/redis++/redis++.h>
#include <openssl/rand.h>
#include <spdlog/spdlog.h>
#include <iostream>
#include <cppcodec/base64_rfc4648.hpp>

#include "../include/hash_service.hpp"

HashService::HashService(Database &db, const std::string &redis_host, int redis_port)
    : db(db), redis_host(redis_host), redis_port(redis_port) {
    redis = std::make_shared<sw::redis::Redis>("tcp://" + redis_host + ":" + std::to_string(redis_port));
    spdlog::info("Initializing HashService");
    generateHashes();
}

std::string HashService::generateBase64Hash() {
    unsigned char buffer[6];
    RAND_bytes(buffer, sizeof(buffer));
    return cppcodec::base64_rfc4648::encode(buffer, sizeof(buffer));
}

void HashService::generateHashes() {
    std::thread([this]() {
        while (true) {
            if (redis->llen("hashes") < 100) {
                std::string unique_number = db.getUniqueNumber();
                std::string hash = generateBase64Hash();
                redis->rpush("hashes", hash);
                spdlog::info("Generated hash: {}", hash);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();
}

std::string HashService::getHash() {
    auto hash = redis->lpop("hashes");
    if (hash) {
        return *hash;
    } else {
        spdlog::warn("No hashes available in Redis");
        return "";
    }
}
