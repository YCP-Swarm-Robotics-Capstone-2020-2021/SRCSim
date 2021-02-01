#!/bin/bash -e
if [[ -d "./logs" ]]; then
    echo  "Deleting all log files."
    rm -rf ./logs
else
    echo "There is no such directory called 'logs'"
fi
