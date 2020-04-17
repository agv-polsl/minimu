FROM debian:buster

RUN apt-get update && apt-get update \
	&& apt-get install -y --no-install-recommends \
	g++ \
	cmake \
	libi2c-dev \
