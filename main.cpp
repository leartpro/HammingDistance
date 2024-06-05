#include <iostream>
#include <vector>
#include <valarray>
#include <iomanip>

using namespace std;

std::vector<std::vector<int>> generate_binary_vectors(int n) {
    std::vector<std::vector<int>> vectors;
    int total_vectors = static_cast<int>(pow(2, n));

    for (int i = 1; i < total_vectors; ++i) {
        std::vector<int> vec(n, 0);
        for (int j = 0; j < n; ++j) {
            vec[j] = (i >> (n - 1 - j)) & 1;
        }
        vectors.push_back(vec);
    }
    return vectors;
}

std::vector<int> multiply(const std::vector<int> &v, const vector<vector<int>>& A) {
    std::vector<int> result(A.size(), 0);
    for (size_t i = 0; i < A.size(); ++i) {
        for (size_t j = 0; j < A[i].size(); ++j) {
            result[i] += A[i][j] * v[j];
        }
        result[i] %= 2;
    }
    return result;
}

int hamming_distance(const std::vector<int> &a, const std::vector<int> &b) {
    int distance = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            ++distance;
        }
    }
    return distance;
}

int gaussElimination(vector < vector < int >> &matrix) {
    int N = (int) matrix.size();
    int M = (int) matrix[0].size();
    int rank = 0;

    for (int col = 0; col < M; col++) {
        int row = rank;
        while (row < N && matrix[row][col] == 0) {
            row++;
        }
        if (row < N) {
            swap(matrix[row], matrix[rank]);
            for (int i = rank + 1; i < N; i++) {
                if (matrix[i][col] == 1) {
                    for (int j = col; j < M; j++) {
                        matrix[i][j] ^= matrix[rank][j];
                    }
                }
            }
            rank++;
        }
    }
    return rank;
}

int main() {
    int N, M;
    cout << "Anzahl der Zeilen (N): ";
    cin >> N;
    cout << "Anzahl der Spalten (M): ";
    cin >> M;
    vector<vector<int>> matrix(N, vector < int > (M));
    cout << "Elemente der Matrix:\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> matrix[i][j];
        }
    }
    vector<vector<int>> original_matrix = matrix;
    int k = gaussElimination(matrix);
    std::vector<std::vector<int>> binary_vectors = generate_binary_vectors(k);
    std::vector<std::vector<int>> codewords;
    for (const auto &vec: binary_vectors) {
        codewords.push_back(multiply(vec, original_matrix));
    }
    int min_distance = (int) original_matrix.size();
    for (size_t i = 0; i < codewords.size(); ++i) {
        for (size_t j = i + 1; j < codewords.size(); ++j) {
            int distance = hamming_distance(codewords[i], codewords[j]);
            if (distance > 0) {
                min_distance = std::min(min_distance, distance);
            }
        }
    }
    std::cout << "n: " << original_matrix.size() << std::endl;
    std::cout << "k: " << k << std::endl;
    std::cout << "d: " << min_distance << std::endl;
    std::vector<std::vector<int>> transposed_codewords(codewords[0].size(), std::vector<int>(codewords.size()));
    for (size_t row = 0; row < codewords.size(); ++row) {
        for (size_t col = 0; col < codewords[row].size(); ++col) {
            transposed_codewords[col][row] = codewords[row][col];
        }
    }
    std::cout << "Generierte Codewoerter:" << std::endl;
    for (auto & transposed_codeword : transposed_codewords) {
        for (int col : transposed_codeword) {
            std::cout << std::setw(2) << col << " ";
        }
        std::cout << std::endl;
    }
    return 0;
}