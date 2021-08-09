FROM ubuntu:20.04

ENV TZ=Europe/Prague
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
RUN apt-get update && \
    apt-get install -y \
        g++ \
        cmake \
        pkg-config \
        libfreetype6-dev \
        libx11-dev \
        libxinerama-dev \
        libxrandr-dev \
        libxcursor-dev \
        mesa-common-dev \
        libasound2-dev \
        freeglut3-dev \
        libxcomposite-dev
