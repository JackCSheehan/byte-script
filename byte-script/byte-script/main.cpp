#include "Preprocessor.h"
#include "InstructionUtils.h"
#include "Interpreter.h"

int main()
{
   Preprocessor reprocessor("source.bss", "source");
   reprocessor.process();
   reprocessor.finish();

   Interpreter interpreter("source.bse");
   interpreter.interpret();


   //TODO: add try/catch to moveRight()
   //TODO: Add check for periods in preprocessor
   return 0;
}