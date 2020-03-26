@ECHO OFF
TITLE CMLL : Debugging/Running script
ECHO CMLL EXECUTABLE SCRIPT - Imanpal Singh
:start
ECHO ---------------------------------------------------
ECHO Compiling . . .
g++ Test.cpp Linear/Linear.cpp utils/defined.cpp Numerical/Numeric.cpp utils/util.cpp Bayes/NaiveBayes.cpp Data/DataHandler.cpp -o main -std=c++17
ECHO:
ECHO:__________________________________________________
ECHO:
ECHO Running ... 
ECHO:
main
ECHO:
ECHO ___________________________________________________
ECHO:
SET /p choice= Recompile and run again ?(y/or any other key for exit) : 
if /I "%choice%" EQU "y" GOTO start