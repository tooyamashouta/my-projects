// this is make_hist_0130 (segsegcor cut TagB_head und allTofF)
#define make_hist_cxx
#include "make_hist.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void make_hist::Loop( const char* output_file_name )
{
	if (fChain == 0) return;

	Long64_t nentries = fChain->GetEntriesFast();
	
	TH1F* th1f_time_tagb[30];
	TH2F* th2f_width_vs_time_tagb[30];

	TH1F* th1f_time_tagb_head[30];
	TH2F* th2f_width_vs_time_tagb_head[30];

	TH1F* th1f_multi_b;//各イベントで電子が当たったTagBのセグメント数(1~30)
	TH1F* th1f_distribution_b;//どのセグメントに当たったかを、_headのタイミングでFill(各イベントで重ね書きする？数万高数十万個のグラフを見るわけにはいかんでしょ)→THStack

	TH1F* th1f_time_tagf[105];
	TH1F* th1f_time_tagf_head[105];

	TH1F* th1f_distribution_f;

	TH1F* th1f_time_tagb_head_cut[30];
	TH2F* th2f_width_vs_time_tagb_head_cut[30];
	TH1F* th1f_multi_b_cut;

	TH2F* th2f_seg_seg_cor;
	TH2F* th2f_seg_seg_cor_cut;

	TH1F* th1f_tof_sbs[104];//side_by_side
	TH1F* th1f_tof_sbs_cut2[104];
	TH1F* th1f_time_tagf_head_cut2[105];
	TH2F* th2f_seg_seg_cor_cut2;

	TH2F* th2f_seg_seg_cor_cutbf;
	TH1F* th1f_tof_bf[30][105];
	TH1F* th1f_time_tagf_head_cutbf[105];

	for ( int i=0; i<30; i++ ) {    // 1 ch = 25 ps
		th1f_time_tagb[i]   = new TH1F( TString::Format("th1f_time_TagB%02d"  , i+1), "", 5000, 170000., 220000. );
		th1f_time_tagb[i] -> GetXaxis() -> SetTitle( "time [ps]" );

		th2f_width_vs_time_tagb[i]        = new TH2F(  TString::Format("th2f_width_vs_time_TagB%02d" , i+1)               , "",  5000, 170000., 220000., 80, 0., 80000.   );
		th2f_width_vs_time_tagb[i] -> GetXaxis() -> SetTitle( TString::Format("Time (TagB%02d) [ps]" , i+1) );
		th2f_width_vs_time_tagb[i] -> GetYaxis() -> SetTitle( TString::Format("Width (TagB%02d) [ps]", i+1) );

		/*No.15以前と以後で、シグナルの範囲が違うので、描画に反映する↓
		th1f_time_tagb_head[i]   = new TH1F( TString::Format("th1f_time_TagB_head%02d"  , i+1), "",  5000, 170000., 220000. );
		th1f_time_tagb_head[i] -> GetXaxis() -> SetTitle( "time [ps]" );
		
		th2f_width_vs_time_tagb_head[i]        = new TH2F(  TString::Format("th2f_width_vs_time_TagB_head%02d" , i+1)               , "",  5000, 170000., 220000., 80, 0., 80000.   );
		th2f_width_vs_time_tagb_head[i] -> GetXaxis() -> SetTitle( TString::Format("Time (TagB%02d) [ps]" , i+1) );
		th2f_width_vs_time_tagb_head[i] -> GetYaxis() -> SetTitle( TString::Format("Width (TagB%02d) [ps]", i+1) );

		th1f_time_tagb_head_cut[i]   = new TH1F( TString::Format("th1f_time_TagB_head_cut%02d"  , i+1), "",  5000, 170000., 220000. );
		th1f_time_tagb_head_cut[i] -> GetXaxis() -> SetTitle( "time [ps]" );

		th2f_width_vs_time_tagb_head_cut[i]        = new TH2F(  TString::Format("th2f_width_vs_time_TagB_head_cut%02d" , i+1)               , "",  5000, 170000., 220000., 80, 0., 80000.   );
		th2f_width_vs_time_tagb_head_cut[i] -> GetXaxis() -> SetTitle( TString::Format("Time (TagB%02d) [ps]" , i+1) );
		th2f_width_vs_time_tagb_head_cut[i] -> GetYaxis() -> SetTitle( TString::Format("Width (TagB%02d) [ps]", i+1) );
		*/
	}

	for ( int i=0; i<15; i++ ) {    // 1 ch = 25 ps
		th1f_time_tagb_head[i]   = new TH1F( TString::Format("th1f_time_TagB_head%02d"  , i+1), "",  80, 187000., 190000. );
		th1f_time_tagb_head[i] -> GetXaxis() -> SetTitle( "time [ps]" );
		
		th2f_width_vs_time_tagb_head[i]        = new TH2F(  TString::Format("th2f_width_vs_time_TagB_head%02d" , i+1)               , "",  80, 187000., 190000., 80, 0., 80000.   );
		th2f_width_vs_time_tagb_head[i] -> GetXaxis() -> SetTitle( TString::Format("Time (TagB%02d) [ps]" , i+1) );
		th2f_width_vs_time_tagb_head[i] -> GetYaxis() -> SetTitle( TString::Format("Width (TagB%02d) [ps]", i+1) );

		th1f_time_tagb_head_cut[i]   = new TH1F( TString::Format("th1f_time_TagB_head_cut%02d"  , i+1), "", 80, 187000., 190000. );
		th1f_time_tagb_head_cut[i] -> GetXaxis() -> SetTitle( "time [ps]" );

		th2f_width_vs_time_tagb_head_cut[i]        = new TH2F(  TString::Format("th2f_width_vs_time_TagB_head_cut%02d" , i+1)               , "",  80, 187000., 190000., 80, 0., 80000.   );
		th2f_width_vs_time_tagb_head_cut[i] -> GetXaxis() -> SetTitle( TString::Format("Time (TagB%02d) [ps]" , i+1) );
		th2f_width_vs_time_tagb_head_cut[i] -> GetYaxis() -> SetTitle( TString::Format("Width (TagB%02d) [ps]", i+1) );
	}

	for ( int i=15; i<30; i++ ) {    // 1 ch = 25 ps
		th1f_time_tagb_head[i]   = new TH1F( TString::Format("th1f_time_TagB_head%02d"  , i+1), "",  80, 205000., 208000. );
		th1f_time_tagb_head[i] -> GetXaxis() -> SetTitle( "time [ps]" );
		
		th2f_width_vs_time_tagb_head[i]        = new TH2F(  TString::Format("th2f_width_vs_time_TagB_head%02d" , i+1)               , "",  80, 205000., 208000., 80, 0., 80000.   );
		th2f_width_vs_time_tagb_head[i] -> GetXaxis() -> SetTitle( TString::Format("Time (TagB%02d) [ps]" , i+1) );
		th2f_width_vs_time_tagb_head[i] -> GetYaxis() -> SetTitle( TString::Format("Width (TagB%02d) [ps]", i+1) );

		th1f_time_tagb_head_cut[i]   = new TH1F( TString::Format("th1f_time_TagB_head_cut%02d"  , i+1), "",  80, 205000., 208000. );
		th1f_time_tagb_head_cut[i] -> GetXaxis() -> SetTitle( "time [ps]" );

		th2f_width_vs_time_tagb_head_cut[i]        = new TH2F(  TString::Format("th2f_width_vs_time_TagB_head_cut%02d" , i+1)               , "",  80, 205000., 208000., 80, 0., 80000.  );
		th2f_width_vs_time_tagb_head_cut[i] -> GetXaxis() -> SetTitle( TString::Format("Time (TagB%02d) [ps]" , i+1) );
		th2f_width_vs_time_tagb_head_cut[i] -> GetYaxis() -> SetTitle( TString::Format("Width (TagB%02d) [ps]", i+1) );
	}

	th1f_multi_b = new TH1F("th1f_multi_b", "", 31,0,31); // 1eventの中で、同一chに複数回入ることもあるが、今回、nhitloopの最後に残った物のみなので0~31(30は30以上31未満のbinに入る)
	th1f_multi_b -> GetXaxis() -> SetTitle("TagBの1eventあたりのhit数");//日本語ダメだった。
	th1f_multi_b_cut = new TH1F("th1f_multi_b_cut", "", 31,0,31);
	th1f_multi_b_cut -> GetXaxis() -> SetTitle("TagBの1eventあたりのhit数");

	th1f_distribution_b = new TH1F("th1f_distribution_b", "", 31,0,31);
	th1f_distribution_b	-> GetXaxis() -> SetTitle("各イベントでどのセグメントに当たっているか");

	for ( int i=0; i<105; i++ ) {    // 1 ch = 100 ps
		th1f_time_tagf[i]  = new TH1F( TString::Format("th1f_time_TagF%03d"  , i+1), "", 4000, -1000000., 3000000. );
		th1f_time_tagf[i] -> GetXaxis() -> SetTitle( "time [ps]" );
	}

	for ( int i=0; i<105; i++ ) {    // 1 ch = 100 ps
		th1f_time_tagf_head[i]  = new TH1F( TString::Format("th1f_time_TagF_head%03d"  , i+1), "", 4000, -1000000., 3000000. );
		th1f_time_tagf_head[i] -> GetXaxis() -> SetTitle( "time [ps]" );
	}

	th1f_distribution_f = new TH1F("th1f_distribution_f", "", 106,0,106);
	th1f_distribution_f -> GetXaxis() -> SetTitle("distribution of TagF");

	th2f_seg_seg_cor = new TH2F("th2f_seg_seg_cor", "", 106, 0, 106, 31, 0, 31);
	th2f_seg_seg_cor -> GetXaxis() -> SetTitle("TagF");
	th2f_seg_seg_cor -> GetYaxis() -> SetTitle("TagB");
	th2f_seg_seg_cor -> GetZaxis() -> SetTitle("Intensity");

	th2f_seg_seg_cor_cut = new TH2F("th2f_seg_seg_cor_cut", "", 106, 0, 106, 31, 0, 31);
	th2f_seg_seg_cor_cut -> GetXaxis() -> SetTitle("TagF");
	th2f_seg_seg_cor_cut -> GetYaxis() -> SetTitle("TagB");
	th2f_seg_seg_cor_cut -> GetZaxis() -> SetTitle("Intensity");


	for ( int i=0; i<104; i++ ) {
		th1f_tof_sbs[i]  = new TH1F( TString::Format("th1f_tof_TagF%03d_TagF%03d" ,i+1 ,i+2), "", 4000, -500000., 500000. );
		th1f_tof_sbs[i] -> GetXaxis() -> SetTitle( TString::Format("TagF%03d - TagF%03d[ps]" ,i+1 ,i+2)  );
	}

	for ( int i=0; i<104; i++ ) {
		th1f_tof_sbs_cut2[i]  = new TH1F( TString::Format("th1f_tof_cut_TagF%03d_TagF%03d" ,i+1 ,i+2), "", 4000, -500000., 500000. );
		th1f_tof_sbs_cut2[i] -> GetXaxis() -> SetTitle( TString::Format("TagF%03d - TagF%03d[ps]" ,i+1 ,i+2)  );
	}

	for ( int i=0; i<105; i++ ) {    // 1 ch = 100 ps
		th1f_time_tagf_head_cut2[i]  = new TH1F( TString::Format("th1f_time_TagF_head_cut2%03d"  , i+1), "", 4000, -1000000., 3000000. );
		th1f_time_tagf_head_cut2[i] -> GetXaxis() -> SetTitle( "time [ps]" );
	}

	th2f_seg_seg_cor_cut2 = new TH2F("th2f_seg_seg_cor_cut2", "", 106, 0, 106, 31, 0, 31);
	th2f_seg_seg_cor_cut2 -> GetXaxis() -> SetTitle("TagF");
	th2f_seg_seg_cor_cut2 -> GetYaxis() -> SetTitle("TagB");
	th2f_seg_seg_cor_cut2 -> GetZaxis() -> SetTitle("Intensity");

	th2f_seg_seg_cor_cutbf = new TH2F("th2f_seg_seg_cor_cutbf", "", 106, 0, 106, 31, 0, 31);
	th2f_seg_seg_cor_cutbf -> GetXaxis() -> SetTitle("TagF");
	th2f_seg_seg_cor_cutbf -> GetYaxis() -> SetTitle("TagB");
	th2f_seg_seg_cor_cutbf -> GetZaxis() -> SetTitle("Intensity");

	for ( int i=0; i<30; i++ ) {
		for ( int j=0; j<105; j++ ){
			th1f_tof_bf[i][j]  = new TH1F( TString::Format("th1f_tof_TagB%02d_TagF%03d" ,i+1 ,j+1), "", 2000, -1000000., 1000000. );
			th1f_tof_bf[i][j] -> GetXaxis() -> SetTitle( TString::Format("TagB%02d - TagF%03d[ps]" ,i+1 ,j+1)  );
		}
	}

	for ( int i=0; i<105; i++ ) {    // 1 ch = 100 ps
		th1f_time_tagf_head_cutbf[i]  = new TH1F( TString::Format("th1f_time_TagF_head_cutbf%03d"  , i+1), "", 4000, -1000000., 3000000. );
		th1f_time_tagf_head_cutbf[i] -> GetXaxis() -> SetTitle( "time [ps]" );
	}

	Long64_t nbytes = 0, nb = 0;
	for (Long64_t jentry=0; jentry<nentries;jentry++) {
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break;
		nb = fChain->GetEntry(jentry);   nbytes += nb;
		// if (Cut(ientry) < 0) continue;

		Int_t time_tagb[30];
		Int_t width_tagb[30];

		Int_t time_tagf[105];

		Int_t multi_b, multi_b_cut;
		multi_b = 0;//multiplicityの初期値。シグナルが来ていないなら0
		multi_b_cut = 0;

		for ( int i=0; i<30; i++ ) {
			time_tagb[i] = -1;
		}

		for ( int i=0; i<105; i++ ) {
			time_tagf[i] = -1;
		}

		for ( int i=0; i<nhit; i++ ) {
			Int_t itagb = -1;
			Int_t itagf = -1;

			if ( geo[i] == 1 ) {
				if      ( -1 < ch[i] && ch[i] < 15 )  { itagb = ch[i]+1; }
				else if ( 15 < ch[i] && ch[i] < 31 )  { itagb = ch[i];   }

				if ( itagb != -1 ) {
					th1f_time_tagb[itagb-1]  -> Fill( (Float_t)( time[i]) * 25. );

					th2f_width_vs_time_tagb[itagb-1] -> Fill( (Float_t)( time[i]) * 25.,  (Float_t)(width[i]) * 25. );
		
					time_tagb[itagb-1] = (Float_t)( time[i]) * 25. ;
					width_tagb[itagb-1] = (Float_t)(width[i]) * 25. ;
				}
			}

			if ( geo[i] == 0 ) {
				if      ( -1 < ch[i] && ch[i] <  41 ) { itagf = ch[i] +1; }
				else if ( 63 < ch[i] && ch[i] < 128 ) { itagf = ch[i]-22; }

				if ( itagf != -1 ) {
					th1f_time_tagf[itagf-1]  -> Fill( (Float_t)( time[i]) * 100. );

					time_tagf[itagf-1] = (Float_t)( time[i]) * 100.;
				}
			}

		} // end of nhit loop


		//1/9 nhit loopの最後だけをFillした
		for ( int i=0; i<30; i++ ) {
			if ( time_tagb[i] != -1){ //itagbで条件分岐してはいけない。それらはnhitloopで最後まで変化してしまうが、time_tagb[i]は同じiが来ないと塗り替えられない。
				th1f_time_tagb_head[i]  -> Fill( (Float_t)( time_tagb[i]) );//あってる？i=0がTag no.1のはずなんだけど。
				th2f_width_vs_time_tagb_head[i]  -> Fill( time_tagb[i], width_tagb[i] );

				multi_b += 1;
				th1f_distribution_b -> Fill(( Float_t)(i+1));
			}
		}
		th1f_multi_b -> Fill( (Float_t)(multi_b));//for文で0~30まで確かめきったら、たまった数をFill


		for ( int i=0; i<105; i++ ) {
			if ( time_tagf[i] != -1 ){
				th1f_time_tagf_head[i]  -> Fill( (Float_t)( time_tagf[i]) );
				th1f_distribution_f -> Fill( (Float_t)(i+1) );
			}
		}

		for ( int j=0; j<30; j++ ) {
			for ( int k=0; k<105; k++ ) {
				if ( time_tagb[j] != -1 && time_tagf[k] != -1 ){
					th2f_seg_seg_cor -> Fill( (Float_t)(k+1) , (Float_t)(j+1) );
				}
			}
		}//ここでやっているのは、time_tagb[i]という配列とtime_tagf[i]という配列のうち、値が入っている組み(正しくは-1以外)を列挙しているに過ぎない。
		 //本当にやりたいのは、トリガーをかけているTagBorのうち、自分がトリガーになっており、かつその時のTagFのヒットとの相関がシミュレーション通りかを確かめること
		 //ここで注意したいのは、一個前のeventの残留やノイズ、理想的でない散乱が混ざっていること
		 //TagBについてはpeakを切り出すことで解決できる。
		 //TagFについては、TagBに依存して良いか？HULを前提に考えると、TagBとのcoincidenceをとるのが正しそうだ。
		 //↑!!1/16!!いい考え方!!
		 //1/23その次は？LGに到達しているものとの比をとり、tagging efficientを評価する？

		//TagBが自分をtriggerにした条件でcut
		for ( int j=0; j<30; j++ ) {
			Int_t A,B;

			if (j == 0 ){ A = 188800; B = 189200; }
			else if (j == 1 ){ A = 188700; B = 189100; }
			else if (j == 2 ){ A = 188900; B = 189300; }
			else if (j == 3 ){ A = 188800; B = 189200; }
			else if (j == 4 ){ A = 189100; B = 189500; }
			else if (j == 5 ){ A = 189200; B = 189600; }
			else if (j == 6 ){ A = 189100; B = 189700; }
			else if (j == 7 ){ A = 189100; B = 189500; }
			else if (j == 8 ){ A = 187600; B = 188000; }
			else if (j == 9 ){ A = 187900; B = 188300; }
			else if (j == 10 ){ A = 188200; B = 188700; }
			else if (j == 11 ){ A = 188200; B = 188700; }
			else if (j == 12 ){ A = 187600; B = 188000; }
			else if (j == 13 ){ A = 187700; B = 188100; }
			else if (j == 14 ){ A = 187800; B = 188300; }
			else if (j == 15 ){ A = 206600; B = 207000; }
			else if (j == 16 ){ A = 206300; B = 206700; }
			else if (j == 17 ){ A = 206400; B = 206900; }
			else if (j == 18 ){ A = 206500; B = 206900; }
			else if (j == 19 ){ A = 206500; B = 206900; }
			else if (j == 20 ){ A = 206500; B = 206900; }
			else if (j == 21 ){ A = 206300; B = 206700; }
			else if (j == 22 ){ A = 206200; B = 206700; }
			else if (j == 23 ){ A = 205800; B = 206200; }
			else if (j == 24 ){ A = 206000; B = 206500; }
			else if (j == 25 ){ A = 206400; B = 206800; }
			else if (j == 26 ){ A = 206500; B = 207000; }
			else if (j == 27 ){ A = 206000; B = 206400; }
			else if (j == 28 ){ A = 206100; B = 206500; }
			else if (j == 29 ){ A = 206300; B = 206800; }

			if ( A < time_tagb[j] && time_tagb[j] < B ){
				th1f_time_tagb_head_cut[j] -> Fill( (Float_t)( time_tagb[j]) );
				th2f_width_vs_time_tagb_head_cut[j]  -> Fill( time_tagb[j], width_tagb[j] );

				multi_b_cut += 1;//自分をトリガーにしているものだけを残しているのだから1になるはず。

				for ( int k=0; k<105; k++ ) {
					if ( time_tagf[k] != -1 ){
						th2f_seg_seg_cor_cut -> Fill( (Float_t)(k+1) , (Float_t)(j+1) );
					}
				}

				//tof_sbsによるcut
				//TagFにシグナルがあった時、隣にも(ほぼ同時に)シグナルがあった時のみを採用したい。
				//TagF No.2~104の場合、隣は両サイドがあるから、TOF(n - n+1)とTOF(n-1 - n)のどっちかのピークにあれば良い。
				//No.1~105に対してシグナルがあるかどうかを確認する(!= -1)→隣(+1側)にもシグナルがあるか確認する(!= -1)→隣のシグナルがあったら、隣とのTOFがpeak内か確認する(<&&<)→　満たせばそのNo.と＋1のNo.をFill
				//2~104は両サイド確認しないといけないと思ったんだけど、そうすると重複が生じるから上記のようにする。
				for ( int k=0; k<104; k++ ) {
					if ( time_tagf[k] != -1 ){
						if ( time_tagf[k+1] != -1 ){
							Int_t tof_sbs;
							Int_t C,D;

							tof_sbs = time_tagf[k] - time_tagf[k+1];
							th1f_tof_sbs[k] -> Fill(tof_sbs);

							//隣あったTagFに高速の電子が通るのだから、TOFのピークはほぼ0の位置にあるはず。
							//ズレてるやつを探す。23-24, 27-28, 28-29, 32-33, 41-42, 73-74, 
							if (k < 14 ){ C = -20000; D = 20000; }
							else if (k == 14 ){ C = -5000; D = 5000; }
							else if (14 < k && k < 22 ){ C = -20000; D = 20000; }
							else if (k == 22 ){ C = -70000; D = -40000; }
							else if (22 < k && k < 26 ){ C = -20000; D = 20000; }
							else if (k == 26 ){ C = 40000; D = 70000; }
							else if (26 < k && k < 31 ){ C = -20000; D = 20000; }
							else if (k == 31 ){ C = -60000; D = 60000; }//この二組特にNo.33のために大変
							else if (k == 32 ){ C = 0; D = 10000; }//この二組特にNo.33のために大変
							else if (k == 33 ){ C = 0; D = 20000; }
							else if (33 < k && k < 40 ){ C = -20000; D = 20000; }
							else if (k == 40 ){ C = -80000; D = -60000; }
							else if (41 < k && k < 72 ){ C = -20000; D = 20000; }
							else if (k == 72 ){ C = -120000; D = -80000; }
							else if (72 < k && k < 104 ){ C = -20000; D = 20000; }//84-85が悩み

							if( C < tof_sbs && tof_sbs < D ){
								th2f_seg_seg_cor_cut2 -> Fill( (Float_t)(k+1) , (Float_t)(j+1) );
								th2f_seg_seg_cor_cut2 -> Fill( (Float_t)(k+2) , (Float_t)(j+1) );

								th1f_tof_sbs_cut2[k] -> Fill(tof_sbs);

								th1f_time_tagf_head_cut2[k] -> Fill( (Float_t)( time_tagf[k]) );
								th1f_time_tagf_head_cut2[k+1] -> Fill( (Float_t)( time_tagf[k+1]) );
							}
						}
					}
				}

				//TagBに対応するTagFだけを考えるために、EからFまで(k+1するからF-1)に限定
				Int_t E,F;

				if (j == 0 ){ E = 0; F = 2;}
				else if (j == 1 ){ E = 0; F = 3;}
				else if (j == 2 ){ E = 1; F = 4;}
				else if (j == 3 ){ E = 2; F = 5;}
				else if (j == 4 ){ E = 3; F = 6;}
				else if (j == 5 ){ E = 4; F = 8;}
				else if (j == 6 ){ E = 5; F = 9;}
				else if (j == 7 ){ E = 6; F = 11;}
				else if (j == 8 ){ E = 8; F = 12;}
				else if (j == 9 ){ E = 10; F = 14;}
				else if (j == 10 ){ E = 12; F = 16;}
				else if (j == 11 ){ E = 13; F = 18;}
				else if (j == 12 ){ E = 16; F = 21;}
				else if (j == 13 ){ E = 18; F = 23;}
				else if (j == 14 ){ E = 20; F = 26;}
				else if (j == 15 ){ E = 23; F = 29;}
				else if (j == 16 ){ E = 26; F = 33;}
				else if (j == 17 ){ E = 30; F = 36;}
				else if (j == 18 ){ E = 33; F = 40;}
				else if (j == 19 ){ E = 37; F = 44;}
				else if (j == 20 ){ E = 41; F = 49;}
				else if (j == 21 ){ E = 46; F = 54;}
				else if (j == 22 ){ E = 51; F = 59;}
				else if (j == 23 ){ E = 56; F = 65;}
				else if (j == 24 ){ E = 62; F = 71;}
				else if (j == 25 ){ E = 68; F = 77;}
				else if (j == 26 ){ E = 74; F = 84;}
				else if (j == 27 ){ E = 81; F = 91;}
				else if (j == 28 ){ E = 88; F = 98;}
				else if (j == 29 ){ E = 95; F = 105;}

				//TagBに対応するTagFだけを考えるために、EからFまで(k+1するからF-1)に限定
				for ( int k=E; k<F-1; k++ ) {
					if ( time_tagf[k] != -1 ){
						if ( time_tagf[k+1] != -1 ){
							Int_t tof_sbs,tof_bf;
							Int_t C,D;

							//隣あったTagFに高速の電子が通るのだから、TOFのピークはほぼ0の位置にあるはず。
							//ズレてるやつを探す。23-24, 27-28, 28-29, 32-33, 41-42, 73-74, 
							if (k < 14 ){ C = -20000; D = 20000; }
							else if (k == 14 ){ C = -5000; D = 5000; }
							else if (14 < k && k < 22 ){ C = -20000; D = 20000; }
							else if (k == 22 ){ C = -70000; D = -40000; }
							else if (22 < k && k < 26 ){ C = -20000; D = 20000; }
							else if (k == 26 ){ C = 40000; D = 70000; }
							else if (26 < k && k < 31 ){ C = -20000; D = 20000; }
							else if (k == 31 ){ C = -60000; D = 60000; }//この二組特にNo.33のために大変
							else if (k == 32 ){ C = 0; D = 10000; }//この二組特にNo.33のために大変
							else if (k == 33 ){ C = 0; D = 20000; }
							else if (33 < k && k < 40 ){ C = -20000; D = 20000; }
							else if (k == 40 ){ C = -80000; D = -60000; }
							else if (41 < k && k < 72 ){ C = -20000; D = 20000; }
							else if (k == 72 ){ C = -120000; D = -80000; }
							else if (72 < k && k < 104 ){ C = -20000; D = 20000; }//84-85が悩み

							tof_sbs = time_tagf[k] - time_tagf[k+1];
							tof_bf = time_tagb[j] - time_tagf[k];
							if( C < tof_sbs && tof_sbs < D ){
								th2f_seg_seg_cor_cutbf -> Fill( (Float_t)(k+1) , (Float_t)(j+1) );
								th2f_seg_seg_cor_cutbf -> Fill( (Float_t)(k+2) , (Float_t)(j+1) );


								th1f_tof_bf[j][k] -> Fill(tof_bf);
								th1f_time_tagf_head_cutbf[k] -> Fill( (Float_t)( time_tagf[k]) );
								th1f_time_tagf_head_cutbf[k+1] -> Fill( (Float_t)( time_tagf[k+1]) );
							}
						}
					}
				}

			}
		}

		th1f_multi_b_cut -> Fill( (Float_t)(multi_b_cut));


	} // end of jentry loop

	//なんかできちゃった。cut後/cut前の2Dhistを作る
	TH2F* th2f_result = (TH2F*) th2f_seg_seg_cor_cut->Clone("th2f_result");
	th2f_result->Divide(th2f_seg_seg_cor);

	TH2F* th2f_result2 = (TH2F*) th2f_seg_seg_cor_cut2->Clone("th2f_result2");
	th2f_result2->Divide(th2f_seg_seg_cor_cut);

	TH2F* th2f_result3 = (TH2F*) th2f_seg_seg_cor_cutbf->Clone("th2f_result3");
	th2f_result3->Divide(th2f_seg_seg_cor);

	TFile* output = new TFile( output_file_name, "RECREATE" );

	for ( int i=0; i<30; i++ ) {
		th1f_time_tagb[i]  -> Write();
	}

	for ( int i=0; i<30; i++ ) {
		th2f_width_vs_time_tagb[i] -> Write();
	}

	for ( int i=0; i<30; i++ ) {
		th1f_time_tagb_head[i]  -> Write();
	}

	for ( int i=0; i<30; i++ ) {
		th2f_width_vs_time_tagb_head[i] -> Write();
	}

	for ( int i=0; i<30; i++ ) {
		th1f_time_tagb_head_cut[i]  -> Write();
	}

	for ( int i=0; i<30; i++ ) {
		th2f_width_vs_time_tagb_head_cut[i] -> Write();
	}

	th1f_multi_b -> Write();
	th1f_multi_b_cut -> Write();
	th1f_distribution_b ->  Write();

	for ( int i=0; i<105; i++ ) {
		th1f_time_tagf[i] -> Write();
	}

	for ( int i=0; i<105; i++ ) {
		th1f_time_tagf_head[i] -> Write();
	}

	for ( int i=0; i<104; i++ ) {
		th1f_tof_sbs[i] -> Write();
	}

	for ( int i=0; i<104; i++ ) {
		th1f_tof_sbs_cut2[i] -> Write();
	}

	for ( int i=0; i<105; i++ ) {
		th1f_time_tagf_head_cut2[i] -> Write();
	}

	th1f_distribution_f -> Write();

	th2f_seg_seg_cor  -> Write();
	th2f_seg_seg_cor_cut  -> Write();
	th2f_seg_seg_cor_cut2  -> Write();

	th2f_seg_seg_cor_cutbf -> Write();
	
	for ( int j=0; j<30; j++ ) {
		Int_t E,F;

		if (j == 0 ){ E = 0; F = 2;}
		else if (j == 1 ){ E = 0; F = 3;}
		else if (j == 2 ){ E = 1; F = 4;}
		else if (j == 3 ){ E = 2; F = 5;}
		else if (j == 4 ){ E = 3; F = 6;}
		else if (j == 5 ){ E = 4; F = 8;}
		else if (j == 6 ){ E = 5; F = 9;}
		else if (j == 7 ){ E = 6; F = 11;}
		else if (j == 8 ){ E = 8; F = 12;}
		else if (j == 9 ){ E = 10; F = 14;}
		else if (j == 10 ){ E = 12; F = 16;}
		else if (j == 11 ){ E = 13; F = 18;}
		else if (j == 12 ){ E = 16; F = 21;}
		else if (j == 13 ){ E = 18; F = 23;}
		else if (j == 14 ){ E = 20; F = 26;}
		else if (j == 15 ){ E = 23; F = 29;}
		else if (j == 16 ){ E = 26; F = 33;}
		else if (j == 17 ){ E = 30; F = 36;}
		else if (j == 18 ){ E = 33; F = 40;}
		else if (j == 19 ){ E = 37; F = 44;}
		else if (j == 20 ){ E = 41; F = 49;}
		else if (j == 21 ){ E = 46; F = 54;}
		else if (j == 22 ){ E = 51; F = 59;}
		else if (j == 23 ){ E = 56; F = 65;}
		else if (j == 24 ){ E = 62; F = 71;}
		else if (j == 25 ){ E = 68; F = 77;}
		else if (j == 26 ){ E = 74; F = 84;}
		else if (j == 27 ){ E = 81; F = 91;}
		else if (j == 28 ){ E = 88; F = 98;}
		else if (j == 29 ){ E = 95; F = 105;}
		for ( int k=E; k<F-1; k++ ) {
			th1f_tof_bf[j][k]  -> Write();
		}
	}

	for ( int i=0; i<105; i++ ) {
		th1f_time_tagf_head_cutbf[i] -> Write();
	}

	th2f_result -> Write();
	th2f_result2 -> Write();
	th2f_result3 -> Write();

	output -> Close();
}
