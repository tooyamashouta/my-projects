#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

//自作関数の定義
double f (double x, double y) {
	const double k = 0.06;
	const double tr = 20.0;
	return -k*(y-tr);
}

//main
int main(void){
	double a,b,x,y;
	int n;


	cout << "オイラー法、ホイン法、4次ルンゲ・クッタ法で微分方程式を計算します。\n";
	cout << "微分区間[a,b]を入力してください。\n";
	cout << "下限値aは何ですか？："; //改行なし
	cin >> a;
	cout << "上限値bは何ですか？："; //改行なし
	cin >> b;
	cout << "分割数は何ですか？：";
	cin >> n;
	cout << "初期値は何ですか？：";
	cin >> y;

	const double h  = (b-a)/n;
	x = a;

	cout << "オイラー法では、\n";

	double x1=x;
	double y1=y;
	cout << "x = "<< x1 <<"　y = " <<  setprecision(16) << y1 << "\n";
	for (int i=0; i<n; i++){
		y1 = y1+h*f(x1,y1);
		x1 = a+h*(i+1);
		cout << "x = "<< x1 <<"　y = " <<  setprecision(16) << y1 << "\n";

	}

	cout << "ホイン法では、\n";

	double x2=x;
	double y2=y;
	cout << "x = "<< x2 <<"　y = " <<  setprecision(16) << y2 << "\n";
	for (int i=0; i<n; i++){
		double k1=f(x2,y2);
		double k2=f(x2+h,y2+h*k1);
		y2 = y2+h*0.5*(k1+k2);
		x2 = a+h*(i+1);
		cout << "x = "<< x2 <<"　y = " <<  setprecision(16) << y2 << "\n";

	}

	cout << "4次ルンゲ・クッタ法では、\n";

	double x3=x;
	double y3=y;
	cout << "x = "<< x3 <<"　y = " <<  setprecision(16) << y3 << "\n";
	for (int i=0; i<n; i++){
		double k1=f(x3,y3);
		double k2=f(x3+0.5*h,y3+0.5*h*k1);
		double k3=f(x3+0.5*h,y3+0.5*h*k2);
		double k4=f(x3+h,y3+h*k3);
		y3 = y3+h*(k1+2.0*k2+2.0*k3+k4)/6.0;
		x3 = a+h*(i+1);
		cout << "x = "<< x3 <<"　y = " <<  setprecision(16) << y3 << "\n";

	}

	cout << "厳密解は、\n";
	double x0 = b;
	double y0 = ( y-20.0 )*exp( -0.06*x0 )+20.0;
	cout << "x = "<< x0 <<"　y = " <<  setprecision(16) << y0 << "\n";

	return 0;
}
