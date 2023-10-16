This sample C code is for demonstrating the skill and design pattern of solving the question as shown below.<br/><br/>

Write a C program that reads the input file (ASCII_DATA.txt) line by line and write it to an output file.<br/>
The reading & writing of input file must follow the steps as below:<br/><br/>

i. Create a function "read_record()" for reading of input file, use "C" fread().<br/>
ii. The record being read must be stored into a linked list structure.<br/>
iii. The data being read must be printed out to screen using a function "show_record()".<br/>
iv. Each data printed out must then be written out to another file, use "C" fwrite().<br/>
vi. Before write data to output, Change each of the record DATAn to MYDATAn.<br/><br/>

How to run the program in Linux environment?<br/>
1. cd src/<br/>
2. make<br/>
3. ./test<br/><br/>
