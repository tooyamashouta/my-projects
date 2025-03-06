#include <iostream>
using namespace std;

//おくと仮定した座標から、八方についておけるか調査する。八方のいずれかの方向に、相手の石があり自分の石がその先に既にあれば置ける
int check_dir(int tate, int yoko, int board[8][8], int junban, int dtate, int dyoko) {
  tate += dtate;  // dtateの値の分だけ縦隣に移動
  yoko += dyoko;  // dyokoの値の分だけ横隣に移動

  if ( tate < 0 || tate > 7 || yoko < 0 || yoko > 7 ) {
     return 0; // 枠外で即アウト
  }

  if ( board[tate][yoko] == 0 ) {
     return  0; // 隣が空なのでアウト
  }

  if ( board[tate][yoko] == junban ) {
     return  0;  // 隣が自分の色なのでアウト
  }

  while ( 1 ) {

    tate += dtate; // さらに縦隣に移動
    yoko += dyoko; // さらに横隣に移動

    if ( tate < 0 || tate > 7 || yoko < 0 || yoko > 7 ) {
      return 0; // 枠外でアウト
    }

    if ( board[tate][yoko] == 0 ) {
       return 0;  // 空のマスにぶつかってアウト
    }

    if ( board[tate][yoko] == junban )  {
       return 1; // 自分の色の石にぶつかってOK
    }
  }
}

int check( int tate, int yoko, int board[8][8], int junban ){
    if ( board[tate][yoko] != 0 ){
	return 0;
    }
    if ( check_dir(tate,yoko,board,junban, 1, 1) == 1 ){
	return 1;
    }
    if ( check_dir(tate,yoko,board,junban, 1, 0) == 1 ){
	return 1;
    }
    if ( check_dir(tate,yoko,board,junban, 1, -1) == 1 ){
	return 1;
    }
    if ( check_dir(tate,yoko,board,junban, 0, 1) == 1 ){
	return 1;
    }
    if ( check_dir(tate,yoko,board,junban, 0, -1) == 1 ){
	return 1;
    }
    if ( check_dir(tate,yoko,board,junban, -1, 1) == 1 ){
	return 1;
    }
    if ( check_dir(tate,yoko,board,junban, -1, 0) == 1 ){
	return 1;
    }
    if ( check_dir(tate,yoko,board,junban, -1, -1) == 1 ){
	return 1;
    }
    return 0; //はさんでいる方向がなかったのでダメ
}

void reverse_dir(int tate, int yoko, int board[8][8],
                    int junban, int dtate, int dyoko) {

  tate += dtate;  // 隣に移動
  yoko += dyoko;  // 隣に移動

  board[tate][yoko] = junban; // 隣は自分の色に置き換え

  while ( 1 ) {

    tate += dtate; // さらに隣に移動
    yoko += dyoko; // さらに隣に移動

    if ( board[tate][yoko] == junban )  {
      return; // 自分の色の石にぶつかったら終了
    }

    board[tate][yoko] = junban; // 自分の色に置き換え

  }
}




void reverse(int tate, int yoko, int board[8][8], int junban) {

  if ( check_dir(tate, yoko, board, junban,  1,  1) == 1 ) {
     reverse_dir(tate, yoko, board, junban,  1,  1);
  }
  if ( check_dir(tate, yoko, board, junban,  1,  0) == 1 ) {
     reverse_dir(tate, yoko, board, junban,  1,  0);
  }
  if ( check_dir(tate, yoko, board, junban,  1, -1) == 1 ) {
     reverse_dir(tate, yoko, board, junban,  1, -1);
  }
  if ( check_dir(tate, yoko, board, junban,  0,  1) == 1 ) {
     reverse_dir(tate, yoko, board, junban,  0,  1);
  }
  if ( check_dir(tate, yoko, board, junban,  0, -1) == 1 ) {
     reverse_dir(tate, yoko, board, junban,  0, -1);
  }
  if ( check_dir(tate, yoko, board, junban, -1,  1) == 1 ) {
     reverse_dir(tate, yoko, board, junban, -1,  1);
  }
  if ( check_dir(tate, yoko, board, junban, -1,  0) == 1 ) {
     reverse_dir(tate, yoko, board, junban, -1,  0);
  }
  if ( check_dir(tate, yoko, board, junban, -1, -1) == 1 ) {
     reverse_dir(tate, yoko, board, junban, -1, -1);
  }
}

int passcheck(int board[8][8], int junban) {
    for (int tate=0; tate<8; tate++) {
	for (int yoko=0; yoko<8; yoko++) {
	    if (check(tate, yoko, board, junban)==1 ) // 置ける!
		return 0; // パスしないので 0を返して関数終わり
	}
    }
    return 1; // 置ける場所が1ヶ所もなかった
}

