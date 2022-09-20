mkdir ./test
cd ./test
man man > man.txt
man ls > ls.txt
mkdir ./test2
cd ./test2
man man > man.txt
chmod -w man.txt
man chown > chown.txt
man chown > chown2.txt
chmod -w chown2.txt
man ls > ls.txt
cd ..
mkdir ./test3
cd ./test3
man mkdir > mkdir.txt
man mkdir > mkdir2.txt
chmod -w mkdir2.txt
man kill > kill.txt
man ping > ping.txt
