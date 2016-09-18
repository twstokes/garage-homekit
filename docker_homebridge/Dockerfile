# initially derived from https://github.com/patrickbusch/homebridge-docker

FROM debian:jessie

ENV LANG='en_US.UTF-8' LANGUAGE='en_US:en' LC_ALL='en_US.UTF-8'
ENV DEBIAN_FRONTEND noninteractive
ENV TERM xterm

RUN apt-get update && apt-get install -y curl wget git apt-transport-https python build-essential make g++ libavahi-compat-libdnssd-dev libkrb5-dev vim net-tools

RUN curl deb.nodesource.com/setup_6.x | bash

RUN apt-get update && apt-get install -y nodejs

RUN npm install -g homebridge
RUN npm install -g homebridge-http

RUN mkdir -p /var/run/dbus

EXPOSE 5353 51826

ADD src/run.sh /root/run.sh

RUN mkdir /root/.homebridge

CMD ["/root/run.sh"]