int main(void){

// タイトルを表示
    cout << "\n";
    cout << "　　　　　　　　　　　　　オセロゲーム\n"; //””の中は全角OK
    cout << "\n";
    cout << "   OOO  TTTTTTT  HH    HH  EEEEEEEEEE  LL      L      OOO   \n" // \nは改行
         << "  O   O    T     HH    HH  EEEEEEEEEE  LL      L     OOOOO  \n"
         << "  O   O    T     HHHHHHHH  EE          LL      L     OOOOO  \n"
         << "   OOO     T     HHHHHHHH  EEEEEEEEEE  LL      L      OOO   \n"
         << "           T     HH    HH  EEEEEEEEEE  LL      LLLLL        \n"
         << "                 HH    HH  EE          LLLLLLL              \n"
         << "                           EEEEEEEEEE                       \n"
         << "                           EEEEEEEEEE                       \n"
         << "                                                            \n"
         << "                                                            \n"
         << "           GGGGGGG                　　     EEEEEEEEEE       \n"
         << "         GGG     GGG            　　       EEEEEEEEEE       \n"
         << "        GG         GG         　           EE               \n"
         << "        GG                　　             EEEEEEEEEE       \n"
         << "        GG                 A     M     M   EEEEEEEEEE       \n"
         << "        GG     GGGGGG     A A    M M M M   EE               \n"
         << "         GGG     GGGG    AAAAA   M  M  M   EEEEEEEEEE       \n"
         << "           GGGGGGGG G   A     A  M     M   EEEEEEEEEE       \n\n"; // セミコロンは忘れずに


	// ２次元配列boardの初期化
    int board[8][8];
    for( int i=0; i < 8; i++ ){
        for( int j=0; j < 8; j++ ){
		board[i][j]=0;
	}
    }

	//初期配置の選択
     int shokitate,shokiyoko,X;

     cout << "初期状態にどこに石を置くか決められます。\n";
     cout << "まずは平行型か交差型かを選んでください。\n";
     cout << "平行型なら1、交差型ならそれ以外の整数を入力してください。：\n";
     cin >> X;
     cout << "続いて初期配置の左上の座標を決めます。\n";
     cout << "縦の座標を入力してください。:";
     cin >> shokitate;
     cout << "横の標を入力してください。:";
     cin >> shokiyoko;

     if ( X == 1){
         board[shokitate-1][shokiyoko-1]=board[shokitate-1][shokiyoko]=1;
         board[shokitate][shokiyoko-1]=board[shokitate][shokiyoko]=2;
     }else{
         board[shokitate-1][shokiyoko-1]=board[shokitate][shokiyoko]=1;
         board[shokitate-1][shokiyoko]=board[shokitate][shokiyoko-1]=2;
     }

	// 変数の宣言
    int junban=2; 
    int tate,yoko,shiro,kuro,mekakushi;//変数”mekakushi"を追加

    cout << "初期状態はこちらです。";
    printf("\x1b[42m");
    cout << "\n";
    cout << "\n";
    cout << "                 1   2   3   4   5   6   7   8 \n";
    cout << "               十ー十ー十ー十ー十ー十ー十ー十一十 \n";
    for ( int i=0; i < 8; i++ ){
   	cout << "              " << i+1 << "｜";
        for( int j=0; j < 8; j++ ){
		if ( board[i][j]==0 ){
			cout << "　" <<  "｜";
		}
		if ( board[i][j]==1 ){
			cout << "⚪️" <<  "｜";
		}
		if ( board[i][j]==2 ){
			cout << "⚫️" <<  "｜";
		}
	}
	cout << "\n" << "               十ー十ー十ー十ー十ー十ー十ー十ー十  \n";
    }
    printf("\x1b[49m");
    cout << "\n";


    while(1){
	    cout << "目隠しを実行する、あるいは続ける場合は " << 1 << " を\n";
	    cout << "実行しない、あるいは解除する場合は " << 2 << " を入力してください。：\n";
	    cin >> mekakushi;

		// オセロ盤を表示
	    if ( mekakushi == 1 ){
        	printf("\x1b[42m");
		cout << "\n";
		cout << "\n";
	        cout << "                 1   2   3   4   5   6   7   8 \n";
	        cout << "               十ー十ー十ー十ー十ー十ー十ー十一十 \n";
	        for ( int i=0; i < 8; i++ ){
	   	    cout << "              " << i+1 << "｜";
	  	    for( int j=0; j < 8; j++ ){
			if ( board[i][j]==0 ){
				cout << "　" <<  "｜";
			}
			if ( board[i][j]==1 ){
				cout << "　" <<  "｜";//空のマスと見分けがつかない。
			}
			if ( board[i][j]==2 ){
				cout << "　" <<  "｜";//空のマスと見分けがつかない。
			}
		    }
		    cout << "\n" << "               十ー十ー十ー十ー十ー十ー十ー十ー十  \n";
	        }
	    }else if( mekakushi == 2 ){
      		    printf("\x1b[42m");
		    cout << "\n";
		    cout << "\n";
		    cout << "                 1   2   3   4   5   6   7   8 \n";
		    cout << "               十ー十ー十ー十ー十ー十ー十ー十一十 \n";
		    for ( int i=0; i < 8; i++ ){
		   	cout << "              " << i+1 << "｜";
		        for( int j=0; j < 8; j++ ){
				if ( board[i][j]==0 ){
					cout << "　" <<  "｜";
				}
				if ( board[i][j]==1 ){
					cout << "⚪️" <<  "｜";
				}
				if ( board[i][j]==2 ){
					cout << "⚫️" <<  "｜";
				}
			}
			cout << "\n" << "               十ー十ー十ー十ー十ー十ー十ー十ー十  \n";
		    }
	    }else{
		cout << 1 << "か" << 2 << "を入力してください。\n";
		continue;//繰り返し処理のスキップ。
	    }

	    //枚数を数えて表示
	    shiro=kuro=0; // shiroとkuroを0にリセット
	    for (int i=0; i<8; i++ ) {
		for (int j=0; j<8; j++) {
		    if ( board[i][j] == 1 ) {
			shiro++;
		    }
		    if ( board[i][j] == 2 ) {
			kuro++;		    }
		}
	    }
	    cout << "⚪️: " << shiro << " 枚  ⚫️: " << kuro << " 枚"
	        << " 合計: " << shiro+kuro << " 枚\n";


	    //ループに入らないために
	    if ( (shiro+kuro) == 64 ){
		break;
	    }

            printf("\x1b[49m");//背景色をデフォルトに戻す
            cout << "\n";//ここで改行させると緑色になる部分がきれいになる。

	    //順番の表示
	    if( junban==1 ){
	        cout << "⚪️の番です。\n";
	    } else {
	        cout << "⚫️の番です。\n";
	    }

	    //　パスが必要か
	    if ( passcheck(board, junban) == 1 ){
		junban = 3 - junban;

		if ( passcheck(board, junban) == 1 ){
		    cout << "しかし、双方とも石を置くことができません。よって強制終了します。\n";
		    break;

		} else {

		    cout << "あなたは石を置くことができません。パスを実行します。\n";
	        continue; //くり返し処理を途中で切り上げて繰り返しの先頭(この場合はwhileの先頭)に戻る。
			  // (breakは繰り返しから抜ける）
		}
	    }

	    //石を置く場所の入力
	    //縦の座標の入力
	    do{
		cout << "石を置く位置の座標を入力します。\n";
		cout << "縦の座標を入力してください。:";
		cin >> tate;
		cin.clear(); // エラー状態を解除
		cin.ignore(1000,'\n');// 入力バッファを 1000文字分消去
	    } while  ( tate < 1 || tate > 8);// ||は論理和（または）を示す。
	    tate--;

	    //横の座標の入力
	    do{
		    cout << "横の座標を入力してください。:";
		    cin >> yoko;
		    cin.clear(); // エラー状態を解除
		    cin.ignore(1000,'\n');// 入力バッファを 10000文字分消去
	    } while  ( yoko < 1 || yoko > 8);
	    yoko--;

	    //石を置いて良いかと、置いた後の石の反転を行う
    	    if ( check(tate,yoko,board,junban) == 1 ){
		//石をひっくり返す関数
		reverse(tate,yoko,board,junban);

	        //石を置く
	        board[tate][yoko]=junban;

	        //順番交代
	        junban=3-junban;//3-1=2,3-2=1
	    } else {
		printf("\x1b[7m");      // 反転（背景色と前景色の入れ替え)
		cout << "ルール上禁止されている場所です。\n";
		cout << "異なる座標を指定してください。\n";
		printf("\x1b[0m");	// 背景色をデフォルトに戻す
	    }

    }//while(1)の}

    //終了処理
    cout << "ゲームが終了しました。\n";
    if ( shiro > kuro ) {
	cout << "⚪️の勝ちです。Congratulations!\n";
    }
    if ( shiro < kuro ) {
	cout << "⚫️の勝ちです。Congratulations!\n";
    }
    if ( shiro == kuro ) {
	cout << "結果は引き分けでした。\n";
    }
    return 0;
}
