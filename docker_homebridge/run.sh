#!/bin/sh

docker run -d --net=host -v `pwd`/config/homebridge:/root/.homebridge --name homebridge homebridge:latest
