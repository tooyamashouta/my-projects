#!/bin/csh -f

  set macro_name = ${0}


  if ( $#argv < 1 ) then
    echo ""
    echo "  Usage: ${macro_name} [run number]"
    echo ""
    exit
  endif


  set rn = ${1}

  set run_4d = `printf "%04d" ${rn}`

  set input_root_file_name =  root/make_hist_${run_4d}.root
  set output_pdf_file_name =  pdf/make_hist_${run_4d}.pdf
  
  cd /data/41a/ELS/NKS2/RARiS_beamtest_2024_06

root -b << EOF
.L C/draw_hist.C
draw_hist( "${input_root_file_name}","${output_pdf_file_name}" );
.q
EOF
