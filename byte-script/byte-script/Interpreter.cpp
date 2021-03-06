#include "Interpreter.h"

/*
Constructor; takes the path to the executable file and opens it.
*/
Interpreter::Interpreter(std::string path)
{
   //Open file and throw exception if it couldn't be opened
   executableFile.open(path, std::ios::binary);

   if (executableFile.fail())
   {
      throw ErrorOpeningExecutableException(path);
   }
 
   //Cell pointer should start at cell 0
   cellPointer = 0;

   //Add a zero for the first cell
   tape.push_back(0);
}

/*
Destructor; double checks that the file is closed.
*/
Interpreter::~Interpreter()
{
   executableFile.close();
}

/*
Used so that the user can call interpret() with no arguments.
*/
void Interpreter::interpret()
{
   interpret(executableFile);
}

/*
Interprets the given stream and displays the output to the console.
*/
void Interpreter::interpret(std::istream& stream)
{
   char currentInstruction;   //The current instruction being read from the executable
   unsigned char argument;    //The argument of the current instruction
   std::stringstream block;   //The block of the current instruction

   //Iterate through each character in the executable file
   while (stream.get(currentInstruction))
   {
      //Specific steps for parsing sequential instructions
      if (InstructionUtils::isSequentialInstruction(currentInstruction))
      {
         argument = getSequentialArgument(stream);

         //Determine which instruction should be run
         switch (currentInstruction)
         {
         case ASSIGNMENT:
            assign(argument);
            break;
         case PRINT:
            print();
            break;
         case INPUT:
            input(argument);
            break;
         case MOVE_LEFT:
            moveLeft(argument);
            break;
         case MOVE_RIGHT:
            moveRight(argument);
            break;
         case JUMP:
            jump(argument);
            break;
         case ADD:
            add(argument);
            break;
         case SUBTRACT:
            subtract(argument);
            break;
         case MULTIPLY:
            multiply(argument);
            break;
         case DIVIDE:
            divide(argument);
            break;
         default:
            throw SyntaxErrorException(executableFile.tellg());
         }
      }
      //Specific steps for evaluating non-sequential instructions
      else if (InstructionUtils::isNonSequentialInstruction(currentInstruction))
      {
         block = getBlock(stream);
         //Determine what to do depending on the current instruction
         switch (currentInstruction)
         {
         case IF_START:
            interpretIf(block);
            break;
         case ELSE_START:
            interpretElse(block);
            break;
         case LOOP_START:
            interpretLoop(block);
            break;
         }
      }
   }
}

/*
This function gets the argument of the instruction at the current position in the stream. Throws a
SyntaxErrorException if the argument could not be read or if there is no terminator. Throws InvalidArgumentException
if the argument cannot be read (such as if it is bigger than a 4-byte integer). Returns the argument value as an
unsigned char, meaning that if the value is greater than a char, it will wrap around until it is within the valid
range for a char.
*/
unsigned char Interpreter::getSequentialArgument(std::istream& stream)
{
   unsigned char argumentValue;     //The actual value of the argument
   std::string argument;            //The argument read from the file (might be multiple characters)
   char currentCharacter;           //The current character being read from the file

   //Get all the characters until a terminator is found
   do
   {
      stream.get(currentCharacter);

      //If EOF is reached, throw an exception
      if (stream.eof())
      {
         throw ReachedEOFException();
      }

      //Append the current character to the argument
      argument += currentCharacter;

   } while (currentCharacter != TERMINATOR);

   //Check for the size of the argument to determine if there is an implicit or explicit value
   if (argument.length() == 1)
   {
      argumentValue = 1;
   }
   else
   {
      //Try to get the actual value of the argument
      try
      {
         //Try to convert the argument to an integer
         argumentValue = std::stoi(argument.substr(0, argument.length() - 1));
      }
      catch (std::exception)
      {
         throw InvalidArgumentException(argument);
      }
   }

   /*
   NOTE: if the argument is greater than an unsigned int, it will wrap around as many times as needed to be in the range of one.
   This is done automatically in C++ when returning an int from a function with type unsigned char
   */
   return argumentValue;
}

/*
Gets the block of code after a non-sequential instruction (e.g. ifs, loops, and elses). Throws syntax error
exception if the instruction is not immediately followed by an open separator.
*/
std::stringstream Interpreter::getBlock(std::istream& stream)
{
   int expectedClosingBraces = 1;   //The expected number of closing braces; needed so that nested loops/ifs work
   int foundClosingBraces = 0;      //Number of braces found
   std::stringstream block;         //The block parsed from the non-sequential instruction
   char currentCharacter;           //The current character being read from the file
   
   stream.get(currentCharacter);

   //Throw syntax error if the first character after the non-sequential instruction is not an BLOCK_OPEN token
   if (currentCharacter != BLOCK_OPEN)
   {
      throw SyntaxErrorException(stream.tellg());
   }

   //Iterate through the rest of the block until a BLOCK_CLOSE is found
   do
   {
      stream.get(currentCharacter);

      //If EOF is reached, throw an exception
      if (stream.eof())
      {
         throw ReachedEOFException();
      }

      //Keep track of opening/closing braces
      switch (currentCharacter)
      {
         //When an open brace is encountered, the interpreter needs to expect another closing brace
      case BLOCK_OPEN:
         ++expectedClosingBraces;
         break;
         //When a closing brace is encountered, the interpreter needs to keep track of that so that
         //nested if statements/loops work
      case BLOCK_CLOSE:
         ++foundClosingBraces;
         break;
      }

      //Append the current character to the block
      block << currentCharacter;

   } while (expectedClosingBraces != foundClosingBraces);

   //Remove the last character of the block (the closing brace)
   std::string blockCopy(block.str());
   block.str("");
   block << blockCopy.substr(0, blockCopy.length() - 1);

   return block;
}

