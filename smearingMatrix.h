#ifndef smearingMatrix_h
#define smearingMatrix_h
	
class smearingMatrix {

private:
	TMatrixD unsmeared_func;
	TMatrixD smearing_matrix;
	int bins;
	double xmin, xmax;
	
public:
	smearingMatrix();
	smearingMatrix(TH1D *func, TH2D *matrix, double minx = 0., double maxx = 1.);
	
	TH1D* get_smeared_func();
	
};




#endif
