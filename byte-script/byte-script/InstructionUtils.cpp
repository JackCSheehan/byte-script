#include "InstructionUtils.h"

/*
Searches the instruction set for the given character. Returns true if the given character is an instruction character
and false if it is not.
*/
bool InstructionUtils::isInstruction(char c)
{
   bool wasInstructionFound = false;   //Keeps track of whether or not instruction was found
   
   //Check given char against instructions
   switch (c)
   {
   case TERMINATOR:
   case ASSIGNMENT:
   case IF_START:
   case ELSE_START:
   case LOOP_START:
   case PRINT:
   case INPUT:
   case MOVE_LEFT:
   case MOVE_RIGHT:
   case JUMP:
   case ADD:
   case SUBTRACT:
   case MULTIPLY:
   case DIVIDE:
   case IMPORT:
      wasInstructionFound = true;
   }

   return wasInstructionFound;
}

/*
Returns true if the given character is a terminator instruction.
*/
bool InstructionUtils::isTerminator(char c)
{
   return c == TERMINATOR;
}