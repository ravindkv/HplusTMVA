
TString inFile("$PWD/");
TString inFile_HiggsBkg("$PWD/higgsBkg_eleChannel/");
TString histPath(histSubDir+histName);
TFile *wh80 	  		= new TFile(inFile+"all_Hplus80.root"); 
TFile *wh90 	  		= new TFile(inFile+"all_Hplus90.root"); 
TFile *wh100 	  		= new TFile(inFile+"all_Hplus100.root"); 
TFile *wh120 	  		= new TFile(inFile+"all_Hplus120.root"); 
TFile *wh140 	  		= new TFile(inFile+"all_Hplus140.root"); 
TFile *wh150 	  		= new TFile(inFile+"all_Hplus150.root"); 
TFile *wh155 	  		= new TFile(inFile+"all_Hplus155.root"); 
TFile *wh160 	  		= new TFile(inFile+"all_Hplus160.root"); 

TFile *ttbar    		= new TFile(inFile+"all_TTJetsP.root"); 
TFile *wjet  			= new TFile(inFile+"all_WJets.root"); 
TFile *zjet  			= new TFile(inFile+"all_DY.root");
TFile *qcd  			= new TFile(inFile+"all_QCD.root");
TFile *stop  			= new TFile(inFile+"all_ST.root");
TFile *vv 		= new TFile(inFile+"all_VV.root");

TFile *data = new TFile(inFile+"all_EleData.root");
//TFile *data = new TFile(inFile+"all_muData.root");

//Files
//Gluon gluon fusion                //Gluon gluon fusion                                      
TFile* GluGluHToBB                  =  new TFile(inFile_HiggsBkg+"all_GluGluHToBB.root");           
TFile* GluGluHToTauTau              =  new TFile(inFile_HiggsBkg+"all_GluGluHToTauTau.root");       
TFile* GluGluHToCC                  =  new TFile(inFile_HiggsBkg+"all_GluGluHToCC.root");           
TFile* GluGluHToGG                  =  new TFile(inFile_HiggsBkg+"all_GluGluHToGG.root");           
TFile* GluGluHToWWTo2L2Nu           =  new TFile(inFile_HiggsBkg+"all_GluGluHToWWTo2L2Nu.root");    
TFile* GluGluHToWWToLNuQQ           =  new TFile(inFile_HiggsBkg+"all_GluGluHToWWToLNuQQ.root");    
TFile* GluGluHToZZTo2L2Q            =  new TFile(inFile_HiggsBkg+"all_GluGluHToZZTo2L2Q.root");     
TFile* GluGluHToZZTo4L              =  new TFile(inFile_HiggsBkg+"all_GluGluHToZZTo4L.root");       
//W+H production                    //W+H production
TFile* WplusH_HToBB_WToLNu          =  new TFile(inFile_HiggsBkg+"all_WplusH_HToBB_WToLNu.root");   
TFile* WplusH_HToBB_WToQQ           =  new TFile(inFile_HiggsBkg+"all_WplusH_HToBB_WToQQ.root");    
TFile* WplusHToTauTau               =  new TFile(inFile_HiggsBkg+"all_WplusHToTauTau.root");        
TFile* WplusH_HToCC_WToLNu          =  new TFile(inFile_HiggsBkg+"all_WplusH_HToCC_WToLNu.root");   
TFile* WplusH_HToCC_WToQQ           =  new TFile(inFile_HiggsBkg+"all_WplusH_HToCC_WToQQ.root");    
TFile* WplusH_HToGG_WToAll          =  new TFile(inFile_HiggsBkg+"all_WplusH_HToGG_WToAll.root");   
//W-H production                    //W-H production
TFile* WminusH_HToBB_WToQQ          =  new TFile(inFile_HiggsBkg+"all_WminusH_HToBB_WToQQ.root");   
TFile* WminusHToTauTau              =  new TFile(inFile_HiggsBkg+"all_WminusHToTauTau.root");       
TFile* WminusH_HToCC_WToLNu         =  new TFile(inFile_HiggsBkg+"all_WminusH_HToCC_WToLNu.root");  
TFile* WminusH_HToCC_WToQQ          =  new TFile(inFile_HiggsBkg+"all_WminusH_HToCC_WToQQ.root");   
TFile* WminusH_HToGG_WToAll         =  new TFile(inFile_HiggsBkg+"all_WminusH_HToGG_WToAll.root");  
TFile* WminusH_HToZZTo2L2X          =  new TFile(inFile_HiggsBkg+"all_WminusH_HToZZTo2L2X.root");   
//ZH production                     //ZH production
TFile* ZH_HToBB_ZToNuNu             =  new TFile(inFile_HiggsBkg+"all_ZH_HToBB_ZToNuNu.root");      
TFile* ZH_HToBB_ZToLL               =  new TFile(inFile_HiggsBkg+"all_ZH_HToBB_ZToLL.root");        
TFile* ZH_HToBB_ZToQQ               =  new TFile(inFile_HiggsBkg+"all_ZH_HToBB_ZToQQ.root");        
TFile* ZHToTauTau                   =  new TFile(inFile_HiggsBkg+"all_ZHToTauTau.root");            
TFile* ZH_HToCC_ZToNuNu             =  new TFile(inFile_HiggsBkg+"all_ZH_HToCC_ZToNuNu.root");      
TFile* ZH_HToCC_ZToLL               =  new TFile(inFile_HiggsBkg+"all_ZH_HToCC_ZToLL.root");        
TFile* ZH_HToCC_ZToQQ               =  new TFile(inFile_HiggsBkg+"all_ZH_HToCC_ZToQQ.root");        
TFile* ZH_HToGG_ZToAll              =  new TFile(inFile_HiggsBkg+"all_ZH_HToGG_ZToAll.root");       
TFile* ZH_HToZZ_2L                  =  new TFile(inFile_HiggsBkg+"all_ZH_HToZZ_2L.root");           
//gg fusion to ZH                   //gg fusion to ZH
TFile* ggZH_HToBB_ZToNuNu           =  new TFile(inFile_HiggsBkg+"all_ggZH_HToBB_ZToNuNu.root");    
TFile* ggZH_HToBB_ZToLL             =  new TFile(inFile_HiggsBkg+"all_ggZH_HToBB_ZToLL.root");      
TFile* ggZH_HToBB_ZToQQ             =  new TFile(inFile_HiggsBkg+"all_ggZH_HToBB_ZToQQ.root");      
TFile* ggZH_HToCC_ZToNuNu           =  new TFile(inFile_HiggsBkg+"all_ggZH_HToCC_ZToNuNu.root");    
TFile* ggZH_HToCC_ZToLL             =  new TFile(inFile_HiggsBkg+"all_ggZH_HToCC_ZToLL.root");      
TFile* ggZH_HToCC_ZToQQ             =  new TFile(inFile_HiggsBkg+"all_ggZH_HToCC_ZToQQ.root");      
TFile* GluGluZH_HToWW               =  new TFile(inFile_HiggsBkg+"all_GluGluZH_HToWW.root");        
//tt fusion                         //tt fusion
TFile* ttHToCC                      =  new TFile(inFile_HiggsBkg+"all_ttHToCC.root");               
TFile* ttHToGG                      =  new TFile(inFile_HiggsBkg+"all_ttHToGG.root");               
//bb fusion                         //bb fusion
TFile* bbHToBB                      =  new TFile(inFile_HiggsBkg+"all_bbHToBB.root");               
TFile* bbHToGG                      =  new TFile(inFile_HiggsBkg+"all_bbHToGG.root");               
TFile* bbHToWWTo2L2Nu               =  new TFile(inFile_HiggsBkg+"all_bbHToWWTo2L2Nu.root");        
TFile* bbH_HToZZTo4L                =  new TFile(inFile_HiggsBkg+"all_bbH_HToZZTo4L.root");         
//vector boson fustion              //vector boson fustion
TFile* VBFHToBB                     =  new TFile(inFile_HiggsBkg+"all_VBFHToBB.root");              
TFile* VBFHToTauTau                 =  new TFile(inFile_HiggsBkg+"all_VBFHToTauTau.root");          
TFile* VBFHToCC                     =  new TFile(inFile_HiggsBkg+"all_VBFHToCC.root");              
TFile* VBFHToGG                     =  new TFile(inFile_HiggsBkg+"all_VBFHToGG.root");              
TFile* VBFHToWWTo2L2Nu              =  new TFile(inFile_HiggsBkg+"all_VBFHToWWTo2L2Nu.root");       
TFile* VBFHToWWToLNuQQ              =  new TFile(inFile_HiggsBkg+"all_VBFHToWWToLNuQQ.root");       

