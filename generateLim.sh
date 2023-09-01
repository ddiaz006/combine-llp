region=csc
outDir=Lim_OOT_${region}

model=SigPi0
#model=SigPiPlusPiMinus

inputs=inputs_DPhi-MS3-Limits/inputs_${region}_${model}_M0p3_OOT.root

#rm -rf $outDir
mkdir -p $outDir
rm -f out.txt
rm -f names.txt
touch out.txt
touch names.txt

sig=( \
  ${model}_M0p3_ctau1 \
  ${model}_M0p3_ctau3 \
  ${model}_M0p3_ctau5 \
  ${model}_M0p3_ctau7 \
  ${model}_M0p3_ctau10 \
  ${model}_M0p3_ctau30 \
  ${model}_M0p3_ctau50 \
  ${model}_M0p3_ctau70 \
  ${model}_M0p3_ctau100 \
  ${model}_M0p3_ctau300 \
  ${model}_M0p3_ctau500 \
  ${model}_M0p3_ctau700 \
  ${model}_M0p3_ctau1000 \
  ${model}_M0p3_ctau3000 \
  ${model}_M0p3_ctau5000 \
  ${model}_M0p3_ctau10000 \
)

for s in ${sig[@]}
do
  echo $s >> names.txt
  mkdir -p $outDir/$s
  echo python create_datacard_bp.py --nbins=18 --carddir=$outDir/$s --sig=$s --passBinName=Bin1 --inputfile=$inputs
  python create_datacard_bp.py --nbins=18 --carddir=$outDir/$s --sig=$s --passBinName=Bin1 --inputfile=$inputs
  cd $outDir/$s/BPModel/
  combineCards.py pass=SRBin1.txt fail=fitfail.txt > BPModel_combined.txt; text2workspace.py BPModel_combined.txt ;
  #combine -M AsymptoticLimits Lim_csc/$s/BPModel/BPModel_combined.root  --rMin 0 --rMax 1 | grep "Expected 50"  >> out.txt 
  combine -M AsymptoticLimits --run expected BPModel_combined.root  --rMin 0 --rMax 1
  cd -
done

#awk '{print 100000000*(1./5.72E11)*$5}' out.txt >tmp.txt
#paste names.txt tmp.txt >lim.txt

