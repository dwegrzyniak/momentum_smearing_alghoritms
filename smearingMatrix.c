smearingMat#include "smearingMatrix.h"

smearingMatrix::smearingMatrix(){
	
}

smearingMatrix::smearingMatrix(TH1D *func, TH2D *matrix, double minx = 0., double maxx = 1.){

	
//convert unsmeared function to matrix	
	bins = func -> GetNbinsX();
	xmin = minx;
	xmax = maxx;

//convert histograms to matrix

	unsmeared_func.ResizeTo(bins + 2, 1);
	smearing_matrix.ResizeTo(bins + 2, bins + 2);

	TMatrixD matrix_from_hist(bins + 2, bins + 2, matrix->GetArray(),"F");
	TMatrixD func_from_hist(bins + 2, 1, func->GetArray(),"F");

	unsmeared_func = func_from_hist;
	smearing_matrix = matrix_from_hist;

	
//transpose matrix	
	smearing_matrix.Transpose(smearing_matrix); 	

	
//normalize matrix	

	double norm_matrix[bins + 2];
	
	for (int i = 0; i < bins + 2; i++){
		norm_matrix[i] = 0;
		
		for (int j = 0; j < bins + 2; j++){
			norm_matrix[i] += smearing_matrix(j, i);
		}
		
		if (norm_matrix[i] != 0) {
			for (int j = 0; j < bins + 2; j++){
				smearing_matrix(j, i) = smearing_matrix(j, i) / norm_matrix[i];
			}
		}
	}
}
	
TH1D* smearingMatrix::get_smeared_func(){
	
	TMatrixD result = TMatrixD(smearing_matrix,TMatrixD::kMult,unsmeared_func);
	TH1D* resultHist = new TH1D("result", "result", bins, 0., 1.);



	for (int i = 0; i < bins + 2; i ++){
            resultHist -> SetBinContent(i, result(i, 0));
    }	

	return resultHist;
	
}
	
	