//Histos
//Gluon gluon fusion 		     //Gluon gluon fusion
TH1F* h_GluGluHToBB                = (TH1F*)GluGluHToBB->Get("base/"+histPath);           
TH1F* h_GluGluHToTauTau            = (TH1F*)GluGluHToTauTau->Get("base/"+histPath);       
TH1F* h_GluGluHToCC                = (TH1F*)GluGluHToCC->Get("base/"+histPath);           
TH1F* h_GluGluHToGG                = (TH1F*)GluGluHToGG->Get("base/"+histPath);           
TH1F* h_GluGluHToWWTo2L2Nu         = (TH1F*)GluGluHToWWTo2L2Nu->Get("base/"+histPath);    
TH1F* h_GluGluHToWWToLNuQQ         = (TH1F*)GluGluHToWWToLNuQQ->Get("base/"+histPath);    
TH1F* h_GluGluHToZZTo2L2Q          = (TH1F*)GluGluHToZZTo2L2Q->Get("base/"+histPath);     
TH1F* h_GluGluHToZZTo4L            = (TH1F*)GluGluHToZZTo4L->Get("base/"+histPath);       
//W+H production                     //W+H production
TH1F* h_WplusH_HToBB_WToLNu        = (TH1F*)WplusH_HToBB_WToLNu->Get("base/"+histPath);   
TH1F* h_WplusH_HToBB_WToQQ         = (TH1F*)WplusH_HToBB_WToQQ->Get("base/"+histPath);    
TH1F* h_WplusHToTauTau             = (TH1F*)WplusHToTauTau->Get("base/"+histPath);        
TH1F* h_WplusH_HToCC_WToLNu        = (TH1F*)WplusH_HToCC_WToLNu->Get("base/"+histPath);   
TH1F* h_WplusH_HToCC_WToQQ         = (TH1F*)WplusH_HToCC_WToQQ->Get("base/"+histPath);    
TH1F* h_WplusH_HToGG_WToAll        = (TH1F*)WplusH_HToGG_WToAll->Get("base/"+histPath);   
//W-H production                     //W-H production
TH1F* h_WminusH_HToBB_WToQQ        = (TH1F*)WminusH_HToBB_WToQQ->Get("base/"+histPath);   
TH1F* h_WminusHToTauTau            = (TH1F*)WminusHToTauTau->Get("base/"+histPath);       
TH1F* h_WminusH_HToCC_WToLNu       = (TH1F*)WminusH_HToCC_WToLNu->Get("base/"+histPath);  
TH1F* h_WminusH_HToCC_WToQQ        = (TH1F*)WminusH_HToCC_WToQQ->Get("base/"+histPath);   
TH1F* h_WminusH_HToGG_WToAll       = (TH1F*)WminusH_HToGG_WToAll->Get("base/"+histPath);  
TH1F* h_WminusH_HToZZTo2L2X        = (TH1F*)WminusH_HToZZTo2L2X->Get("base/"+histPath);   
//ZH production                      //ZH production
TH1F* h_ZH_HToBB_ZToNuNu           = (TH1F*)ZH_HToBB_ZToNuNu->Get("base/"+histPath);      
TH1F* h_ZH_HToBB_ZToLL             = (TH1F*)ZH_HToBB_ZToLL->Get("base/"+histPath);        
TH1F* h_ZH_HToBB_ZToQQ             = (TH1F*)ZH_HToBB_ZToQQ->Get("base/"+histPath);        
TH1F* h_ZHToTauTau                 = (TH1F*)ZHToTauTau->Get("base/"+histPath);            
TH1F* h_ZH_HToCC_ZToNuNu           = (TH1F*)ZH_HToCC_ZToNuNu->Get("base/"+histPath);      
TH1F* h_ZH_HToCC_ZToLL             = (TH1F*)ZH_HToCC_ZToLL->Get("base/"+histPath);        
TH1F* h_ZH_HToCC_ZToQQ             = (TH1F*)ZH_HToCC_ZToQQ->Get("base/"+histPath);        
TH1F* h_ZH_HToGG_ZToAll            = (TH1F*)ZH_HToGG_ZToAll->Get("base/"+histPath);       
TH1F* h_ZH_HToZZ_2L                = (TH1F*)ZH_HToZZ_2L->Get("base/"+histPath);           
//gg fusion to ZH                    //gg fusion to ZH
TH1F* h_ggZH_HToBB_ZToNuNu         = (TH1F*)ggZH_HToBB_ZToNuNu->Get("base/"+histPath);    
TH1F* h_ggZH_HToBB_ZToLL           = (TH1F*)ggZH_HToBB_ZToLL->Get("base/"+histPath);      
TH1F* h_ggZH_HToBB_ZToQQ           = (TH1F*)ggZH_HToBB_ZToQQ->Get("base/"+histPath);      
TH1F* h_ggZH_HToCC_ZToNuNu         = (TH1F*)ggZH_HToCC_ZToNuNu->Get("base/"+histPath);    
TH1F* h_ggZH_HToCC_ZToLL           = (TH1F*)ggZH_HToCC_ZToLL->Get("base/"+histPath);      
TH1F* h_ggZH_HToCC_ZToQQ           = (TH1F*)ggZH_HToCC_ZToQQ->Get("base/"+histPath);      
TH1F* h_GluGluZH_HToWW            = (TH1F*)GluGluZH_HToWW->Get("base/"+histPath);        
//tt fusion                          //tt fusion
TH1F* h_ttHToCC                    = (TH1F*)ttHToCC->Get("base/"+histPath);               
TH1F* h_ttHToGG                    = (TH1F*)ttHToGG->Get("base/"+histPath);               
//bb fusion                          //bb fusion
TH1F* h_bbHToBB                    = (TH1F*)bbHToBB->Get("base/"+histPath);               
TH1F* h_bbHToGG                    = (TH1F*)bbHToGG->Get("base/"+histPath);               
TH1F* h_bbHToWWTo2L2Nu             = (TH1F*)bbHToWWTo2L2Nu->Get("base/"+histPath);        
TH1F* h_bbH_HToZZTo4L              = (TH1F*)bbH_HToZZTo4L->Get("base/"+histPath);         
//vector boson fustion               //vector boson fustion
TH1F* h_VBFHToBB                   = (TH1F*)VBFHToBB->Get("base/"+histPath);              
TH1F* h_VBFHToTauTau               = (TH1F*)VBFHToTauTau->Get("base/"+histPath);          
TH1F* h_VBFHToCC                   = (TH1F*)VBFHToCC->Get("base/"+histPath);              
TH1F* h_VBFHToGG                   = (TH1F*)VBFHToGG->Get("base/"+histPath);              
TH1F* h_VBFHToWWTo2L2Nu            = (TH1F*)VBFHToWWTo2L2Nu->Get("base/"+histPath);       
TH1F* h_VBFHToWWToLNuQQ            = (TH1F*)VBFHToWWToLNuQQ->Get("base/"+histPath);       


