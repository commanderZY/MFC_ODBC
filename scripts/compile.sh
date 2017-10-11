#!bin/sh
cd ../src/
#gcc *.c -I ./mysql_include -L ./lib -g -o stu -lmysqlclient
gcc *.c -I /usr/include/mysql/ -L /usr/lib/mysql -g -o stu -lmysqlclient
if [ -f "./stu" ];
then
    mv ./stu ../tmp/
    cd ../tmp
else
    cd ../scripts/
fi
