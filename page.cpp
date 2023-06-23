#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

int n, m;
int a[10005], b[10005];
int f[10005], l[10005], o[10005];

void FIFO() {
    queue<int> q;
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        if (q.size() < n) {
            if (!f[a[i]]) {
                q.push(a[i]);
                f[a[i]] = 1;
                cnt++;
            }
        }
        else {
            if (!f[a[i]]) {
                int x = q.front();
                q.pop();
                f[x] = 0;
                q.push(a[i]);
                f[a[i]] = 1;
                cnt++;
            }
        }
    }
    printf("FIFO: %d\n", cnt);
}

void LRU() {
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        if (l[a[i]]) {
            b[l[a[i]]] = i;
        }
        else {
            if (l[a[i - n]]) {
                f[l[a[i - n]]] = 0;
            }
            l[a[i]] = i;
            b[i] = a[i];
            f[a[i]] = 1;
            cnt++;
        }
    }
    printf("LRU: %d\n", cnt);
}

void OPT() {
    int cnt = 0;
    for (int i = 1; i <= m; i++) {
        if (o[a[i]]) {
            continue;
        }
        if (o[0] < n) {
            o[0]++;
            o[a[i]] = o[0];
        }
        else {
            int x = -1, y = -1;
            for (int j = i + 1; j <= m; j++) {
                if (!x || b[o[b[x]]] > b[o[b[j]]]) {
                    x = j;
                }
                if (!y || b[o[b[y]]] < b[o[b[j]]]) {
                    y = j;
                }
            }
            o[b[o[b[x]]]] = 0;
            o[a[i]] = o[b[y]];
        }
        b[i] = a[i];
        cnt++;
    }
    printf("OPT: %d\n", cnt);
}

int main() {
    freopen("page.inp", "r", stdin);
    freopen("page.out", "w", stdout);
    scanf("%d", &n);
    while (~scanf("%d", &a[++m])) {}
    m--;
    LRU();
    memset(f, 0, sizeof(f));
    memset(o, 0, sizeof(o));
    OPT();
    memset(f, 0, sizeof(f));
    FIFO();
}
