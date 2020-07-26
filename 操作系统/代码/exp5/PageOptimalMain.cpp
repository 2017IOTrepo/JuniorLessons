//
// Created by xmmmmmovo on 2019/12/10.
//
#include<iostream>
#include<list>
#include<vector>
#include<iterator>
#include<fstream>
#include<algorithm>

using namespace std;

int succ = 0;
int fail = 0;

class Optimal {
public:
    int index;
    int dis;
public:
    friend istream &operator>>(istream &i, Optimal &o);

    friend ostream &operator<<(ostream &s, const Optimal &o);

    Optimal(int i) {
        this->index = i;
        dis = 0;
    }

    Optimal() {
        dis = 0;
    }

    ~Optimal() {

    }

    bool operator<(Optimal &s) {
        if (this->dis < s.dis)
            return true;
        return false;
    }

    bool operator>(Optimal &s) {
        if (this->dis > s.dis)
            return true;
        return false;
    }

    bool operator==(const Optimal &s) {
        if (this->dis == s.dis)
            return true;
        return false;
    }
};

istream &operator>>(istream &i, Optimal &o) {
    i >> o.index;
    return i;
}

ostream &operator<<(ostream &s, const Optimal &o) {

    s << "[" << o.index << "\t" << "下次位置：" << o.dis << "]";

    return s;
}

int main() {
    fstream out("data.txt");
    list<Optimal> v;
    list<Optimal> w;
    copy(istream_iterator<Optimal>(out), istream_iterator<Optimal>(), back_inserter(v));

    while (v.size()) {
        if (w.size() < 3) {
            succ++;
            copy(w.begin(), w.end(), ostream_iterator<Optimal>(cout, " "));
            cout << endl;
            Optimal p = v.front();
            v.pop_front();
            w.push_front(p);
        } else {
            bool istrue = false;
            for (auto ib = w.begin(); ib != w.end(); ib++) {
                if (ib->index == v.front().index) {
                    istrue = true;
                }
            }
            if (istrue == false) {
                fail++;
                for (auto ib = w.begin(); ib != w.end(); ib++) {
                    int x = 0;
                    for (auto vib = v.begin(); vib != v.end(); vib++) {
                        if ((*ib).index == (*vib).index) {
                            break;
                        }
                        (*ib).dis = x++;
                    }
                }
                copy(w.begin(), w.end(), ostream_iterator<Optimal>(cout, " "));
                cout << endl;
                auto s = max_element(w.begin(), w.end());
                w.remove(*s);
                Optimal p = v.front();
                v.pop_front();
                w.push_front(p);
            } else {
                succ++;
                v.pop_front();
            }
        }
    }
    copy(w.begin(), w.end(), ostream_iterator<Optimal>(cout, " "));
    cout << endl;

    cout << "成功请求次数:" << succ << endl;
    cout << "失败请求次数:" << fail << endl;
    cout << "缺页率:" << (double)fail / (succ + fail) << endl;

    return 0;
}