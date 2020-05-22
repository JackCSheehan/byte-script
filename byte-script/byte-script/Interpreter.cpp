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
Interprets the given executable and displays the output to the console.
*/
void Interpreter::interpret()
{
   char currentInstruction;   //The current instruction being read from the executable
   unsigned char argument;    //The argument of the current instruction

   //Iterate through each character in the executable file
   while (executableFile.get(currentInstruction))
   {
      argument = getArgument();

      //Determine which instruction should be run
      switch (currentInstruction)
      {
      case ASSIGNMENT:
         assign(argument);
         break;
      case PRINT:
         print();
         break;
      case MOVE_LEFT:
         moveLeft(argument);
         break;
      case MOVE_RIGHT:
         moveRight(argument);
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
}

/*
This function gets the argument of the instruction at the current position in the executable file. Throws a
SyntaxErrorException if the argument could not be read or if there is no terminator. Throws InvalidArgumentException
if the argument cannot be read (such as if it is bigger than a 4-byte integer). Returns the argument value as an
unsigned char, meaning that if the value is greater than a char, it will wrap around until it is within the valid
range for a char.
*/
unsigned char Interpreter::getArgument()
{
   unsigned char argumentValue;     //The actual value of the argument
   std::string argument;   //The argument read from the file (might be multiple characters)
   char currentCharacter;  //The current character being read from the file

   //Get all the characters until a terminator is found
   do
   {
      executableFile.get(currentCharacter);

      //If EOF is reached, throw an exception
      if (executableFile.eof())
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
Assigns the given value to the current tape pointer
*/
void Interpreter::assign(unsigned char value)
{
   tape[cellPointer] = value;
}

void Interpreter::print()
{

}

void Interpreter::moveLeft(unsigned char)
{

}

/*
Moves right the given number of cells. If not enough space, will add more cells on to tape to accommodate request.
*/
void Interpreter::moveRight(unsigned char cells)
{
   int cellsToAdd;   //The number of cells needed to add
}

void Interpreter::add(unsigned char)
{

}

void Interpreter::subtract(unsigned char)
{

}

void Interpreter::multiply(unsigned char)
{

}

void Interpreter::divide(unsigned char)
{

}

/*
Closes the executable file.
*/
void Interpreter::finish()
{
   executableFile.close();
}