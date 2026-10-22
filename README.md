# GDB Assignment – Phase 2 Report

## Task 1: Finding an Incorrect Calculation

In this task, I used GDB to find why the multiplication result was wrong.

For testing, I changed the multiplication function in `calculator.cpp` by mistake. I used `+` instead of `*`.

```cpp
double Calculator::multiply(double operandA, double operandB) {
    double intermediate = operandA + operandB;
    return intermediate;
}
```

When I entered `10 * 5`, the correct answer should have been `50`, but the program gave `15`.

### GDB Commands Used

```gdb
break Calculator::multiply
run 10 "*" 5
info args
print operandA
print operandB
next
print intermediate
backtrace
```

### GDB Output

```powershell
PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> gdb .\calculator_debug.exe
GNU gdb (GDB) 17.2
Reading symbols from .\calculator_debug.exe...

(gdb) break Calculator::multiply
Breakpoint 1 at 0x140001722: file calculator.cpp, line 13.

(gdb) run 10 "*" 5
Starting program: C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2\calculator_debug.exe 10 "*" 5

Thread 1 hit Breakpoint 1, Calculator::multiply
(this=0x5ffe8f, operandA=10, operandB=5) at calculator.cpp:13

(gdb) info args
this = 0x5ffe8f
operandA = 10
operandB = 5

(gdb) print operandA
$1 = 10

(gdb) print operandB
$2 = 5

(gdb) next
14          return intermediate;

(gdb) print intermediate
$3 = 15

(gdb) backtrace
#0  Calculator::multiply
    (this=0x5ffe8f, operandA=10, operandB=5)
    at calculator.cpp:14
#1  0x00007ff6ee191622 in main
    (argc=4, argv=0x79b840)
    at main.cpp:27

(gdb) quit
```

From the output, I found that the values of the two operands were correct. The problem was in the calculation of `intermediate`, which was `15` instead of `50`.

### Fix

I changed the `+` operator to the `*` operator.

```cpp
double Calculator::multiply(double operandA, double operandB) {
    double intermediate = operandA * operandB;
    return intermediate;
}
```

### Verification

```powershell
PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> g++ -g -O0 main.cpp calculator.cpp -o calculator_debug.exe

PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> .\calculator_debug.exe 10 "*" 5
Result: 50
```

The program gave the correct answer after I fixed the operator.

---

## Task 2: Finding an Infinite Loop

In this task, I used GDB to check a problem in the `calculatePower()` function.

The function calculated powers by multiplying the base again and again. The loop had a problem because `counter++` was missing.

```cpp
double Calculator::calculatePower(double base, int exponent) {
    double result = 1.0;
    int counter = 0;

    while (counter < exponent) {
        result *= base;
    }

    return result;
}
```

The value of `counter` stayed at `0`, so the condition `counter < exponent` was always true. This caused an infinite loop.

### GDB Commands Used

```gdb
break Calculator::calculatePower
run 2 "^" 3
next
next
next
print counter
print result
backtrace
```

### GDB Output

```powershell
PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> gdb .\calculator_debug.exe
GNU gdb (GDB) 17.2
Reading symbols from .\calculator_debug.exe...

(gdb) break Calculator::calculatePower
Breakpoint 1 at 0x14000190d: file calculator.cpp, line 38.

(gdb) run 2 "^" 3
Starting program: C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2\calculator_debug.exe 2 "^" 3

Thread 1 hit Breakpoint 1, Calculator::calculatePower
(this=0x5ffe8f, base=2, exponent=3) at calculator.cpp:38

(gdb) next
39          double result = 1.0;

(gdb) next
40          int counter = 0;

(gdb) next
42          while (counter < exponent) {

(gdb) next
43              result *= base;

(gdb) print counter
$1 = 0

(gdb) print result
$2 = 2

(gdb) backtrace
#0  Calculator::calculatePower
    (this=0x5ffe8f, base=2, exponent=3)
    at calculator.cpp:43
#1  0x00007ff7e9c91680 in main
    (argc=4, argv=0x6384d0)
    at main.cpp:38
```

I saw that `counter` was still `0` after the loop ran once. This showed that the counter was not being increased.

### Fix

I added `counter++` inside the loop.

```cpp
double Calculator::calculatePower(double base, int exponent) {
    double result = 1.0;
    int counter = 0;

    while (counter < exponent) {
        result *= base;
        counter++;
    }

    return result;
}
```

### Verification

```powershell
PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> g++ -g -O0 main.cpp calculator.cpp -o calculator_debug.exe

PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> .\calculator_debug.exe 2 "^" 3
Result: 8
```

The program returned `8`, which was the correct answer for `2^3`.

---

## Task 3: Finding a Segmentation Fault

In this task, I created an `ExpressionHelper` class. It used pointers to receive two numbers and add them together.

A null pointer was used by mistake in `main.cpp`.

