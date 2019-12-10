#!/bin/bash

numLines=$(cat passwd_212 | wc -l)
((numLines + 1))
readUpTo=$( grep -n ":9" passwd_212 | cut -d":" -f1 | head -n 1 )
lastRead=$( grep -n ":9" passwd_212 | cut -d":" -f1 | tail -n 1 )
# echo $((lastRead - readUpTo))
 echo $readUpTo
 echo $lastRead
cat passwd_212 | head -n $((readUpTo - 1))  >> passwd_212_no90s
cat passwd_212 | tail -n $((numLines - lastRead)) >> passwd_212_no90s

#count the number of times each shell type appears
#cat passwd_212_no90s | cut -d":" -f7 | grep -v '#' | sort | uniq -c| grep /
