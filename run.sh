#!/bin/bash

command=./bin/./Dijkstra

if ! type "valgrind" > /dev/null; 
then
    $command
else
    valgrind $command
fi
