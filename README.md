# Maths Expression Evaluator
Evaluates mathematical expressions by compiling to byte code for a stack machine.

# Installation
Clone the repo, e.g. using git:

```sh
git clone https://github.com/BakerSmithA/expr_evaluator.git
```

Build the compiler and virtual machine using Make:

```
cd expr_evaluator
make
```

# Example Program
Programs can consist of numbers, the +, -, *, and / operators, and parenthesis.
The program below is saved in a file named `example`.

```
2 * (10 + 5)
```

# Compiling
To run a program you first need to compile it. The example below compiles a
file named `example`, producing bytecode in a file named `output`.

```sh
$ ./out/comp example output
Done
```

# Interpreting
The outputted bytecode can now be run using the stack machine. To run the
outputted file above, use:

```sh
$ ./out/vm output
Result: 30
```
