#!/bin/bash
 
USERID=$(id -u)
GROUPID=$(id -g)
 
mkdir -p share
sudo mount -t vboxsf -o uid=$USERID,gid=$GROUPID x ./x
