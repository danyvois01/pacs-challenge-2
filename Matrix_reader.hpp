#ifndef MATRIX_READER_HPP
#define MATRIX_READER_HPP

#include <fstream>
#include <sstream>
#include <string>

#include "Matrix.hpp"

namespace algebra {

    /// Method to read a matrix from a Matrix Market file
    template<typename T, StorageOrder Order>
    void Matrix<T, Order>::read_MatrixMarket(const std::string& filename) {
        // Open the file
        std::ifstream file(filename);
        // If the file cannot be opened, throw an error
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + filename);
        }

        // Read the first line of the file
        std::string line;
        std::getline(file, line);
        // If the first line does not match the expected Matrix Market format, throw an error
        if (line[0] != '%') {
            throw std::runtime_error("Invalid Matrix Market format");
        }

        // Read the number of rows, columns, and non-zero elements from the file
        std::size_t NumRows, NumCols, NumNnz;
        file >> NumRows >> NumCols >> NumNnz;

        // Resize the matrix to the read dimensions
        this->resize(NumRows, NumCols);

        // Read the matrix data from the file
        for (std::size_t k = 0; k < NumNnz; ++k) {
            std::size_t i, j;
            T value;
            // Read the row index, column index, and value of each non-zero element
            file >> i >> j >> value;
            // Subtract 1 from the indices because Matrix Market indices are 1-based
            (*this)(i - 1, j - 1) = value;
        }

        // Close the file
        file.close();
    }

} // namespace algebra

#endif
