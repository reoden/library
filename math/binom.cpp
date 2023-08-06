namespace CNM {
    const static int N = 200005;
    Mint fact[N], invfact[N];

    void init() {
        fact[0] = 1;
        for (int i = 1; i <= N - 1; i ++ ) fact[i] = fact[i - 1] * i;
        invfact[N - 1] = 1 / fact[N - 1];
        for (int i = N - 1; i; i -- ) invfact[i - 1] = invfact[i] * i;
    }

    Mint binom(int n, int m) {
        if (n < m || m < 0) return 0;
        return fact[n] * invfact[m] * invfact[n - m];
    }
}
