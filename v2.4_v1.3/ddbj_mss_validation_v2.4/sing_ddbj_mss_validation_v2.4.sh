 cat ddbj_mss_validation_beta
# supercom:/home/andrea/scripts/sing_ddbj_mss_validation
#!/bin/bash
nohup singularity run --bind .:/data,/home/andrea/scripts/tables:/srv /home/andrea/scripts/ddbj_mss_validation_v2.4.sif </dev/null &>sing_ddbj_mss_validation.log &
sing_ddbj_mss=$!
echo "singularity PID: "${sing_ddbj_mss}
echo "Running format_ann_file, mss_validation, SVP, and common_check."
wait ${sing_ddbj_mss}
# Run jParser
if [[ ! -f Rfixed/ERROR_MISSING_ANN_FILES.tsv && ! -f Rfixed/ERROR_MISSING_FASTA_FILES.tsv ]]; then
  hostname=`cat /proc/sys/kernel/hostname`
  declare -i len_check_fasta=`ls *.fasta 2> /dev/null | wc -l`
  echo "Started jParser and transChecker, please wait ..."
  if [ $len_check_fasta -gt 0 ]; then
    jParser="/home/andrea/scripts/ag_jParser_transChecker.sh"
    nohup sh ${jParser} </dev/null &>jParser_transChecker.log &
    jParser_pid=$!
    echo "jParser_transChecker PID: "${jParser_pid}
  fi
  wait ${jParser_pid}
  # Read output of transChecker and jParser
  check_errors="/home/andrea/scripts/check_output_jParser_transChecker.sh"
  sh ${check_errors}
fi
rm -f check_filesize.txt
chmod -Rf 775 out_jParser/ out_tranChecker/ temp_autofix/ temp_svp/ Rfixed/
chmod -f 664 out_jParser/* out_tranChecker/* temp_autofix/* temp_svp/* Rfixed/* *.ann *.fasta all_jParser.txt all_tranChecker.txt jParser_transChecker.log sing_ddbj_mss_validation.log
chgrp -Rf mass-adm *
