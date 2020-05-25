#include "InstructionUtils.h"

/*
Searches the token set and returns true if the given character is a token.
*/
bool InstructionUtils::isToken(char c)
{
   bool wasTokenFound = false;   //Keeps track of whether or not token was found
   
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
   case BLOCK_OPEN:
   case BLOCK_CLOSE:
      wasTokenFound = true;
   }

   return wasTokenFound;
}

/*
Returns true if the given character is a terminator instruction.
*/
bool InstructionUtils::isTerminator(char c)
{
   return c == TERMINATOR;
}

/*
Returns true if the given character is a sequential instruction (i.e. an instruction that simply takes an argument).
*/
bool InstructionUtils::isSequentialInstruction(char c)
{
   bool wasTokenFound = false;   //Keeps track of whether or not the token was found

   switch (c)
   {
   case ASSIGNMENT:
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
      wasTokenFound = true;
   }

   return wasTokenFound;
}

/*
Returns true if the given character is a non-sequential instruction (i.e an instruction that may require a 
block of code with it).
*/
bool InstructionUtils::isNonSequentialInstruction(char c)
{
   bool wasTokenFound = false;   //Keeps track of whether or not the token was found

   switch (c)
   {
   case IF_START:
   case ELSE_START:
   case LOOP_START:
      wasTokenFound = true;
   }

   return wasTokenFound;
}

/*
Returns true if the given character is a separator token.
*/
bool InstructionUtils::isSeparator(char c)
{
   bool wasTokenFound = false;   //Keeps track of whether or not the token was found

   switch (c)
   {
   case BLOCK_CLOSE:
   case BLOCK_OPEN:
      wasTokenFound = true;
   }

   return wasTokenFound;
}
