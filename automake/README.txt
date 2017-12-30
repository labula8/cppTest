
autoscan
mv configure.scan configure.ac
aclocal
autoconf
autoheader
automake
touch Makefile.am
automake --add-missing
./configure
