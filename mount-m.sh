#!/bin/bash
 
USER=""
USER_FILE="m-user.txt"
USERID=$(id -u)
GROUPID=$(id -g)
 
if [ -f $USER_FILE ]; then
        USER=$(cat $USER_FILE)
else
        read -p "NTB-Benutzername: " USER
fi
 
mkdir -p m
sudo mount -t cifs -o user=$USER,uid=$USERID,gid=$GROUPID //fs003/stud/$USER ./m
 
if [ $? -eq 0 ]; then
        echo $USER>$USER_FILE
fi
