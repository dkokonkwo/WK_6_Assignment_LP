Tasks to Complete

Qn1. Create a Shared Library (3)

You are required to write a program that completes text processing. 

The function reads names (first name, last name) from a file and sort them in the ascending order
The function that counts how many entries in the file and return the value at the console
This program is called string_manipulator.c

Given the program (string_manipulator.c)

Create a static shared library from the above code
Create a dynamic shared library from the above code
Write another program test.c that will be used test program correctness (will make use of the shared libraries function).

You can link test.c with the static shared library and generate an executable code named test1
You can link test.c with the dynamic shared library and generate an executable code name test2
You are required to confirm which of the files you have written or generated are elf files. Support your answer with the appropriate use of readelf command.

Qn2. Calculator (3)

Given the nature of a simple calculator that has 4 functions (add, subtract, multiply and divide) that we want to implement. It is intentional to implement this program using x86 assembly language.

You are required to implement this simple calculator where the user will will be required to type the values from the keyboard.

Qn3. Weather Data Manipulation (3)

Given a datasetLinks to an external site. for the weather, you will be analyzing the data based on average temperature and complete the following tasks.

You are asked to determine the mode temperate
You are required to determine the standard deviation
You are required to determine the median
You are required to implement a CPython program that achieves the tasks highlighted.

Qn4. POSIX Threads (4)

Adding n numbers is a mathematical function that is used to test system performance in regard to how system behaves as n increases reasonably. Multi-threads are implemented improve the performance as opposed to single threaded programs.

You are required to implement a multi-threaded program each thread will add up 100 elements to form a sub-total whereby all sub-totals will be added together in the end to give the grand sum. 

For example; if n=1000, where shall have 10 threads where each thread will be taking 100 elements. 

We assume that n is any value between 200 and 2000 (200<n<=2000).

Implement a multi-threaded program that achieves the addition of n numbers.
Implement a single threaded program that achieves the addition of n numbers.
Use system monitor tool to highlight which program is working efficiently as n grows reasonably.
Qn5. Using Strace Tool (2)

Write a C program that creates a child process using fork and execute the new program with exec

Use strace to trace the parent and child process. The results will be logged in a file.