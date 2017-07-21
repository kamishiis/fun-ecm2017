#!/bin/sh

if [ $# -ne 1 ]; 
then
  echo "[USAGE]sh script.sh number.csv"
  exit 1
fi

#csvファイルの行数をloopへ
loop=$(awk 'END{print NR}' $1)

rm -rf $HOME/funecm_2017/main/out*
rm -rf $HOME/funecm_2017/2016/out*

#csvファイルを一行ずつ処理
for line in $(cat $1)
do
  #csvファイルの1列目をdigitに代入．number,B1,B2も同様
  digit=$(echo $line|awk -F, '{print $1}')
  number=$(echo $line|awk -F, '{print $4}')
  B1=$(echo $line|awk -F, '{print $5}')
  B2=$(echo $line|awk -F, '{print $6}')

  #処理する桁数，合成数，B1，B2を表示
  echo  digit : $digit  number : $number  B1 : $B1 B2 : $B2

  #2017年度のプログラムを実行する．
  $HOME/funecm_2017/main/funecm -a $number $B1 $B2 $HOME/funecm_2017/main/out.$digit.$number.txt>/dev/null
  #funecmの出力ファイルから処理時間を抽出
  time=$(cat $HOME/funecm_2017/main/out.$digit.$number.txt|grep total|tail -n 1|sed -e 's/[^0-9.]//g')
  #処理時間表示
  echo 2017time : $time
  #処理時間を桁数に応じたファイルに保存
  echo "$number,$time">>$HOME/funecm_2017/main/out.$digit.txt

  #2016年度のプログラムを実行する.
  $HOME/funecm_2017/2016/funecm -a $number $B1 $B2 $HOME/funecm_2017/2016/out.$digit.$number.txt>/dev/null
  #funecmの出力ファイルから処理時間を抽出
  time=$(cat $HOME/funecm_2017/2016/out.$digit.$number.txt|grep total|tail -n 1|sed -e 's/[^0-9.]//g')
  #処理時間を表示
  echo 2016time : $time
  #処理時間を桁数に応じたファイルに保存
  echo "$number,$time">>$HOME/funecm_2017/2016/out.$digit.txt
done

for ((i=20;i<=50; i+=5))
do
  echo -n 2017 digit : $i  average : 
  awk -F, '{sum+=$2}END{print sum/NR}' $HOME/funecm_2017/main/out.$i.txt
  echo -n 2016 digit : $i  average :
  awk -F, '{sum+=$2}END{print sum/NR}' $HOME/funecm_2017/2016/out.$i.txt
done

