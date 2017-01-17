#!/bin/bash

head -n 1001 32768.txt > a.txt
./gen_pop_names 1000   > b.txt
diff a.txt b.txt

