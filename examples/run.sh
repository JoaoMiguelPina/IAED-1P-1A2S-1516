#!/bin/bash  

gcc -o bla $1 -Wall
shift
for arg in "$@"
do
  echo "Running $arg"
  echo ""
  ./bla < "${arg%.*}".in > "${arg%.*}".out.bla
  diff "${arg%.*}".out "${arg%.*}".out.bla
done

rm *.bla
rm bla
