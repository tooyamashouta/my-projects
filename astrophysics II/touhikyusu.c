#include <stdio.h>
#include <math.h>

int main(void){
  double a = 1.0;
  int N = 100;
  double r = 0.01;
  printf(" 初項は%lf、\n 公比は%lf、\n 項数は%d。\n",a,r,N);
  double A = a;
  double s = A;
  for(int i=1; i<=N-1; ++i){
     s = s*r;
     A = A+s;
     //printf("%lf,%lf\n",s,A);
  }
  printf(" 小さい側から足し上げた和はSl = %.16g\n",A);

  double AA = a*pow(r,N-1);
  double rr = 1/r;
  double ss = AA;
  for(int i=1; i<=N-1; ++i){
     ss = ss*rr;
     AA = AA+ss;
     //printf("%lf,%lf\n",ss,AA);
  }

  double S = a*(1-pow(r,N))/(1-r);
  double SA = S-A;
  double SAA = S-AA;
  printf(" 大きい側から足し上げた和はSb = %.16g\n",AA);
  printf(" 公式で算出したSは %.16g\n",S);
  printf(" S-Sl = %.16g\n S-Sb = %.16g\n",SA,SAA);
  if(SA < 0.0){
  SA = -SA;
  }
  if(SAA < 0.0){
  SAA = -SAA;
  }
  if(SA < SAA){
  printf(" 小さい側から足し上げた和の方が解析解に近い。\n");
  }
  else if(SAA < SA){
  printf(" 大きい側から足し上げた和の方が解析解に近い。\n");
  }
  else {
    if(SAA <= 1e-10){
    printf(" 大きい側から足し上げた和と小さい側から足した和の双方が解析解と等しい。\n");
    }
    else{
    printf(" 大きい側から足し上げた和と小さい側から足した和の双方が解析解との差は等しい。\n");
    }
  }
  return 0;
}
