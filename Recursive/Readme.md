# Recursive 

Recursive call refers to referring to oneself when defining something.

[Baek_Recursive_question](https://www.acmicpc.net/step/19)

+ A question that uses recursive calls.

```c
unsigned int factorial(unsigned int n)
 {
     if (n <= 1)
         return 1;
     else
         return n * factorial(n-1);
 }
 ```
