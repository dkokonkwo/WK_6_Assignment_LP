Qn1. Create a Shared Library (3)

You are required to write a program that completes text processing. 

1. The function reads names (first name, last name) from a file and sort them in the ascending order
2. The function that counts how many entries in the file and return the value at the console

This program is called string_manipulator.c

Given the program (string_manipulator.c)

- Create a static shared library from the above code
- Create a dynamic shared library from the above code

Write another program test.c that will be used test program correctness (will make use of the shared libraries function).

- You can link test.c with the static shared library and generate an executable code named test1
- You can link test.c with the dynamic shared library and generate an executable code name test2

You are required to confirm which of the files you have written or generated are elf files. Support your answer with the appropriate use of readelf command.