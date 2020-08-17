#!/bin/bash
[ $# -ne 1 ] && echo "Usage: $0 <baud speed>" && exit 1
i=0
( stty $1 < /dev/ttyUSB1; cat;
  while [ $i -ne 10 ]
  do
    echo "Receiving packet $i"
    i=$((i + 1))
  done
)& < /dev/ttyUSB1 > /dev/ttyUSB1
