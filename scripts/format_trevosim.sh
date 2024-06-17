#!/bin/bash

DATA_DIR=../data/TREvoSim_output
SCRIPTS_DIR=$PWD

for file in $DATA_DIR/*.inf
do
  filepref=$(echo $file | rev | cut -d'.' -f2 | cut -d'/' -f1 | rev)
  sed 's/_//g' $file | sed 's/\t/ \t/g' | sed 's/Species[0-9] /& /g' > $DATA_DIR/$filepref.infile 
  rm $file
done

for file in $DATA_DIR/*.nex
do
  filenum=$(echo $file | rev | cut -d'.' -f2 | cut -d'_' -f1 | rev)
  python $SCRIPTS_DIR/nexus_to_intree.py $file > "$DATA_DIR/trevosim_${filenum}.intree"
  rm $file
done

for file in $DATA_DIR/*
do
  filenum=$(echo $file | rev | cut -d'.' -f2 | cut -d'_' -f1 | rev)
  extension=$(echo $file | rev | cut -d'.' -f1 | rev)
  mkdir -p $DATA_DIR/$filenum
  mv $file $DATA_DIR/$filenum/$extension
done

CURR_DIR=$PWD
for folder in $DATA_DIR/*
do
  cd $folder
  echo -ne "U\n2\n6\nY\n" | pars > /dev/null
  grep "requires a total of" outfile | tr -d -c 0-9\. | cut -d'.' -f1 > score
  rm outfile
  cd $CURR_DIR
done
