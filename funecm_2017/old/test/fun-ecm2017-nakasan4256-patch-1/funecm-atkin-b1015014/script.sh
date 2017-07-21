#!/bin/sh

if [ $# -ne 5 ]; 
then
  echo "[USAGE]sh script.sh number B1 B2 loop output_csv_name"
  exit 1
fi


#合成数
number=$1
B1=$2
B2=$3
#試行回数
loop=$4

#実行時間のCSV
out_file=$5

#funecmを実行する処理
for ((i=1; i <= $loop ;i++))
do
  ./funecm $number $B1 $B2 out$i.txt>/dev/null
done

#out.total.txtの初期化
echo -n "">$out_file

#funecmの出力ファイルからCSVファイルを作成
for ((i=1; i<= $loop ;i++))
do
  echo -n $i,>> $out_file
  cat out$i.txt|grep total|tail -n 1|sed -e 's/[^0-9.]//g' >>$out_file
done

#平均を出力
awk -F, '{sum+=$2}END{print sum}' $out_file
