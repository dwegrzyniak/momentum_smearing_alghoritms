#include "funcConv.h"

convert_1Dhisto::convert_1Dhisto(TH1D* h_in){
	h_input = (TH1*)h_in;
	spline = new Spline1D(h_input);
}

double convert_1Dhisto::operator() (double *vx, double *p){
	double x = vx[0];
    if (x < h_input->GetBinLowEdge(1) || x > h_input->GetBinLowEdge(h_input->GetNbinsX())+ h_input->GetBinWidth(1))
      return 0.;

    return spline -> Eval(x);
    }
}


fun_mult_to_conv::fun_mult_to_conv(){
}

fun_mult_to_conv::fun_mult_to_conv(TF1 *ff1, TF1 *ff2, minx = 0., maxx = 1.){
	f1 = ff1;
	f2 = ff2;
	xmin = minx;
	xmax = maxx;
}

void fun_mult_to_conv::set_param(double param){
	p0 = param;
}

double fun_mult_to_conv::operator()(double *vx, double *p){
	return f1 -> Eval(vx[0]) * f2 -> Eval(p0 - vx[0]);
}



functions_convultion::functions_convultion(TF1* ff1, double u, double sigma, double minx = 0., double maxx = 1.) {
	double A = 1;
	f1 = ff1;
			
	TF1 *gaus = new TF1("gaus", "gaus", xmin, xmax);
	gaus -> SetParameters(A, u, sigma);

	A = 1./gaus -> Integral(u - 3 * sigma, u + 3 * sigma);
	gaus -> SetParameters(A, u, sigma);
		
	fun_mult.init(f1, gaus, xmin, xmax);
	xmin = minx;
	xmax = maxx;
}
	
functions_convultion::double operator() (double *vx, double *p){
	double x = vx[0];
		
	fun_mult.set_param(x);
		
	TF1 *multiplied_func = new TF1("multiplied_func", fun_mult, xmin, xmax, 0);
	return multiplied_func -> Integral(xmin, xmax);
}



