#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using Vec = std::vector<int>;

Vec MakeRandomVec(size_t sz) {
    Vec retval;
    for (size_t i = 0; i < sz; ++i) {
        retval.emplace_back(std::rand() % (sz*2));
    }
    std::sort(retval.begin(), retval.end());
    return retval;
}

void PrintVec(const Vec & v) {
    std::cout << "Size: " << v.size() << ", [";
    for (auto a : v)
        std::cout << a << " ";
    std::cout << "]" << std::endl;
}

Vec MergeSortedVecs(const Vec & v1, const Vec & v2) {
    int sizeDiff = v1.size() - v2.size();
    size_t minSz = sizeDiff > 0 ? v2.size() : v1.size();

    Vec retv;
    size_t i = 0;
    for (; i < minSz; ++i) {
        int a, b;
        if (v1[i] < v2[i]) {
            a = v1[i];
            b = v2[i];
        } else {
            a = v2[i];
            b = v1[i];
        }
        retv.emplace_back(a);
        retv.emplace_back(b);
    }

    int lim = std::abs(sizeDiff);
    const Vec & rest = sizeDiff > 0 ? v1 : v2;
    for (int j = i; j < lim; ++j) {
        retv.emplace_back(rest[j]);
    }
    return retv;
}

bool TestMergeSortVecs(int numTests, int sizeLim) {
    for (int i = 0; i < numTests; ++i) {
        size_t sz1 = rand() % sizeLim;
        size_t sz2 = rand() % sizeLim;
        std::cout << "Making two random vecs: " << std::endl;
        auto v1 = MakeRandomVec(sz1);
        PrintVec(v1);
        auto v2 = MakeRandomVec(sz2);
        PrintVec(v2);
        auto v3 = MergeSortedVecs(v1, v2);
        std::cout << "Merged result: " << std::endl;
        PrintVec(v3);
        bool ok = (v3.size() == sz1 + sz2) && std::is_sorted(v3.begin(), v3.end());
        std::cout << "Result: " << (ok ? "SUCCESS" : "FAILED") << std::endl;
        if (!ok)
            return ok;
    }
    return true;
}

int main()
{
    srand(time(NULL));
    TestMergeSortVecs(3, 5);
    return 0;
}
