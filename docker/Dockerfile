FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y --no-install-recommends \
    cmake \
    build-essential \
    zlib1g-dev \
    libcgal-dev \
	libboost-all-dev \
	protobuf-compiler \
	libprotobuf-dev \
	libgtest-dev \
	libgmock-dev

COPY ../ /app
WORKDIR /app/cgal/
