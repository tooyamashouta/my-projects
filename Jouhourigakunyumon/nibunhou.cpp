#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//自作関数の定義
double f (double x ) {
	//double y = x - log10(x) - 1.0;
	//double y = pow(x,5) -5.0*pow(x,3) +4.0*x;
	//double y = sin(x);
	double y = (x-2.0)*(x-2.0)*(x+2.0)*(x+2.0)*(x-1.0)*(x+1.0);
	return y;
}

//main
int main(void){
	double a,b,c,a0,b0,c0;
	constexpr double alpha = pow(2.0, -20);
	constexpr double epsilon = pow(2.0, -52);
	int n,j,kaiari;

	//a0,b0,nの入力及び分割区間c0の決定
	cout << "二分法で方程式を解きます\n";
	cout << "解を挟む区間[a0,b0]を入力してください。\n";
	cout << "下限値a0は何ですか？："; //改行なし
	cin >> a0;
	cout << "上限値b0は何ですか？："; //改行なし
	cin >> b0;
	cout << "区間を何分割しますか？おすすめは大きめな素数です。：\n";
	cin >> n;
	cout << "\n";// 解を見やすいようにするため

	c0 = fabs( a0 - b0 )/n;
	j=0; //くり返しごとにa,bをc0だけずらす準備
	kaiari=0; //解があるかどうかを判別する基準を作る

	for ( double i=a0; i < b0; i = i+c0 ){
		j = j+1;
		a = a0+(j-1)*c0 ;
		b = a0+j*c0  ;


		if ( f(a)*f(b) < 0.0 ) {
			kaiari = 1;//解がひとつでもあれば1になる。ないなら0のまま
			while ( fabs(a-b) > alpha ) {
				c = (a+b)/2.0;
				if ( fabs(f(c)) < epsilon ) {
					break;
				}
				if ( f(a)*f(c) < 0.0 ) {
					b = c;
				} else {
					a = c;
				}
			} //繰り返し作業終わり
			cout << setprecision(16) << (a+b)/2.0 << "\n";
		}
	}
	if ( kaiari == 0 ){
		cout << "解は見つかりませんでした。\n";
	}else{
		cout << "を解として見つけました。\n";
	}
	return 0;
}
