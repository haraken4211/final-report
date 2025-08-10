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
    double deviation; // 偏差値
    int rank;         // 順位

    Candidates(string n, double s) : name(n), score(s), deviation(0), rank(0) {}

    string getGrade(int totalCandidates) const {
        double percent = 100.0 * (rank - 1) / totalCandidates; // 上位○％

        if (score >= 80 && percent < 10.0) return "S";
        else if (percent < 20.0) return "A";
        else if (percent < 40.0) return "B";
        else if (percent < 60.0) return "C";
        else if (percent < 80.0) return "D";
        else return "E";
    }

    string getResult(const string& grade) const {
        if (grade == "S" || grade == "A" || grade == "B" || grade == "C")
            return "合格";
        else
            return "不合格";
    }
};

class TestResult {
private:
    vector<Candidates> candidates;

public:
    // 受験者を追加
    void addCandidates(const string& name, double score) {
        candidates.emplace_back(name, score);
    }

    // 偏差値と順位を計算
    void getStats() {
        int n = candidates.size();
        if (n == 0) return;

        // 平均点
        double total = 0;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            total += i->score;
        }
        double average = total / n;

        // 標準偏差
        double sum_sq = 0;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            sum_sq += pow(i->score - average, 2);
        }
        double stddev = sqrt(sum_sq / n);

        // 偏差値計算
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            if (stddev == 0)
                i->deviation = 50.0; // 標準偏差が0なら全員同じ点数
            else
                i->deviation = 50 + 10 * ((i->score - average) / stddev);
        }

        // 順位計算
        sort(candidates.begin(), candidates.end(), [](const Candidates& a, const Candidates& b) {
            return a.score > b.score;
            });

        int r = 1;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            i->rank = r++;
        }
    }

    // 名前で検索し、結果を出力
    void showResult(const string& name) const {
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            if (i->name == name) {
                string grade = i->getGrade(candidates.size());
                string result = i->getResult(grade);

                cout << "\n【検索結果】\n";
                cout << "名前: " << i->name << endl;
                cout << "点数: " << i->score << endl;
                cout << "偏差値: " << i->deviation << endl;
                cout << "順位: " << i->rank << "位／" << candidates.size() << "人中" << endl;
                cout << "評価: " << grade << endl;
                cout << "判定: " << result << endl;

                return;
            }
        }
        cout << "該当する受験者が見つかりませんでした。\n";
    }

    void listPassers() const {
        cout << "\n【合格者一覧（評価C以上）】\n";
        bool found = false;
        for (auto i = candidates.begin(); i != candidates.end(); ++i) {
            string grade = i->getGrade(candidates.size());
            if (i->getResult(grade) == "合格") {
                cout << "名前: " << i->name << " / 点数: " << i->score << " / 評価: " << grade << "\n";
                found = true;
            }
        }
        if (!found) {
            cout << "合格者はいませんでした。\n";
        }
    }
    bool isEmpty() const {
        return candidates.empty();
    }
};

int main() {
    TestResult test;
    int n;

    cout << "受験者数を入力: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string name;
        double score;
        cout << i + 1 << "人目の名前と点数を入力（例：Taro 75）: ";
        cin >> name >> score;
        test.addCandidates(name, score);
    }
    test.getStats();

    int choice;

    do {
        cout << "\n====== メニュー ======\n";
        cout << "1. 受験者を追加\n";
        cout << "2. 成績検索\n";
        cout << "3. 合格者一覧\n";
        cout << "0. 終了\n";
        cout << "\n選択してください: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            double score;
            cout << "\n名前を入力: ";
            cin >> name;
            cout << "点数を入力: ";
            cin >> score;
            test.addCandidates(name, score);
            test.getStats();
            cout << "受験者を追加しました。\n";
            break;
        }
        case 2: {
            if (test.isEmpty()) {
                cout << "\n受験者データがありません。\n";
                break;
            }
            string name;
            cout << "\n検索する名前を入力: ";
            cin >> name;
            test.showResult(name);
            break;
        }
        case 3: {
            if (test.isEmpty()) {
                cout << "\n受験者データがありません。\n";
                break;
            }
            test.listPassers();
            break;
        }
        case 0:
            cout << "\n終了します。\n";
            break;
        default:
            cout << "\n無効な選択です。\n";
        }

    } while (choice != 0);

    return 0;
}