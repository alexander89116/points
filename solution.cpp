#include <bits/stdc++.h>
#include <type_traits>

#define _USE_MATH_DEFINES

using namespace std;

typedef long long ll;
typedef long double ld;

long double EPS = 1e-8;

template<typename T>
bool IsEqual(T a, T b) {

    if constexpr (is_same<T, long double>::value)
        return abs(a - b) < EPS;
    else
        return (a == b);
}

template<typename Type>
class Point {
public:
    Type X, Y;

    Point() = default;

    Point(Type x, Type y) : X(x), Y(y) {};

    bool operator==(const Point &point) {
        return X == point.X && Y == point.Y;
    }

    bool operator!=(const Point &point) {
        return !(*this == point);
    }

    bool operator<(const Point &point) {
        return X < point.X || (X == point.X && Y < point.Y);
    }

    friend ostream &operator<<(ostream &out, const Point &point) {
        out << fixed << setprecision(10) << point.X << " " << point.Y << endl;
        return out;
    }

    friend istream &operator>>(istream &in, Point &point) {
        in >> point.X >> point.Y;
        return in;
    }

    template<typename T>
    Point<T> operator-(Point<T> point) {
        return Point<T>(X - point.X, Y - point.Y);
    }

    template<typename T>
    Point<T> operator+(Point<T> point) {
        return Point<T>(X + point.X, Y + point.Y);
    }

    template<typename T>
    Point<T> operator*(T k) {
        return Point<T>(X * k, Y * k);
    }

    long double Len() {
        return sqrtl(X * X + Y * Y);
    }

    Type Len2() {
        return X * X + Y * Y;
    }
};

template<typename T>
long long Distance(Point<T> &p1, Point<T> &p2) {
    return (p1 - p2).Len2();
}

template <typename T>
long long FindMinDistance(int left, int right, vector<Point<T>> &in, vector<Point<T>> &sorted) {
    if (right - left == 1)
        return 1e15;
    if (right - left == 2)
        return (in[left] - in[right - 1]).Len2();
    if (right - left == 3)
        return min(min(Distance(in[left], in[left + 1]), Distance(in[left], in[left + 2])),
                   Distance(in[left + 1], in[left + 2]));

    int mid = (right + left) / 2;

    long long minDistance = min(FindMinDistance(left, mid, in, sorted), FindMinDistance(mid, right, in, sorted));

    for (int i = left; i < right; i++) {
        if (abs(in[i].X - in[mid].X) < minDistance)
            sorted.push_back(in[i]);
    }

    sort(sorted.begin(), sorted.end(), [](const Point<long long> &p1, const Point<long long> &p2) {
        return p1.Y < p2.Y;
    });

    for (int i = 1; i < sorted.size(); i++) {
        for (int j = i - 1; j >= 0 && sorted[i].Y - sqrtl(minDistance) < sorted[j].Y; j--) {
            minDistance = min(minDistance, Distance(sorted[i], sorted[j]));
        }
    }
    sorted.clear();
    return minDistance;
}

int main() {
    int n;
    cin >> n;
    vector<Point<long long>> in(n);
    vector<Point<long long>> sorted;
    for (int i = 0; i < n; i++) {
        cin >> in[i];
    }
    sort(in.begin(), in.end());
    for (int i = 0; i < n; i++) {
        if (in[i] == in[i + 1]) {
            cout << 0;
            return 0;
        }
    }
    cout << fixed << setprecision(10) << FindMinDistance(0, n, in, sorted);
    return 0;
}