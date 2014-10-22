#!/bin/bash
#
# Helen Chac
#


if [ $# -eq 0 ]; then
  for file in *.c
  do
  if [ -e $file ]; then
    echo "Displaying first 10 lines of $file"
    head -10 $file
    echo
    echo -n "Delete file $file? (y/n) "
    read user_input
    if [ "$user_input" == "y" ]; then
      rm $file
    fi
  fi
  done
fi

if [ $# -gt 0 ]; then
for file in $@
 do
 if [[ $file = *.c && -e $file ]]; then
  echo "Displaying first 10 lines of $file"
  head -10 $file
  echo
  echo -n "Delete file $file? (y/n) "
  read user_input
  if [ "$user_input" == "y" ]; then
   rm $file
  fi
 fi
 done
fi

