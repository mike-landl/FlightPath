# Base image is ubuntu LTS
FROM ubuntu:24.04

WORKDIR /

# Disable interactive promots during apt-get install
ARG DEBIAN_FRONTEND=noninteractive

# Install dependencies 
# wget, lsb-release, software-properties-common, gnupg is only needed for Clang 18
# At the end: Remove cached package lists
RUN apt-get update \
 && apt-get install -y \
    wget \ 
    lsb-release \
    software-properties-common \
    gnupg \
    build-essential \
    cmake \
    ninja-build \
    git-all \
 && rm -rf /var/lib/apt/lists/*

# Add LLVM repo and install Clang 18
RUN wget https://apt.llvm.org/llvm.sh && \
    chmod +x llvm.sh && \
    ./llvm.sh 18 && \
    rm llvm.sh

# Make Clang 18 the default (100 is the priority)
RUN update-alternatives --install /usr/bin/clang   clang   /usr/bin/clang-18   100 && \
    update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-18 100

# Restores the frontend mode to default (dialog)
ENV DEBIAN_FRONTEND=dialog
