FROM ubuntu:bionic

RUN apt-get update && apt-get install -y gnupg2 software-properties-common apt-utils && \
  apt-key adv --keyserver keyserver.ubuntu.com --recv 4e8a0c1418494cf45d1b8533799e9fe74bb0156c && \
  add-apt-repository 'deb http://internrepo.met.no/bionic bionic main contrib'

RUN apt-get update && apt-get -y install \
  debhelper autotools-dev debconf devscripts fakeroot \
  automake libtool libboost-dev libboost-thread-dev \
  libboost-regex-dev libboost-filesystem-dev libboost-program-options-dev libboost-system-dev \
  libboost-timer-dev cmake google-mock 
# libhttpserver-dev (= 0.9.0)


RUN addgroup --gid 41494 borgem && adduser --uid 41494  --gid 41494 --disabled-password --disabled-login --gecos '' borgem

USER borgem:borgem

VOLUME /src
VOLUME /build
WORKDIR /build

ENTRYPOINT [ "/bin/bash", "-c", "while true; do sleep 10000; done" ]