```cpp
double* firstPointer = nullptr;

computationResult =
    helper.evaluate(firstPointer, &inputNum2);
```

The `evaluate()` function tried to use the pointer:

```cpp
double ExpressionHelper::evaluate(double* firstNumber, double* secondNumber) {
    return *firstNumber + *secondNumber;
}
```

Because `firstPointer` was null, the program crashed when it tried to use `*firstNumber`.

### Build and Start GDB

```powershell
PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> g++ -g -O0 main.cpp calculator.cpp expression_helper.cpp -o calculator_debug.exe

PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> gdb .\calculator_debug.exe
GNU gdb (GDB) 17.2
Reading symbols from .\calculator_debug.exe...
```

### GDB Output

```gdb
(gdb) break ExpressionHelper::evaluate
Breakpoint 1 at 0x140001xxx: file expression_helper.cpp, line 4.

(gdb) run 10 + 5
Starting program: C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2\calculator_debug.exe 10 + 5

Thread 1 hit Breakpoint 1, ExpressionHelper::evaluate
(this=0x5ffe86, firstNumber=0x0, secondNumber=0x5ffe88)
at expression_helper.cpp:4

4           return *firstNumber + *secondNumber;

(gdb) step
Thread 1 received signal SIGSEGV, Segmentation fault.
0x00007ff603031964 in ExpressionHelper::evaluate
(this=0x5ffe86, firstNumber=0x0, secondNumber=0x5ffe88)
at expression_helper.cpp:4

4           return *firstNumber + *secondNumber;

(gdb) backtrace
#0  0x00007ff603031964 in ExpressionHelper::evaluate
    (this=0x5ffe86, firstNumber=0x0, secondNumber=0x5ffe88)
    at expression_helper.cpp:4
#1  0x00007ff6030315d1 in main
    (argc=4, argv=0x74b900)
    at main.cpp:25

(gdb) frame 0
#0  ExpressionHelper::evaluate
    (this=0x5ffe86, firstNumber=0x0, secondNumber=0x5ffe88)
    at expression_helper.cpp:4

(gdb) info args
this = 0x5ffe86
firstNumber = 0x0
secondNumber = 0x5ffe88

(gdb) print firstNumber
$1 = (double *) 0x0

(gdb) print *firstNumber
Cannot access memory at address 0x0

(gdb) list
1       #include "expression_helper.h"
2
3       double ExpressionHelper::evaluate(double* firstNumber, double* secondNumber) {
4           return *firstNumber + *secondNumber;
5       }
```

I found that `firstNumber` had the value `0x0`. This meant that it was a null pointer. The error happened when the program tried to dereference it.

### Fix

I changed the pointer so that it pointed to `inputNum1`.

```cpp
double* firstPointer = &inputNum1;

computationResult =
    helper.evaluate(firstPointer, &inputNum2);
```

### Verification

```powershell
PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> g++ -g -O0 main.cpp calculator.cpp expression_helper.cpp -o calculator_debug.exe

PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> .\calculator_debug.exe 10 + 5
Result: 15
```

The program ran correctly and returned `15` after I fixed the pointer.

---

## Task 4: Debugging a Multi-File Problem

In this task, I checked a problem that involved more than one source file.

The program used `main.cpp`, `calculator.cpp`, and `expression_helper.cpp`. I used GDB to follow the program from `main()` to the function that caused the problem.

### GDB Commands Used

```gdb
break main
run
next
step
backtrace
info locals
list
```

I checked the function calls and the values of the variables. I found the problem in the source code, corrected it, and compiled all the files again.

```powershell
PS C:\Users\subas\Desktop\Multicoreware\GDB\I000569-Subashree_S\Phase2> g++ -g -O0 main.cpp calculator.cpp expression_helper.cpp -o calculator_debug.exe
```

After recompiling, the program ran without the earlier problem.

---

## Task 5: Logging and GDB

I also compared normal logging with GDB debugging.

Logging displayed values by using print statements in the program. For example:

```cpp
std::cout << "operandA: " << operandA << std::endl;
std::cout << "operandB: " << operandB << std::endl;
```

This was useful for checking values, but I had to add the print statements to the program and compile it again.

GDB allowed me to stop the program at a particular line and check the values without adding many print statements. I used commands such as `print`, `next`, `step`, and `backtrace`.

I found GDB more useful for this assignment because it helped me find the exact line where each problem happened.

---

## Difficulties Faced

I faced a few problems while doing this assignment:

- I used the wrong operator in the multiplication function.
- I forgot to increase the counter in the power function.
- I passed a null pointer to the expression helper.
- I initially found it difficult to understand the GDB output.
- I learned that the program had to be compiled with `-g` to use GDB properly.
- I used `-O0` so that the program was easier to follow while debugging.

I solved these problems by setting breakpoints, checking variable values, using `backtrace`, fixing the code, and running the program again.
