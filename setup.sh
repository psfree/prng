basedir=`pwd`
cd TestU01-1.2.3
./configure --prefix="$basedir"
make
make install
cd ..
gcc -std=c99 -Iinclude -Llib -ltestu01 -lprobdist -lmylib -lm prng.c -o prng
