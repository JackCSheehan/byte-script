#ifndef INSTRUCTION_UTILS_H
#define INSTRUCTION_UTILS_H

//Instruction set for Byte Script
const char TERMINATOR = ';';
const char ASSIGNMENT = '=';
const char IF_START = '?';
const char ELSE_START = ':';
const char LOOP_START = '@';
const char PRINT = '$';
const char MOVE_LEFT = '<';
const char MOVE_RIGHT = '>';
const char ADD = '+';
const char SUBTRACT = '-';
const char MULTIPLY = '*';
const char DIVIDE = '/';

/*
This class contains utility functions for dealing with the Byte Script instruction set
*/
class InstructionUtils
{
public:
   static bool isInstruction(char);
   static bool isTerminator(char);
};

#endif