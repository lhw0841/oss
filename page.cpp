#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;

int main() {
    ifstream in("page.inp");
    ofstream out("page.out");

    int frameSize;
    in >> frameSize;

    vector<int> referenceString;
    int reference;
    while (in >> reference) {
        if (reference == -1) break;
        referenceString.push_back(reference);
    }

    // FIFO
    queue<int> fifoQueue;
    vector<bool> fifoPresent(10001, false);
    int fifoPageFaults = 0;
    for (int i = 0; i < referenceString.size(); i++) {
        if (!fifoPresent[referenceString[i]]) {
            fifoPageFaults++;
            if (fifoQueue.size() == frameSize) {
                int removed = fifoQueue.front();
                fifoQueue.pop();
                fifoPresent[removed] = false;
            }
            fifoQueue.push(referenceString[i]);
            fifoPresent[referenceString[i]] = true;
        }
    }
    out << "FIFO: " << fifoPageFaults << endl;

    // LRU
    list<int> lruList;
    vector<bool> lruPresent(10001, false);
    int lruPageFaults = 0;
    for (int i = 0; i < referenceString.size(); i++) {
        if (!lruPresent[referenceString[i]]) {
            lruPageFaults++;
            if (lruList.size() == frameSize) {
                int removed = lruList.back();
                lruList.pop_back();
                lruPresent[removed] = false;
            }
            lruList.push_front(referenceString[i]);
            lruPresent[referenceString[i]] = true;
        }
        else {
            lruList.remove(referenceString[i]);
            lruList.push_front(referenceString[i]);
        }
    }
    out << "LRU: " << lruPageFaults << endl;


    // OPT
    vector<int> optFrame(frameSize, -1);
    int optPageFaults = 0;
    for (int i = 0; i < referenceString.size(); i++) {
        bool found = false;
        for (int j = 0; j < frameSize; j++) {
            if (optFrame[j] == referenceString[i]) {
                found = true;
                break;
            }
        }
        if (!found) {
            optPageFaults++;
            vector<int> nextUse(frameSize, 10001);
            for (int j = 0; j < frameSize; j++) {
                for (int k = i + 1; k < referenceString.size(); k++) {
                    if (referenceString[k] == optFrame[j]) {
                        nextUse[j] = k;
                        break;
                    }
                }
            }
            int maxIndex = max_element(nextUse.begin(), nextUse.end()) - nextUse.begin();
            optFrame[maxIndex] = referenceString[i];
        }
    }
    out << "OPT: " << optPageFaults << endl;

    in.close();
    out.close();

    return 0;
}
