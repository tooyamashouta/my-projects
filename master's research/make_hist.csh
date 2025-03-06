#!/bin/csh -f

  set macro_name = ${0}


  if ( $#argv < 1 ) then
    echo ""
    echo "  Usage: ${macro_name} [run number]"
    echo ""
    exit
  endif


  set rn = ${1}

  set run_7d = `printf "%07d" ${rn}`
  set run_4d = `printf "%04d" ${rn}`

  set  ttree_root_file_name = ttree/r${run_7d}.root
  set output_root_file_name =  root/make_hist_${run_4d}.root
  
  cd /data/41a/ELS/NKS2/RARiS_beamtest_2024_06

root -b << EOF
.L C/make_hist.C
TFile* f = new TFile( "${ttree_root_file_name}" );
TTree* tree = (TTree*) f -> Get("tree");
make_hist a(tree);
a.Loop( "${output_root_file_name}" );
.q
EOF
