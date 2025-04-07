# Base image is ubuntu LTS
FROM ubuntu:24.04

WORKDIR /

# Disable interactive promots during apt-get install
ARG DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update \
    && apt-get install -y \
       build-essential \
       cmake \
       ninja-build \
       catch2 \
    && rm -rf /var/lib/apt/lists/*

# Install dependencies for Clang
RUN apt-get update \
    && apt-get install -y \
       wget \ 
       lsb-release \
       software-properties-common \
       gnupg \
    && rm -rf /var/lib/apt/lists/*

# Add LLVM repo and install Clang 18
RUN wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh 18 && \
    rm llvm.sh

# Make Clang 18 the default (100 is the priority)
RUN update-alternatives --install /usr/bin/clang   clang   /usr/bin/clang-18   100 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100

# Install dependencies for coverage report
RUN apt-get update \
    && apt-get install -y \
       llvm \
       lcov \
    && rm -rf /var/lib/apt/lists/*

# Restores the frontend mode to default (dialog)
ENV DEBIAN_FRONTEND=dialog
