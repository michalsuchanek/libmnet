cd documentation
doxygen.exe doxygen.project
copy html\index.chm mnet.chm
rd /s /q html
cd ..
php package.php
