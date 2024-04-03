/**
 * @brief Scanner(高速入力)
 */
struct Scanner {
public:
  explicit Scanner(FILE *fp) : fp(fp) {}

  template <typename T, typename... E> void read(T &t, E &...e) {
    read_single(t);
    read(e...);
  }

private:
  static constexpr size_t line_size = 1 << 16;
  static constexpr size_t int_digits = 20;
  char line[line_size + 1] = {};
  FILE *fp = nullptr;
  char *st = line;
  char *ed = line;

  void read() {}

  static inline bool is_space(char c) { return c <= ' '; }

  void reread() {
    ptrdiff_t len = ed - st;
    memmove(line, st, len);
    char *tmp = line + len;
    ed = tmp + fread(tmp, 1, line_size - len, fp);
    *ed = 0;
    st = line;
  }

  void skip_space() {
    while (true) {
      if (st == ed) reread();
      while (*st && is_space(*st)) ++st;
      if (st != ed) return;
    }
  }

  template <typename T, enable_if_t<is_integral<T>::value, int> = 0>
  void read_single(T &s) {
    skip_space();
    if (st + int_digits >= ed) reread();
    bool neg = false;
    if (is_signed<T>::value && *st == '-') {
      neg = true;
      ++st;
    }
    typename make_unsigned<T>::type y = *st++ - '0';
    while (*st >= '0') { y = 10 * y + *st++ - '0'; }
    s = (neg ? -y : y);
  }

  template <typename T, enable_if_t<is_same<T, string>::value, int> = 0>
  void read_single(T &s) {
    s = "";
    skip_space();
    while (true) {
      char *base = st;
      while (*st && !is_space(*st)) ++st;
      s += string(base, st);
      if (st != ed) return;
      reread();
    }
  }

  template <typename T> void read_single(vector<T> &s) {
    for (auto &d : s) read(d);
  }
};

/**
 * @brief Printer(高速出力)
 */
struct Printer {
public:
  explicit Printer(FILE *fp) : fp(fp) {}

  ~Printer() { flush(); }

  template <bool f = false, typename T, typename... E>
  void write(const T &t, const E &...e) {
    if (f) write_single(' ');
    write_single(t);
    write<true>(e...);
  }

  template <typename... T> void writeln(const T &...t) {
    write(t...);
    write_single('\n');
  }

  void flush() {
    fwrite(line, 1, st - line, fp);
    st = line;
  }

private:
  FILE *fp = nullptr;
  static constexpr size_t line_size = 1 << 16;
  static constexpr size_t int_digits = 20;
  char line[line_size + 1] = {};
  char *st = line;

  template <bool f = false> void write() {}

  void write_single(const char &t) {
    if (st + 1 >= line + line_size) flush();
    *st++ = t;
  }

  template <typename T, enable_if_t<is_integral<T>::value, int> = 0>
  void write_single(T s) {
    if (st + int_digits >= line + line_size) flush();
    st += to_chars(st, st + int_digits, s).ptr - st;
  }

  void write_single(const string &s) {
    for (auto &c : s) write_single(c);
  }

  void write_single(const char *s) {
    while (*s != 0) write_single(*s++);
  }

  template <typename T> void write_single(const vector<T> &s) {
    for (size_t i = 0; i < s.size(); i++) {
      if (i) write_single(' ');
      write_single(s[i]);
    }
  }
};

Scanner scanner = Scanner(stdin);
Printer printer = Printer(stdout);

void flush() { printer.flush(); }
void print() { printer.write('\n'); }
template <class Head, class... Tail> void print(Head &&head, Tail &&...tail) {
  printer.write(head);
  if (sizeof...(Tail)) printer.write(' ');
  print(forward<Tail>(tail)...);
}

void read() {}
template <class Head, class... Tail> void read(Head &head, Tail &...tail) {
  scanner.read(head);
  read(tail...);
}
#define INT(...)                                                               \
  int __VA_ARGS__;                                                             \
  read(__VA_ARGS__)
#define LL(...)                                                                \
  long long __VA_ARGS__;                                                       \
  read(__VA_ARGS__)
#define STR(...)                                                               \
  string __VA_ARGS__;                                                          \
  read(__VA_ARGS__)
#define CHAR(...)                                                              \
  char __VA_ARGS__;                                                            \
  read(__VA_ARGS__)
#define DBL(...)                                                               \
  double __VA_ARGS__;                                                          \
  read(__VA_ARGS__)

#define VEC(type, name, size)                                                  \
  vector<type> name(size);                                                     \
  read(name)
#define VV(type, name, h, w)                                                   \
  vector<vector<type>> name(h, vector<type>(w));                               \
  read(name)