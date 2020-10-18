FROM ubuntu:18.04

COPY . /tmp/kaprino/
WORKDIR /

RUN \
########################################################
#
# Install tools which are required.
#
########################################################
    apt update; \
    apt upgrade; \
    apt install \
        curl \
        build-essential \
        python3 \
        openjdk11 \
        cmake \
        clang \
        git; \
########################################################
#
# Build Kaprino
#
########################################################
    cd /tmp/kaprino; \
    python3 bootstrap.py Release; \
########################################################
#
# Clean unused files
#
########################################################
    apt remove --purge \
        python3 \
        openjdk11 \
        cmake \
        git \
    rm -rf /var/lib/apt/lists/*;

ENV KAPRINOPKG /usr/local/include
