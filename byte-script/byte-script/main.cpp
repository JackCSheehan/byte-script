#include <iostream>
#include <string>
#include "Preprocessor.h"
#include "InstructionUtils.h"
#include "Interpreter.h"

/*
To preprocess:                ./byte-script -p [filename.bss]
To interpret:                 ./byte-script -i [filename.bse]
To preprocess and interpret:  ./byte-script -pi [filename.bss]
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

   //TODO: finish text interface stuff
   flag = argv[FLAG_INDEX];
   fileName = argv[FILE_INDEX];

   //Check flag
   if (flag != PREPROCESS_FLAG && flag != INTERPRET_FLAG && flag != FULL_FLAG)
   {
      std::cerr << "The flag " << flag << " is not a valid flag. ";
      std::cerr << "Please only use one of the following flags: " << PREPROCESS_FLAG << ", " << INTERPRET_FLAG << ", " << FULL_FLAG << ".\n";
   }

   //TODO: Put code in if and else into functions in helper class to reduce duplicate code when -pi flag needs to be implemented
   //Process given file based on the flag
   if (flag == PREPROCESS_FLAG)
   {
      //Use given source file as the source and grab the name of the given file as the name of the executable
      try
      {
         //Get name of executable to make based on the name given by the user
         std::string executableName = fileName.substr(0, fileName.find_last_of("."));

         //Create preprocessor and preprocess given file
         Preprocessor preprocessor(fileName, executableName);
         preprocessor.process();
         preprocessor.finish();

      }
      catch (ErrorOpeningSourceException e)
      {
         std::cerr << e.what() << "\n";
      }
      catch (ErrorOpeningExecutableException e)
      {
         std::cerr << e.what() << "\n";
      }
   }
   else if (flag == INTERPRET_FLAG)
   {
      //Use given executable file and run it through the interpreter
      try
      {
         //Create interpreter object and interpret
         Interpreter interpreter(fileName);
         interpreter.interpret();
      }
      //TODO: Change these catches to catch errors from the interpreter
      catch (ErrorOpeningSourceException e)
      {
         std::cerr << e.what() << "\n";
      }
      catch (ErrorOpeningExecutableException e)
      {
         std::cerr << e.what() << "\n";
      }
   }

   /*
   Preprocessor reprocessor("source.bss", "source");
   reprocessor.process();
   reprocessor.finish();

   Interpreter interpreter("source.bse");
   interpreter.interpret();

   */
   
   return 0;
}