#include <stdio.h> 
#include <math.h>
#include <stdlib.h>

//Newton-Raphson法は多次元(多変数)でも使える。
//その場合、変数xはベクトルに、 微分は多次元空間での勾配演算子(ヤコビ行列)に置き換える。

double f(double r[]){
 return r[0]*r[0]+r[1]*r[1]-1;
}

double g(double r[]){
 return r[1]-r[0]*r[0]*r[0]+1;
}

//ヤコビアンの要素４つを解析的に計算する
double dfdx(double r[]){return 2*r[0]; } 
double dfdy(double r[]){return 2*r[1]; }
double dgdx(double r[]){return -3*r[0]*r[0]; }
double dgdy(double r[]){return r[1]; }

// ヤコビアンの逆行列を計算する
double gyakuJacob(double r[],double aa[][2]){ //各行ごとの要素数を指定しないと、二次元配列として認識してくれない。
 double detJ = dfdx(r)*dgdy(r) - dfdy(r)*dgdx(r); //0になるとnan
 aa[0][0] = dgdy(r)/detJ;
 aa[0][1] = -dfdy(r)/detJ;
 aa[1][0] = -dgdx(r)/detJ;
 aa[1][1] = dfdx(r)/detJ;
}
 
void step(double r[], double dr[],double aa[][2]){　//各行ごとの要素数を指定しないと、二次元配列として認識してくれない
 double fnow = f(r); //今x,yでのｆの値を求める
 double gnow = g(r);
 gyakuJacob(r,aa); //ヤコビアンの逆行列を求める関数
 dr[0] = -(aa[0][0]*fnow + aa[0][1]*gnow);
 dr[1] = -(aa[1][0]*fnow + aa[1][1]*gnow);
}


int main(int argc, char **argv) { //変数は入力する
 if(argc!=5){ 
  printf("x,y,dx,dyの順で初期値をコマンドプロンプトから入力してください\n");
  return 1;
 }

 double r[2]={atof(argv[1]),atof(argv[2])};
 double dr[2]={atof(argv[3]),atof(argv[4])};
 const double eps = 1e-10;
 double aa[2][2] = {{0.0, 0.0},{0.0, 0.0}}; //後にdrを計算するときに使うヤコビアンの逆行列を格納する二次元配列
 while (fabs(dr[0]) > eps && fabs(dr[1]) > eps) { //計算を終える条件は、drが変化しなくなったとき
  step(r,dr,aa); //drを算出するための関数
  r[0] += dr[0];
  r[1] += dr[1];
 }
 printf("(x,y) = %16f,%16f\n",r[0],r[1] );

 return 0;
}
