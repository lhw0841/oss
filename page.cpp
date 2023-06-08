#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

int main() {
    ifstream fin("page.inp");
    ofstream fout("page.out");

    int n;
    fin >> n;

    vector<int> ref;
    while (1) {
        int x;
        fin >> x;
        if (x == -1) break;
        ref.push_back(x);
    }

    int len = ref.size();
    int* fifo = new int[n];
    int* lru = new int[n];
    int* opt = new int[n];
    memset(fifo, -1, sizeof(int) * n);
    memset(lru, -1, sizeof(int) * n);
    memset(opt, -1, sizeof(int) * n);
    int fifo_cnt = 0, lru_cnt = 0, opt_cnt = 0;

    for (int i = 0; i < len; i++) {
        int x = ref[i];
        bool flag;

        // FIFO
        flag = false;
        for (int j = 0; j < n; j++) {
            if (fifo[j] == x) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            fifo_cnt++;
            if (i >= n) {
                int y = fifo[0];
                for (int j = 0; j < n - 1; j++) {
                    fifo[j] = fifo[j + 1];
                }
                fifo[n - 1] = x;
            }
            else {
                fifo[i] = x;
            }
        }

        // LRU
        flag = false;
        for (int j = 0; j < n; j++) {
            if (lru[j] == x) {
                flag = true;
                for (int k = j; k < n - 1; k++) {
                    lru[k] = lru[k + 1];
                }
                lru[n - 1] = x;
                break;
            }
        }
        if (!flag) {
            lru_cnt++;
            if (i >= n) {
                for (int j = 0; j < n - 1; j++) {
                    lru[j] = lru[j + 1];
                }
                lru[n - 1] = x;
            }
            else {
                lru[i] = x;
            }
        }

        // OPT
        flag = false;
        for (int j = 0; j < n; j++) {
            if (opt[j] == x) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            opt_cnt++;
            int* idx = new int[10001];
            memset(idx, -1, sizeof(int) * 10001);
            for (int j = i + 1; j < len; j++) {
                bool f2 = false;
                for (int k = 0; k < n; k++) {
                    if (opt[k] == ref[j]) {
                        idx[ref[j]] = j;
                        f2 = true;
                        break;
                    }
                }
                if (f2) continue;

                for (int k = 0; k < n; k++) {
                    if (idx[ref[j]] == -1 || idx[ref[j]] > idx[opt[k]]) idx[opt[k]] = idx[ref[j]];
                }
            }

            int mx_idx = -1, mx_val = -1;
            for (int j = 0; j < n; j++) {
                if (idx[opt[j]] > mx_val || mx_idx == -1) {
                    mx_val = idx[opt[j]];
                    mx_idx = j;
                }
            }

            opt[mx_idx] = x;

            delete[] idx;
        }
    }

    fout << "FIFO: " << fifo_cnt << '\n';
    fout << "LRU: " << lru_cnt << '\n';
    fout << "OPT: " << opt_cnt << '\n';

    delete[] fifo;
    delete[] lru;
    delete[] opt;

    return 0;
}
