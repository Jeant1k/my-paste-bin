#include "../include/yandex_object_storage.hpp"

YandexObjectStorage::YandexObjectStorage(const std::string &bucket) : bucketName(bucket) {
    Aws::InitAPI(this->options);
}
 
YandexObjectStorage::~YandexObjectStorage() {
    Aws::ShutdownAPI(this->options);
}
 
std::string YandexObjectStorage::uploadText(const std::string &text, const std::string &hash) {
    try {
        Aws::S3::S3ClientConfiguration clientConfig;
        clientConfig.region = "ru-central1";
        clientConfig.endpointOverride = "storage.yandexcloud.net";
 
        Aws::S3::S3Client s3Client(clientConfig);
 
        Aws::S3::Model::PutObjectRequest request;
        request.SetBucket(bucketName);
        request.SetKey(hash);
 
        const std::shared_ptr<Aws::IOStream> inputData = Aws::MakeShared<Aws::StringStream>("");
        *inputData << text.c_str();
 
        request.SetBody(inputData);
 
        Aws::S3::Model::PutObjectOutcome outcome = s3Client.PutObject(request);
 
        if (!outcome.IsSuccess()) {
            throw std::runtime_error("Error uploading to Yandex Object Storage: " + outcome.GetError().GetMessage());
        }
        spdlog::info("Success: Object '{}' with content '{}' uploaded to bucket '{}'.", hash, text, bucketName);
        return "https://storage.yandexcloud.net/" + bucketName + "/" + hash;
    } catch (const std::exception &e) {
        spdlog::error("Error uploading text: {}", e.what());
        throw;
    }
}