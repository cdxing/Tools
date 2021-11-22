#!/bin/bash
for((i=0;i<20;i++))
do
#rm -rf PhiMesonAna_OUTPUT_sys_primary_var0_iter3_099CFA8E8D76DEF4CABB57C5DB2706D2_${i}.root
for((j=0;j<40;j++))
do
k=$((i+20*j))
echo $k

if [ $j -eq 0 ]
then
touch hist_Samplex.root
fi

hadd  PhiMesonAna_OUTPUT_sys_primary_var0_iter3_099CFA8E8D76DEF4CABB57C5DB2706D2_${i}.root  PhiMesonAna_OUTPUT_sys_primary_var0_iter3_099CFA8E8D76DEF4CABB57C5DB2706D2_${k}* hist_Samplex.root

if [ $j -lt 39 ]
then
mv PhiMesonAna_OUTPUT_sys_primary_var0_iter3_099CFA8E8D76DEF4CABB57C5DB2706D2_${i}.root hist_Samplex.root
fi

if [ $j -eq 39 ]
then
mv PhiMesonAna_OUTPUT_sys_primary_var0_iter3_099CFA8E8D76DEF4CABB57C5DB2706D2_${i}.root hist_Sample_test${i}.root
rm -f hist_Samplex.root
fi

done
done

#rm -rf PhiMesonAna_OUTPUT_sys_primary_var0_iter3_099CFA8E8D76DEF4CABB57C5DB2706D2_*Job*.root

rm -rf hist_All.root
