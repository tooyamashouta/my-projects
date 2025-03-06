//this is draw_hist_0227 (TagFTDCcomparison)
void draw_hist( const char* input_file_name, const char* pdf_file_name )
{
	gROOT -> Reset();

	TFile* f = new TFile( input_file_name, "READONLY" );

	TH1F* th1f_time_tagf_head[105];
	TH1F* th1f_time_tagf_head_cut2[105];
	TH1F* th1f_time_tagf_head_cutbf[105];


	for ( int i=0; i<105; i++ ) {    // 1 ch = 100 ps
		th1f_time_tagf_head[i]  = (TH1F*) f -> Get( TString::Format("th1f_time_TagF_head%03d"  , i+1) );
	}

	for ( int i=0; i<105; i++ ) {    // 1 ch = 100 ps
		th1f_time_tagf_head_cut2[i]  = (TH1F*) f -> Get( TString::Format("th1f_time_TagF_head_cut2%03d"  , i+1) );
	}

	for ( int i=0; i<105; i++ ) {    // 1 ch = 100 ps
		th1f_time_tagf_head_cutbf[i]  = (TH1F*) f -> Get( TString::Format("th1f_time_TagF_head_cutbf%03d"  , i+1) );
	}


	//---------------------------------------------------
	//                                     pdf1枚の大きさ(ピクセル)を決めてる
	TCanvas* c1 = new TCanvas( "c1", "c1", 1200, 800 );

	c1 -> Divide( 5, 3 );

	TPDF* pdf1 = new TPDF( pdf_file_name, 111 );

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+5] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+5] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+5] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+10] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+10] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+10] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+15] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+15] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+15] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+20] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+20] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+20] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+25] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+25] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+25] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+30] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+30] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+30] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+35] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+35] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+35] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+40] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+40] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+40] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+45] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+45] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+45] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+50] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+50] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+50] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+55] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+55] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+55] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+60] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+60] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+60] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+65] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+65] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+65] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+70] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+70] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+70] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+75] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+75] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+75] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+80] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+80] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+80] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+85] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+85] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+85] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+90] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+90] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+90] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+95] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+95] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+95] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	c1 -> cd();
	pdf1 -> NewPage();

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+1);
		th1f_time_tagf_head[i+100] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+6);
		th1f_time_tagf_head_cut2[i+100] -> Draw("colz");
	}

	for ( int i=0; i<5; i++ ) {
		c1 -> cd(i+11);
		th1f_time_tagf_head_cutbf[i+100] -> Draw("colz");
	}

	c1 -> cd();
	c1 -> Update();

	// ---------

	pdf1 -> Close();

	f -> Close();

}
