FROM debian:buster

LABEL name="minimu-i2c-builder"

RUN apt-get update && apt-get update \
	&& apt-get install -y --no-install-recommends \
	git \
	clang \
	make \
	cmake \
	libi2c-dev \
