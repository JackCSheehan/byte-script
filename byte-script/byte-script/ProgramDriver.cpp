#include "ProgramDriver.h"

/*
This function calls the preprocessor and handles preprocessor errors. Takes a path to
the .bss file to preprocess.
*/
void ProgramDriver::drivePreprocessor(std::string fileName)
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

/*
Calls the interpreter and handles interpreter errors. Takes a paht to the .bse file to interpret.
*/
void ProgramDriver::driveInterpreter(std::string fileName)
{
   //Use given executable file and run it through the interpreter
   try
   {
      //Create interpreter object and interpret
      Interpreter interpreter(fileName);
      interpreter.interpret();
   }
   catch (ErrorOpeningExecutableException e)
   {
      std::cerr << e.what() << "\n";
   }
   catch (SyntaxErrorException e)
   {
      std::cerr << e.what() << "\n";
   }
   catch (ReachedEOFException e)
   {
      std::cerr << e.what() << "\n";
   }
   catch (InvalidArgumentException e)
   {
      std::cerr << e.what() << "\n";
   }
   catch (DivisionByZeroException e)
   {
      std::cerr << e.what() << "\n";
   }
   catch (OutOfMemoryException e)
   {
      std::cerr << e.what() << "\n";
   }
}

/*
This function calls the preprocessor and the interpreter in one. Takes a path to the .bss file to be 
preprocessed then executed by the interpreter.
*/
void ProgramDriver::driveFull(std::string fileName)
{
   drivePreprocessor(fileName);

   //Get name of executable to make based on the name given by the user
   std::string executableName = fileName.substr(0, fileName.find_last_of(".")) + ".bse";

   driveInterpreter(executableName);
}