# pacs-challenge-2

## A sparse matrix class

This repository hosts the second assignment of the APSC course 2023-2024.
The C++ program implements a class which is designed to represent a dynamic sparse matrix with flexible storage ordering. The class is implemented in the **algebra** namespace.

## Features

- Dynamic construction using a `std::map<std::array<std::size_t,2>,T>`.
- Capable of storing elements in row-wise or column-wise order.
- Provides methods for compression, decompression, resizing, and checking compression status.
- Includes friend operators for matrix-vector multiplication.

## Project Overview

The project consists of the following files:

1. **Matrix.hpp**:
   - Defines the `Matrix` class for representing a dynamic matrix.
   - Includes method declarations for compression, element extraction, and more.

2. **Matrix_impl.hpp**:
   - Implements the following methods of the `Matrix` class defined in `Matrix.hpp`:
     - `resize`: Resizes the matrix to the specified number of rows and columns.
     - `compress`: Compresses the matrix.
     - `uncompress`: Uncompresses the matrix from either CSR or CSC format.
     - `is_compressed`: Checks if the matrix is compressed.
     - `print`: Prints the matrix.

3. **Matrix_operators.hpp**:
   - Defines the following operators for the `Matrix` class:
     - `operator()`: Overloaded for accessing matrix elements.
     - `operator*`: Overloaded for matrix-vector multiplication.

4. **Matrix_reader.hpp**:
   - Contains the method for reading a matrix from a file in Matrix Market format.

## Usage

1. Clone the repository.
4. Compile and execute the program with the following command:

```
make run
```

## Output

