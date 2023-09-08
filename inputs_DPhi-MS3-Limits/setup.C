void analyzer_config::setConfig(){ // loggit
  genMuonFilterEff = 0.00514; // loggit
  muPt = 7.;                       // loggit
  muEta = 1.5;                     // loggit
  DtSize  = 0.0; //100;                   // loggit
  CscSize = 0.0; //130;                   // loggit
  CscEta = 1.9;                    // loggit
  DtEta = 1.9;                     // loggit
  dr_LeadMu_DtCluster = 0.8;       // loggit
  dr_LeadMu_CscCluster = 0.8;      // loggit
  dr_GenMu_DtCluster = 0.4;        // loggit
  dr_GenMu_CscCluster = 0.4;       // loggit
  DtMuonVetoPt = 20.;              // loggit
  CscMuonVetoPt = 20.;             // loggit
  DtMB1Veto = 1;                   // loggit
  dPhiCut_LeadMu_CscCluster = 1.9; //loggit
  dPhiCut_LeadMu_DtCluster = 1.9;  //loggit
  cscClusterTimeLow = -5.;         // loggit
  cscClusterTimeHigh = 12.5;       // loggit
  cscClusterTimeSpread = 20.;      // loggit
  HLTIndexLow = 1157;              // loggit
  HLTIndexHigh = 1197;             // loggit
}                                  // loggit
//-------- Test-OOT Selections     Fail OOT region                     // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_testOOT(bool passHLT){    // loggit
  std::vector<int> ids;                                                // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                       // loggit
      if(                                                              // loggit
        askDoesPassClusterSize_csc(j)       &&                        // loggit 
        askDoesPassOverlapMuon_csc(j)        &&                        // loggit
        askDoesPassME1112Veto_csc(j)         &&                        // loggit
        askDoesPassMB1Veto_csc(j)            &&                        // loggit
        askDoesPassRB1Veto_csc(j)            &&                        // loggit
        askDoesPassMuonVeto_csc(j)           &&                        // loggit
        !askDoesPassClusterTime_csc(j)       &&                        // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                        // loggit
        askDoesPassID_csc(j)                 &&                        // loggit
        !askDoesPassdPhiLeadMuon_csc(j)      &&                       // loggit
        askDoesPassClusterEta_csc(j)         //&&                      // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                      // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_testOOT(bool passHLT){     // loggit
  std::vector<int> ids;                                                // loggit
  if(!passHLT) return ids;                                             // loggit
  else{                                                                // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                        // loggit
      if(   askDoesPassNominal_dt(j)                                   // loggit
         && !askDoesPassRPCTimeCut_dt(j)                               // loggit
         && !askDoesPassMaxStation_dt(j)                              // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  }                                                                    // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
//-------- Test Selections   Fail in time region                       // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_test(bool passHLT){    // loggit
  std::vector<int> ids;                                                // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                       // loggit
      if(                                                              // loggit
        askDoesPassClusterSize_csc(j)       &&                         // loggit 
        askDoesPassOverlapMuon_csc(j)        &&                        // loggit
        askDoesPassME1112Veto_csc(j)         &&                        // loggit
        askDoesPassMB1Veto_csc(j)            &&                        // loggit
        askDoesPassRB1Veto_csc(j)            &&                        // loggit
        askDoesPassMuonVeto_csc(j)           &&                        // loggit
        askDoesPassClusterTime_csc(j)        &&                        // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                        // loggit
        askDoesPassID_csc(j)                 &&                        // loggit
        !askDoesPassdPhiLeadMuon_csc(j)       &&                       // loggit
        askDoesPassClusterEta_csc(j)         //&&                      // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                      // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_test(bool passHLT){// loggit
  std::vector<int> ids;                                                // loggit
  if(!passHLT) return ids;                                             // loggit
  else{                                                                // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                        // loggit
      if(askDoesPassNominal_dt(j)                                      // loggit
      && askDoesPassRPCTimeCut_dt(j)                                   // loggit 
      && !askDoesPassMaxStation_dt(j)                                 // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  }                                                                    // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
//--------------------- Out of Time Region       Pass OOT region        // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_OOT(bool passHLT){ // loggit
  std::vector<int> ids;                                                 // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                        // loggit
      if(                                                               // loggit
        askDoesPassClusterSize_csc(j)        &&                         // loggit
        askDoesPassOverlapMuon_csc(j)        &&                         // loggit
        askDoesPassME1112Veto_csc(j)         &&                         // loggit
        askDoesPassMB1Veto_csc(j)            &&                         // loggit
        askDoesPassRB1Veto_csc(j)            &&                         // loggit
        askDoesPassMuonVeto_csc(j)           &&                         // loggit
        !askDoesPassClusterTime_csc(j)       &&                         // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                         // loggit
        askDoesPassdPhiLeadMuon_csc(j)       &&                         // loggit
        askDoesPassClusterEta_csc(j)         &&                         // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                         // loggit
        ) ids.push_back(j);      // loggit
    }                                                                   // loggit
  return ids;                                                           // loggit
}                                                                       // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_OOT(bool passHLT){  // loggit
  std::vector<int> ids;                                                 // loggit
  if(!passHLT) return ids;                                              // loggit
  else{                                                                 // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                         // loggit
      if(   askDoesPassNominal_dt(j)                                    // loggit
         && !askDoesPassRPCTimeCut_dt(j)                                // loggit
         && askDoesPassMaxStation_dt(j)                                // loggit
           ) ids.push_back(j);                                          // loggit
    }                                                                   // loggit
  }                                                                     // loggit
  return ids;                                                           // loggit
}                                                                       // loggit
//--------------------------------------------------------- Begin SR    // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_SR(bool passHLT) { // loggit
    std::vector<int> ids;                                               // loggit
    if (!passHLT)                                                       // loggit
        return ids;                                                     // loggit
    else {                                                              // loggit
        for (int j = 0; j < nCscRechitClusters; j++) {                  // loggit
            if (                                                        // loggit
                   askDoesPassClusterSize_csc(j)                        // loggit
                && askDoesPassOverlapMuon_csc(j)                        // loggit
                && askDoesPassME1112Veto_csc(j)                         // loggit
                && askDoesPassMB1Veto_csc(j)                            // loggit
                && askDoesPassRB1Veto_csc(j)                            // loggit
                && askDoesPassMuonVeto_csc(j)                           // loggit
                && askDoesPassClusterTime_csc(j)                        // loggit 
                && askDoesPassClusterTimeSpread_csc(j)                  // loggit
                && askDoesPassdPhiLeadMuon_csc(j)                       // loggit
                && askDoesPassClusterEta_csc(j)                         // loggit
                && askDoesPassID_csc(j)                                 // loggit
                // && askDoesOverlapGenLLP_csc(j)                       // loggit
                ){                                                      // loggit
                    ids.push_back(j);                                   // loggit
            }                                                           // loggit
        }                                                               // loggit
    }                                                                   // loggit
    return ids;                                                         // loggit
}                                                                       // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_SR(bool passHLT) { // loggit
    std::vector<int> ids;                                              // loggit
    if (!passHLT)                                                      // loggit
        return ids;                                                    // loggit
    else {                                                             // loggit
        for (int j = 0; j < nDtRechitClusters; j++) {                  // loggit
            if (askDoesPassNominal_dt(j)                               // loggit
                && askDoesPassRPCTimeCut_dt(j)                         // loggit
                && askDoesPassMaxStation_dt(j)                        // loggit
            )                                                          // loggit
                ids.push_back(j);                                      // loggit
        }                                                              // loggit
    }                                                                  // loggit
    return ids;                                                        // loggit
}                                                                      // loggit
void analyzer_config::setConfig(){ // loggit
  genMuonFilterEff = 0.00514; // loggit
  muPt = 7.;                       // loggit
  muEta = 1.5;                     // loggit
  DtSize  = 0.0; //100;                   // loggit
  CscSize = 0.0; //130;                   // loggit
  CscEta = 1.9;                    // loggit
  DtEta = 1.9;                     // loggit
  dr_LeadMu_DtCluster = 0.8;       // loggit
  dr_LeadMu_CscCluster = 0.8;      // loggit
  dr_GenMu_DtCluster = 0.4;        // loggit
  dr_GenMu_CscCluster = 0.4;       // loggit
  DtMuonVetoPt = 20.;              // loggit
  CscMuonVetoPt = 20.;             // loggit
  DtMB1Veto = 1;                   // loggit
  dPhiCut_LeadMu_CscCluster = 1.9; //loggit
  dPhiCut_LeadMu_DtCluster = 1.9;  //loggit
  cscClusterTimeLow = -5.;         // loggit
  cscClusterTimeHigh = 12.5;       // loggit
  cscClusterTimeSpread = 20.;      // loggit
  HLTIndexLow = 1157;              // loggit
  HLTIndexHigh = 1197;             // loggit
}                                  // loggit
//-------- Test-OOT Selections     Fail OOT region                     // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_testOOT(bool passHLT){    // loggit
  std::vector<int> ids;                                                // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                       // loggit
      if(                                                              // loggit
        askDoesPassClusterSize_csc(j)       &&                        // loggit 
        askDoesPassOverlapMuon_csc(j)        &&                        // loggit
        askDoesPassME1112Veto_csc(j)         &&                        // loggit
        askDoesPassMB1Veto_csc(j)            &&                        // loggit
        askDoesPassRB1Veto_csc(j)            &&                        // loggit
        askDoesPassMuonVeto_csc(j)           &&                        // loggit
        !askDoesPassClusterTime_csc(j)       &&                        // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                        // loggit
        askDoesPassID_csc(j)                 &&                        // loggit
        !askDoesPassdPhiLeadMuon_csc(j)      &&                       // loggit
        askDoesPassClusterEta_csc(j)         //&&                      // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                      // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_testOOT(bool passHLT){     // loggit
  std::vector<int> ids;                                                // loggit
  if(!passHLT) return ids;                                             // loggit
  else{                                                                // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                        // loggit
      if(   askDoesPassNominal_dt(j)                                   // loggit
         && !askDoesPassRPCTimeCut_dt(j)                               // loggit
         && !askDoesPassMaxStation_dt(j)                              // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  }                                                                    // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
//-------- Test Selections   Fail in time region                       // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_test(bool passHLT){    // loggit
  std::vector<int> ids;                                                // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                       // loggit
      if(                                                              // loggit
        askDoesPassClusterSize_csc(j)       &&                         // loggit 
        askDoesPassOverlapMuon_csc(j)        &&                        // loggit
        askDoesPassME1112Veto_csc(j)         &&                        // loggit
        askDoesPassMB1Veto_csc(j)            &&                        // loggit
        askDoesPassRB1Veto_csc(j)            &&                        // loggit
        askDoesPassMuonVeto_csc(j)           &&                        // loggit
        askDoesPassClusterTime_csc(j)        &&                        // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                        // loggit
        askDoesPassID_csc(j)                 &&                        // loggit
        !askDoesPassdPhiLeadMuon_csc(j)       &&                       // loggit
        askDoesPassClusterEta_csc(j)         //&&                      // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                      // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_test(bool passHLT){// loggit
  std::vector<int> ids;                                                // loggit
  if(!passHLT) return ids;                                             // loggit
  else{                                                                // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                        // loggit
      if(askDoesPassNominal_dt(j)                                      // loggit
      && askDoesPassRPCTimeCut_dt(j)                                   // loggit 
      && !askDoesPassMaxStation_dt(j)                                 // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  }                                                                    // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
//--------------------- Out of Time Region       Pass OOT region        // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_OOT(bool passHLT){ // loggit
  std::vector<int> ids;                                                 // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                        // loggit
      if(                                                               // loggit
        askDoesPassClusterSize_csc(j)        &&                         // loggit
        askDoesPassOverlapMuon_csc(j)        &&                         // loggit
        askDoesPassME1112Veto_csc(j)         &&                         // loggit
        askDoesPassMB1Veto_csc(j)            &&                         // loggit
        askDoesPassRB1Veto_csc(j)            &&                         // loggit
        askDoesPassMuonVeto_csc(j)           &&                         // loggit
        !askDoesPassClusterTime_csc(j)       &&                         // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                         // loggit
        askDoesPassdPhiLeadMuon_csc(j)       &&                         // loggit
        askDoesPassClusterEta_csc(j)         &&                         // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                         // loggit
        ) ids.push_back(j);      // loggit
    }                                                                   // loggit
  return ids;                                                           // loggit
}                                                                       // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_OOT(bool passHLT){  // loggit
  std::vector<int> ids;                                                 // loggit
  if(!passHLT) return ids;                                              // loggit
  else{                                                                 // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                         // loggit
      if(   askDoesPassNominal_dt(j)                                    // loggit
         && !askDoesPassRPCTimeCut_dt(j)                                // loggit
         && askDoesPassMaxStation_dt(j)                                // loggit
           ) ids.push_back(j);                                          // loggit
    }                                                                   // loggit
  }                                                                     // loggit
  return ids;                                                           // loggit
}                                                                       // loggit
//--------------------------------------------------------- Begin SR    // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_SR(bool passHLT) { // loggit
    std::vector<int> ids;                                               // loggit
    if (!passHLT)                                                       // loggit
        return ids;                                                     // loggit
    else {                                                              // loggit
        for (int j = 0; j < nCscRechitClusters; j++) {                  // loggit
            if (                                                        // loggit
                   askDoesPassClusterSize_csc(j)                        // loggit
                && askDoesPassOverlapMuon_csc(j)                        // loggit
                && askDoesPassME1112Veto_csc(j)                         // loggit
                && askDoesPassMB1Veto_csc(j)                            // loggit
                && askDoesPassRB1Veto_csc(j)                            // loggit
                && askDoesPassMuonVeto_csc(j)                           // loggit
                && askDoesPassClusterTime_csc(j)                        // loggit 
                && askDoesPassClusterTimeSpread_csc(j)                  // loggit
                && askDoesPassdPhiLeadMuon_csc(j)                       // loggit
                && askDoesPassClusterEta_csc(j)                         // loggit
                && askDoesPassID_csc(j)                                 // loggit
                // && askDoesOverlapGenLLP_csc(j)                       // loggit
                ){                                                      // loggit
                    ids.push_back(j);                                   // loggit
            }                                                           // loggit
        }                                                               // loggit
    }                                                                   // loggit
    return ids;                                                         // loggit
}                                                                       // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_SR(bool passHLT) { // loggit
    std::vector<int> ids;                                              // loggit
    if (!passHLT)                                                      // loggit
        return ids;                                                    // loggit
    else {                                                             // loggit
        for (int j = 0; j < nDtRechitClusters; j++) {                  // loggit
            if (askDoesPassNominal_dt(j)                               // loggit
                && askDoesPassRPCTimeCut_dt(j)                         // loggit
                && askDoesPassMaxStation_dt(j)                        // loggit
            )                                                          // loggit
                ids.push_back(j);                                      // loggit
        }                                                              // loggit
    }                                                                  // loggit
    return ids;                                                        // loggit
}                                                                      // loggit
void analyzer_config::setConfig(){ // loggit
  genMuonFilterEff = 0.00514; // loggit
  muPt = 7.;                       // loggit
  muEta = 1.5;                     // loggit
  DtSize  = 0.0; //100;                   // loggit
  CscSize = 0.0; //130;                   // loggit
  CscEta = 1.9;                    // loggit
  DtEta = 1.9;                     // loggit
  dr_LeadMu_DtCluster = 0.8;       // loggit
  dr_LeadMu_CscCluster = 0.8;      // loggit
  dr_GenMu_DtCluster = 0.4;        // loggit
  dr_GenMu_CscCluster = 0.4;       // loggit
  DtMuonVetoPt = 20.;              // loggit
  CscMuonVetoPt = 20.;             // loggit
  DtMB1Veto = 1;                   // loggit
  dPhiCut_LeadMu_CscCluster = 1.9; //loggit
  dPhiCut_LeadMu_DtCluster = 1.9;  //loggit
  cscClusterTimeLow = -5.;         // loggit
  cscClusterTimeHigh = 12.5;       // loggit
  cscClusterTimeSpread = 20.;      // loggit
  HLTIndexLow = 1157;              // loggit
  HLTIndexHigh = 1197;             // loggit
}                                  // loggit
//-------- Test-OOT Selections     Fail OOT region                     // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_testOOT(bool passHLT){    // loggit
  std::vector<int> ids;                                                // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                       // loggit
      if(                                                              // loggit
        askDoesPassClusterSize_csc(j)       &&                        // loggit 
        askDoesPassOverlapMuon_csc(j)        &&                        // loggit
        askDoesPassME1112Veto_csc(j)         &&                        // loggit
        askDoesPassMB1Veto_csc(j)            &&                        // loggit
        askDoesPassRB1Veto_csc(j)            &&                        // loggit
        askDoesPassMuonVeto_csc(j)           &&                        // loggit
        !askDoesPassClusterTime_csc(j)       &&                        // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                        // loggit
        askDoesPassID_csc(j)                 &&                        // loggit
        !askDoesPassdPhiLeadMuon_csc(j)      &&                       // loggit
        askDoesPassClusterEta_csc(j)         //&&                      // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                      // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_testOOT(bool passHLT){     // loggit
  std::vector<int> ids;                                                // loggit
  if(!passHLT) return ids;                                             // loggit
  else{                                                                // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                        // loggit
      if(   askDoesPassNominal_dt(j)                                   // loggit
         && !askDoesPassRPCTimeCut_dt(j)                               // loggit
         && !askDoesPassMaxStation_dt(j)                              // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  }                                                                    // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
//-------- Test Selections   Fail in time region                       // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_test(bool passHLT){    // loggit
  std::vector<int> ids;                                                // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                       // loggit
      if(                                                              // loggit
        askDoesPassClusterSize_csc(j)       &&                         // loggit 
        askDoesPassOverlapMuon_csc(j)        &&                        // loggit
        askDoesPassME1112Veto_csc(j)         &&                        // loggit
        askDoesPassMB1Veto_csc(j)            &&                        // loggit
        askDoesPassRB1Veto_csc(j)            &&                        // loggit
        askDoesPassMuonVeto_csc(j)           &&                        // loggit
        askDoesPassClusterTime_csc(j)        &&                        // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                        // loggit
        askDoesPassID_csc(j)                 &&                        // loggit
        !askDoesPassdPhiLeadMuon_csc(j)       &&                       // loggit
        askDoesPassClusterEta_csc(j)         //&&                      // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                      // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_test(bool passHLT){// loggit
  std::vector<int> ids;                                                // loggit
  if(!passHLT) return ids;                                             // loggit
  else{                                                                // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                        // loggit
      if(askDoesPassNominal_dt(j)                                      // loggit
      && askDoesPassRPCTimeCut_dt(j)                                   // loggit 
      && !askDoesPassMaxStation_dt(j)                                 // loggit
        ) ids.push_back(j);                                            // loggit
    }                                                                  // loggit
  }                                                                    // loggit
  return ids;                                                          // loggit
}                                                                      // loggit
//--------------------- Out of Time Region       Pass OOT region        // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_OOT(bool passHLT){ // loggit
  std::vector<int> ids;                                                 // loggit
    for (int j = 0; j <nCscRechitClusters; j++){                        // loggit
      if(                                                               // loggit
        askDoesPassClusterSize_csc(j)        &&                         // loggit
        askDoesPassOverlapMuon_csc(j)        &&                         // loggit
        askDoesPassME1112Veto_csc(j)         &&                         // loggit
        askDoesPassMB1Veto_csc(j)            &&                         // loggit
        askDoesPassRB1Veto_csc(j)            &&                         // loggit
        askDoesPassMuonVeto_csc(j)           &&                         // loggit
        !askDoesPassClusterTime_csc(j)       &&                         // loggit
        askDoesPassClusterTimeSpread_csc(j)  &&                         // loggit
        askDoesPassdPhiLeadMuon_csc(j)       &&                         // loggit
        askDoesPassClusterEta_csc(j)         &&                         // loggit
        //askDoesOverlapGenLLP_csc(j)          &&                         // loggit
        ) ids.push_back(j);      // loggit
    }                                                                   // loggit
  return ids;                                                           // loggit
}                                                                       // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_OOT(bool passHLT){  // loggit
  std::vector<int> ids;                                                 // loggit
  if(!passHLT) return ids;                                              // loggit
  else{                                                                 // loggit
    for (int j = 0; j <nDtRechitClusters; j++){                         // loggit
      if(   askDoesPassNominal_dt(j)                                    // loggit
         && !askDoesPassRPCTimeCut_dt(j)                                // loggit
         && askDoesPassMaxStation_dt(j)                                // loggit
           ) ids.push_back(j);                                          // loggit
    }                                                                   // loggit
  }                                                                     // loggit
  return ids;                                                           // loggit
}                                                                       // loggit
//--------------------------------------------------------- Begin SR    // loggit
std::vector<int> analyzer_objects::CscClusterPassSel_SR(bool passHLT) { // loggit
    std::vector<int> ids;                                               // loggit
    if (!passHLT)                                                       // loggit
        return ids;                                                     // loggit
    else {                                                              // loggit
        for (int j = 0; j < nCscRechitClusters; j++) {                  // loggit
            if (                                                        // loggit
                   askDoesPassClusterSize_csc(j)                        // loggit
                && askDoesPassOverlapMuon_csc(j)                        // loggit
                && askDoesPassME1112Veto_csc(j)                         // loggit
                && askDoesPassMB1Veto_csc(j)                            // loggit
                && askDoesPassRB1Veto_csc(j)                            // loggit
                && askDoesPassMuonVeto_csc(j)                           // loggit
                && askDoesPassClusterTime_csc(j)                        // loggit 
                && askDoesPassClusterTimeSpread_csc(j)                  // loggit
                && askDoesPassdPhiLeadMuon_csc(j)                       // loggit
                && askDoesPassClusterEta_csc(j)                         // loggit
                && askDoesPassID_csc(j)                                 // loggit
                // && askDoesOverlapGenLLP_csc(j)                       // loggit
                ){                                                      // loggit
                    ids.push_back(j);                                   // loggit
            }                                                           // loggit
        }                                                               // loggit
    }                                                                   // loggit
    return ids;                                                         // loggit
}                                                                       // loggit
std::vector<int> analyzer_objects::DtClusterPassSel_SR(bool passHLT) { // loggit
    std::vector<int> ids;                                              // loggit
    if (!passHLT)                                                      // loggit
        return ids;                                                    // loggit
    else {                                                             // loggit
        for (int j = 0; j < nDtRechitClusters; j++) {                  // loggit
            if (askDoesPassNominal_dt(j)                               // loggit
                && askDoesPassRPCTimeCut_dt(j)                         // loggit
                && askDoesPassMaxStation_dt(j)                        // loggit
            )                                                          // loggit
                ids.push_back(j);                                      // loggit
        }                                                              // loggit
    }                                                                  // loggit
    return ids;                                                        // loggit
}                                                                      // loggit
