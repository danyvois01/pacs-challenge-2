#include <chrono>
#include "Matrix.hpp"

using namespace algebra;

template <StorageOrder Order>
void test() {
    Matrix<double, Order> mat(3, 4);

    // Populate the matrix
    mat(0, 0) = 1;
    mat(0, 1) = 2;
    mat(0, 3) = 3;
    mat(1, 1) = 4;
    mat(1, 2) = 5;
    mat(2, 3) = 6;

    mat.print();
    mat.compress();
    mat.print();
    mat.uncompress();
    mat.print();

    mat.read_MatrixMarket("lnsp_131.mtx");

    const std::vector<double> x(131, 1);

    // Before compression
    auto start_multiply = std::chrono::steady_clock::now();
    const std::vector<double> y_before_compress = mat * x;
    auto end_multiply = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> multiply_time_before_compress = end_multiply - start_multiply;

    // Before compression
    auto start_compress = std::chrono::steady_clock::now();
    mat.compress();
    auto end_compress = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> compress_time = end_compress - start_compress;

    // After compression
    start_multiply = std::chrono::steady_clock::now();
    const std::vector<double> y_after_compress = mat * x;
    end_multiply = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::micro> multiply_time_after_compress = end_multiply - start_multiply;

    std::cout << "Compression time: " << compress_time.count() << " microseconds" << std::endl;
    std::cout << "Matrix-vector product before compression took: " << multiply_time_before_compress.count() << " microseconds" << std::endl;
    std::cout << "Matrix-vector product after compression took: " << multiply_time_after_compress.count() << " microseconds" << std::endl;
}
