#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <sstream>
#include <fstream>
#include <istream>
#include <iostream>
#include <deque>
#include "IOExceptions.h"
#include "InstructionUtils.h"

/*
This class is used for interpreting a given Byte Script executable file.
*/
class Interpreter
{
private:
   std::ifstream executableFile;    //The file stream for the given executable file
   int cellPointer;                 //Keeps track of the current cell being pointed to on the tape
   std::deque<unsigned char> tape;  //Program tape

   //Helper functions
   unsigned char getSequentialArgument(std::istream&);
   unsigned char getNonSequentialArgument();
   std::stringstream getBlock(std::istream&);

   //Functions for specific instructions
   void assign(unsigned char);
   void print();
   void input(unsigned char);
   void moveLeft(unsigned char);
   void moveRight(unsigned char);
   void jump(unsigned char);
   void add(unsigned char);
   void subtract(unsigned char);
   void multiply(unsigned char);
   void divide(unsigned char);

   void interpretIf(std::stringstream&);
   void interpretElse(std::stringstream&);
   void interpretLoop(std::stringstream&, unsigned char);

public:
   Interpreter(std::string);
   ~Interpreter();

   void interpret();
   void interpret(std::istream&);
   void finish();
};

#endif