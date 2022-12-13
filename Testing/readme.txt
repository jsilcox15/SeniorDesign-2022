//Put sample.exe in the top MP-SPDZ folder
//Put testprog.mpc in MP-SPDZ/Programs/Source
//
//Run the top MP-SPDZ folder in terminal and input the following 2 commands
//Replace <path> with the path to your cryptopp folder wherever it is

g++ -I/<path>/cryptopp -c -fPIC sample.cpp -o sample.exe -lcryptopp -lpthread
g++ -I/<path>/cryptopp -shared -Wl,-soname,librsa.so -o librsa.so  sample.exe -lcryptopp -lpthread

//Then run ./compile.py as normal

./compile.py -l testprog.mpc

//It is set to be run in 4 person mode, not interactive, so make sure to have
//the Player Data files in MP-SPDZ/Player-Data set up ie Input-P0-0, Input-P1-0, ...
//and so on, you can run it in interactive just add the -I tag
//
//Run the following lines of code in the top MP-SPDZ folder in 4 seperate terminals
//Make sure to run the first line first before there others.

./mascot-party.x -N 4 -p 0 testprog
./mascot-party.x -N 4 -p 1 testprog
./mascot-party.x -N 4 -p 2 testprog
./mascot-party.x -N 4 -p 3 testprog

