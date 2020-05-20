# byte-script
An esoteric programming language made up of 1-byte long instructions. Byte Script data is stored in a program tape where each cell is an 8-byte integer.

Below is a tentative, work-in-progress list of Byte Script's instruction set:

|Instruction Code (ASCII)|Description|
|------------------------|-----------|
|59 (;)                   |terminator                                                                |
|61 (=)                   |assign value to current cell                                              |
|63 (?)                   |if start                                                                  |
|58 (:)                   |else start                                                                |
|64 (@)                   |loop start                                                                |
|36 ($)                   |print from current cell onward until a 0 is encountered                   |
|60 (<)                   |move left given number of cells                                           |
|62 (>)                   |move right given number of cells                                          |
|43 (+)                   |add to current cell                                                       |
|45 (-)                   |subtract from current cell                                                |
|42 (\*)                  |multiply to current cell                                                  |
|47 (/)                   |divide current cell                                                       |
