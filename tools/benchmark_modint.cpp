#include "../library/math/combination.hpp"
#include "../library/math/convolution.hpp"

// f5c2173 operations, kept here to compare against the immediately previous version.
template<int MOD> struct BaselineModInt {
    int v;
    BaselineModInt(long long x = 0) : v((int)(x % MOD)){ if (v < 0) v += MOD; }
    int val() const { return v; }
    BaselineModInt& operator+=(const BaselineModInt& o){ unsigned int sum = (unsigned int)v + o.v; v = sum >= MOD ? sum - MOD : sum; return *this; }
    BaselineModInt& operator*=(const BaselineModInt& o){ v = (unsigned long long)(unsigned int)v * (unsigned int)o.v % MOD; return *this; }
    BaselineModInt pow(long long n) const {
        BaselineModInt a = *this, r = 1;
        while (n){ if (n & 1) r *= a; a *= a; n >>= 1; } return r;
    }
    BaselineModInt inv() const {
        int a = v, b = MOD; long long x = 1, y = 0;
        while (b){ int q = a / b; a -= q * b; swap(a, b); x -= q * y; swap(x, y); }
        assert(a == 1); BaselineModInt r; r.v = x < 0 ? x + MOD : x; return r;
    }
};

struct Measurement { double ms; unsigned long long checksum; };

template<class T, int Task> Measurement measure(const vector<T>& data){
    T x = 1; unsigned long long sum = 0;
    auto start = chrono::steady_clock::now();
    if constexpr (Task == 2){
        for (int i = 0; i < 400000; ++i) sum += data[i & 4095].inv().val();
    } else if constexpr (Task == 3){
        for (int i = 0; i < 100000; ++i) sum += data[i & 4095].pow(123456789).val();
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
    vector<MontgomeryModInt<MOD>> new_data(4096);
    mt19937 rng(20261028);
    for (int i = 0; i < 4096; ++i){
        int value = 1 + rng() % (MOD - 1);
        old_data[i] = value; new_data[i] = value;
    }
    auto warm_old = measure<BaselineModInt<MOD>, Task>(old_data);
    auto warm_new = measure<MontgomeryModInt<MOD>, Task>(new_data);
    assert(warm_old.checksum == warm_new.checksum);
    vector<double> old_times, new_times;
    for (int trial = 0; trial < 7; ++trial){
        Measurement old_result, new_result;
        if (trial & 1){
            new_result = measure<MontgomeryModInt<MOD>, Task>(new_data);
            old_result = measure<BaselineModInt<MOD>, Task>(old_data);
        } else {
            old_result = measure<BaselineModInt<MOD>, Task>(old_data);
            new_result = measure<MontgomeryModInt<MOD>, Task>(new_data);
        }
        if (old_result.checksum != new_result.checksum) throw runtime_error("checksum mismatch");
        old_times.push_back(old_result.ms); new_times.push_back(new_result.ms);
    }
    sort(old_times.begin(), old_times.end()); sort(new_times.begin(), new_times.end());
    cout << MOD << ',' << name << ',' << old_times[3] << ',' << new_times[3] << ','
         << old_times[3] / new_times[3] << '\n';
}

// The previous transform deliberately recomputes twiddles inside every block.
void baseline_ntt(vector<mint>& a, bool inverse){
    int n = a.size();
    for (int i = 1, j = 0; i < n; ++i){
        int bit = n >> 1; for (; j & bit; bit >>= 1) j ^= bit; j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1){
        mint root = mint(3).pow((mint::mod() - 1) / len); if (inverse) root = root.inv();
        for (int i = 0; i < n; i += len){ mint w = 1; for (int j = 0; j < len / 2; ++j){ auto u = a[i+j], v = a[i+j+len/2] * w; a[i+j] = u + v; a[i+j+len/2] = u - v; w *= root; } }
    }
    if (inverse){ mint inv_n = mint(n).inv(); for (auto& x : a) x *= inv_n; }
}
vector<mint> baseline_convolution(vector<mint> a, vector<mint> b){
    int need = a.size() + b.size() - 1, n = 1; while (n < need) n <<= 1;
    a.resize(n); b.resize(n); baseline_ntt(a, false); baseline_ntt(b, false);
    for (int i = 0; i < n; ++i) a[i] *= b[i];
    baseline_ntt(a, true); a.resize(need); return a;
}

template<class Old, class New> void compare_workload(const char* name, Old old_fn, New new_fn){
    vector<double> old_times, new_times;
    for (int trial = 0; trial < 8; ++trial){
        Measurement old_result, new_result;
        auto timed = [](auto fn){
            auto start = chrono::steady_clock::now(); auto result = fn();
            auto stop = chrono::steady_clock::now();
            return Measurement{chrono::duration<double, milli>(stop - start).count(), (unsigned long long)result};
        };
        if (trial & 1){ new_result = timed(new_fn); old_result = timed(old_fn); }
        else { old_result = timed(old_fn); new_result = timed(new_fn); }
        if (old_result.checksum != new_result.checksum) throw runtime_error("workload checksum mismatch");
        if (trial){ old_times.push_back(old_result.ms); new_times.push_back(new_result.ms); }
    }
    sort(old_times.begin(), old_times.end()); sort(new_times.begin(), new_times.end());
    cout << "998244353," << name << ',' << old_times[3] << ',' << new_times[3] << ','
         << old_times[3] / new_times[3] << '\n';
}

int main(){
    cout << fixed << setprecision(3) << "mod,operation,previous_ms,optimized_ms,speedup\n";
    compare<998244353, 0>("multiply"); compare<998244353, 1>("multiply_add"); compare<998244353, 2>("inverse");
    compare<998244353, 3>("power");
    compare<1000000007, 0>("multiply"); compare<1000000007, 1>("multiply_add"); compare<1000000007, 2>("inverse");
    compare<1000000007, 3>("power");
    vector<mint> a(1 << 15), b(1 << 15); mt19937 rng(20261028);
    for (auto& x : a) x = rng();
    for (auto& x : b) x = rng();
    auto reference = baseline_convolution(a, b);
    if (convolution(a, b) != reference) throw runtime_error("convolution mismatch");
    auto checksum = [](const vector<mint>& v){
        unsigned long long h = 0; for (auto x : v) h = h * 1000003 + x.val(); return h;
    };
    compare_workload("convolution_32768", [&]{ return checksum(baseline_convolution(a, b)); }, [&]{ return checksum(convolution(a, b)); });
    combination<mint> co(1000000000LL);
    compare_workload("large_combination_r50000", []{
        mint r = 1;
        for (int i = 1; i <= 50000; ++i){ r *= mint(1000000000LL - 50000 + i); r /= mint(i); }
        return r.val();
    }, [&]{ return co.C(1000000000LL, 50000).val(); });
}
