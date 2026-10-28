#include "../library/math/modint.hpp"

// Pre-optimization operations, kept here to make comparisons reproducible.
template<int MOD> struct BaselineModInt {
    int v;
    BaselineModInt(long long x = 0) : v((int)(x % MOD)){ if (v < 0) v += MOD; }
    int val() const { return v; }
    BaselineModInt& operator+=(const BaselineModInt& o){ if ((v += o.v) >= MOD) v -= MOD; return *this; }
    BaselineModInt& operator*=(const BaselineModInt& o){ v = (int)((long long)v * o.v % MOD); return *this; }
    BaselineModInt inv() const {
        long long a = v, b = MOD, x = 1, y = 0;
        while (b){ long long q = a / b; a -= q * b; swap(a, b); x -= q * y; swap(x, y); }
        assert(a == 1); return BaselineModInt(x);
    }
};

struct Measurement { double ms; unsigned long long checksum; };

template<class T, int Task> Measurement measure(const vector<T>& data){
    T x = 1; unsigned long long sum = 0;
    auto start = chrono::steady_clock::now();
    if constexpr (Task == 2){
        for (int i = 0; i < 400000; ++i) sum += data[i & 4095].inv().val();
    } else {
        for (int i = 0; i < 10000000; ++i){
            x *= data[i & 4095];
            if constexpr (Task == 1) x += data[(i + 1) & 4095];
        }
    }
    auto stop = chrono::steady_clock::now();
    return {chrono::duration<double, milli>(stop - start).count(), sum + x.val()};
}

template<int MOD, int Task> void compare(const char* name){
    vector<BaselineModInt<MOD>> old_data(4096);
    vector<ModInt<MOD>> new_data(4096);
    mt19937 rng(20261028);
    for (int i = 0; i < 4096; ++i){
        int value = 1 + rng() % (MOD - 1);
        old_data[i] = value; new_data[i] = value;
    }
    auto warm_old = measure<BaselineModInt<MOD>, Task>(old_data);
    auto warm_new = measure<ModInt<MOD>, Task>(new_data);
    assert(warm_old.checksum == warm_new.checksum);
    vector<double> old_times, new_times;
    for (int trial = 0; trial < 7; ++trial){
        Measurement old_result, new_result;
        if (trial & 1){
            new_result = measure<ModInt<MOD>, Task>(new_data);
            old_result = measure<BaselineModInt<MOD>, Task>(old_data);
        } else {
            old_result = measure<BaselineModInt<MOD>, Task>(old_data);
            new_result = measure<ModInt<MOD>, Task>(new_data);
        }
        if (old_result.checksum != new_result.checksum) throw runtime_error("checksum mismatch");
        old_times.push_back(old_result.ms); new_times.push_back(new_result.ms);
    }
    sort(old_times.begin(), old_times.end()); sort(new_times.begin(), new_times.end());
    cout << MOD << ',' << name << ',' << old_times[3] << ',' << new_times[3] << ','
         << old_times[3] / new_times[3] << '\n';
}

int main(){
    cout << fixed << setprecision(3) << "mod,operation,old_ms,new_ms,speedup\n";
    compare<998244353, 0>("multiply"); compare<998244353, 1>("multiply_add"); compare<998244353, 2>("inverse");
    compare<1000000007, 0>("multiply"); compare<1000000007, 1>("multiply_add"); compare<1000000007, 2>("inverse");
}
