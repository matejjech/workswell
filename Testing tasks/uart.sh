#!/bin/bash
[ $# -ne 1 ] && echo "Usage: $0 <baud speed>" && exit 1
i=0
( stty $1 < /dev/ttyUSB0;
  [ $? -ne 0 ] && echo "Invalid stty settings" && exit 1
  cat;
  while [ $i -ne 10 ]
  do
    echo "Receiving packet $i" > /dev/ttyUSB0
    i=$((i + 1))
  done
)& < /dev/ttyUSB0 > /dev/ttyUSB0
