# Byte Script 1.0
### Goals for this release:
* Plan out the basic constructs of the language
    * Lay out the capabilities of the language
* Implement a basic interpreter and preprocessor

### Future goals:
* Improve efficiency of preprocessor and interpreter

# Byte Script Design Specifications
An esoteric programming language made up of 1-byte long instructions. Byte Script data is stored in a program tape where each cell is an 8-byte integer.

Byte Script is inspired by BF, but it is intended to be easier to use and understand, faster to execute, and produce smaller interpreter sources.

Below is a tentative, work-in-progress list of Byte Script's instruction set (Descriptions marked with asterisks are in early stages and may not be implemented or may be changed):

|Instruction Code (ASCII)|Description|
|------------------------|-----------|
|59 (;)                   |terminator                                                                                    |
|61 (=)                   |assign value to current cell                                                                  |
|63 (?)                   |if start                                                                                      |
|58 (:)                   |else start                                                                                    |
|64 (@)                   |loop start                                                                                    |
|36 ($)                   |print from current cell onward until a 0 is encountered                                       |
|34 (")                   |input the given number of bytes into the tape starting at the current cell from standard input|
|60 (<)                   |move left given number of cells                                                               |
|62 (>)                   |move right given number of cells                                                              |
|94 (^)                   |jump to the given cell                                                                        |
|43 (+)                   |add to current cell                                                                           |
|45 (-)                   |subtract from current cell                                                                    |
|42 (\*)                  |multiply to current cell                                                                      |
|47 (/)                   |divide current cell                                                                           |
|35 (#)                   |\*import the given .bss or .bse file's instructions                                           |
|46 (.)                   |\*define a function with the given name                                                       |
|33 (!)                   |\*call a function with the given name                                                         |

## Introduction
Most of the above instructions can take an argument of a single 8-bit integer. For example, you can tell Byte Script to move 10 cells forward in the program tape with this instruction:
```
>10;
```
Byte Script will encounter the `>` then read the next byte of data from the file to determine how far it needs to go. The terminator character is needed to close off the statement.

You can also add an argument to the increment instruction to add a given number to the current cell.
```
+10;
```
The above instruction adds 10 to the current cell.

By design, Byte Script does not except any arguments outside of the range of an unsigned 8-bit integer (0 - 255). Any attempt to input a larger or smaller integer literal will simply cause it to wrap around until it is in the range of an unsigned 8-bit integer. Byte Script also has no support for floating-point numbers. Any division operations resulting in a floating-point number will simply be truncated.  

## The Instruction Set
Below is an explanation of each of the instructions that Byte Script currently implements. Instructions with an asterisk are currently still in developmental or planning stages and may not be implemented. 

Even though the Byte Script instruction set might seem relatively arbitrary, each one was picked for a specific reason. Below, in the explanations of each instruction, I will (with the exception of the most arbitrary cases, such as the addition instruction) also discuss the reason why a particular character was chosen for a particular task. This makes the instruction set easier to remember and the source code easier to understand.

A quick note on arguments: for instructions that take arguments, the default argument is always `1`. This is so that instructions such as `>;` work similar to their corresponding instructions in BF.

### Terminator (;)
The terminator instruction acts as Byte Script's punctuation. Every statement in Byte Script requires a terminator to close it off. The terminator is analgous to the ';' character used as a punctuating token in languages like C, C++, Java, etc.

### Assignment Instruction (=)
The assignment instruction assigns the given value to the current cell. This makes it so that users do not have to increment a cell until they get to their desired value. Instead, a user can simply directly assign the value of a cell.

Examples:
```
Assign fifteen to the current cell
=15;

Reassign the current cell to twenty
=20;
```
