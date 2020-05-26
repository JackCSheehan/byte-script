# Byte Script Language Specifications
Byte script is an esoteric programming language made up of 1-byte long instructions. Byte Script data is stored in a program tape where each cell is an 8-byte integer.

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

A quick note on arguments: for instructions that take arguments, the default argument is always `1`. This is so that instructions such as `>;` work similar to their corresponding instructions in BF.

### Terminator (;)
The terminator instruction acts as Byte Script's punctuation. Every statement in Byte Script requires a terminator to close it off. The terminator is analgous to the ';' character used as a punctuating token in languages like C, C++, Java, etc.

### Assignment Instruction (=)
The assignment instruction assigns the given value to the current cell. This makes it so that users do not have to increment a cell until they get to their desired value. Instead, a user can simply directly assign the value of a cell. If no argument is provided, the cell will be assigned the value of 1.

Examples:
```
Assign fifteen to the current cell
=15;

Reassign the current cell to twenty
=20;
```

### Move Left (<)
This instruction decrements the cell pointer the given number of indices. Trying to move past index 0 does nothing; the pointer will stop at 0 and will not go any lower. If no argument is provided, the instruction will move one cell left. 

Examples:
```
Move left two cells
<2;

Move left one cell
<;
```

### Jump (^)
This instruction jumps to the given cell. The jump instruction uses the logic of both the move left and move right instructions, and inherits their behavior as a result. In other words, the jump instruction will append more cells to the tape if needed, and it will not go below cell index 0. If no argument is provided, the instruction will jump to cell 1.

Examples:
```
Jump to cell twenty
^20;

Jump to cell three
^3;
```

### Move Right (>)
This instruction increments the cell pointer the given number of indices. For efficiency purposes, the program tape is extended as needed when the user needs to store more data. If the user moves right over the current largest index, as many cells as needed are added to the tape to accommodate the request. If the user allocates too many cells and they do not have memory left for more, an error will be thrown and the interpreter will terminate. If no argument is provided, the instruction will move one cell right. 

Example:
```
Move right two cells
>2;

Move right one cell
>;
```

### Print Instruction ($)
The print instruction will print the value of every cell from the current cell onward until either an ASCII 0 is encountered or the end of the allocated program tape is reached. This means that Byte Script supports C-style string. To print something to the console, simply assign the value of contiguous memory locations to spell out some kind of word in ASCII characters. Then, assign the cell after your word to 0 to avoid printing the data in any cells after.

Here's a simple hello world program in Byte Script:
```
Assign contiguous memory locations with the ASCII characters for 'Hello World'

Hello
=72;
>;
=101;
>;
=108;
>;
=108;
>;
=111;
>;
=32;
>;

World
=87;
>;
=111;
>;
=114;
>;
=108;
>;
=100;

Add ASCII null terminator
>;
=0;

Jump back to beginning of tape
^0;

Call print instruction
$;
```

### Input Instruction(")
The input instruction reads the given number of bytes from stdin into the program tape starting at the current cell. If more input is entered than was requested to be read by the input instruction, the extra input will be truncated. If fewer bytes of input are entered than request, only what was actually input will be written to the program tape. If there is already data in the program tape that is after the cell pointer's position, it will be overwritten if enough bytes are requested. For example, if there is a string stored at cell 5, the cell pointer is at cell 0, and the user requests and gets 10 bytes of input, the string at cell 5 will simply be overwritten. Keep in mind, strings in Byte Script are treated as C-string, so 10 bytes of input is really 9 bytes of input plus the null terminator. The null terminator is automatically placed at the end of the user's input.

Example:
```
Jump to cell zero
^0

Get ten bytes of input from stdin
"10;

Print the input
$;
```

### Add Instruction (+)
Adds the given value to the current cell. If no argument is provided, the instruction will add 1 to the current cell. If this operation results in a cell value outside the range of an unsigned 8-bit integer, the cell value will wrap around until it is within said range.

### Subtract Instruction (-)
Subtracts the given value from the current cell. If no argument is provided, the instruction will subtract 1 from the current cell. If this operation results in a cell value outside the range of an unsigned 8-bit integer, the cell value will wrap around until it is within said range.

### Multiply Instruction (*)
Multiplies the given value to the current cell. If no argument is provided, the instruction will multiply 1 to the current cell. If this operation results in a cell value outside the range of an unsigned 8-bit integer, the cell value will wrap around until it is within said range.

### Divide Instruction (/)
Adds the given value to the current cell. If no argument is provided, the instruction will add 1 to the current cell. If this operation results in a cell value outside the range of an unsigned 8-bit integer, the cell value will wrap around until it is within said range.

Examples:
```
Add five to current cell
+5;

Multiply current cell by five
*5;

Subtract five from current cell
-5;

Divide current cell by five
/5;
```

### If Start Instruction (?)
Executes the Byte Script code between the braces if the cell pointed to by the cell pointer is 0. Program will thrown an error if no braces are present.

Example:
```
If the current cell is zero, assign current cell to five and move 5 cells right
?
{
    =5;
    >5;
}
```

### Else Instruction (:)
If the current cell is *not* 0, execute the code in the braces. Can be used on its own, though it is called an else instruction because it effectively acts as an `else` statement when used with the `?` instruction. Program will thrown an error if no braces are present.

Example:
```
Assign current cell to five if the current cell is zero and assign the current cell to ten if the current cell is NOT zero
?
{
    =5;
}
:
{
    =10;
}
```

### Loop Start (@)
Repeats the Byte Script code inside the braces until the given number of times.

Example:
```
Print string that starts at cell zero twenty times
@20;
{
    Jump to cell zero
    ^0;

    Print string starting at cell zero
    $;
}
```
