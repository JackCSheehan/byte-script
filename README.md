# byte-script
An esoteric programming language made up of 1-byte long instructions.

Below is a tentative, work-in-progress list of Byte Script's instruction set:

|Instruction Code (ASCII)|Description|
|------------------------|-----------|
|59 (;)                   |terminator                       |
|61 (=)                   |assign value to current cell     |
|63 (?)                   |if start                         |
|58 (:)                   |else start                       |
|64 (@)                   |loop start                       |
|36 ($)                   |function start                   |
|33 (!)                   |call function                    |
|60 (<)                   |move left given number of cells  |
|62 (>)                   |move right given number of cells |
