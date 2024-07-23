#pragma once

#include <memory>
#include <string>
#include <stdexcept>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <cstdlib>

class YandexObjectStorage {
public:
    YandexObjectStorage(const std::string &bucket);
    ~YandexObjectStorage();
    std::string uploadText(const std::string &text, const std::string &hash);

private:
    std::string bucketName;
    Aws::SDKOptions options;
};
