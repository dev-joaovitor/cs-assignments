# Programming Lab I
## Projects

### [1. Matrix Operations](#1-matrix-operations-1)
### [2. Base Converter](#2-base-converter-1)
---

### 1. Matrix Operations

#### Summary

The purpose of this program is to generate two random matrices and perform operations with them.

#### What should it do?
- [x] Read matrix A dimensions
- [x] Fill matrix A with random values
- [x] Read matrix B dimensions
- [x] Fill matrix B with random values
- [x] Show matrices
- [x] Multiply matrices (A * B)
- [x] Add matrices (A + B)
- [x] Subtract matrices (A - B)
- [x] Transpose matrices
- [x] Generate identity matrix of given size

#### How to run?
```sh
cd matrix-operations
gcc main.c matrix.c operations/operations.c -o exec.o
./exec.o
```
---

### 2. Base Converter

#### Summary

The purpose of this program is to allow you to convert a number from any base (until 32) to base 10 (decimal).

#### What should it do?
- [x] Read the number to be converted
- [x] Read the base of the number to be converted
- [x] Convert the number to base 10

#### How to run?
```sh
cd base-converter
gcc main.c -o exec.o
./exec.o
```
---

#### GCC (GNU Compiler Collection) Version
```
gcc 14.2.1
```
###### [Back to projects](#projects)
