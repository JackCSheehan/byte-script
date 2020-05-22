#ifndef IO_EXCEPTIONS_H
#define IO_EXCEPTIONS_H

/*
Exception thrown when an executable could not be opened.
*/
class ErrorOpeningExecutableException
{
private:
   std::string file;

public:
   ErrorOpeningExecutableException(std::string f) { file = f; }

   std::string what() const
   {
      return "Could not open executable: " + file;
   }
};

/*
Exception thrown when a source file could not be opened.
*/
class ErrorOpeningSourceException
{
private:
   std::string file;

public:
   ErrorOpeningSourceException(std::string f) { file = f; }

   std::string what() const
   {
      return "Could not open source: " + file;
   }
};

/*
Exception for general syntax errors
*/
class SyntaxErrorException
{
private:
   int errorIndex;

public:
   SyntaxErrorException(int i) { errorIndex = i; }

   std::string what() const
   {
      return "Syntax error at index: " + std::to_string(errorIndex);
   }
};

/*
Exception for reaching EOF while trying to parse an argument.
*/
class ReachedEOFException
{

   std::string what() const
   {
      return "Reached EOF while parsing argument for instruction";
   }
};

/*
Exception if an argument cannot be converted to an int or if it is too large.
*/
class InvalidArgumentException
{
private:
   std::string argument;

public:
   InvalidArgumentException(std::string a) { argument = a; }

   std::string what() const
   {
      return "Invalid argument: " + argument;
   }
};


#endif