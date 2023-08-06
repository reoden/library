int exgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }

    int xx, yy;
    int d = exgcd(b, a % b, xx, yy);
    x = yy;
    y = xx - (a / b) * yy;
    /*
        int d = exgcd(b, a % b, y, x);
        y -= (a / b) * x;
        return d;
    */
    return d;
}
/*
    int d = exgcd(a, b, x, y);
    assert(a * x + b * y == d);
    此时x y为 方程组的两个一般解
    调整x y大小则 x += b / d, y -= a / d;
    x0 = x + b * t, y0 = (d - a * x) / b;   这个是通解
*/
