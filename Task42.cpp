#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void worker_multiply_row(int row, int matrix[3][3], int vec[3], int result[3]) {
    int sum = 0;
    for (int col = 0; col < 3; col++) sum += matrix[row][col] * vec[col];
    result[row] = sum;
}

int main() {
    int matrix[3][3] = { {1,2,3}, {4,5,6}, {7,8,9} };
    int vec[3] = {1, 2, 3};
    int result[3];
    vector<thread> threads;
    for (int i = 0; i < 3; i++)
        threads.push_back(thread(worker_multiply_row, i, matrix, vec, result));
    for (auto& t : threads) t.join();
    cout << "Result Vector : [" << result[0] << ", " << result[1] << ", " << result[2] << "]" << endl;
    return 0;
}
