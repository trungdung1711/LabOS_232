# $0 is the same of the script
#First argument is the number size-----------$1
#Second argument is the number of threads----$2
#Third argument is the seed number-----------$3
make
./aggsum $1 $2 $3
make clean