//////////
//Hplus  wh80   signal 
TH1F* h_wh80_base  		= (TH1F*)wh80->Get("base/"+histPath)->Clone("h_wh80_base"); 
TH1F* h_wh80_JESPlus 		= (TH1F*)wh80->Get("JESPlus/"+histPath)->Clone("h_wh80_JESPlus");
TH1F* h_wh80_JESMinus 		= (TH1F*)wh80->Get("JESMinus/"+histPath)->Clone("h_wh80_JESMinus");
TH1F* h_wh80_PileupPlus 		= (TH1F*)wh80->Get("PileupPlus/"+histPath)->Clone("h_wh80_PileupPlus");
TH1F* h_wh80_PileupMinus 		= (TH1F*)wh80->Get("PileupMinus/"+histPath)->Clone("h_wh80_PileupMinus");
TH1F* h_wh80_JERPlus 		= (TH1F*)wh80->Get("JERPlus/"+histPath)->Clone("h_wh80_JERPlus");
TH1F* h_wh80_JERMinus 		= (TH1F*)wh80->Get("JERMinus/"+histPath)->Clone("h_wh80_JERMinus");
TH1F* h_wh80_TopPtPlus 		= (TH1F*)wh80->Get("TopPtPlus/"+histPath)->Clone("h_wh80_TopPtPlus");
TH1F* h_wh80_TopPtMinus 	= (TH1F*)wh80->Get("TopPtMinus/"+histPath)->Clone("h_wh80_TopPtMinus");
TH1F* h_wh80_bTagPlus 		= (TH1F*)wh80->Get("bTagPlus/"+histPath)->Clone("h_wh80_bTagPlus");
TH1F* h_wh80_bTagMinus 		= (TH1F*)wh80->Get("bTagMinus/"+histPath)->Clone("h_wh80_bTagMinus");
TH1F* h_wh80_cTagPlus 		= (TH1F*)wh80->Get("cTagPlus/"+histPath)->Clone("h_wh80_cTagPlus");
TH1F* h_wh80_cTagMinus 		= (TH1F*)wh80->Get("cTagMinus/"+histPath)->Clone("h_wh80_cTagMinus");

