#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

class Candidates {
public:
    string name;
    double score;
    double deviation; // �΍��l
    int rank;         // ����

    Candidates(string n, double s) : name(n), score(s), deviation(0), rank(0) {}

    string getGrade(int totalCandidates) const {
        double percent = 100.0 * (rank - 1) / totalCandidates; // ��ʁ���

        if (score >= 80 && percent < 10.0) return "S";
        else if (percent < 20.0) return "A";
        else if (percent < 40.0) return "B";
        else if (percent < 60.0) return "C";
        else if (percent < 80.0) return "D";
        else return "E";
    }

    string getResult(const string& grade) const {
        if (grade == "S" || grade == "A" || grade == "B" || grade == "C")
            return "���i";
        else
            return "�s���i";
    }
};

class TestResult {
private:
    vector<Candidates> candidates;

public:
    // �󌱎҂�ǉ�
    void addCandidates(const string& name, double score) {
        candidates.emplace_back(name, score);
    }

    // �΍��l�Ə��ʂ��v�Z
    void getStats() {
        int n = candidates.size();
        if (n == 0) return;

        // ���ϓ_
        double total = 0;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            total += i->score;
        }
        double average = total / n;

        // �W���΍�
        double sum_sq = 0;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            sum_sq += pow(i->score - average, 2);
        }
        double stddev = sqrt(sum_sq / n);

        // �΍��l�v�Z
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            if (stddev == 0)
                i->deviation = 50.0; // �W���΍���0�Ȃ�S�������_��
            else
                i->deviation = 50 + 10 * ((i->score - average) / stddev);
        }

        // ���ʌv�Z
        sort(candidates.begin(), candidates.end(), [](const Candidates& a, const Candidates& b) {
            return a.score > b.score;
            });

        int r = 1;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            i->rank = r++;
        }
    }

    // ���O�Ō������A���ʂ��o��
    void showResult(const string& name) const {
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            if (i->name == name) {
                string grade = i->getGrade(candidates.size());
                string result = i->getResult(grade);

                cout << "\n�y�������ʁz\n";
                cout << "���O: " << i->name << endl;
                cout << "�_��: " << i->score << endl;
                cout << "�΍��l: " << i->deviation << endl;
                cout << "����: " << i->rank << "�ʁ^" << candidates.size() << "�l��" << endl;
                cout << "�]��: " << grade << endl;
                cout << "����: " << result << endl;

                return;
            }
        }
        cout << "�Y������󌱎҂�������܂���ł����B\n";
    }

    void listPassers() const {
        cout << "\n�y���i�҈ꗗ�i�]��C�ȏ�j�z\n";
        bool found = false;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            string grade = i->getGrade(candidates.size());
            if (i->getResult(grade) == "���i") {
                cout << "���O: " << i->name << " / �_��: " << i->score << " / �]��: " << grade << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "���i�҂͂��܂���ł����B\n";
        }
    }
    bool isEmpty() const {
        return candidates.empty();
    }
};

int main() {
    TestResult test;
    int n;

    cout << "�󌱎Ґ������: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string name;
        double score;
        cout << i + 1 << "�l�ڂ̖��O�Ɠ_������́i��FTaro 75�j: ";
        cin >> name >> score;
        test.addCandidates(name, score);
    }
    test.getStats();

    int choice;

    do {
        cout << "\n====== ���j���[ ======\n";
        cout << "1. �󌱎҂�ǉ�\n";
        cout << "2. ���ь���\n";
        cout << "3. ���i�҈ꗗ\n";
        cout << "0. �I��\n";
        cout << "\n�I�����Ă�������: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            double score;
            cout << "\n���O�����: ";
            cin >> name;
            cout << "�_�������: ";
            cin >> score;
            test.addCandidates(name, score);
            test.getStats();
            cout << "�󌱎҂�ǉ����܂����B\n";
            break;
        }
        case 2: {
            if (test.isEmpty()) {
                cout << "\n�󌱎҃f�[�^������܂���B\n";
                break;
            }
            string name;
            cout << "\n�������閼�O�����: ";
            cin >> name;
            test.showResult(name);
            break;
        }
        case 3: {
            if (test.isEmpty()) {
                cout << "\n�󌱎҃f�[�^������܂���B\n";
                break;
            }
            test.listPassers();
            break;
        }
        case 0:
            cout << "\n�I�����܂��B\n";
            break;
        default:
            cout << "\n�����ȑI���ł��B\n";
        }

    } while (choice != 0);

    return 0;
}