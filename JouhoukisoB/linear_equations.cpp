#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main(void){
	int n;
	cout << "連立一次方程式を計算します。\n変数（式)の数はいくつですか？整数を入力してください。:\n";
	cin >> n;
	double a[n][n];
	double b[n];
        cout << "以下、変数の係数及び定数項の値を入力してください。\n";
        for ( int k=0; k<n; k++){
                for ( int j=0; j<n; j++){
                        cout << k+1 << "番目の式の、" << j+1 << "番目の変数の係数は何ですか。:\n";
  	          	cin >> a[k][j];
                }
                cout << k+1 << "番目の式の、定数項の値は何ですか。:\n";
   		cin >> b[k];
        }
	double sum;

	//前進消去
	for ( int k=0; k<=n-2; k++){

		// 部分ピボット選択
		double absmax=fabs(a[k][k]);
		int imax=k;
		for ( int i=k+1; i<n; i++){
			if ( fabs(a[i][k]) > absmax ){
				absmax = fabs(a[i][k]);
				imax = i;
			}
		}

		if ( imax != k){
			double tmp;
			for (int j=k; j<n; j++){
				tmp = a[k][j];
				a[k][j]=a[imax][j];
				a[imax][j]=tmp;
			}
			tmp = b[k];
			b[k]=b[imax];
			b[imax]=tmp;
		}



		/*
		if ( imax !=k ){
			swap(a[imax], a[k]);//imax行目とk行目の係数チェンジ
			swap(b[imax], b[k]);//定数項チェンジ
		}
*/
		for (int i=k+1; i<=n-1; i++ ){
			for (int j=k+1; j<=n-1; j++ ){
				a[i][j] = a[i][j] - a[k][j]*a[i][k]/a[k][k];
			}
			b[i] = b[i] - b[k]*a[i][k]/a[k][k];
		}
	}
	//後退代入
	for ( int i=n-1; i>=0; i-- ){
		sum = b[i];
		for ( int j=i+1; j<=n-1; j++ ){
			sum = sum - b[j]*a[i][j];
		}
		b[i] = sum/a[i][i];
	}




	//解の表示

	for (int i=0; i<n; i++  ){
		cout << "x" << i << "=" <<  setprecision(17) << b[i] <<  "\n";
	}
	return 0;
}