//Hplus  wh90   signal 
TH1F* h_wh90_base  		= (TH1F*)wh90->Get("base/"+histPath)->Clone("h_wh90_base"); 
TH1F* h_wh90_JESPlus 		= (TH1F*)wh90->Get("JESPlus/"+histPath)->Clone("h_wh90_JESPlus");
TH1F* h_wh90_JESMinus 		= (TH1F*)wh90->Get("JESMinus/"+histPath)->Clone("h_wh90_JESMinus");
TH1F* h_wh90_PileupPlus 		= (TH1F*)wh90->Get("PileupPlus/"+histPath)->Clone("h_wh90_PileupPlus");
TH1F* h_wh90_PileupMinus 		= (TH1F*)wh90->Get("PileupMinus/"+histPath)->Clone("h_wh90_PileupMinus");
TH1F* h_wh90_JERPlus 		= (TH1F*)wh90->Get("JERPlus/"+histPath)->Clone("h_wh90_JERPlus");
TH1F* h_wh90_JERMinus 		= (TH1F*)wh90->Get("JERMinus/"+histPath)->Clone("h_wh90_JERMinus");
TH1F* h_wh90_TopPtPlus 		= (TH1F*)wh90->Get("TopPtPlus/"+histPath)->Clone("h_wh90_TopPtPlus");
TH1F* h_wh90_TopPtMinus 	= (TH1F*)wh90->Get("TopPtMinus/"+histPath)->Clone("h_wh90_TopPtMinus");
TH1F* h_wh90_bTagPlus 		= (TH1F*)wh90->Get("bTagPlus/"+histPath)->Clone("h_wh90_bTagPlus");
TH1F* h_wh90_bTagMinus 		= (TH1F*)wh90->Get("bTagMinus/"+histPath)->Clone("h_wh90_bTagMinus");
TH1F* h_wh90_cTagPlus 		= (TH1F*)wh90->Get("cTagPlus/"+histPath)->Clone("h_wh90_cTagPlus");
TH1F* h_wh90_cTagMinus 		= (TH1F*)wh90->Get("cTagMinus/"+histPath)->Clone("h_wh90_cTagMinus");


//Hplus  wh100   signal 
TH1F* h_wh100_base  		= (TH1F*)wh100->Get("base/"+histPath)->Clone("h_wh100_base"); 
TH1F* h_wh100_JESPlus 		= (TH1F*)wh100->Get("JESPlus/"+histPath)->Clone("h_wh100_JESPlus");
TH1F* h_wh100_JESMinus 		= (TH1F*)wh100->Get("JESMinus/"+histPath)->Clone("h_wh100_JESMinus");
TH1F* h_wh100_PileupPlus 		= (TH1F*)wh100->Get("PileupPlus/"+histPath)->Clone("h_wh100_PileupPlus");
TH1F* h_wh100_PileupMinus 		= (TH1F*)wh100->Get("PileupMinus/"+histPath)->Clone("h_wh100_PileupMinus");
TH1F* h_wh100_JERPlus 		= (TH1F*)wh100->Get("JERPlus/"+histPath)->Clone("h_wh100_JERPlus");
TH1F* h_wh100_JERMinus 		= (TH1F*)wh100->Get("JERMinus/"+histPath)->Clone("h_wh100_JERMinus");
TH1F* h_wh100_TopPtPlus 		= (TH1F*)wh100->Get("TopPtPlus/"+histPath)->Clone("h_wh100_TopPtPlus");
TH1F* h_wh100_TopPtMinus 	= (TH1F*)wh100->Get("TopPtMinus/"+histPath)->Clone("h_wh100_TopPtMinus");
TH1F* h_wh100_bTagPlus 		= (TH1F*)wh100->Get("bTagPlus/"+histPath)->Clone("h_wh100_bTagPlus");
TH1F* h_wh100_bTagMinus 		= (TH1F*)wh100->Get("bTagMinus/"+histPath)->Clone("h_wh100_bTagMinus");
TH1F* h_wh100_cTagPlus 		= (TH1F*)wh100->Get("cTagPlus/"+histPath)->Clone("h_wh100_cTagPlus");
TH1F* h_wh100_cTagMinus 		= (TH1F*)wh100->Get("cTagMinus/"+histPath)->Clone("h_wh100_cTagMinus");

