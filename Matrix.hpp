#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <map>
#include <array>
#include <vector>
#include <functional> // for std::less
#include <type_traits> // for std::conditional

namespace algebra {

    /// Enum class to specify the storage order of the matrix
    enum class StorageOrder { RowMajor, ColumnMajor };

    /// Custom comparison function for column-major ordering
    template<typename T, std::size_t N>
    struct ColumnMajorCompare {
        bool operator()(const std::array<T, N>& lhs, const std::array<T, N>& rhs) const {
            // Compare column indices first
            if (lhs[1] < rhs[1]) return true;
            if (lhs[1] > rhs[1]) return false;
            // If column indices are equal, compare row indices
            return lhs[0] < rhs[0];
        }
    };

    template <typename T, StorageOrder Order> // forward declaration needed for friend method
    class Matrix;

    template <typename T, StorageOrder Order>
    std::vector<T> operator*(const Matrix<T, Order>& mat, const std::vector<T>& vec);

    /// Matrix class template
    template<typename T, StorageOrder Order>
    class Matrix {
    private:
        std::size_t rows; // Stores the number of rows in the matrix
        std::size_t cols; // Stores the number of columns in the matrix

        // Define default comparison type for row-major ordering
        using DefaultCompareType = std::less<std::array<std::size_t, 2>>;
        // Define custom comparison type for column-major ordering
        using ColumnMajorCompareType = ColumnMajorCompare<std::size_t, 2>;

        // Use conditional type selection based on the specified order
        using DataMapCompareType = std::conditional_t<Order == StorageOrder::ColumnMajor, ColumnMajorCompareType, DefaultCompareType>;

        /// Matrix data stored in a map for dynamic storage
        std::map<std::array<std::size_t, 2>, T, DataMapCompareType> data_map;

        /// Compressed storage variables
        std::vector<T> val; // Stores the non-zero values of the matrix
        std::vector<std::size_t> inner_idx; // Stores the inner indices of the non-zero values
        std::vector<std::size_t> outer_idx; // Stores the outer indices of the non-zero values

    public:

        // Default constructor
        Matrix() : rows(0), cols(0) {}

        /// Constructor to initialize the matrix with a specific number of rows and columns
        Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {}

        /// Method to resize the matrix
        void resize(std::size_t numRows, std::size_t numCols);

        /// Method to compress the matrix
        void compress();

        /// Method to uncompress the matrix
        void uncompress();

        /// Method to check if the matrix is compressed
        bool is_compressed() const;

        /// Method to print the matrix
        void print() const;

        /// Overloaded operators to access elements of the matrix
        T& operator()(std::size_t row, std::size_t col);
        const T operator()(std::size_t row, std::size_t col) const;

        /// Overloaded operator for matrix-vector multiplication
        friend std::vector<T> operator* <T>(const Matrix<T, Order>& mat, const std::vector<T>& vec);

        /// Method to read a matrix from a Matrix Market file
        void read_MatrixMarket(const std::string& filename);

    };

} // namespace algebra

#include "Matrix_impl.hpp" // Include the implementation of the Matrix class
#include "Matrix_operators.hpp" // Include the overloaded operators for the Matrix class
#include "Matrix_reader.hpp" // Include the Matrix Market file reader

#endif