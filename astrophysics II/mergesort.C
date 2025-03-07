#include <stdio.h>
#include <stdlib.h>

struct particle { //構造体を宣言
 long double ra, dec, par, gm, bm, rm;
};
typedef struct particle pa;

void mergesort (pa *listb, int left, int right) { //マージソート listbはポインタ渡し
 int j, k, l, o, p, mid; //midはわざとint。こうすることで0.5を回避できる。
 pa lista[4271];  // 作業用AoS
 if (left < right) {
  mid = (left + right)/2; // midに中央が何番目か教える
  mergesort(listb, left, mid);  // 左を再帰呼び出し
  mergesort(listb, mid+1, right);  // 右を再帰呼出し
  for (o = mid; o >= left; o--) { // 左半分を作業用AoSに移す
   lista[o] = listb[o]; 
  } 
  for (p = mid+1; p <= right; p++) { // 右半分を逆順で作業用AoSに移す
   lista[right-(p-(mid+1))] = listb[p];
  }
  j = left; k = right;
  for (l = left; l <= right; l++) { //小さい方からlistbに戻す
   if (lista[j].par < lista[k].par) { //右半分を逆順に作業用AoSに収めたから、作業用AoSのその時対象にしている部分は左から/\のような背の順になっている
    listb[l] = lista[j++];
   }else{
    listb[l] = lista[k--];
   }
  }
 }
}


int main(int argc, char **argv) {  //書き込むファイル名は与える。

 if(argc!=2){ 
  printf("書き込むファイル名をコマンドプロンプトから入力してください\n");
  return 1;
 }

 FILE *fbefore, *fcheck, *fafter;
 fbefore = fopen("ngc6397.dat", "r");
 if (fbefore == NULL) {
  printf("Error: cannot open the file\n");
  return 1;
 }

 pa listb[4271]; // 構造体の配列を宣言
 char line[1000]; // 入力データをchar型で一時的に保存
 int i = 0;
 while (fgets(line, 1000, fbefore) != NULL) {
  if (line[0] == '#') continue;
 long double A,B,C,D,E,F;
  sscanf(line, "%16Lf %16Lf %16Lf %16Lf %16Lf %16Lf", &A, &B, &C, &D, &E, &F); // double型として読んでlistbの要素としていれていく
  listb[i].ra = A;
  listb[i].dec = B;
  listb[i].par = C;
  listb[i].gm = D;
  listb[i].bm = E;
  listb[i].rm = F;
  i++;
 }

 mergesort(listb, 0, 4270); //0と4270はそれぞれ配列の要素の番号

 fcheck = fopen(argv[1], "r"); // 書き込もうとしているファイルがすでにあった場合警告してファイルを閉じる
 if (fcheck != NULL) {
  printf("Error: The file already exists.\n");
  fclose(fcheck);
  return 2;
 }

 fafter = fopen(argv[1], "w"); // ソート済みのlistbを別のファイルに出力
 for(i=0;i<4271;i++){
  fprintf(fafter,"%Lf %Lf %Lf %Lf %Lf %Lf\n", 
  listb[i].ra, listb[i].dec, listb[i].par, listb[i].gm, listb[i].bm, listb[i].rm);
 }

 fclose(fbefore); //忘れずに
 fclose(fafter); //忘れずに
 }
