# C Minus Compiler

C Minus is a very simple language which we implemented the frontend and IR generator of it in Python with a self made IR [here](https://github.com/bigwhoman/C-Minus-Compiler) for the project of compiler course in Sharif University of Technology, lectured by Dr. Ghasemsani. However, because the IR was a self made thing, we could only run it via an interpreter. Instead, I challenged myself to write the project in Flex/Bison/LLVM in order to learn them and have fun.

## Compiling

To compile this compiler, you need Flex, Bison and LLVM-15. You can get them all with the following command in Ubuntu/Debian:

```bash
apt install flex bison clang-15 llvm-15 build-essential g++-12
```

Note: You might also need g++-12 because llvm-15 uses it.

Then simply execute `make` command to build the compiler. The compiler will accept the input source filename as the first argument. This will cause the IR to be outputted in the stdout. If you want it to be outputted in a file, you can pass the output filename as the second argument.

The IR can be compiled with `clang-15 output.ll` command to an executable.

### Tests

Tests can be run via `make verify-all` command. If any of the tests fail, the testing will stop on that test. Otherwise, a green message that reads `All tests passed!` will appear. Tests are simply just an input program and an expected output that should be generated after the program is ran.


## Limitations

### Semantic Analyzer

Currently, the compiler does not have an semantic analyzer which means that most of errors are either not caught at all or result in an assertion failure that results in compiler aborting.

### Optimizer

Literally the amount of optimizations done for the IR is fucking zero. Even the constant folding is turned off. You can turn on the constant folding by changing `the_builder` initialization with this line:

```cpp
builder(std::make_unique<llvm::IRBuilder<llvm::NoFolder>>(*the_context))
```

### Exit Code

The exit code of the compiled program is almost always non zero. The program runs successfully but the return value must be explicitly defined which in this case is not.

## Language Specification

The language specification (the assignments) is placed in the `spec` folder.

Alongside the specification, there is also an addition: The `input()` function. This function will simply read an integer from stdin. For example, this program can be used to calculate the square of a number:

```c
void main(void){
	int a;
	a = input();
	output(a * a);
}
```