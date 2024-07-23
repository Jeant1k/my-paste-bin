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
    uuid-dev \
    zlib1g-dev \
    libpulse-dev \
    tzdata \
    git

WORKDIR /app

# Установка часового пояса
RUN ln -fs /usr/share/zoneinfo/Europe/Moscow /etc/localtime && dpkg-reconfigure -f noninteractive tzdata

# Установка spdlog
RUN git clone https://github.com/gabime/spdlog.git && cd spdlog && mkdir build && cd build && cmake .. && make && make install

# Установка cpp-httplib
RUN git clone https://github.com/yhirose/cpp-httplib.git /usr/local/include/cpp-httplib

# Установка yaml-cpp
RUN git clone https://github.com/jbeder/yaml-cpp.git && cd yaml-cpp && mkdir build && cd build && cmake .. && make && make install

# Установка cppcodec
RUN git clone https://github.com/tplgy/cppcodec.git /usr/local/include/cppcodec

# Установка AWS SDK для Yandex Object Storage
RUN git clone --recurse-submodules https://github.com/aws/aws-sdk-cpp.git && \
    cd aws-sdk-cpp && \
    mkdir build && \
    cd build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_PREFIX_PATH=/usr/local/ -DCMAKE_INSTALL_PREFIX=/usr/local/ -DBUILD_ONLY="s3" && \
    make && \
    make install

COPY . .

# Устанавливаем временную зону на UTC+03:00 (Москва)
RUN ln -sf /usr/share/zoneinfo/Etc/GMT-3 /etc/localtime && echo "Etc/GMT-3" > /etc/timezone

# Устанавливаем переменные окружения
ENV TZ=Etc/GMT-3

ENV AWS_ACCESS_KEY_ID=YCAJERIM8mzsRTcrIQAWamh8m
ENV AWS_SECRET_ACCESS_KEY=YCMMa2__2Q2XUlfGB7fvszc4TY9f

RUN mkdir build && cd build && cmake .. && make

CMD ["./build/new-note-service"]