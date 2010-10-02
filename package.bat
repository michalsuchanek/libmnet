@echo off
set MYVERSION=0.5.0
cls
php -f "%UTIL%\dumpline.php" readme.txt 1
php -f "%UTIL%\dumpline.php" documentation\doxygen.project 8
php -f "%UTIL%\dumpline.php" package.bat 2
echo Did you increment version numbers?
pause

md tmp\build\vs2008\mnet
md tmp\include\mnet
md tmp\source
md tmp\documentation
md tmp\lib
md tmp\samples\client-server

copy build\vs2008\mnet\mnet.sln tmp\build\vs2008\mnet
copy build\vs2008\mnet\mnet.vcproj tmp\build\vs2008\mnet
copy include\mnet tmp\include\mnet
copy source tmp\source
copy documentation\mnet.chm tmp\documentation
copy samples\client-server tmp\samples\client-server
xcopy /s lib tmp\lib

copy *.txt tmp

cd tmp
delfiles *.ncb *.suo *.user
pkzip -add -dir mnet-%MYVERSION%.zip
move mnet-%MYVERSION%.zip ..
cd ..
delfiles -d tmp
