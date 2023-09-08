mkdir -p parts

region=testOOT #SR testOOT test OOT

hadd Parking_2018A_${region}_plots.root\
 ParkingBPH1_2018Ato_${region}_plots.root\
 ParkingBPH2_2018Ato_${region}_plots.root\
 ParkingBPH3_2018Ato_${region}_plots.root\
 ParkingBPH4_2018Ato_${region}_plots.root\
 ParkingBPH5_2018Ato_${region}_plots.root\
 ParkingBPH6_2018Ato_${region}_plots.root 

hadd Parking_2018B_${region}_plots.root\
 ParkingBPH1_2018Bto_${region}_plots.root\
 ParkingBPH2_2018Bto_${region}_plots.root\
 ParkingBPH3_2018Bto_${region}_plots.root\
 ParkingBPH4_2018Bto_${region}_plots.root\
 ParkingBPH5_2018Bto_${region}_plots.root\
 ParkingBPH6_2018Bto_${region}_plots.root 

hadd Parking_2018C_${region}_plots.root\
 ParkingBPH1_2018Cto_${region}_plots.root\
 ParkingBPH2_2018Cto_${region}_plots.root\
 ParkingBPH3_2018Cto_${region}_plots.root\
 ParkingBPH4_2018Cto_${region}_plots.root\
 ParkingBPH5_2018Cto_${region}_plots.root


mv ParkingBPH*_2018*to_${region}_plots.root parts/
