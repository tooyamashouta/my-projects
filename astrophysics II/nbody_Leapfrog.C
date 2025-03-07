#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// 粒子構造体の定義：ID、質量、座標、速度、加速度、半径（解析用）
typedef struct particle {
  double m, x, y, z, vx, vy, vz, ax, ay, az, r;
} particle_t;



// Box Muller法で平均0分散1の正規分布乱数を生成する
double bmrand(void) {
  double x = (double)rand()/RAND_MAX;
  double y = (double)rand()/RAND_MAX;
  // 本来２つ乱数が生成されるが、片方は捨てる
  return sqrt(-2.0*log(x))*cos(2.0*M_PI*y);
}


// 全粒子の合計の運動エネルギーを計算する
double total_ekinetic(particle_t *data, int n) {
  double ekin = 0.0;
  for (int i = 0; i < n; ++i) {
    ekin += 0.5*data[i].m*(data[i].vx*data[i].vx
         +data[i].vy*data[i].vy+data[i].vz*data[i].vz);
  }
  return ekin;
}


// 全粒子の合計のポテンシャルエネルギーを計算する
double total_potential(particle_t *data, int n, double eps) {
  double pot = 0.0;
  // 全てのi-j粒子の組についてポテンシャルを積算する
  // 重複しないよう、ループの上限下限に注意する
  for (int i = 0; i < n-1; ++i) {
    for (int j = i+1; j < n; ++j) {
      double dx = data[j].x - data[i].x;
      double dy = data[j].y - data[i].y;
      double dz = data[j].z - data[i].z;
      double r = sqrt(dx*dx + dy*dy + dz*dz + eps*eps);
      pot -= data[i].m*data[j].m/r;
    }
  }
  return pot;
}


// 初期の粒子の空間分布を計算する関数
// radは初期の一様球の半径（今回の例では1.0にしてある）
void init_position(particle_t *data, int n, double rad) {
  for (int i = 0; i < n; ++i) {
    // data[i].x,y,zが一様球になるように計算する
    // 一様乱数を生成して、それが指定された半径の球内にある場合は採用、
    // 球の外にある場合は廃棄するという手順を繰り返して作ると良い。
    double x; // -radに0以上2rad以下の乱数を足して、-radからradまでの一様乱数を与える。
    double y;
    double z;
    double r;
    do{
    x = -1.0*rad + (double)rand()*2.0*rad/((double)RAND_MAX); // -radに0以上2rad以下の乱数を足して、-radからradまでの一様乱数を与える。
    y = -1.0*rad + (double)rand()*2.0*rad/((double)RAND_MAX);
    z = -1.0*rad + (double)rand()*2.0*rad/((double)RAND_MAX);
    r = sqrt(x*x+y*y+z*z);
    data[i].x = x, data[i].y = y,data[i].z = z;
    }while( r >= rad ); // r >= radの場合はもう１度doから上書き
    
  }
  return;
}


// 初期の粒子の速度を計算する関数
// rvはビリアル比（パラメータ）、potは全ポテンシャルエネルギー
void init_velocity(particle_t *data, int n, double rv, double pot) {
  for (int i = 0; i < n; ++i) {
    // data[i].vx,vy,vzが平均0、分散σの正規分布になるように計算する
    // 分散をσにするには分散1の正規分布乱数をσ倍すればよい。
    
    double sigma = sqrt(2.0*rv*fabs(pot)/3.0); //全質量M = 1の単位系にしていることに注意。
    data[i].vx = sigma*bmrand();
    data[i].vy = sigma*bmrand();
    data[i].vz = sigma*bmrand(); 
    
  }
  return;
}


// 粒子分布を作成する関数
void init_particles(particle_t *data, int n, double eps,
                    double rad, double rv) {
  for (int i = 0; i < n; ++i)
    data[i].m = 1.0/(double)n; // 質量をセット：全質量M=1
  init_position(data, n, rad);
  double pot = total_potential(data, n, eps);
  init_velocity(data, n, rv, pot);
  return;
}


void calc_acceleration(particle_t *data, int n, double eps) {
  // 加速度を全てゼロでクリア
  for (int i = 0; i < n; ++i) {
    data[i].ax = 0.0;
    data[i].ay = 0.0;
    data[i].az = 0.0;
  }
  for (int i = 0; i < n; ++i) {  // 全てのi粒子について加速度を計算する
    for (int j = i; j < n; ++j) { // j粒子について和を取る
      // 加速度data[i].ax,ay,azを計算する

	double dx = 0.0, dy = 0.0, dz = 0.0;
	dx = data[i].x -data[j].x;
	dy = data[i].y -data[j].y;
	dz = data[i].z -data[j].z;
	double b1 =sqrt(dx*dx+dy*dy+dz*dz+eps*eps);
	double b3 = b1*b1*b1;

	data[i].ax -= data[j].m*dx/b3; // G=1にしている。
	data[i].ay -= data[j].m*dy/b3;
	data[i].az -= data[j].m*dz/b3;

        data[j].ax += data[i].m*dx/b3; // G=1にしている。
	data[j].ay += data[i].m*dy/b3;
	data[j].az += data[i].m*dz/b3;

    }
  }
  return;
}


