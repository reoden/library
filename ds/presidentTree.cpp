/*
 *
 *  president tree
 *  update single elements
 * */
const int _ = 100010;
struct node {
  node *l, *r;
  int sum;

  node() : l(nullptr), r(nullptr), sum(0) {}
  node(node *lhs) : l(lhs->l), r(lhs->r), sum(lhs->sum) {}

  void pull() { sum = l->sum + r->sum; }

} * root[_];

void build(node *p, int l, int r) {
  if (l == r) { return; }

  int mid = (l + r) / 2;
  build(p->l = new node(), l, mid);
  build(p->r = new node(), mid + 1, r);
}

void modify(node *p, int l, int r, int x, int v) {
  if (l == r) {
    p->sum += v;
    return;
  }

  int mid = (l + r) / 2;

  if (x <= mid) {
    modify(p->l = new node(p->l), l, mid, x, v);
  } else {
    modify(p->r = new node(p->r), mid + 1, r, x, v);
  }

  p->pull();
}

int query(node *p, int l, int r, int ln, int rn) {
  if (rn < l || ln > r) { return 0; }
  if (ln <= l && r <= rn) { return p->sum; }

  int mid = (l + r) / 2;
  return query(p->l, l, mid, ln, rn) + query(p->r, mid + 1, r, ln, rn);
}
