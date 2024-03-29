#include <iostream>
#include <vector>
#include <cmath>

using std::vector, std::cout, std::endl;

typedef vector<vector<double>> Mat;

void printMat(const Mat& matrix) {
    for (const auto& line : matrix){
        for (const auto& val : line){
            cout << val << " ";
        }
        cout << "\n";
    }
}

Mat divideMat(const Mat& matrix, double num){
    Mat res = matrix;
    int n = res.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            res[i][j] /= num;
        }
    }
    return res;
}

Mat identityMatrix(int size) {
    Mat matC(size, vector<double>(size, 0.0));
    for (int i = 0; i < size; i ++) {
        matC[i][i] = 1;
    }
    return matC;
}

// C = A*B; very inefficient as it createx new C instead of changin A or B;
Mat multMat(const Mat& matA, const Mat& matB) {
    int n = matA.size();
    Mat matC(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++){
                matC[i][j] += matA[i][k]*matB[k][j];
            }
        }
    }
    return matC;
}

Mat sumMat(const Mat& matA, const Mat& matB) {
    int n = matA.size();
    Mat matC(n, vector<double>(n, 0.0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matC[i][j] = matA[i][j] + matB[i][j];
        }
    }
    return matC;
}

// C = exp(A), super inefficient
Mat expMat(const Mat& matA, int order) {
    Mat matB = matA; // for intermideate powers
    Mat matC = identityMatrix(matA.size()); //for accumulating and result
    if (order == 0){ return matC;}
    matC = sumMat(matC, matB);
    if (order == 1){ return matC;}
    double factor = 1;
    for (int i = 2; i < order+1; i ++) {
        factor *= i; //factor = i!
        matB = multMat(matA, matB); // B = A^n
        matC = sumMat(matC, divideMat(matB, factor));
    }
    return matC;
}

Mat sinMat(const Mat& matA, int order) {
    Mat matB = matA; // for intermideate powers
    Mat matC = matA; //for accumulating and result
    if (order == 0){ return matC;}
    double factor = 1;
    for (int i = 3; i < 2*order+1; i = i + 2) {
        factor = (-1)*factor*i*(i - 1); //factor = i!*(-1)^n
        matB = multMat(matA, matB);
        matB = multMat(matA, matB); // B = A^n now
        matC = sumMat(matC, divideMat(matB, factor));
    }
    return matC;
}

Mat cosMat(const Mat& matA, int order) {
    Mat matB = identityMatrix(matA.size()); // for intermideate powers
    Mat matC = identityMatrix(matA.size()); //for accumulating and result
    if (order == 0){ return matC;}
    double factor = 1;
    for (int i = 2; i < 2*order+1; i = i + 2) {
        factor = (-1)*factor*i*(i - 1); //factor = i!*(-1)^n
        matB = multMat(matA, matB);
        matB = multMat(matA, matB); // B = A^n now
        matC = sumMat(matC, divideMat(matB, factor));
    }
    return matC;
}


int main() {
    Mat matrix = {{1, 0, 0}, {0, 2, 0}, {0, 0, 0}};
    Mat c = cosMat(matrix, 10);
    Mat s = sinMat(matrix, 10);
    Mat e = expMat(matrix, 10);
    printMat(matrix);
    
    printMat(c);
    cout << cos(1) << " " << cos(2) << endl << endl;
    
    printMat(s);
    cout << sin(1) << " " << sin(2) << endl << endl;
    
    printMat(e);
    cout << exp(1) << " " << exp(2) << endl << endl;

    return 0;
}