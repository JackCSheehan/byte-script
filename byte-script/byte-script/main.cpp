#include <iostream>
#include <string>
#include "Preprocessor.h"
#include "InstructionUtils.h"
#include "Interpreter.h"
#include "ProgramDriver.h"

/*
To preprocess:                ./byte-script.exe -p [filename.bss]
To interpret:                 ./byte-script.exe -i [filename.bse]
To preprocess and interpret:  ./byte-script.exe -pi [filename.bss]
*/
int main(int argc, char** argv)
{
   const std::string PREPROCESS_FLAG = "-p"; //Flag to only preprocess
   const std::string INTERPRET_FLAG = "-i";  //Flag to only interpret
   const std::string FULL_FLAG = "-pi";      //Flag to preprocess and interpret

   const int FLAG_INDEX = 1;                 //Index of flag in cmd arguments
   const int FILE_INDEX = 2;                 //Index of file in cmd arguments

   std::string flag;                         //The flag passed in cmd argument
   std::string fileName;                     //Name of file passed in cmd argument

   //Ensure that there are enough arguments
   if (argc < 3)
   {
      std::cerr << "Not enough arguments!\n";
   }

   flag = argv[FLAG_INDEX];
   fileName = argv[FILE_INDEX];

   //Check flag
   if (flag != PREPROCESS_FLAG && flag != INTERPRET_FLAG && flag != FULL_FLAG)
   {
      std::cerr << "The flag " << flag << " is not a valid flag. ";
      std::cerr << "Please only use one of the following flags: " << PREPROCESS_FLAG << ", " << INTERPRET_FLAG << ", " << FULL_FLAG << ".\n";
   }

   //Process given file based on the flag
   if (flag == PREPROCESS_FLAG)
   {
      ProgramDriver::drivePreprocessor(fileName);
   }
   else if (flag == INTERPRET_FLAG)
   {
      ProgramDriver::driveInterpreter(fileName);
   }
   else
   {
      ProgramDriver::driveFull(fileName);
   }

   return 0;
}