#!/bin/bash

count=0

while true; do
    ARG=$(pgrep minishell)
    cd /proc/"$ARG"/fd || { echo "Error: Couldn't change directory"; exit 1; }
    ls -l 

	echo -e "$count ==========================================="
    ((count++))
    sleep 2
done

