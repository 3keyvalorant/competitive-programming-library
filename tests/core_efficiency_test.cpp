#include "../library/math/batch_inverse.hpp"
#include "../library/math/combination.hpp"
#include "../library/math/montgomery_modint.hpp"

struct CountedMint {
    mint value;
    static inline int multiplications = 0, inversions = 0;
    CountedMint(long long x = 0) : value(x) {}
    CountedMint(mint x) : value(x) {}
    static constexpr int mod(){ return mint::mod(); }
    int val() const { return value.val(); }
    CountedMint& operator*=(const CountedMint& other){ ++multiplications; value *= other.value; return *this; }
    CountedMint inv() const { ++inversions; return CountedMint(value.inv()); }
    friend CountedMint operator*(CountedMint a, const CountedMint& b){ return a *= b; }
    friend CountedMint operator/(CountedMint a, const CountedMint& b){ return a *= b.inv(); }
    static void reset_counts(){ multiplications = inversions = 0; }
};

template<class T> void check_batches(){
    mt19937 rng(20261028);
    for (int trial = 0; trial < 100; ++trial){
        vector<T> a(rng() % 100);
        for (auto& x : a) x = 1 + rng() % (T::mod() - 1);
        auto before = a, inverse = batch_inverse(a);
        assert(a == before && inverse.size() == a.size());
        for (size_t i = 0; i < a.size(); ++i) assert(a[i] * inverse[i] == T(1));
    }
}

template<int MOD> void check_combinations(){
    using T = ModInt<MOD>;
    combination<T> table(min(100, MOD - 1)), no_table(1000000000LL);
    vector<T> row(202); row[0] = 1;
    for (int n = 0; n <= 200; ++n){
        for (int r = 0; r <= n; ++r){
            assert(table.C(n, r) == row[r]);
            assert(no_table.C(n, r) == row[r]);
            if (n < MOD) assert(no_table.small_C(n, r) == row[r]);
        }
        assert(table.C(n, -1) == T(0) && no_table.C(n, n + 1) == T(0));
        for (int r = n + 1; r > 0; --r) row[r] += row[r - 1];
        for (int r = 0; r <= n; ++r){
            T want = 1; for (int i = 0; i < r; ++i) want *= T(n - i);
            assert(no_table.P(n, r) == want);
        }
    }
    assert(no_table.C(LLONG_MAX, 0) == T(1));
    assert(no_table.C(LLONG_MAX, LLONG_MAX) == T(1));
    assert(no_table.C(LLONG_MAX, 1) == T(LLONG_MAX));
    assert(no_table.C(LLONG_MAX, LLONG_MAX - 1) == T(LLONG_MAX));
    assert(no_table.P(LLONG_MAX, 0) == T(1));
    assert(no_table.P(LLONG_MAX, 1) == T(LLONG_MAX));
    assert(no_table.C(-1, 0) == T(0) && no_table.P(-1, 0) == T(0));
}

int main(){
    combination<CountedMint> table(1000), large(1000000000LL);
    for (auto [n, r] : vector<pair<long long,long long>>{{100,0},{100,1},{100,99},{100,100},{1000000000LL,0},{LLONG_MAX,LLONG_MAX-1}}){
        CountedMint::reset_counts(); auto value = large.C(n, r);
        assert(CountedMint::inversions == 0 && CountedMint::multiplications == 0);
        assert(value.val() == ((r == 0 || r == n) ? mint(1).val() : mint(n).val()));
    }
    CountedMint::reset_counts(); auto c = table.C(100, 17);
    assert(c.val() == combination<mint>(100).C(100, 17).val());
    assert(CountedMint::inversions == 0 && CountedMint::multiplications == 2);
    CountedMint::reset_counts(); c = large.C(30, 10);
    assert(c.val() == combination<mint>(30).C(30, 10).val());
    assert(CountedMint::inversions == 1 && CountedMint::multiplications == 21);
    CountedMint::reset_counts(); auto empty = batch_inverse(vector<CountedMint>{});
    assert(empty.empty() && CountedMint::inversions == 0 && CountedMint::multiplications == 0);
    for (int n : {1, 2, 64}){
        vector<CountedMint> a(n); for (int i = 0; i < n; ++i) a[i] = i + 1;
        CountedMint::reset_counts(); auto inverse = batch_inverse(a);
        assert(CountedMint::inversions == 1 && CountedMint::multiplications == 3 * (n - 1));
        for (int i = 0; i < n; ++i) assert(a[i].value * inverse[i].value == mint(1));
    }
    check_batches<mint>(); check_batches<amint>(); check_batches<fastmint>();
    using composite = ModInt<15>;
    vector<composite> units{1,2,4,7,8,11,13,14}; auto inverse = batch_inverse(units);
    for (size_t i = 0; i < units.size(); ++i) assert(units[i] * inverse[i] == composite(1));
    check_combinations<2>(); check_combinations<7>(); check_combinations<998244353>();
    cout << "core efficiency tests passed\n";
}
