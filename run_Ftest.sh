#Example files are here: /uscms/home/guerrero/nobackup/Run2/VLLAnalysis/CMSSW_10_2_13/src/combine-llp/

#CSC OOT model
python runFtest.py -n 7  --v1n1=0 --v1n2=1 --toys=1000 -s 1 --ifile histos_cscmodel_ootime.root

#DT OOT model
#python runFtest.py -n 7  --v1n1=0 --v1n2=1 --toys=1000 -s 1 --ifile histos_dtmodel_ootime.root