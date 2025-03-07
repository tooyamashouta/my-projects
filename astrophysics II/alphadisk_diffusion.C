#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initialize(double *u, double xmin, double xmax, 
                double dx, int n, int ngh) {
  for (int i = ngh; i < n+ngh; ++i) {
    double x = xmin+(i-ngh+0.5)*dx;
    double sx = sqrt(x);
    u[i] = 2000.0/(sx*sx*sx)*exp(-x/50.0); // *** 初期条件を設定
  } 
  return;
}

double cs2(double r) {
  return 0.044/sqrt(r);
}

void boundary_left(double *u, int n, int ngh, double t) {
  // *** 内側の境界条件を設定
  u[0] = 2.0*u[1]-u[2];
  if (u[0] < 0.0) u[0] = 0.0;
  return;
}

void boundary_right(double *u, int n, int ngh, double t) {
  // *** 外側の境界条件を設定
  u[n+ngh] = 2.0*u[n]-u[n-1];
  if (u[n+ngh] < 0.0) u[n+ngh] = 0.0;
  return;
} 

void output(double *u, double t, 
            double xmin, double xmax, double dx,
            int n, int ngh, int step) {
  char fn[32];
  sprintf(fn, "output%04d.dat", step);
  FILE *fp;
  fp = fopen(fn, "w");
  if (fp == NULL) {
    printf("Error: cannot open file %s\n", fn);
    exit(1);
  }

  fprintf(fp, "# t=%f, xmin=%f, xmax=%f, dx=%f, n=%d, ngh=%d, step=%d\n",
          t, xmin, xmax, dx, n, ngh, step);
  for (int i = 1; i < n+ngh; ++i) {
    double x = xmin+(i-ngh+0.5)*dx;
    fprintf(fp, "%d %g %g\n", i, x, u[i]);
  }
  fclose(fp);
  return;
}

void outputt(double *u, double t, 
            double xmin, double xmax, double dx,
            int n, int ngh, int step) {
  char fn[32];
  sprintf(fn, "output10e5.dat");
  FILE *fp;
  fp = fopen(fn, "w");
  if (fp == NULL) {
    printf("Error: cannot open file %s\n", fn);
    exit(1);
  }

  fprintf(fp, "# t=%f, xmin=%f, xmax=%f, dx=%f, n=%d, ngh=%d, step=%d\n",
          t, xmin, xmax, dx, n, ngh, step);
  for (int i = 1; i < n+ngh; ++i) {
    double x = xmin+(i-ngh+0.5)*dx;
    fprintf(fp, "%d %g %g\n", i, x, u[i]);
  }
  fclose(fp);
  return;
}

int main(void) {
  const int NX = 1000, NGH = 1;
  const int NT = 10000000, NOUT = NT/10; // *** 適切なNTを自分で決めよ
  const double xmin = 1.0, xmax = 1000.0, tend = 1e7;
  const double alpha = 0.01;
  const double C = 0.05;
  double dx = (xmax-xmin)/NX, dt = tend/NT, t = 0.0;
  double u[NX+2*NGH], u1[NX+2*NGH];

  initialize(u, xmin, xmax, dx, NX, NGH);
  boundary_left(u, NX, NGH, t);
  boundary_right(u, NX, NGH, t);

  for (int n = 0; n < NT; ++n) {
    if (n%NOUT == 0)
      output(u, t, xmin, xmax, dx, NX, NGH, n/NOUT);
    if (n == 100000)
      outputt(u, t, xmin, xmax, dx, NX, NGH, n);

    for (int i = NGH; i < NX+NGH; ++i) {
      double x = xmin+(i-NGH+0.5)*dx;
      // *** 時間発展の式を自分で書け
      double B1,B2,B3;
      B1 = u[i+1]*(x+dx)*(x+dx)*0.044/sqrt(x+dx); //今はdx = 1.0である。
      B2 = u[i]*x*x*0.044/sqrt(x);
      B3 = u[i-1]*(x-dx)*(x-dx)*0.044/sqrt(x-dx);
      u1[i] = u[i] + dt*C*alpha*(sqrt(x+0.5*dx)*(B1-B2)/dx-sqrt(x-0.5*dx)*(B2-B3)/dx)/x/dx;
    }
    for (int i = NGH; i < NX+NGH; ++i)
      u[i] = u1[i]; // 計算した結果をu1からuにコピー

    t += dt;
    boundary_left(u, NX, NGH, t);
    boundary_right(u, NX, NGH, t);
  }

  output(u, t, xmin, xmax, dx, NX, NGH, NT/NOUT);

  return 0;
}

// gcc -o 6282 6282.c -lm
