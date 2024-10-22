############################################################
# this file should be called sortrace.sh
# it must have execute privilege set to run
# run it as a background task like this:
# $ rm sortrace.log # start with fresh log file
# $ sortrace.sh >> sortrace.log & # run in the background
############################################################
echo "=======Start======="
whoami
Sorted
Section 1
Sorted
Section 2
Sorted
section 3
Sorted
section 4
Sorted
section 5
Sorted
section 6
Sorted
section 7
Sorted
section 8
Sorted sections
1&2
Sorted sections
3&4
Sorted sections
5&6
Sorted sections
7&8
Sorted Sections 1&2&3&4 Sorted Sections 5&6&7&8
Internaldate
echo My machine has this many processors
nproc # this is for Windows machines
echo Generating 1000000 random numbers
sleep 1
./generate 1000000 -1000000 1000000 # you have to write generate.cpp
sleep 1
echo Starting system sort
sleep 1
{ time sort -n numbers.dat > systemsort.out; } 2>> sortrace.log # this line is for Windows
sleep 1
echo Starting my sort
sleep 1
{ time ./mysort numbers.dat mysort.out; } 2>> sortrace.log # this line is for Windows
sleep 1
ls -l systemsort.out
ls -l mysort.out
echo Comparing systemsort.out to mysort.out
diff systemsort.out mysort.out 2>> sortrace.log
echo All done with diff compare
echo "=======End======="
date