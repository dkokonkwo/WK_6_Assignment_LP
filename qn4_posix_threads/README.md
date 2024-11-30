Qn4. POSIX Threads (4)

Adding n numbers is a mathematical function that is used to test system performance in regard to how system behaves as n increases reasonably. Multi-threads are implemented improve the performance as opposed to single threaded programs.

You are required to implement a multi-threaded program each thread will add up 100 elements to form a sub-total whereby all sub-totals will be added together in the end to give the grand sum. 

For example; if n=1000, where shall have 10 threads where each thread will be taking 100 elements. 

We assume that n is any value between 200 and 2000 (200<n<=2000).

- Implement a multi-threaded program that achieves the addition of n numbers.
- Implement a single threaded program that achieves the addition of n numbers.
- Use system monitor tool to highlight which program is working efficiently as n grows reasonably.

SOLUTION:
Run the "single_thread" file to test the single thread implementation. To test the multi-threaded implementation, run the "multi_thread" file.

To monitor the effciency of the both programs, run the "threads_monitor" file which produce ouputs with diffrent n values between 200 and 2000.