//Hplus  wh120   signal 
TH1F* h_wh120_base  		= (TH1F*)wh120->Get("base/"+histPath)->Clone("h_wh120_base"); 
TH1F* h_wh120_JESPlus 		= (TH1F*)wh120->Get("JESPlus/"+histPath)->Clone("h_wh120_JESPlus");
TH1F* h_wh120_JESMinus 		= (TH1F*)wh120->Get("JESMinus/"+histPath)->Clone("h_wh120_JESMinus");
TH1F* h_wh120_PileupPlus 		= (TH1F*)wh120->Get("PileupPlus/"+histPath)->Clone("h_wh120_PileupPlus");
TH1F* h_wh120_PileupMinus 		= (TH1F*)wh120->Get("PileupMinus/"+histPath)->Clone("h_wh120_PileupMinus");
TH1F* h_wh120_JERPlus 		= (TH1F*)wh120->Get("JERPlus/"+histPath)->Clone("h_wh120_JERPlus");
TH1F* h_wh120_JERMinus 		= (TH1F*)wh120->Get("JERMinus/"+histPath)->Clone("h_wh120_JERMinus");
TH1F* h_wh120_TopPtPlus 		= (TH1F*)wh120->Get("TopPtPlus/"+histPath)->Clone("h_wh120_TopPtPlus");
TH1F* h_wh120_TopPtMinus 	= (TH1F*)wh120->Get("TopPtMinus/"+histPath)->Clone("h_wh120_TopPtMinus");
TH1F* h_wh120_bTagPlus 		= (TH1F*)wh120->Get("bTagPlus/"+histPath)->Clone("h_wh120_bTagPlus");
TH1F* h_wh120_bTagMinus 		= (TH1F*)wh120->Get("bTagMinus/"+histPath)->Clone("h_wh120_bTagMinus");
TH1F* h_wh120_cTagPlus 		= (TH1F*)wh120->Get("cTagPlus/"+histPath)->Clone("h_wh120_cTagPlus");
TH1F* h_wh120_cTagMinus 		= (TH1F*)wh120->Get("cTagMinus/"+histPath)->Clone("h_wh120_cTagMinus");

//Hplus  wh140   signal 
TH1F* h_wh140_base  		= (TH1F*)wh140->Get("base/"+histPath)->Clone("h_wh140_base"); 
TH1F* h_wh140_JESPlus 		= (TH1F*)wh140->Get("JESPlus/"+histPath)->Clone("h_wh140_JESPlus");
TH1F* h_wh140_JESMinus 		= (TH1F*)wh140->Get("JESMinus/"+histPath)->Clone("h_wh140_JESMinus");
TH1F* h_wh140_PileupPlus 		= (TH1F*)wh140->Get("PileupPlus/"+histPath)->Clone("h_wh140_PileupPlus");
TH1F* h_wh140_PileupMinus 		= (TH1F*)wh140->Get("PileupMinus/"+histPath)->Clone("h_wh140_PileupMinus");
TH1F* h_wh140_JERPlus 		= (TH1F*)wh140->Get("JERPlus/"+histPath)->Clone("h_wh140_JERPlus");
TH1F* h_wh140_JERMinus 		= (TH1F*)wh140->Get("JERMinus/"+histPath)->Clone("h_wh140_JERMinus");
TH1F* h_wh140_TopPtPlus 		= (TH1F*)wh140->Get("TopPtPlus/"+histPath)->Clone("h_wh140_TopPtPlus");
TH1F* h_wh140_TopPtMinus 	= (TH1F*)wh140->Get("TopPtMinus/"+histPath)->Clone("h_wh140_TopPtMinus");
TH1F* h_wh140_bTagPlus 		= (TH1F*)wh140->Get("bTagPlus/"+histPath)->Clone("h_wh140_bTagPlus");
TH1F* h_wh140_bTagMinus 		= (TH1F*)wh140->Get("bTagMinus/"+histPath)->Clone("h_wh140_bTagMinus");
TH1F* h_wh140_cTagPlus 		= (TH1F*)wh140->Get("cTagPlus/"+histPath)->Clone("h_wh140_cTagPlus");
TH1F* h_wh140_cTagMinus 		= (TH1F*)wh140->Get("cTagMinus/"+histPath)->Clone("h_wh140_cTagMinus");


//Hplus  wh150   signal 
TH1F* h_wh150_base  		= (TH1F*)wh150->Get("base/"+histPath)->Clone("h_wh150_base"); 
TH1F* h_wh150_JESPlus 		= (TH1F*)wh150->Get("JESPlus/"+histPath)->Clone("h_wh150_JESPlus");
TH1F* h_wh150_JESMinus 		= (TH1F*)wh150->Get("JESMinus/"+histPath)->Clone("h_wh150_JESMinus");
TH1F* h_wh150_PileupPlus 		= (TH1F*)wh150->Get("PileupPlus/"+histPath)->Clone("h_wh150_PileupPlus");
TH1F* h_wh150_PileupMinus 		= (TH1F*)wh150->Get("PileupMinus/"+histPath)->Clone("h_wh150_PileupMinus");
TH1F* h_wh150_JERPlus 		= (TH1F*)wh150->Get("JERPlus/"+histPath)->Clone("h_wh150_JERPlus");
TH1F* h_wh150_JERMinus 		= (TH1F*)wh150->Get("JERMinus/"+histPath)->Clone("h_wh150_JERMinus");
TH1F* h_wh150_TopPtPlus 		= (TH1F*)wh150->Get("TopPtPlus/"+histPath)->Clone("h_wh150_TopPtPlus");
TH1F* h_wh150_TopPtMinus 	= (TH1F*)wh150->Get("TopPtMinus/"+histPath)->Clone("h_wh150_TopPtMinus");
TH1F* h_wh150_bTagPlus 		= (TH1F*)wh150->Get("bTagPlus/"+histPath)->Clone("h_wh150_bTagPlus");
TH1F* h_wh150_bTagMinus 		= (TH1F*)wh150->Get("bTagMinus/"+histPath)->Clone("h_wh150_bTagMinus");
TH1F* h_wh150_cTagPlus 		= (TH1F*)wh150->Get("cTagPlus/"+histPath)->Clone("h_wh150_cTagPlus");
TH1F* h_wh150_cTagMinus 		= (TH1F*)wh150->Get("cTagMinus/"+histPath)->Clone("h_wh150_cTagMinus");

