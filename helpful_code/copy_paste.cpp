#include <cstdio>
#include <memory>
#include <string>

using namespace std;

typedef unsigned int UI;

int BinarySearch(int begin, int end) {
    while (begin < end) {
        int middle = (begin + end) / 2;
        if (middle == middle /* TODO(implement the predicate for middle) */) {
            end = middle;
        } else {
            begin = middle + 1;
        }
    }
    return begin;
}

// TODO(add your own custom functionality)
class Trie {
public:
    static constexpr int ALPHABET_SIZE = 26;

    void Insert(const string& s) {
        Trie* current = this;
        for (UI i = 0; i < s.size(); i++) {
            int index = Index(s[i]);
            if (current->children[index] == nullptr) {
                current->children[index] = make_unique<Trie>();
                current->children[index]->parent = current;
            }
            current = current->children[index].get();
            current->depth = i + 1;
        }
    }

    bool Exists(const string& s) {
        Trie* current = this;
        for (UI i = 0; i < s.size(); i++) {
            int index = Index(s[i]);
            if (current->children[index] == nullptr) {
                return false;
            }
            current = current->children[index].get();
        }
        return true;
    }

    int Index(const char c) {
        int index = c - 'A';
        if (index < 0 || index >= ALPHABET_SIZE) {
            printf("Wrong letter %c\n", c);
            exit(EXIT_FAILURE);
        }
        return index;
    }

    int depth = 0;
    Trie* parent = nullptr;
    array<unique_ptr<Trie>, ALPHABET_SIZE> children = {nullptr};
};

// TODO(add your own custom functionality)
template<typename T>
class SegmentTree {
public:
    // time: O(N)
    // space: O(N)
    SegmentTree(const vector<T>& elements): elements_(elements), min_(elements) {
        CheckNotEmpty(elements);
        Construct(0, elements_.size()-1);
    }

    // time: O(log(N))
    // space: O(log(N))
    T Min(const UI from, const UI to) const {
        CheckNotGreater(from, to);
        return Min(from, to, 0, elements_.size()-1);
    }

    // time: O(log(N))
    // space: O(log(N))
    void Update(const UI index, const T value) {
        elements_[index] = value;
        Update(index, 0, elements_.size()-1);
    }

    // time: O(1)
    // space: O(1)
    T Get(const UI index) const {
        return elements_[index];
    }

    // for debug only
    void Print() const {
        cout << "elements_: ", ::Print(elements_);
        cout << "min_: ", ::Print(min_);
    }

private:
    int Construct(const UI begin, const UI end) {
        CheckNotGreater(begin, end);
        if (begin == end) {
            return elements_[begin];
        }
        const UI middle = (begin + end) / 2;
        min_[middle] = min(Construct(begin, middle), Construct(middle+1, end));
        return min_[middle];
    }

    int Update(const UI index, const UI begin, const UI end) {
        CheckNotGreater(begin, end);
        if (begin == end) {
            return elements_[begin];
        }

        const UI middle = (begin + end) / 2;
        if (index <= middle) {
            min_[middle] = min(Update(index, begin, middle), Min(middle+1, end, middle+1, end));
        } else {
            min_[middle] = min(Min(begin, middle, begin, middle), Update(index, middle+1, end));
        }
        return min_[middle];
    }

    T Min(const UI from, const UI to, const UI begin, const UI end) const {
        if (from > end or to < begin) {
            return numeric_limits<T>::max();
        }
        if (begin == end) {
            return elements_[begin];
        }
        const UI middle = (begin + end) / 2;
        if (from <= begin and end <= to) {
            return min_[middle];
        }
        return min(Min(from, to, begin, middle), Min(from, to, middle+1, end));
    }

    vector<T> elements_;
    vector<T> min_;
};





