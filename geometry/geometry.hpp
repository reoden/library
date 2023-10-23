#pragma once

#include <bits/stdc++.h>

namespace std {
bool operator<(const complex<long double> &a, const complex<long double> &b) {
  return !(fabs(a.real() - b.real()) < 1e-8) ? a.real() < b.real()
                                             : a.imag() < b.imag();
}
} // namespace std

using namespace std;

namespace Geometry {
using Real = long double;
using Point = std::complex<Real>;
const Real EPS = 1e-10;
const Real PI = acos(-1);

inline bool eq(Real a, Real b) { return std::fabs(b - a) < EPS; }

Point operator*(const Point &p, const Real &d) {
  return Point(real(p) * d, imag(p) * d);
}

std::istream &operator>>(std::istream &is, Point &p) {
  Real a, b;
  is >> a >> b;
  p = Point(a, b);
  return is;
}

std::ostream &operator<<(std::ostream &os, Point &p) {
  return os << p.real() << " " << p.imag();
}

// 点 p を反時計回りに theta 回転
Point rotate(Real theta, const Point &p) {
  return Point(cos(theta) * p.real() - sin(theta) * p.imag(),
               sin(theta) * p.real() + cos(theta) * p.imag());
}

Point rotate90(const Point &p) { return {-p.imag(), p.real()}; }

Real radian_to_degree(Real r) { return (r * 180.0 / PI); }

Real degree_to_radian(Real d) { return (d * PI / 180.0); }

// a-b-c の角度のうち小さい方を返す
Real get_angle(const Point &a, const Point &b, const Point &c) {
  const Point v(b - a), w(c - b);
  Real alpha = atan2(v.imag(), v.real()), beta = atan2(w.imag(), w.real());
  if (alpha > beta)
    std::swap(alpha, beta);
  Real theta = (beta - alpha);
  return std::min(theta, 2 * acos(-1) - theta);
}

struct Line {
  Point a, b;

  Line() = default;

  Line(Point a, Point b) : a(a), b(b) {}

  Line(Real A, Real B, Real C) // Ax + By = C
  {
    if (eq(A, 0))
      a = Point(0, C / B), b = Point(1, C / B);
    else if (eq(B, 0))
      a = Point(C / A, 0), b = Point(C / A, 1);
    else
      a = Point(0, C / B), b = Point(C / A, 0);
  }

  friend std::ostream &operator<<(std::ostream &os, Line &p) {
    return os << p.a << " to " << p.b;
  }

  friend std::istream &operator>>(std::istream &is, Line &a) {
    return is >> a.a >> a.b;
  }
};

struct Segment : Line {
  Segment() = default;

  Segment(Point a, Point b) : Line(a, b) {}
};

struct Circle {
  Point p;
  Real r;

  Circle() = default;

