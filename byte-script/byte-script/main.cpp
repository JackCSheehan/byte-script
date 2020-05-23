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
   return 0;
}