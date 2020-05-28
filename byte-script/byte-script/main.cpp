#include <iostream>
#include <string>
#include "Preprocessor.h"
#include "InstructionUtils.h"
#include "Interpreter.h"

const std::string PREPROCESS_FLAG = "-p"; //Flag to only preprocess
const std::string INTERPRET_FLAG = "-i";  //Flag to only interpret
const std::string FULL_FLAG = "-pi";      //Flag to preprocess and interpret

const int FLAG_INDEX = 1;                 //Index of flag in cmd arguments
const int FILE_INDEX = 2;                 //Index of file in cmd arguments

/*
To preprocess:                ./byte-script -p [filename.bss]
To interpret:                 ./byte-script -i [filename.bse]
To preprocess and interpret:  ./byte-script -pi [filename.bss]
*/
int main(int argc, char** argv)
{
   std::string flag;       //The flag passed in cmd argument
   std::string fileName;   //Name of file passed in cmd argument

   //Ensure that there are enough arguments
   if (argc < 3)
   {
      std::cerr << "Not enough arguments!\n";
   }

   //TODO: finish text interface stuff
   flag = argv[FLAG_INDEX];
   fileName = argv[FILE_INDEX];

   //Check flag
   if (argv[FLAG_INDEX] != PREPROCESS_FLAG || argv[FLAG_INDEX] != INTERPRET_FLAG || argv[FLAG_INDEX] != FULL_FLAG)
   {
      std::cerr << "The flag " << argv[FLAG_INDEX] << " is not a valid flag. ";
      std::cerr << "Please only use one of the following flags: " << PREPROCESS_FLAG << ", " << INTERPRET_FLAG << ", " << FULL_FLAG << ".\n";
   }

   //Process given file based on the flag
   if (argv[FLAG_INDEX] == PREPROCESS_FLAG)
   {
      //Use given source file as the source and grab the name of the given file as the name of the executable
      try
      {
         Preprocessor preprocessor(argv[FILE_INDEX], );
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