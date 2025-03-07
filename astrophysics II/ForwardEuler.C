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
 double T = 2*M_PI, tmax = 100*T; // 1周期は2πである。
 for (int j = 0; j < 30; ++j) { // T/nのnを1から2の29乗まで行う。
  double x=1.0, v=0.0, t=0.0, dt = T/n; //dtを変えるごとに初期条件をリセットする
  for (int i = 1; i <= 100*n; ++i) { //前進オイラー法
   double dx = dt*dxdt(x,v,t);
   double dv = dt*dvdt(x,v,t);
   x +=dx, v +=dv;
   t +=dt;
//   printf("%d %fπ %f %f\n",i, t/M_PI, x, v); //動作確認用
  } 
  double e = sqrt(Dx(x,v,t)*Dx(x,v,t) + Dv(x,v,t)*Dv(x,v,t)); //100周期まで行ったところで位置と速度の誤差のL2ノルムeを計算する
  printf("%d %fπ %f\n", j, t/M_PI, e); //eを表示する
  n *= 2; // 一回のT/nでやりたいことが終わったら2の累乗の回数を一つ増やす
 }
 return 0;
}

// gcc -o 6201 6201.c -lm
// ./6201
