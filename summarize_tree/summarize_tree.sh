#!/bin/bash

path=$1;
num_regular=$(find "$path" -type f | wc -l)
num_dir=$(find "$path" -type d | wc -l)

echo "There were" $num_dir "directories."
echo "There were" $num_regular "regular files."
