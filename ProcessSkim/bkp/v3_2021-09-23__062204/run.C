int run(const char* opt = "sample=MCQCD|year=2016|input=input/files.txt|run=prod|mode=proof|workers=3") // sample = data, bkg, signal
{
  
  bool isproof  = false ;
  
  TString options(opt);
  TChain *chain = new TChain("Events");
  
  Ssiz_t from = 0;
  TString tok;
  TString op(opt);
  TString filename = ""; 
  TString mode = ""; 
  int workers = 3;
  TString run = ""; 
  // Now analyze the arguments
  while (op.Tokenize(tok , from , "|")) {
    if(tok.BeginsWith("input"))
      filename = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("mode"))
      mode = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
    if(tok.BeginsWith("workers"))
      workers = (((TObjString *) (tok.Tokenize("="))->At(1))->GetString()).Atoi();
    if(tok.BeginsWith("run"))
      run = ((TObjString *) (tok.Tokenize("="))->At(1))->GetString();
  }
  if(mode.BeginsWith("proof"))
    isproof = true;
  
  cout << "Input filename: " << filename << endl;
  ifstream fin(filename.Data());
  
  string s;
  while(getline(fin,s)){
    //cout << s << endl;
    chain->Add(s.c_str());
  }
  
  if(isproof){
    TProof *p = TProof::Open(Form("workers=%d",workers));
    p->ClearPackages();
    p->UploadPackage("loadpackages.par");
    p->EnablePackage("loadpackages");
    chain->SetProof();
  }
  
  if(run == "prod")
    chain->Process("ProcessSkim.C++", options.Data() );    
  else
    chain->Process("ProcessSkim.C++", options.Data(), 10000 );    
  
  return true;
}

