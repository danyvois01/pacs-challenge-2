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
   - Defines the `Matrix` class for representing a sparse matrix.
   - Includes method declarations for compression, element extraction, and more.

2. **Matrix_impl.hpp**:
   - Implements the methods of the `Matrix` class defined in `Matrix.hpp`.

3. **Matrix_operators.hpp**:
   - Defines operators for accessing matrix elements and vector multiplication.

4. **Matrix_reader.hpp**:
   - Contains the method for reading a matrix from a file in Matrix Market format.

## Usage

1. Clone the repository.
4. Compile and execute the program with the following command:

```
make run
```

## Output