/*
Assigns the given value to the current tape pointer
*/
void Interpreter::assign(unsigned char value)
{
   tape[cellPointer] = value;
}

/*
Prints all the characters in the tape from the cell pointer to the first ASCII 0 or until the end of the allocated
tape. Cell pointer is not changed.
*/
void Interpreter::print()
{
   int printCounter = cellPointer;  //Pointer that iterates through tape

   //Iterate through the tape until an escape character is found
   while (printCounter < tape.size() && tape[printCounter] != 0)
   {
      std::cout << tape[printCounter];

      ++printCounter;
   }
}

/*
Gets the given number of bytes of input from standard input. Adds those bytes to the program tape starting at the
cell pointer. If more data is entered than was requested, it will be truncated. A \0 is automatically added. 
*/
void Interpreter::input(unsigned char bytes)
{
   std::string input;               //Input given by user
   int tapeCounter = cellPointer;   //Counts along program tape to insert the input

   //Use the move functions to ensure that the necessary amount of space is allocated for the input
   if ((cellPointer + bytes) > tape.size())
   {
      //Move right to allocate the space
      moveRight(bytes);

      //Move left to return the cell pointer back to its original location
      moveLeft(bytes);
   }

   //Get the user's input
   std::getline(std::cin, input);

   //Add the input to the program tape
   for (int characterCount = 0; (characterCount < bytes - 1) && (characterCount < input.size()); ++characterCount)
   {
      //Add the current character to the program tape
      tape[tapeCounter] = input.at(characterCount);

      ++tapeCounter;
   }

   //Add the null terminator
   tape[tapeCounter] = '\0';
}

/*
Moves the cell pointer left the given number of spaces. If the user tries to move left of cell 0, the cell pointer
will go to cell 0 but will never go below it.
*/
void Interpreter::moveLeft(unsigned char cells)
{
   //If the cell pointer would go too far, set it to 0
   if (cells > cellPointer)
   {
      cellPointer = 0;
   }
   //If not, just subtract the given number of cells
   else
   {
      cellPointer -= cells;
   }
}

/*
Moves right the given number of cells. If not enough space, will add more cells on to tape to accommodate request.
*/
void Interpreter::moveRight(unsigned char cells)
{
   int cellsToAdd;   //The number of cells needed to be added to the program tape

   //Calculate the number of cells to add
   cellsToAdd = (cellPointer + cells) - (tape.size() - 1);

   //If cells need to be added, then add them
   if (cellsToAdd > 0)
   {
      try
      {
         tape.insert(tape.end(), cellsToAdd, DEFAULT_CELL_VALUE);
      }
      catch (...)
      {
         throw OutOfMemoryException();
      }
   }

   //Increment the cell pointer so that it points to the right cell
   cellPointer += cells;
}

/*
Moves the cell pointer to the given cell. Does nothing if given cell is the same as the cell pointer.
*/
void Interpreter::jump(unsigned char cell)
{
   //Call either the go left or go right functions depending on which direction the pointer has to move
   if (cell < cellPointer)
   {
      moveLeft(cellPointer - cell);
   }
   else
   {
      moveRight(cell - cellPointer);
   }

   /*
   Note: the cell pointer is not simply assigned the jump value because certain checks are in place in both the
   moveLeft and moveRight functions.
   */
}

/*
Adds the given value to the current cell. Cell will wrap around if it exceeds the bounds of an unsigned character.
*/
void Interpreter::add(unsigned char value)
{
   tape[cellPointer] += value;
}

/*
Subtracts the given value to the cell. Cell will wrap around if it exceeds the bounds of an unsigned character.
*/
void Interpreter::subtract(unsigned char value)
{
   tape[cellPointer] -= value;
}

/*
Multiplies the given value to the cell. Cell will wrap around if it exceeds the bounds of an unsigned character.
*/
void Interpreter::multiply(unsigned char value)
{
   tape[cellPointer] *= value;
}

/*
Divides the current cell value by the given value. Cell will wrap around if it exceeds the bounds of an 
unsigned character. Decimals will be truncated. If the given value is 0, an exception will be thrown.
*/
void Interpreter::divide(unsigned char value)
{
   //Check for division by 0
   if (value == 0)
   {
      throw DivisionByZeroException();
   }
   
   tape[cellPointer] /= value;
}

/*
Interprets an if statement given the instruction block. Runs the block if the current cell is 0.
*/
void Interpreter::interpretIf(std::stringstream& block)
{
   //If the current cell is zero, interpret the block
   if (tape[cellPointer] == 0)
   {
      interpret(block);
   }
}

/*
Interprets an else statement given the instruction block. Runs the block if the current cell is NOT 0.
*/
void Interpreter::interpretElse(std::stringstream& block)
{
   if (tape[cellPointer] != 0)
   {
      interpret(block);
   }
}

/*
Interprets a loop given the block and the argument.
*/
void Interpreter::interpretLoop(std::stringstream& block)
{
   //Loop while the current cell is not 0
   while(tape[cellPointer] != 0)
   {
      //Copy block to avoid changes being made to original block stream
      std::stringstream blockCopy(block.str());
      interpret(blockCopy);
   }
}

/*
Closes the executable file.
*/
void Interpreter::finish()
{
   executableFile.close();
}