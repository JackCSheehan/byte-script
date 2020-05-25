#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <fstream>
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
   unsigned char getArgument();

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

public:
   Interpreter(std::string);
   ~Interpreter();

   void interpret();
   void finish();
};

#endif