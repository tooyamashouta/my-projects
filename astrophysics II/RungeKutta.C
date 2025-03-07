#include <stdio.h> 
#include <math.h>

double dxdt(double x, double v, double t) {
 return v;
}

double dvdt(double x, double v, double t) {
 return -x;
}

double Dx(double x, double v, double t){ //Δx
 return cos(t) -x;
}

double Dv(double x, double v, double t){ //Δv
 return -sin(t) -v;
}

int main(void) {
 int n = 1;
 double T = 2*M_PI, tmax = 100*T;
 for (int j =0; j < 20; ++j) {
  double x=1.0, v=0.0, t=0.0, dt = T/n;
//  printf("\n0 %fπ 0\n", t/M_PI);
  for (int i = 1; i <= 100*n; ++i) {
   double kx1 = dxdt(x,v,t);
   double kv1 = dvdt(x,v,t);

   double t1 = t + 0.5*dt;
   double x1 = x+0.5*dt*kx1;
   double v1 = v+0.5*dt*kv1;
   double kx2 = dxdt(x1,v1,t1);
   double kv2 = dvdt(x1,v1,t1);

   double x2 = x+0.5*dt*kx2;
   double v2 = v+0.5*dt*kv2;
   double kx3 = dxdt(x2,v2,t1);
   double kv3 = dvdt(x2,v2,t1);

   double x3 = x+dt*kx3;
   double v3 = v+dt*kv3;
   double t3 = t+dt;
   double kx4 = dxdt(x3,v3,t3);
   double kv4 = dvdt(x3,v3,t3);

   x += (1.0/6.0)*dt*(kx1+2.0*kx2+2.0*kx3+kx4); // 係数もdouble型にする
   v += (1.0/6.0)*dt*(kv1+2.0*kv2+2.0*kv3+kv4);
   t +=dt;
//   printf("%d %fπ %f %f\n",i, t/M_PI, x, v);
//  double e = sqrt(Dx(x,v,t)*Dx(x,v,t) + Dv(x,v,t)*Dv(x,v,t));
  //printf("%d %fπ %f\n", i, t/M_PI, e);
  } 
  double e = sqrt(Dx(x,v,t)*Dx(x,v,t) + Dv(x,v,t)*Dv(x,v,t));
  printf("%d %fπ %f \n", n, t/M_PI, e);
  n *= 2;
 }
 return 0;
}

// gcc -o 6202 6202.c -lm
// ./6202
