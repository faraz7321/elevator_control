# Use an official C++ build image with Ubuntu as base
FROM ubuntu:20.04

# Set environment variables to avoid interactive prompts during build
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies for building the project
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    libssl-dev \
    zlib1g-dev \
    libcurl4-openssl-dev \
    libboost-all-dev \
    libjsoncpp-dev \
    libsqlite3-dev \
    libwebsocketpp-dev \
    wget \
    curl \
    unzip \
    && rm -rf /var/lib/apt/lists/*

# Install CMake (version 3.21 or newer)
RUN wget -qO- https://cmake.org/files/v3.21/cmake-3.21.2-linux-x86_64.tar.gz | tar xvz -C /opt
RUN ln -s /opt/cmake-3.21.2-linux-x86_64/bin/cmake /usr/local/bin/cmake

# Set up the working directory
WORKDIR /app

# Copy the source code into the container
COPY . /app

# Build dependencies via CMake
RUN cmake -B build
RUN cmake --build build --parallel

# Set the default command to run the project
CMD ["./build/elevator_control"]