  Circle(Point p, Real r) : p(p), r(r) {}
};

using Points = vector<Point>;
using Polygon = vector<Point>;
using Segments = vector<Segment>;
using Lines = vector<Line>;
using Circles = vector<Circle>;

// cross > 0 a b COUNTER_CLOCKWISE
Real cross(const Point &a, const Point &b) {
  return real(a) * imag(b) - imag(a) * real(b);
}

Real dot(const Point &a, const Point &b) {
  return real(a) * real(b) + imag(a) * imag(b);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C
// 点の回転方向
int ccw(const Point &a, Point b, Point c) {
  b = b - a, c = c - a;
  if (cross(b, c) > EPS)
    return +1; // "COUNTER_CLOCKWISE"
  if (cross(b, c) < -EPS)
    return -1; // "CLOCKWISE"
  if (dot(b, c) < 0)
    return +2; // "ONLINE_BACK"
  if (norm(b) < norm(c))
    return -2; // "ONLINE_FRONT"
  return 0;    // "ON_SEGMENT"
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
// 平行判定
bool parallel(const Line &a, const Line &b) {
  return eq(cross(a.b - a.a, b.b - b.a), 0.0);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A
// 垂直判定
bool orthogonal(const Line &a, const Line &b) {
  return eq(dot(a.a - a.b, b.a - b.b), 0.0);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
// 射影
// 直線 l に p から垂線を引いた交点を求める
Point projection(const Line &l, const Point &p) {
  Real t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

Point projection(const Segment &l, const Point &p) {
  Real t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
  return l.a + (l.a - l.b) * t;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B
// 反射
// 直線 l を対称軸として点 p  と線対称にある点を求める
Point reflection(const Line &l, const Point &p) {
  return p + (projection(l, p) - p) * 2.0;
}

bool intersect(const Line &l, const Point &p) {
  return abs(ccw(l.a, l.b, p)) != 1;
}

bool intersect(const Line &l, const Line &m) {
  return abs(cross(l.b - l.a, m.b - m.a)) > EPS ||
         abs(cross(l.b - l.a, m.b - l.a)) < EPS;
}

bool intersect(const Segment &s, const Point &p) {
  return ccw(s.a, s.b, p) == 0;
}

bool intersect(const Line &l, const Segment &s) {
  return cross(l.b - l.a, s.a - l.a) * cross(l.b - l.a, s.b - l.a) < EPS;
}

Real distance(const Line &l, const Point &p);

bool intersect(const Circle &c, const Line &l) {
  return distance(l, c.p) <= c.r + EPS;
}

bool intersect(const Circle &c, const Point &p) {
  return abs(abs(p - c.p) - c.r) < EPS;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B
bool intersect(const Segment &s, const Segment &t) {
  return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) <= 0 &&
         ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

int intersect(const Circle &c, const Segment &l) {
  if (norm(projection(l, c.p) - c.p) - c.r * c.r > EPS)
    return 0;
  auto d1 = abs(c.p - l.a), d2 = abs(c.p - l.b);
  if (d1 < c.r + EPS && d2 < c.r + EPS)
    return 0;
  if (d1 < c.r - EPS && d2 > c.r + EPS || d1 > c.r + EPS && d2 < c.r - EPS)
    return 1;
  const Point h = projection(l, c.p);
  if (dot(l.a - h, l.b - h) < 0)
    return 2;
  return 0;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A&lang=jp
int intersect(Circle c1, Circle c2) { // return the number of tangent lines
  if (c1.r < c2.r)
    std::swap(c1, c2);
  Real d = abs(c1.p - c2.p);
  if (c1.r + c2.r < d)
    return 4;
  if (eq(c1.r + c2.r, d))
    return 3;
  if (c1.r - c2.r < d)
    return 2;
  if (eq(c1.r - c2.r, d))
    return 1;
  return 0;
}

Real distance(const Point &a, const Point &b) { return abs(a - b); }

Real distance(const Line &l, const Point &p) {
  return abs(p - projection(l, p));
}

Real distance(const Line &l, const Line &m) {
  return intersect(l, m) ? 0 : distance(l, m.a);
}

Real distance(const Segment &s, const Point &p) {
  Point r = projection(s, p);
  if (intersect(s, r))
    return abs(r - p);
  return std::min(abs(s.a - p), abs(s.b - p));
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D
Real distance(const Segment &a, const Segment &b) {
  if (intersect(a, b))
    return 0;
  return std::min(
      {distance(a, b.a), distance(a, b.b), distance(b, a.a), distance(b, a.b)});
}

Real distance(const Line &l, const Segment &s) {
  if (intersect(l, s))
    return 0;
  return std::min(distance(l, s.a), distance(l, s.b));
}

Point crosspoint(const Line &l, const Line &m) {
  Real A = cross(l.b - l.a, m.b - m.a);
  Real B = cross(l.b - l.a, l.b - m.a);
  if (eq(abs(A), 0.0) && eq(abs(B), 0.0))
    return m.a;
  return m.a + (m.b - m.a) * B / A;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C
Point crosspoint(const Segment &l, const Segment &m) {
  return crosspoint(Line(l), Line(m));
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D
std::pair<Point, Point> crosspoint(const Circle &c, const Line l) {
  Point pr = projection(l, c.p);
  Point e = (l.b - l.a) / abs(l.b - l.a);
  if (eq(distance(l, c.p), c.r))
    return {pr, pr};
  Real base = sqrt(c.r * c.r - norm(pr - c.p));
  return {pr - e * base, pr + e * base};
}

std::pair<Point, Point> crosspoint(const Circle &c, const Segment &l) {
  Line aa = Line(l.a, l.b);
  if (intersect(c, l) == 2)
    return crosspoint(c, aa);
  auto ret = crosspoint(c, aa);
  if (dot(l.a - ret.first, l.b - ret.first) < 0)
    ret.second = ret.first;
  else
    ret.first = ret.second;
  return ret;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E
std::pair<Point, Point> crosspoint(const Circle &c1, const Circle &c2) {
  Real d = abs(c1.p - c2.p);
  Real a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
  Real t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
  Point p1 = c1.p + Point(cos(t + a) * c1.r, sin(t + a) * c1.r);
  Point p2 = c1.p + Point(cos(t - a) * c1.r, sin(t - a) * c1.r);
  return {p1, p2};
}

Circle inCircle(Polygon P) {
  assert((int)P.size() == 3);
  Real l0 = distance(P[1], P[2]), l1 = distance(P[0], P[2]),
       l2 = distance(P[0], P[1]);
  Circle c;
  c.p = crosspoint(Line(P[0], (P[1] * l1 + P[2] * l2) / (l1 + l2)),
                   Line(P[1], (P[0] * l0 + P[2] * l2) / (l0 + l2)));
  c.r = distance(Line(P[0], P[1]), c.p);
  return c;
}

Circle circumcircle(Polygon P) {
  assert((int)P.size() == 3);
  Circle c;
  c.p = crosspoint(Line((P[0] + P[1]) / (Real)2.0,
                        (P[0] + P[1]) / (Real)2.0 + rotate90(P[0] - P[1])),
                   Line((P[0] + P[2]) / (Real)2.0,
                        (P[0] + P[2]) / (Real)2.0 + rotate90(P[0] - P[2])));
  c.r = distance(c.p, P[0]);
  return c;
}

#define BOTTOM 0
#define LEFT 1
#define RIGHT 2
#define TOP 3

class EndPoint {
public:
  Point p;
  int seg, st; // 线段的ID，端点的种类
  EndPoint() {}
  EndPoint(Point p, int seg, int st) : p(p), seg(seg), st(st) {}

  // 按y坐标升序排序
  bool operator<(const EndPoint &ep) const {
    if (p.imag() == ep.p.imag())
      return st < ep.st;
    return p.imag() < ep.p.imag();
  }
};
EndPoint EP[2 * 1000010];

// 线段相交问题，曼哈顿几何
int manhattanIntersection(const Segments &S) {
  int n = S.size();
  std::sort(EP, EP + (2 * n)); // 按照端点的y坐标升序排序

  std::set<int> BT;      // 二叉搜索树
  BT.insert(2000000000); // 设置标记
  int cnt = 0;

  for (int i = 0; i < 2 * n; i++) {
    if (EP[i].st == TOP)
      BT.erase(EP[i].p.real()); // 删除上端点
    else if (EP[i].st == BOTTOM)
      BT.insert(EP[i].p.real());
    else if (EP[i].st == LEFT) {
      auto b = BT.lower_bound(S[EP[i].seg].a.real());
      auto e = BT.upper_bound(S[EP[i].seg].b.real());
      cnt += distance(b, e); // 加上b到e距离
    }
  }
  return cnt;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F
// 点 p を通る円 c の接線
std::pair<Point, Point> tangent(const Circle &c1, const Point &p2) {
  return crosspoint(c1, Circle(p2, sqrt(norm(c1.p - p2) - c1.r * c1.r)));
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G
// 円 c1, c2 の共通接線
Lines tangent(Circle c1, Circle c2) {
  Lines ret;
  if (c1.r < c2.r)
    std::swap(c1, c2);
  Real g = norm(c1.p - c2.p);
  if (eq(g, 0))
    return ret;
  Point u = (c2.p - c1.p) / sqrt(g);
  Point v = rotate(PI * 0.5, u);
  for (int s : {-1, 1}) {
    Real h = (c1.r + s * c2.r) / sqrt(g);
    if (eq(1 - h * h, 0)) {
      ret.emplace_back(c1.p + u * c1.r, c1.p + (u + v) * c1.r);
    } else if (1 - h * h > 0) {
      Point uu = u * h, vv = v * sqrt(1 - h * h);
      ret.emplace_back(c1.p + (uu + vv) * c1.r, c2.p - (uu + vv) * c2.r * s);
      ret.emplace_back(c1.p + (uu - vv) * c1.r, c2.p - (uu - vv) * c2.r * s);
    }
  }
  return ret;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_B
// 凸性判定
bool is_convex(const Polygon &p) {
  int n = (int)p.size();
  for (int i = 0; i < n; i++) {
    if (ccw(p[(i + n - 1) % n], p[i], p[(i + 1) % n]) == -1)
      return false;
  }
  return true;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A
// 凸包
Polygon convex_hull(Polygon &p, bool strict = true) {
  int n = (int)p.size(), k = 0;
  if (n <= 2)
    return p;
  std::sort(p.begin(), p.end());
  Points ch(2 * n);
  Real eps = strict ? EPS : -EPS;
  for (int i = 0; i < n; ch[k++] = p[i++]) {
    while (k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < eps)
      --k;
  }
  for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
    while (k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < eps)
      --k;
  }
  ch.resize(k - 1);
  return ch;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C
// 多角形と点の包含判定
enum { OUTTT, ONNN, INNN };

int contains(const Polygon &Q, const Point &p) {
  bool in = false;
  for (int i = 0; i < Q.size(); i++) {
    Point a = Q[i] - p, b = Q[(i + 1) % Q.size()] - p;
    if (a.imag() > b.imag())
      swap(a, b);
    if (a.imag() <= 0 && 0 < b.imag() && cross(a, b) < 0)
      in = !in;
    if (cross(a, b) == 0 && dot(a, b) <= 0)
      return ONNN;
  }
  return in ? INNN : OUTTT;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1033
// 線分の重複除去
void merge_segments(Segments &segs) {

  auto merge_if_able = [](Segment &s1, const Segment &s2) {
    if (abs(cross(s1.b - s1.a, s2.b - s2.a)) > EPS)
      return false;
    if (ccw(s1.a, s2.a, s1.b) == 1 || ccw(s1.a, s2.a, s1.b) == -1)
      return false;
    if (ccw(s1.a, s1.b, s2.a) == -2 || ccw(s2.a, s2.b, s1.a) == -2)
      return false;
    s1 = Segment(std::min(s1.a, s2.a), max(s1.b, s2.b));
    return true;
  };

  for (int i = 0; i < segs.size(); i++) {
    if (segs[i].b < segs[i].a)
      std::swap(segs[i].a, segs[i].b);
  }
  for (int i = 0; i < segs.size(); i++) {
    for (int j = i + 1; j < segs.size(); j++) {
      if (merge_if_able(segs[i], segs[j])) {
        segs[j--] = segs.back(), segs.pop_back();
      }
    }
  }
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1033
// 線分アレンジメント
// 任意の2線分の交点を頂点としたグラフを構築する
vector<vector<int>> segment_arrangement(Segments &segs, Points &ps) {
  vector<vector<int>> g;
  int N = (int)segs.size();
  for (int i = 0; i < N; i++) {
    ps.emplace_back(segs[i].a);
    ps.emplace_back(segs[i].b);
    for (int j = i + 1; j < N; j++) {
      const Point p1 = segs[i].b - segs[i].a;
      const Point p2 = segs[j].b - segs[j].a;
      if (cross(p1, p2) == 0)
        continue;
      if (intersect(segs[i], segs[j])) {
        ps.emplace_back(crosspoint(segs[i], segs[j]));
      }
    }
  }
  std::sort(begin(ps), end(ps));
  ps.erase(std::unique(begin(ps), end(ps)), end(ps));

  int M = (int)ps.size();
  g.resize(M);
  for (int i = 0; i < N; i++) {
    vector<int> vec;
    for (int j = 0; j < M; j++) {
      if (intersect(segs[i], ps[j])) {
        vec.emplace_back(j);
      }
    }
    for (int j = 1; j < vec.size(); j++) {
      g[vec[j - 1]].push_back(vec[j]);
      g[vec[j]].push_back(vec[j - 1]);
    }
  }
  return (g);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_C
// 凸多角形の切断
// 直線 l.a-l.b で切断しその左側にできる凸多角形を返す
Polygon convex_cut(const Polygon &U, Line l) {
  Polygon ret;
  for (int i = 0; i < U.size(); i++) {
    Point now = U[i], nxt = U[(i + 1) % U.size()];
    if (ccw(l.a, l.b, now) != -1)
      ret.push_back(now);
    if (ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0) {
      ret.push_back(crosspoint(Line(now, nxt), l));
    }
  }
  return (ret);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A
// 多角形の面積
Real area(const Polygon &p) {
  Real A = 0;
  for (int i = 0; i < p.size(); ++i) {
    A += cross(p[i], p[(i + 1) % p.size()]);
  }
  return A * 0.5;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_H
// 円と多角形の共通部分の面積
Real area(const Polygon &p, const Circle &c) {
  if (p.size() < 3)
    return 0.0;
  function<Real(Circle, Point, Point)> cross_area =
      [&](const Circle &c, const Point &a, const Point &b) {
        Point va = c.p - a, vb = c.p - b;
        Real f = cross(va, vb), ret = 0.0;
        if (eq(f, 0.0))
          return ret;
        if (std::max(abs(va), abs(vb)) < c.r + EPS)
          return f;
        if (distance(Segment(a, b), c.p) > c.r - EPS)
          return c.r * c.r * arg(vb * conj(va));
        auto u = crosspoint(c, Segment(a, b));
        vector<Point> tot{a, u.first, u.second, b};
        for (int i = 0; i + 1 < tot.size(); i++) {
          ret += cross_area(c, tot[i], tot[i + 1]);
        }
        return ret;
      };
  Real A = 0;
  for (int i = 0; i < p.size(); i++) {
    A += cross_area(c, p[i], p[(i + 1) % p.size()]);
  }
  return A;
}

Real area(const Circle &a, const Circle &b) {
  Real d = abs(a.p - b.p);
  if (d >= a.r + b.r - EPS)
    return .0;
  if (d <= abs(a.r - b.r) + EPS) {
    Real r = std::min(a.r, b.r);
    return PI * r * r;
  }
  Real ath = acos((a.r * a.r + d * d - b.r * b.r) / d / a.r / 2.);
  Real res = a.r * a.r * (ath - sin(ath * 2) / 2.);
  Real bth = acos((b.r * b.r + d * d - a.r * a.r) / d / b.r / 2.);
  res += b.r * b.r * (bth - sin(bth * 2) / 2.);
  return res;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_B
// 凸多角形の直径(最遠頂点対間距離)
Real convex_diameter(const Polygon &p) {
  int N = (int)p.size();
  int is = 0, js = 0;
  for (int i = 1; i < N; i++) {
    if (p[i].imag() > p[is].imag())
      is = i;
    if (p[i].imag() < p[js].imag())
      js = i;
  }
  Real maxdis = norm(p[is] - p[js]);

  int maxi, maxj, i, j;
  i = maxi = is;
  j = maxj = js;
  do {
    if (cross(p[(i + 1) % N] - p[i], p[(j + 1) % N] - p[j]) >= 0) {
      j = (j + 1) % N;
    } else {
      i = (i + 1) % N;
    }
    if (norm(p[i] - p[j]) > maxdis) {
      maxdis = norm(p[i] - p[j]);
      maxi = i;
      maxj = j;
    }
  } while (i != is || j != js);
  return std::sqrt(maxdis);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A
// 最近点対
Real closest_pair(Points ps) {
  if (ps.size() <= 1)
    throw(0);
  sort(begin(ps), end(ps));

  auto compare_y = [&](const Point &a, const Point &b) {
    return imag(a) < imag(b);
  };
  vector<Point> beet(ps.size());
  const Real INF = 1e18;

  function<Real(int, int)> rec = [&](int left, int right) {
    if (right - left <= 1)
      return INF;
    int mid = (left + right) >> 1;
    auto x = real(ps[mid]);
    auto ret = std::min(rec(left, mid), rec(mid, right));
    inplace_merge(begin(ps) + left, begin(ps) + mid, begin(ps) + right,
                  compare_y);
    int ptr = 0;
    for (int i = left; i < right; i++) {
      if (abs(real(ps[i]) - x) >= ret)
        continue;
      for (int j = 0; j < ptr; j++) {
        auto luz = ps[i] - beet[ptr - j - 1];
        if (imag(luz) >= ret)
          break;
        ret = std::min(ret, abs(luz));
      }
      beet[ptr++] = ps[i];
    }
    return ret;
  };
  return rec(0, (int)ps.size());
}
} // namespace Geometry
using namespace Geometry;
