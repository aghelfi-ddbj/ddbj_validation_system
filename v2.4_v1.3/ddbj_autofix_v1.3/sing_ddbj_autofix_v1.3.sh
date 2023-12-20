cat sing_ddbj_autofix_v1.3.sh 
#!/bin/bash
singularity run --bind .:/data /home/andrea/scripts/ddbj_autofix_v1.3.sif
# Run jParser
if [[ ! -f Rfixed/ERROR_MISSING_ANN_FILES.tsv && ! -f Rfixed/ERROR_MISSING_FASTA_FILES.tsv ]]; then
  echo "Do you like to run jParser and transChecker) (Yes or No)?"
  read answer
  form_ans=`echo ${answer^^}`
  if [ $form_ans = "Y" ] || [ $form_ans = "YES" ]; then
    cd Rfixed
    declare -i len_check_fasta=`ls *.fasta 2> /dev/null | wc -l`
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
    cd ../
  fi
fi
