#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <string>
#include <fstream>
#include <cctype>
#include "InstructionUtils.h"
#include "IOExceptions.h"

const std::string EXECUTABLE_EXTENSION = ".bse";

/*
This class is used for cleaning up the user's source code and writing it to a .bse file
*/
class Preprocessor
{
private:
   std::ifstream sourceFile;        //The .bss source file given by user
   std::ofstream executableFile;    //The target .bse file where the instructions will be written to

public:
   Preprocessor(std::string, std::string);
   ~Preprocessor();

   void process();
   void finish();
};

#endif