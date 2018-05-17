combine -M FitDiagnostics -t 0  --protectUnbinnedChannels -U datacard.root --rMin=1 --rMax=15. --setParameterRanges lambda=-5,5:x=0,100 --robustFit=1  --setParameters mu=3 --freezeParameters mu  --cminFallbackAlgo "Minuit2,migrad,0:0.1"  --cminApproxPreFitTolerance=100 --X-rtd MINIMIZER_MaxCalls=9999999 --saveNormalizations --saveShapes  2>&1 | tee log.txt
