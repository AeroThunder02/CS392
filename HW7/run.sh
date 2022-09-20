#!/bin/bash
gcc client.c -o client
gcc server.c -o server
./server 3000 &
./client 3000

