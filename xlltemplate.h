// xlltemplate.h
#include "xll12/xll/xll.h"
#include "xll12/xll/ensure.h"
#include "../MATHGR5260_001_2018/GR5260/fms_root1d_newton.h"

#pragma warning(disable: 4100)

namespace fms {

	inline double normal_cdf(double z)
	{
		static double sqrt2 = sqrt(double(2));

		return double (0.5) + erf(z / sqrt2) / 2;; //???Question 2. Return the standard normal cumulative distribution.
	}

	class jump_diffusion {
		double a, b, lambda;
	public:
		jump_diffusion(double a, double lambda)
			: a(a), lambda(lambda)
		{
			ensure(a); // ensure a and lambda are valid

			b = sqrt((1-a*a)/lambda); //??? put Question 1 formula here*/)
		}
		double cdf(double z)
		{
			double n = 10000;
			double sum = 0;
			for (double j = 1; j <= n;++j) {
				double fac = 0;
				for (double i = 1; i <= j;++i) {
					fac *= i;
				}
				double power = 1;
				for (double k = 1; k <= j;++k) {
					power *= lambda;
				}
				sum += normal_cdf(z)*(power/fac)*exp(-lambda);
			}
			return sum; //??? Question 3. Return P(X <= z) where X = a Z + b (N - lambda)
		}
		// Binary put forward value
		double value(double f, double s, double k)
		{
			auto z = (a*a*s*s/2 + lambda*(exp(b*s)-1)-lambda*b*s + log(k / f)) / s;

			return cdf(z); //???Question 4. Return E 1(F <= k)
		}
		// Binary put implied volatility using
		// https://github.com/keithalewis/MATHGR5260_001_2018/blob/master/GR5260/fms_root1d_newton.h
		double implied(double f, double v, double k)
		{
			//double s0 = double(.2);
			//std::function<double(double)> p = [f, v, k](double s) { return -v + value(f, s, k); };
			//std::function<double(double)> dp = [f, k](double s) { return vega(f, s, k, t); };
			//root1d::newton_solver<double, double> solver(s0, p, dp);

			return 0;  //??Question 5. Return s such that v = value(s, k)
		}
	};

}