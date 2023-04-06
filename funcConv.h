#ifndef funcConv_h
#define funcConv_h
	
class convert_1Dhisto {
	private:
		TH1* h_input;
		Spline1D* spline;
		
	
	public:
		convert_1Dhisto(TH1D* h_in);
		double operator() (double *vx, double *p);
};

class fun_mult_to_conv {
	private:
		TF1 *f1;
		TF1 *f2;
		double p0;
		double xmin, xmax;
	
	public:
		fun_mult_to_conv();
		fun_mult_to_conv(TF1 *ff1, TF1 *ff2, minx = 0., maxx = 1.);
		void set_param(double param);
		double operator()(double *vx, double *p);
};

class functions_convultion {
	private:
		TF1* f1;
		TF1* f2;
		fun_mult_to_conv fun_mult;
		double xmin, xmax;
	
	public:
		functions_convultion(TF1* ff1, TF1 *ff2, double minx = 0., double maxx = 1.);
		double operator() (double *vx, double *p);
};




#endif

