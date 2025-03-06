#include <stdio.h> 
#include <math.h>
#include <stdlib.h> 

struct particle { //mainの外におく
  double x,y,z;
 };
typedef struct particle pa; //particle_ にする必要もない

void rotz(pa *v, double th){ //z軸回転 
 double az[3][3] = {{cos(th), -sin(th), 0},{sin(th), cos(th), 0},{0, 0, 1}};
 double av[3] = {v->x, v->y, v->z}; //式中はぜんぶv.xではなくv->x
 double avr[3] = {0,0,0}; //計算結果を収める用
 for (int j = 0; j <3; ++j) {
  for (int i = 0; i <3; ++i) {
 printf("az[%d][%d]=%lf\n",j ,i ,az[j][i]);
   avr[j] += az[j][i]*av[i];
  }
 }
 v->x = avr[0];
 v->y = avr[1];
 v->z = avr[2];
 return; //必須ではない
}

void rotx(pa *v, double th){ //x軸回転 
 double ax[3][3] = {{1, 0, 0},{0, cos(th), -sin(th)},{0, sin(th), cos(th)}};
 double av[3] = {v->x, v->y, v->z}; 
 double avr[3] = {0,0,0}; 
 for (int j = 0; j <3; ++j) {
  for (int i = 0; i <3; ++i) {
   avr[j] += ax[j][i]*av[i];
  }
 }
 v->x = avr[0];
 v->y = avr[1];
 v->z = avr[2];
 return; 
}

int main(int argc, char **argv){ 
    //コマンドラインから引数を取る。argcには(このプログラム自体を含む)引数の数が格納される。
    //argv[i]には i番目の引数が文字列として格納される。argv[0]には常にこのプログラム自体が格納されている。
 const double pi = 3.141592658979;
 double a,b,c;
 if (argc != 7) { //argv[0]がこまんどそのものだから＋１
  printf("Error: x,y,z,a,b,cの順で6つの数値を入力してください。\na,b,cはπの係数にしてください。");
  return 1; //プログラムの失敗を示すらしい。
 }

 pa v;
 v.x=atof(argv[1]); //atof: 文字列 → double型
 v.y=atof(argv[2]);
 v.z=atof(argv[3]);
 a=pi*atof(argv[4]); 
 b=pi*atof(argv[5]);
 c=pi*atof(argv[6]);

 rotz(&v, a);
 rotx(&v, b);
 rotz(&v, c);

 printf("(X,Y,Z) = (%lf,%lf,%lf)\n",v.x, v.y, v.z);
 return 0;
}

