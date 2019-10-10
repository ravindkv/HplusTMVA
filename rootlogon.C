{
char *hosttype = (char *)gSystem->Getenv( "HOSTTYPE" );
char *rootsys  = (char *)gSystem->Getenv( "ROOTSYS" );

// gROOT->Reset();                // Reseting ROOT
gSystem->Load("libPhysics.so"); // Loading Physics library (TVector3)
gSystem->AddIncludePath("-I${PWD}");
gSystem->SetDynamicPath(gSystem->GetDynamicPath());
gSystem->Load("src/libMyEvent");
printf( "libraries loaded\n" );

}
