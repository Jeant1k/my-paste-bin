#include "../include/hash_service.hpp"

HashService::HashService(Database &db, const std::string &redis_host, int redis_port)
    : db(db), redis_host(redis_host), redis_port(redis_port) {
    try {
        redis = std::make_shared<sw::redis::Redis>("tcp://" + redis_host + ":" + std::to_string(redis_port));
        spdlog::info("Initializing HashService");
        generateHashes();
    } catch (const std::exception &e) {
        spdlog::error("Error initializing HashService: {}", e.what());
        throw;
    }
}
 
std::string HashService::generateBase64Hash() {
    unsigned char buffer[6];
    if (RAND_bytes(buffer, sizeof(buffer)) != 1) {
        throw std::runtime_error("Failed to generate random bytes");
    }
    return cppcodec::base64_rfc4648::encode(buffer, sizeof(buffer));
}
 
void HashService::generateHashes() {
    std::thread([this]() {
        while (true) {
            try {
                if (redis->llen("hashes") < 100) {
                    std::string unique_number = db.getUniqueNumber();
                    std::string hash = generateBase64Hash();
                    redis->rpush("hashes", hash);
                    spdlog::info("Generated hash: {}", hash);
                }
            } catch (const std::exception &e) {
                spdlog::error("Error generating hashes: {}", e.what());
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }).detach();
}
 
std::string HashService::getHash() {
    try {
        auto hash = redis->lpop("hashes");
        if (hash) {
            return *hash;
        } else {
            spdlog::warn("No hashes available in Redis");
            return "";
        }
    } catch (const std::exception &e) {
        spdlog::error("Error getting hash: {}", e.what());
        return "";
    }
}
