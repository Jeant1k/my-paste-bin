FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Etc/UTC
ENV LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"

RUN apt-get update && apt-get install -y \
    tzdata \
    build-essential \
    cmake \
    libpqxx-dev \
    libssl-dev \
    libcurl4-openssl-dev \
    libhiredis-dev \
    git

WORKDIR /app

COPY . .

# Установка spdlog
RUN git clone https://github.com/gabime/spdlog.git && cd spdlog && mkdir build && cd build && cmake .. && make && make install

# Установка cpp-httplib
RUN git clone https://github.com/yhirose/cpp-httplib.git /usr/local/include/cpp-httplib

# Установка redis-plus-plus
RUN git clone https://github.com/sewenew/redis-plus-plus.git && cd redis-plus-plus && mkdir build && cd build && cmake .. -DREDIS_PLUS_PLUS_CXX_STANDARD=17 && make && make install

# Установка yaml-cpp
RUN git clone https://github.com/jbeder/yaml-cpp.git && cd yaml-cpp && mkdir build && cd build && cmake .. && make && make install

# Обновляем CMAKE_PREFIX_PATH для поиска yaml-cpp
ENV CMAKE_PREFIX_PATH="/usr/local;/usr/local/include/yaml-cpp"

# Установка cppcodec
RUN git clone https://github.com/tplgy/cppcodec.git /usr/local/include/cppcodec

# Копирование wait-for-it.sh
COPY ./scripts/wait-for-it.sh /usr/local/bin/wait-for-it.sh
RUN chmod +x /usr/local/bin/wait-for-it.sh

RUN mkdir build && cd build && cmake .. && make

# wait-for-it.sh для ожидания готовности базы данных
CMD ["/usr/local/bin/wait-for-it.sh", "postgres:5432", "--", "/usr/local/bin/wait-for-it.sh", "redis:6379", "--", "./build/hash-service"]
