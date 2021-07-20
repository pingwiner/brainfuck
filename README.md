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
