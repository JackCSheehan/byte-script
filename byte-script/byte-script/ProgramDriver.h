#ifndef PROGRAM_DRIVER
#define PROGRAM_DRIVER

#include <string>
#include "Preprocessor.h"
#include "Interpreter.h"

/*
This class contains static functions that drive the preprocessor and interpreter. Used
to handle the logic of the cmd arguments.
*/
class ProgramDriver
{
public:
   static void drivePreprocessor(std::string);
   static void driveInterpreter(std::string);
   static void driveFull(std::string);
};

#endif