#include "Preprocessor.h"

/*
Constructor; creates the ofstream and ifstream objects needed for file IO; takes the path to the source file and the name of the
.bse to create.
*/
Preprocessor::Preprocessor(std::string pathToSource, std::string executableName)
{
   //Open files and validate
   sourceFile.open(pathToSource);

   if (sourceFile.fail())
   {
      throw ErrorOpeningSourceException(pathToSource);
   }

   executableFile.open(executableName + EXECUTABLE_EXTENSION, std::ios::binary);

   if (executableFile.fail())
   {
      throw ErrorOpeningExecutableException(executableName + EXECUTABLE_EXTENSION);
   }
}

/*
Destructor; closes files.
*/
Preprocessor::~Preprocessor()
{
   sourceFile.close();
   executableFile.close();
}

/*
Processes the source file to the executable file.
*/
void Preprocessor::process()
{
   char currentChar; //The current character being read from the file

   //Iterate through the source file and check each character
   while (sourceFile.get(currentChar))
   {
      //If the current character is an instruction or a digit, write it to the executable file
      if (InstructionUtils::isToken(currentChar) || std::isdigit(currentChar))
      {
         //Write the current instruction to the executable file
         executableFile.write(reinterpret_cast<char*>(&currentChar), 1);
      }
   }
}

/*
Closes the files.
*/
void Preprocessor::finish()
{
   sourceFile.close();
   executableFile.close();
}