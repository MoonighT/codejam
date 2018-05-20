#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>
using namespace std;


double partial_square(double d, double R) {
    double theta = acos(d/R);
    double san = R*R*theta/2.0;
    double tri = d*R*sin(theta)/2;
    double r = san - tri;
    printf("partial square degree=%f, tri=%f, r=%f, d=%f\n",theta/M_PI*180.0, tri, r, d);
    return r;
}

double partial_area(double x, double y, double g, double R, double f) {
    double left_bottom = x*x + y*y;
    double right_top = (x+g) * (x+g) + (y+g) * (y+g);
    double left_top = x*x + (y+g) * (y+g);
    double right_bottom = (x+g) * (x+g) + y * y;
    if(left_bottom >= R*R) {
        // no overlap
        printf("no overlap\n");
        return 0.0;
    }
    if(right_top <= R * R) {
        printf("right top inside\n");
        return g*g;
    }
    // 4 cases
    // only right_top > R^2
    //g -= 2*f;
    if(right_top > R * R && left_top <= R*R && right_bottom <= R*R) {
        printf("case 1\n");
        double delta = sqrt(R*R) - (y+g)*(y+g);
        return partial_square(delta, R) - partial_square(x+g, R) + (delta-x) * y - (x + g - delta);
    }
    if(left_top > R*R && right_bottom < R*R) {
        printf("case 2\n");
        return partial_square(x, R) - partial_square(x+g, R) - y*g;
    }
    if(left_top < R*R && right_bottom > R*R) {
        printf("case 3\n");
        double delta1 = sqrt(R*R - (g+y)*(g+y));
        double delta2 = sqrt(R*R - y*y);
        return (delta1-x)*g+partial_square(delta1, R)-partial_square(delta2, R)-(delta1-delta2)*y;
    }
    printf("case 4\n");
    double delta = sqrt(R*R - y*y);
    return partial_square(x, R)-partial_square(delta, R)-(delta-x)*y;
}

double area_miss(double f, double R, double t, double r, double g) {
    if(g <= 2*f) {
        return 0.0;
    }
    // ball can put into square
    // for loop x and for loop y
    double x = r;
    double y = r;
    int full_square = 0;
    double area = 0.0;
    while (x < R-t) {
        int n = 0;
        while (1) {
            y = r + n * (2 * r + g);
            printf("miss x %f, y %f, R-t %f, g %f\n", x, y, R-t, g);
            if(x*x + y*y >= (R-t)*(R-t)) {
                // if left most point
                break;
            }
            if((x+g)*(x+g) + (y+g)*(y+g) <= (R-t)*(R-t)) {
                printf("case full\n");
                full_square++;
            } else {
                area += partial_area(x, y, g, R-t, f) * (g-2*f)/g*(g-2*f)/g;
                printf("case partial area=%f\n", area);
            }
            n++;
        }
        x += g+2*r;
    }
    return full_square * 1.0 * (g-2*f)*(g-2*f) + area;
}

int main() {
    ifstream ifile("/dev/stdin");
    ofstream ofile("/dev/stdout");
    double N, f, R, t, r, g;
    int c = 1;
    ifile >> N;
    while (N--) {
        (ifile >> f >> R >> t >> r >> g).get();
        double am = 4.0*area_miss(f,R,t,r,g);
        double total = M_PI * R * R;
        double p = am * 1.0 / total;
        printf("am =%f, total=%f p=%f\n", am, total, p);
        ofile << "Case #" << c << ": " << fixed << setprecision(6) <<  1.0-p << endl;
        c++;
    }
    return 0;
}
