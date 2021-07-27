Brainfuck interpreter

Compilation: 
  make
  
Usage:
  bf source.bf
  

This interpreter also supports compressed sources. 

Compressing source:
  bfcompress source.bf -o source.cbf
  
Running compressed source:
  bf -c source.cbf

Brainfuck compiler
    bfc source.bf -o out.com

Compiles brainfuck source to MS-DOS COM executable.