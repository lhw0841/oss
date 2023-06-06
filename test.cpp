#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <map>

using namespace std;


int main() {
    ifstream fin("test.inp");
    ofstream fout("test.out");

    int n;
    fin >> n;

    vector<tuple<string, string, string>> people(n);

    for (int i = 0; i < n; i++) {
        string id, first_name, last_name;
        fin >> id >> first_name >> last_name;
        people[i] = make_tuple(id, first_name, last_name);
    }

    sort(people.begin(), people.end());

    map<string, int> last_name_counts;
    string longest_first_name;
    int longest_first_name_len = 0; // 가장 긴 first name 길이 저장 변수
    int space = 0; // 공백 몇칸 넣을지 

    for (auto& person : people) {
        string id, first_name, last_name;
        tie(id, first_name, last_name) = person;

        if (first_name.length() > longest_first_name_len) {
            longest_first_name_len = first_name.length(); // 가장 긴 first name 을 찾아서 길이를 저장하는 코드
        }
    }

    for (auto& person : people) {
        string id, first_name, last_name;
        tie(id, first_name, last_name) = person;

        if (first_name.length() < longest_first_name_len) {
            space = longest_first_name_len - first_name.length() + 1;
        }

        fout << id << " " << first_name;
        if (first_name.length() < longest_first_name_len) {

            for (int i = 0; i < space; i++) {
                fout << " ";
            }
            fout << last_name << "\n";

            last_name_counts[last_name]++;
        }
        else {
            fout << " " << last_name << "\n";
            last_name_counts[last_name]++;
        }
    }
    fout << "\n";


    for (auto& entry : last_name_counts) {
        string last_name = entry.first;
        int count = entry.second;

        if (count == 1) continue;

        fout << last_name << " " << count << "\n";
        vector<string> last_name_people;

        for (auto& person : people) {

            string id, first_name, last_name2;
            tie(id, first_name, last_name2) = person;

            if (last_name2 == last_name) {
                string full_name = first_name + " " + last_name2;
                last_name_people.push_back(full_name);
            }
        }

        sort(last_name_people.begin(), last_name_people.end());


    }

    fin.close();
    fout.close();

    return 0;
}
