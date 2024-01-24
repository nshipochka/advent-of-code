#include<iostream>
#include<vector>

using std::vector;

bool isInMatrix(int x, int y, int m, int n) {
    return x >= 0 && x < n && y >= 0 && y < m;
}

int getAvg(int i, int j, vector<vector<int>>& img) {
    int n = img.size();
    int m = img[0].size();

    double avg = 0;
    int elements = 0;

    int xs[9] = { -1, -1, -1, 0, 0, 0,  1, 1, 1 };
    int ys[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };

    for (int k = 0; k < 9; ++k) {
        if (isInMatrix(i + xs[k], j + ys[k], m, n)) {
            avg += img[i + xs[k]][j + ys[k]];
            elements++;
        }
    }

    return floor(avg / elements);
}

vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
    int n = img.size();
    int m = img[0].size();

    vector<vector<int>> smoothed(n, vector<int>(m));

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            smoothed[i][j] = getAvg(i, j, img);

    return smoothed;
}

void print(vector<vector<int>>& v) {
    for (int i = 0; i < v.size(); ++i) {
        for (int j = 0; j < v[i].size(); ++j)
            std::cout << v[i][j] << " ";
        std::cout << std::endl;
    }
}

int main() {
    vector<vector<int>> v = { {2,3,4}, {5,6,7}, {8,9,10}, {11,12,13}, {14,15,16} };
    vector<vector<int>> result = imageSmoother(v);

    print(result);

    return 0;
}