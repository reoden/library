#include <bits/stdc++.h>
using namespace std;

inline namespace IO {
#define SFINAE(x, ...)                                                                   \
  template <class, class = void> struct x : std::false_type {};                          \
  template <class T> struct x<T, std::void_t<__VA_ARGS__>> : std::true_type {}

SFINAE(DefaultI, decltype(std::cin >> std::declval<T &>()));
SFINAE(DefaultO, decltype(std::cout << std::declval<T &>()));
SFINAE(IsTuple, typename std::tuple_size<T>::type);
SFINAE(Iterable, decltype(std::begin(std::declval<T>())));

template <auto &is> struct Reader {
  template <class T> void Impl(T &t) {
    if constexpr (DefaultI<T>::value)
      is >> t;
    else if constexpr (Iterable<T>::value) {
      for (auto &x : t) Impl(x);
    } else if constexpr (IsTuple<T>::value) {
      std::apply([this](auto &...args) { (Impl(args), ...); }, t);
    } else
      static_assert(IsTuple<T>::value, "No matching type for read");
  }
  template <class... Ts> void read(Ts &...ts) { ((Impl(ts)), ...); }
};

template <class... Ts> void re(Ts &...ts) { Reader<cin>{}.read(ts...); }
#define def(t, args...)                                                                  \
  t args;                                                                                \
  re(args);

template <auto &os, bool debug, bool print_nd> struct Writer {
  string comma() const { return debug ? "," : ""; }
  template <class T> constexpr char Space(const T &) const {
    return print_nd && (Iterable<T>::value or IsTuple<T>::value) ? '\n' : ' ';
  }
  template <class T> void Impl(T const &t) const {
    if constexpr (DefaultO<T>::value)
      os << t;
    else if constexpr (Iterable<T>::value) {
      if (debug) os << '{';
      int i = 0;
      for (auto &&x : t) ((i++) ? (os << comma() << Space(x), Impl(x)) : Impl(x));
      if (debug) os << '}';
    } else if constexpr (IsTuple<T>::value) {
      if (debug) os << '(';
      std::apply(
          [this](auto const &...args) {
            int i = 0;
            (((i++) ? (os << comma() << " ", Impl(args)) : Impl(args)), ...);
          },
          t);
      if (debug) os << ')';
    } else
      static_assert(IsTuple<T>::value, "No matching type for print");
  }
  template <class T> void ImplWrapper(T const &t) const {
    if (debug) os << "\033[0;31m";
    Impl(t);
    if (debug) os << "\033[0m";
  }
  template <class... Ts> void print(Ts const &...ts) const { ((Impl(ts)), ...); }
  template <class F, class... Ts>
  void print_with_sep(const std::string &sep, F const &f, Ts const &...ts) const {
    ImplWrapper(f), ((os << sep, ImplWrapper(ts)), ...), os << '\n';
  }
  void print_with_sep(const std::string &) const { os << '\n'; }
};

template <class... Ts> void pr(Ts const &...ts) {
  Writer<cout, false, true>{}.print(ts...);
}
template <class... Ts> void ps(Ts const &...ts) {
  Writer<cout, false, true>{}.print_with_sep(" ", ts...);
}
} // namespace IO

inline namespace Debug {
template <typename... Args> void err(Args... args) {
  Writer<cerr, true, false>{}.print_with_sep(" | ", args...);
}
template <typename... Args> void errn(Args... args) {
  Writer<cerr, true, true>{}.print_with_sep(" | ", args...);
}

void err_prefix(string func, int line, string args) {
  cerr << "\033[0;31m\u001b[1mDEBUG\033[0m"
       << " | "
       << "\u001b[34m" << func << "\033[0m"
       << ":"
       << "\u001b[34m" << line << "\033[0m"
       << " - "
       << "[" << args << "] = ";
}

#ifdef LOCAL
#define dbg(args...) err_prefix(__FUNCTION__, __LINE__, #args), err(args)
#define dbgn(args...) err_prefix(__FUNCTION__, __LINE__, #args), errn(args)
#else
#define dbg(...)
#define dbgn(args...)
#endif

const auto beg_time = std::chrono::high_resolution_clock::now();
// https://stackoverflow.com/questions/47980498/accurate-c-c-clock-on-a-multi-core-processor-with-auto-overclock?noredirect=1&lq=1
double time_elapsed() {
  return chrono::duration<double>(std::chrono::high_resolution_clock::now() - beg_time)
      .count();
}
} // namespace Debug

inline namespace FileIO {
void setIn(string s) { freopen(s.c_str(), "r", stdin); }
void setOut(string s) { freopen(s.c_str(), "w", stdout); }
void setIO(string s = "") {
  cin.tie(0)->sync_with_stdio(0); // unsync C / C++ I/O streams
  cout << fixed << setprecision(12);
  // cin.exceptions(cin.failbit);
  // throws exception when do smth illegal
  // ex. try to read letter into int
  if (static_cast<int>(s.size())) setIn(s + ".in"), setOut(s + ".out"); // for old USACO
}
} // namespace FileIO
