#include <iomanip>
#include <iostream>
#include <vector>

// http://e-maxx.ru/algo/big_integer

using namespace std;

class lnum
{
private:
    const int BASE = 1000 * 1000 * 1000;
    vector<int> _data;
    size_t size() const { return _data.size(); }
    const int& operator[](size_t i) const { return _data[i]; }
    int& operator[](size_t i) { return _data[i]; }
    void push(int i) { _data.push_back(i); }
    void pop() { _data.pop_back(); }
    void trim()
    {
        while (_data.size() > 1 && _data.back() == 0) _data.pop_back();
    }
public:
    lnum() = default;
    explicit lnum(const string& s)
    {
        for (int i = s.length(); i > 0; i -= 9)
            if (i < 9)
                push(atoi(s.substr(0, i).c_str()));
            else
                push(atoi(s.substr(i - 9, 9).c_str()));
        trim();
    }
    lnum& operator+=(const lnum& rhs)
    {
        int carry = 0;
        for (size_t i = 0; i < max(size(), rhs.size()) || carry; ++i) {
            if (i == size()) push(0);
            _data[i] += carry + (i < rhs.size() ? rhs[i] : 0);
            if ((carry = _data[i] >= BASE)) _data[i] -= BASE;
        }
        return *this;
    }
    lnum operator+(const lnum& rhs) const
    {
        lnum ret = *this;
        ret += rhs;
        return ret;
    }
    lnum& operator-=(const lnum& rhs)
    {
        int carry = 0;
        for (size_t i = 0; i < rhs.size() || carry; ++i) {
            _data[i] -= carry + (i < rhs.size() ? rhs[i] : 0);
            if ((carry = _data[i] < 0)) _data[i] += BASE;
        }
        trim();
        return *this;
    }
    lnum operator-(const lnum& rhs)
    {
        lnum ret = *this;
        ret -= rhs;
        return ret;
    }
    lnum& operator*=(unsigned n)
    {
        int carry = 0;
        for (size_t i = 0; i < size() || carry; ++i) {
            if (i == size()) push(0);
            long long cur = carry + _data[i] * 1ll * n;
            _data[i] = int(cur % BASE);
            carry = int(cur / BASE);
        }
        trim();
        return *this;
    }
    lnum operator*(unsigned n)
    {
        lnum ret = *this;
        ret *= n;
        return ret;
    }
    lnum& operator*=(const lnum& n)
    {
        vector<int> data = _data;
        _data = vector<int>(data.size() + n.size());
        for (size_t i = 0; i < data.size(); ++i) {
            int carry = 0;
            for (size_t j = 0; j < n.size() || carry; ++j) {
                long long cur = data[i] * 1ll * (j < n.size() ? n[j] : 0) + carry;
                _data[i + j] = int(cur % BASE);
                carry = int(cur / BASE);
            }
        }
        trim();
        return *this;
    }
    lnum operator*(const lnum& n)
    {
        lnum ret = *this;
        ret *= n;
        return ret;
    }
    lnum& operator/=(unsigned n)
    {
        int carry = 0;
        for (int i = (int)size() - 1; i >= 0; --i) {
            long long cur = _data[i] + carry * 1ll * BASE;
            _data[i] = int(cur / n);
            carry = int(cur % n);
        }
        trim();
        return *this;
    }
    lnum operator/(unsigned n)
    {
        lnum ret = *this;
        ret /= n;
        return ret;
    }
    unsigned operator%(unsigned n)
    {
        int carry = 0;
        for (int i = (int)size() - 1; i >= 0; --i) {
            long long cur = _data[i] + carry * 1ll * BASE;
            carry = int(cur % n);
        }
        return carry;
    }
    friend ostream& operator<<(ostream&, const lnum&);
};

ostream& operator<<(ostream& os, const lnum& n)
{
    os << (n._data.empty() ? 0 : n._data.back());
    for (int i = (int)n._data.size() - 2; i >= 0; --i)
        os << setw(9) << setfill('0') << n._data[i];
    return os;
}

int main(int argc, char *argv[])
{
    lnum ln("1000000000000000000000000000000000000000000000000000000000");
    cout << ln << endl;
    cout << ln * 12345 << endl;
    cout << ln * ln << endl;
    cout << ln / 2 << endl;
    cout << ln + (ln + lnum("1")) << endl;
    return 0;
}
