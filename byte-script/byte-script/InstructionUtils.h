#ifndef INSTRUCTION_UTILS_H
#define INSTRUCTION_UTILS_H

//Byte Script tokens

//Sequential Instructions
const char TERMINATOR = ';';
const char ASSIGNMENT = '=';
const char PRINT = '$';
const char INPUT = '\"';
const char MOVE_LEFT = '<';
const char MOVE_RIGHT = '>';
const char JUMP = '^';
const char ADD = '+';
const char SUBTRACT = '-';
const char MULTIPLY = '*';
const char DIVIDE = '/';
const char IMPORT = '#';

//Non-sequential instructions
const char IF_START = '?';
const char ELSE_START = ':';
const char LOOP_START = '@';

//Separators
const char BLOCK_OPEN = '{';
const char BLOCK_CLOSE = '}';

//Important values
const int DEFAULT_CELL_VALUE = 0;

/*
This class contains utility functions for dealing with the Byte Script instruction set
*/
class InstructionUtils
{
public:
   //TODO: add is non-sequential instruction and is sequential instruction
   static bool isToken(char);
   static bool isTerminator(char);
};

#endif