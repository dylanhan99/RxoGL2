echo on

cd dependencies\FreeImage\lib\

set dest=..\..\..\bin\Debug\
set file=FreeImage.dll
ROBOCOPY %cd% %dest% *%file%* /copy:DATSO

cd ..\..\..\dependencies\FreeType\lib\

set dest=..\..\..\bin\Debug\
set file=freetype.dll
ROBOCOPY %cd% %dest% *%file%* /copy:DATSO
