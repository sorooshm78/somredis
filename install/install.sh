#!/bin/sh

apt -y update
apt install -y redis-server
apt install -y libhiredis-dev 
apt install -y libgtest-dev