//Hplus  wh155   signal 
TH1F* h_wh155_base  		= (TH1F*)wh155->Get("base/"+histPath)->Clone("h_wh155_base"); 
TH1F* h_wh155_JESPlus 		= (TH1F*)wh155->Get("JESPlus/"+histPath)->Clone("h_wh155_JESPlus");
TH1F* h_wh155_JESMinus 		= (TH1F*)wh155->Get("JESMinus/"+histPath)->Clone("h_wh155_JESMinus");
TH1F* h_wh155_PileupPlus 		= (TH1F*)wh155->Get("PileupPlus/"+histPath)->Clone("h_wh155_PileupPlus");
TH1F* h_wh155_PileupMinus 		= (TH1F*)wh155->Get("PileupMinus/"+histPath)->Clone("h_wh155_PileupMinus");
TH1F* h_wh155_JERPlus 		= (TH1F*)wh155->Get("JERPlus/"+histPath)->Clone("h_wh155_JERPlus");
TH1F* h_wh155_JERMinus 		= (TH1F*)wh155->Get("JERMinus/"+histPath)->Clone("h_wh155_JERMinus");
TH1F* h_wh155_TopPtPlus 		= (TH1F*)wh155->Get("TopPtPlus/"+histPath)->Clone("h_wh155_TopPtPlus");
TH1F* h_wh155_TopPtMinus 	= (TH1F*)wh155->Get("TopPtMinus/"+histPath)->Clone("h_wh155_TopPtMinus");
TH1F* h_wh155_bTagPlus 		= (TH1F*)wh155->Get("bTagPlus/"+histPath)->Clone("h_wh155_bTagPlus");
TH1F* h_wh155_bTagMinus 		= (TH1F*)wh155->Get("bTagMinus/"+histPath)->Clone("h_wh155_bTagMinus");
TH1F* h_wh155_cTagPlus 		= (TH1F*)wh155->Get("cTagPlus/"+histPath)->Clone("h_wh155_cTagPlus");
TH1F* h_wh155_cTagMinus 		= (TH1F*)wh155->Get("cTagMinus/"+histPath)->Clone("h_wh155_cTagMinus");

//Hplus  wh160   signal 
TH1F* h_wh160_base  		= (TH1F*)wh160->Get("base/"+histPath)->Clone("h_wh160_base"); 
TH1F* h_wh160_JESPlus 		= (TH1F*)wh160->Get("JESPlus/"+histPath)->Clone("h_wh160_JESPlus");
TH1F* h_wh160_JESMinus 		= (TH1F*)wh160->Get("JESMinus/"+histPath)->Clone("h_wh160_JESMinus");
TH1F* h_wh160_PileupPlus 		= (TH1F*)wh160->Get("PileupPlus/"+histPath)->Clone("h_wh160_PileupPlus");
TH1F* h_wh160_PileupMinus 		= (TH1F*)wh160->Get("PileupMinus/"+histPath)->Clone("h_wh160_PileupMinus");
TH1F* h_wh160_JERPlus 		= (TH1F*)wh160->Get("JERPlus/"+histPath)->Clone("h_wh160_JERPlus");
TH1F* h_wh160_JERMinus 		= (TH1F*)wh160->Get("JERMinus/"+histPath)->Clone("h_wh160_JERMinus");
TH1F* h_wh160_TopPtPlus 		= (TH1F*)wh160->Get("TopPtPlus/"+histPath)->Clone("h_wh160_TopPtPlus");
TH1F* h_wh160_TopPtMinus 	= (TH1F*)wh160->Get("TopPtMinus/"+histPath)->Clone("h_wh160_TopPtMinus");
TH1F* h_wh160_bTagPlus 		= (TH1F*)wh160->Get("bTagPlus/"+histPath)->Clone("h_wh160_bTagPlus");
TH1F* h_wh160_bTagMinus 		= (TH1F*)wh160->Get("bTagMinus/"+histPath)->Clone("h_wh160_bTagMinus");
TH1F* h_wh160_cTagPlus 		= (TH1F*)wh160->Get("cTagPlus/"+histPath)->Clone("h_wh160_cTagPlus");
TH1F* h_wh160_cTagMinus 		= (TH1F*)wh160->Get("cTagMinus/"+histPath)->Clone("h_wh160_cTagMinus");


