disp('Compiling: Exact MBD')
mex MBD_exact.cpp 
disp('Done.')

disp('Compiling: Approximate MBD')
mex MBD_approx.cpp 
disp('Done.')

disp('Compiling: GeodesicDT')
mex GeodesicDT.cpp 
disp('Done.')

disp('Compiling: FuzzyConnectedness')
mex FuzzyConnectedness.cpp 
disp('Done.')

disp('Compiling: MaxDT')
mex MaxDT.cpp 
disp('Done.')

disp('Compiling: FuzzyDT')
mex FuzzyDT.cpp 
disp('Done.')
