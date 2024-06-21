#!/bin/bash

DATA_DIR=../data
SCRIPTS_DIR=$PWD
GASPAR_EXEC=/home/user/Git-Projects/gaspar/gaspar

function generate_results() {
  echo -ne "${1}\nC\n1\n2\n3\nY\n" | consense > /dev/null
  rm outfile
  mv outtree result.tre

  cat result.tre correct.tre > intree
  echo -ne "C\n1\n2\n3\nY\n" | consense > /dev/null
  rm outfile
  mv outtree cfi.tre
  rm intree

  python $SCRIPTS_DIR/accuracy_and_precision.py >> final.dat
}

for experiment in $DATA_DIR/*
do
  EXP_NAME=$(echo $experiment | rev | cut -d'/' -f1 | rev)
  echo "Experiment $EXP_NAME"
  
  for repl in $experiment/*
  do
    cd $repl
    REPL_NAME=$(echo $repl | rev | cut -d'/' -f1 | rev)
    echo -e "\tReplicate $REPL_NAME"

    $GASPAR_EXEC gas

    for tree in *.intree
    do
      ANALYSIS_NAME=$(echo $tree | rev | cut -d'/' -f1 | rev | cut -d'.' -f1)
      echo -e "\t\tAnalysis $ANALYSIS_NAME"
      echo $ANALYSIS_NAME >> final.dat
      
      generate_results "$tree\nC"

      python $SCRIPTS_DIR/mrc_to_strict.py $tree > strict.intree
      generate_results strict.intree

      head -n2 ${ANALYSIS_NAME}.dat >> final.dat
    done
    rm strict.intree

    cd $SCRIPTS_DIR
  done
done
