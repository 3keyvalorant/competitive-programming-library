#pragma once
#include "../basic/base.hpp"

inline long long modpow(long long a, long long n, long long modulus){ long long r = 1 % modulus; for (a %= modulus; n; n >>= 1, a = (long long)((__int128)a * a % modulus)) if (n & 1) r = (long long)((__int128)r * a % modulus); return r; }
inline long long safe_mod_multiply(long long a, long long b, long long modulus){ return (long long)((__int128)a * b % modulus); }
inline long long extgcd(long long a, long long b, long long& x, long long& y){ if (!b){ x = a >= 0 ? 1 : -1; y = 0; return abs(a); } long long g = extgcd(b, a % b, y, x); y -= a / b * x; return g; }
inline optional<long long> modular_inverse(long long a, long long modulus){ long long x, y, g = extgcd(a, modulus, x, y); if (g != 1) return nullopt; return (x % modulus + modulus) % modulus; }
inline pair<long long, long long> crt(const vector<long long>& r, const vector<long long>& m){
    assert(r.size() == m.size()); long long r0 = 0, m0 = 1;
    for (int i = 0; i < (int)r.size(); ++i){
        assert(m[i] > 0); long long r1 = (r[i] % m[i] + m[i]) % m[i], m1 = m[i];
        long long x, y, g = extgcd(m0, m1, x, y); if ((r1 - r0) % g) return {0, 0};
        long long u = m1 / g, t = safe_mod_multiply((r1 - r0) / g, x, u);
        r0 += m0 * t; m0 *= u; r0 = (r0 % m0 + m0) % m0;
    }
    return {r0, m0};
}
inline vector<int> eratosthenes(int n){ vector<int> prime(n + 1, true); if (n >= 0) prime[0] = false; if (n >= 1) prime[1] = false; for (long long i = 2; i * i <= n; ++i) if (prime[i]) for (long long j = i * i; j <= n; j += i) prime[j] = false; return prime; }
inline vector<int> primes_up_to(int n){ auto p = eratosthenes(n); vector<int> res; for (int i = 2; i <= n; ++i) if (p[i]) res.push_back(i); return res; }
inline bool is_prime(long long n){ if (n < 2) return false; for (long long p = 2; p * p <= n; ++p) if (n % p == 0) return false; return true; }
inline map<long long, int> prime_factorize(long long n){ map<long long, int> f; for (long long p = 2; p * p <= n; ++p) while (n % p == 0) ++f[p], n /= p; if (n > 1) ++f[n]; return f; }
inline vector<long long> divisors(long long n){ vector<long long> d; for (long long i = 1; i * i <= n; ++i) if (n % i == 0){ d.push_back(i); if (i * i != n) d.push_back(n / i); } sort(all(d)); return d; }
inline long long integer_sqrt(long long n){ assert(n >= 0); long long x = sqrt((long double)n); while ((__int128)(x + 1) * (x + 1) <= n) ++x; while ((__int128)x * x > n) --x; return x; }