// Leapfrog法
void leapfrog(particle_t *data, int n, double dt, double eps) {
  // t=tn での加速度は前のステップで計算されたものがax,ay,azに入っている
  // 最初のステップの前にcalc_accelerationを実行しておく必要がある
  for (int i = 0; i < n; ++i) {
    // 各粒子の速度をdt/2分進める

    data[i].vx += 0.5*dt*data[i].ax;
    data[i].vy += 0.5*dt*data[i].ay;
    data[i].vz += 0.5*dt*data[i].az;
    
  }
  for (int i = 0; i < n; ++i) {
    // 各粒子の位置をdt分進める
    
    data[i].x += dt*data[i].vx;
    data[i].y += dt*data[i].vy;
    data[i].z += dt*data[i].vz;
    
    
  }
  calc_acceleration(data, n, eps); // t=tn+1での加速度を計算
  for (int i = 0; i < n; ++i) {
    // 各粒子の速度をdt/2分進める
    // 一つ目のループと同じ形になるはず
    
    data[i].vx += 0.5*dt*data[i].ax;
    data[i].vy += 0.5*dt*data[i].ay;
    data[i].vz += 0.5*dt*data[i].az;
    
  }
  return;
}


// データをファイルに出力する
void output(particle_t *data, int n, int step) {
  char fn[32];
  sprintf(fn, "output%04d.dat", step);
  FILE *fp;
  fp = fopen(fn, "w");
  if (fp == NULL) {
    printf("Error: cannot open file %s\n", fn);
    exit(1); // プログラムを終了させる関数（returnとは違う）
  }

  for (int i = 0; i < n; ++i) {
    fprintf(fp, "%d %g %g %g %g %g %g %g\n", i, 
            data[i].m, data[i].x, data[i].y, data[i].z,
            data[i].vx, data[i].vy, data[i].vz);
  }

  fclose(fp);
  return;
}


// 中心からの半径data[i].rを計算する
void calc_radii(particle_t *data, int n) {
  for (int i = 0; i < n; ++i)
    data[i].r = sqrt(data[i].x*data[i].x
              + data[i].y*data[i].y + data[i].z*data[i].z);
  return;
}


// qsort用の比較関数：中心からの半径で並び替える
int cmp_data(const void *a, const void *b) {
  if (((particle_t*)a)->r < ((particle_t*)b)->r)
    return -1;
  else if (((particle_t*)a)->r > ((particle_t*)b)->r)
    return 1;
  else
    return 0;
}


// 粒子の密度の動径分布を計算する
void radial_profile(particle_t *data, int n, int step) {
  char fn[32];
  sprintf(fn, "radprof%04d.dat", step);
  FILE *fp;
  fp = fopen(fn, "w");
  if (fp == NULL) {
    printf("Error: cannot open file %s\n", fn);
    exit(1); // プログラムを終了させる関数（returnとは違う）
  }

  calc_radii(data, n); // 中心からの半径を計算
  // データを中心からの半径で並び替える
  // これは計算に使われているデータも並び替えてしまうが、
  // 今の場合粒子に個性はないので並び替えても問題ない
  qsort(data, n, sizeof(particle_t), cmp_data);

  // 密度プロファイルを計算して表示する
  int d = 64;
  for (int i = 0; i < n-d; ++i) {
    // i番目からi+d番目の粒子を含む球殻を考え、
    // 球殻の半径をi番目の粒子の半径とi+d番目の粒子の半径の平均、
    // 球殻の密度を球殻中の粒子の質量/球殻の体積で計算する
    double radius, density;
    
    radius = (data[i].r + data[i+d].r)/2.0;
    double Mshell = data[i].m*d;
    double Vshell = 4.0*M_PI*(data[i+d].r*data[i+d].r*data[i+d].r-data[i].r*data[i].r*data[i].r)/3.0;
    density = Mshell / Vshell;
    
    fprintf(fp, "%g %g\n", radius, density);
  }
  fclose(fp);
  return;
}


// データを解析して全エネルギー及びビリアル比を表示
// ポテンシャルの計算はO(N^2)なのでそれなりにコストがかかることに注意
void analyze(particle_t *data, int n, double eps, double t) {
  double ekin = total_ekinetic(data, n);
  double pot  = total_potential(data, n, eps);
  double etot = ekin + pot;
  double rv = ekin / fabs(pot);
  printf("%f %g\n", t,rv);
  return;
}


int main(void) {
  // 定数類の宣言
  const int N = 4096;      // 粒子数 - 時間がかかり過ぎる場合は減らして良い
  const int NSTEP = 4096;  // ステップ数
  const int OSTEP = 64;    // データを出力する間隔
  const double eps = 0.01; // ソフトニングパラメータ
  const double rad = 1.0;  // 初期分布である一様球の半径
  const double rv = 0.1;   // ビリアルパラメータ
  const double tend = 20.0; // 終了時間

  // 粒子・加速度データの宣言と確保
  particle_t *data;
  data = malloc(sizeof(particle_t)*N);

  srand(1); // 乱数列の初期化 これはmainで一回のみ行う。何回も行うとそのたびに乱数が最初に戻ってしまう。

  init_particles(data, N, eps, rad, rv); // 粒子分布を作成 

  double t = 0.0, dt = tend / NSTEP;
  analyze(data, N, eps, t); // 初期状態を確認する
  radial_profile(data, N, 0); // 初期密度プロファイルも出力

  // 最初のステップを始める前に加速度を計算しておく
  // leapfrog()内のコメントも参照のこと
  calc_acceleration(data, N, eps);

  for (int i = 0; i < NSTEP; ++i) {
    if ((i % OSTEP) == 0) { // OSTEP毎にデータを出力
      output(data, N, i/OSTEP);
      radial_profile(data, N, i/OSTEP);
    }

    leapfrog(data, N, dt, eps); // Leapfrog法でdt時間を進める
    t += dt;

    analyze(data, N, eps, t); // エネルギー等を解析する
  }

  output(data, N, NSTEP/OSTEP); // 最終状態の出力
  radial_profile(data, N, NSTEP/OSTEP); // 最終密度プロファイルを出力

  // 終了処理：粒子データを解放
  free(data);

  return 0;
}