//ttbar+jets
TH1F* h_ttbar_base  		= (TH1F*)ttbar->Get("base/"+histPath)->Clone("h_ttbar_base");  
TH1F* h_ttbar_JESPlus 	= (TH1F*)ttbar->Get("JESPlus/"+histPath)->Clone("h_ttbar_JESPlus"); 
TH1F* h_ttbar_JESMinus 	= (TH1F*)ttbar->Get("JESMinus/"+histPath)->Clone("h_ttbar_JESMinus"); 
TH1F* h_ttbar_PileupPlus 	= (TH1F*)ttbar->Get("PileupPlus/"+histPath)->Clone("h_ttbar_PileupPlus"); 
TH1F* h_ttbar_PileupMinus 	= (TH1F*)ttbar->Get("PileupMinus/"+histPath)->Clone("h_ttbar_PileupMinus"); 
TH1F* h_ttbar_JERPlus 	= (TH1F*)ttbar->Get("JERPlus/"+histPath)->Clone("h_ttbar_JERPlus"); 
TH1F* h_ttbar_JERMinus 	= (TH1F*)ttbar->Get("JERMinus/"+histPath)->Clone("h_ttbar_JERMinus"); 
TH1F* h_ttbar_TopPtPlus 	= (TH1F*)ttbar->Get("TopPtPlus/"+histPath)->Clone("h_ttbar_TopPtPlus"); 
TH1F* h_ttbar_TopPtMinus 	= (TH1F*)ttbar->Get("TopPtMinus/"+histPath)->Clone("h_ttbar_TopPtMinus"); 
TH1F* h_ttbar_bTagPlus 	= (TH1F*)ttbar->Get("bTagPlus/"+histPath)->Clone("h_ttbar_bTagPlus"); 
TH1F* h_ttbar_bTagMinus 	= (TH1F*)ttbar->Get("bTagMinus/"+histPath)->Clone("h_ttbar_bTagMinus"); 
TH1F* h_ttbar_cTagPlus 	= (TH1F*)ttbar->Get("cTagPlus/"+histPath)->Clone("h_ttbar_cTagPlus"); 
TH1F* h_ttbar_cTagMinus 	= (TH1F*)ttbar->Get("cTagMinus/"+histPath)->Clone("h_ttbar_cTagMinus"); 
//w+jets
TH1F* h_wjet_base  		= (TH1F*)wjet->Get("base/"+histPath)->Clone("h_wjet_base");  
TH1F* h_wjet_JESPlus 		= (TH1F*)wjet->Get("JESPlus/"+histPath)->Clone("h_wjet_JESPlus"); 
TH1F* h_wjet_JESMinus 	= (TH1F*)wjet->Get("JESMinus/"+histPath)->Clone("h_wjet_JESMinus"); 
TH1F* h_wjet_PileupPlus 		= (TH1F*)wjet->Get("PileupPlus/"+histPath)->Clone("h_wjet_PileupPlus"); 
TH1F* h_wjet_PileupMinus 	= (TH1F*)wjet->Get("PileupMinus/"+histPath)->Clone("h_wjet_PileupMinus"); 
TH1F* h_wjet_JERPlus 		= (TH1F*)wjet->Get("JERPlus/"+histPath)->Clone("h_wjet_JERPlus"); 
TH1F* h_wjet_JERMinus 	= (TH1F*)wjet->Get("JERMinus/"+histPath)->Clone("h_wjet_JERMinus"); 
TH1F* h_wjet_TopPtPlus 	= (TH1F*)wjet->Get("TopPtPlus/"+histPath)->Clone("h_wjet_TopPtPlus"); 
TH1F* h_wjet_TopPtMinus 	= (TH1F*)wjet->Get("TopPtMinus/"+histPath)->Clone("h_wjet_TopPtMinus"); 
TH1F* h_wjet_bTagPlus 	= (TH1F*)wjet->Get("bTagPlus/"+histPath)->Clone("h_wjet_bTagPlus"); 
TH1F* h_wjet_bTagMinus 	= (TH1F*)wjet->Get("bTagMinus/"+histPath)->Clone("h_wjet_bTagMinus"); 
TH1F* h_wjet_cTagPlus 	= (TH1F*)wjet->Get("cTagPlus/"+histPath)->Clone("h_wjet_cTagPlus"); 
TH1F* h_wjet_cTagMinus 	= (TH1F*)wjet->Get("cTagMinus/"+histPath)->Clone("h_wjet_cTagMinus"); 
//dy+jets
TH1F* h_zjet_base  		= (TH1F*)zjet->Get("base/"+histPath)->Clone("h_zjet_base");
TH1F* h_zjet_JESPlus 		= (TH1F*)zjet->Get("JESPlus/"+histPath)->Clone("h_zjet_JESPlus");
TH1F* h_zjet_JESMinus 	= (TH1F*)zjet->Get("JESMinus/"+histPath)->Clone("h_zjet_JESMinus");
TH1F* h_zjet_PileupPlus 		= (TH1F*)zjet->Get("PileupPlus/"+histPath)->Clone("h_zjet_PileupPlus");
TH1F* h_zjet_PileupMinus 	= (TH1F*)zjet->Get("PileupMinus/"+histPath)->Clone("h_zjet_PileupMinus");
TH1F* h_zjet_JERPlus 		= (TH1F*)zjet->Get("JERPlus/"+histPath)->Clone("h_zjet_JERPlus");
TH1F* h_zjet_JERMinus 	= (TH1F*)zjet->Get("JERMinus/"+histPath)->Clone("h_zjet_JERMinus");
TH1F* h_zjet_TopPtPlus 	= (TH1F*)zjet->Get("TopPtPlus/"+histPath)->Clone("h_zjet_TopPtPlus");
TH1F* h_zjet_TopPtMinus 	= (TH1F*)zjet->Get("TopPtMinus/"+histPath)->Clone("h_zjet_TopPtMinus");
TH1F* h_zjet_bTagPlus 	= (TH1F*)zjet->Get("bTagPlus/"+histPath)->Clone("h_zjet_bTagPlus");
TH1F* h_zjet_bTagMinus 	= (TH1F*)zjet->Get("bTagMinus/"+histPath)->Clone("h_zjet_bTagMinus");
TH1F* h_zjet_cTagPlus 	= (TH1F*)zjet->Get("cTagPlus/"+histPath)->Clone("h_zjet_cTagPlus");
TH1F* h_zjet_cTagMinus 	= (TH1F*)zjet->Get("cTagMinus/"+histPath)->Clone("h_zjet_cTagMinus");
//qcd
TH1F* h_qcd_base 		= (TH1F*)qcd->Get("base/"+histPath)->Clone("h_qcd_base");
TH1F* h_qcd_JESPlus 		= (TH1F*)qcd->Get("JESPlus/"+histPath)->Clone("h_qcd_JESPlus");
TH1F* h_qcd_JESMinus 		= (TH1F*)qcd->Get("JESMinus/"+histPath)->Clone("h_qcd_JESMinus");
TH1F* h_qcd_PileupPlus 		= (TH1F*)qcd->Get("PileupPlus/"+histPath)->Clone("h_qcd_PileupPlus");
TH1F* h_qcd_PileupMinus 		= (TH1F*)qcd->Get("PileupMinus/"+histPath)->Clone("h_qcd_PileupMinus");
TH1F* h_qcd_JERPlus 		= (TH1F*)qcd->Get("JERPlus/"+histPath)->Clone("h_qcd_JERPlus");
TH1F* h_qcd_JERMinus 		= (TH1F*)qcd->Get("JERMinus/"+histPath)->Clone("h_qcd_JERMinus");
TH1F* h_qcd_TopPtPlus 	= (TH1F*)qcd->Get("TopPtPlus/"+histPath)->Clone("h_qcd_TopPtPlus");
TH1F* h_qcd_TopPtMinus 	= (TH1F*)qcd->Get("TopPtMinus/"+histPath)->Clone("h_qcd_TopPtMinus");
TH1F* h_qcd_bTagPlus 		= (TH1F*)qcd->Get("bTagPlus/"+histPath)->Clone("h_qcd_bTagPlus");
TH1F* h_qcd_bTagMinus 	= (TH1F*)qcd->Get("bTagMinus/"+histPath)->Clone("h_qcd_bTagMinus");
TH1F* h_qcd_cTagPlus 		= (TH1F*)qcd->Get("cTagPlus/"+histPath)->Clone("h_qcd_cTagPlus");
TH1F* h_qcd_cTagMinus 	= (TH1F*)qcd->Get("cTagMinus/"+histPath)->Clone("h_qcd_cTagMinus");
//single top
TH1F* h_stop_base  		= (TH1F*)stop->Get("base/"+histPath)->Clone("h_stop_base");
TH1F* h_stop_JESPlus 		= (TH1F*)stop->Get("JESPlus/"+histPath)->Clone("h_stop_JESPlus");
TH1F* h_stop_JESMinus 	= (TH1F*)stop->Get("JESMinus/"+histPath)->Clone("h_stop_JESMinus");
TH1F* h_stop_PileupPlus 		= (TH1F*)stop->Get("PileupPlus/"+histPath)->Clone("h_stop_PileupPlus");
TH1F* h_stop_PileupMinus 	= (TH1F*)stop->Get("PileupMinus/"+histPath)->Clone("h_stop_PileupMinus");
TH1F* h_stop_JERPlus 		= (TH1F*)stop->Get("JERPlus/"+histPath)->Clone("h_stop_JERPlus");
TH1F* h_stop_JERMinus 	= (TH1F*)stop->Get("JERMinus/"+histPath)->Clone("h_stop_JERMinus");
TH1F* h_stop_TopPtPlus 	= (TH1F*)stop->Get("TopPtPlus/"+histPath)->Clone("h_stop_TopPtPlus");
TH1F* h_stop_TopPtMinus 	= (TH1F*)stop->Get("TopPtMinus/"+histPath)->Clone("h_stop_TopPtMinus");
TH1F* h_stop_bTagPlus 	= (TH1F*)stop->Get("bTagPlus/"+histPath)->Clone("h_stop_bTagPlus");
TH1F* h_stop_bTagMinus 	= (TH1F*)stop->Get("bTagMinus/"+histPath)->Clone("h_stop_bTagMinus");
TH1F* h_stop_cTagPlus 	= (TH1F*)stop->Get("cTagPlus/"+histPath)->Clone("h_stop_cTagPlus");
TH1F* h_stop_cTagMinus 	= (TH1F*)stop->Get("cTagMinus/"+histPath)->Clone("h_stop_cTagMinus");
//vv
TH1F* h_vv_base 		= (TH1F*)vv->Get("base/"+histPath)->Clone("h_vv_base");
TH1F* h_vv_JESPlus 	= (TH1F*)vv->Get("JESPlus/"+histPath)->Clone("h_vv_JESPlus");
TH1F* h_vv_JESMinus 	= (TH1F*)vv->Get("JESMinus/"+histPath)->Clone("h_vv_JESMinus");
TH1F* h_vv_PileupPlus 	= (TH1F*)vv->Get("PileupPlus/"+histPath)->Clone("h_vv_PileupPlus");
TH1F* h_vv_PileupMinus 	= (TH1F*)vv->Get("PileupMinus/"+histPath)->Clone("h_vv_PileupMinus");
TH1F* h_vv_JERPlus 	= (TH1F*)vv->Get("JERPlus/"+histPath)->Clone("h_vv_JERPlus");
TH1F* h_vv_JERMinus 	= (TH1F*)vv->Get("JERMinus/"+histPath)->Clone("h_vv_JERMinus");
TH1F* h_vv_TopPtPlus 	= (TH1F*)vv->Get("TopPtPlus/"+histPath)->Clone("h_vv_TopPtPlus");
TH1F* h_vv_TopPtMinus 	= (TH1F*)vv->Get("TopPtMinus/"+histPath)->Clone("h_vv_TopPtMinus");
TH1F* h_vv_bTagPlus 	= (TH1F*)vv->Get("bTagPlus/"+histPath)->Clone("h_vv_bTagPlus");
TH1F* h_vv_bTagMinus 	= (TH1F*)vv->Get("bTagMinus/"+histPath)->Clone("h_vv_bTagMinus");
TH1F* h_vv_cTagPlus 	= (TH1F*)vv->Get("cTagPlus/"+histPath)->Clone("h_vv_cTagPlus");
TH1F* h_vv_cTagMinus 	= (TH1F*)vv->Get("cTagMinus/"+histPath)->Clone("h_vv_cTagMinus");

TH1F* h_TotalBkg = (TH1F*)h_wjet_base->Clone("h_TotalBkg");
h_TotalBkg->Reset();
h_TotalBkg->Add(h_ttbar_base);
h_TotalBkg->Add(h_wjet_base);
h_TotalBkg->Add(h_zjet_base);
h_TotalBkg->Add(h_qcd_base);
h_TotalBkg->Add(h_stop_base);
h_TotalBkg->Add(h_vv_base);

TH1F* h_data = (TH1F*)data->Get("base/"+histPath)->Clone("h_data");

