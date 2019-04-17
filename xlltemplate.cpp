// xlltemplate.cpp
#include <random>
#include "xlltemplate.h"

using namespace fms;
using namespace xll;

AddIn xai_template(
	Documentation(LR"(
Jump diffusion binary put option.
)"));

// [f() + ... f()]/n
template<class X>
inline X mean(const std::function<X()>& f, size_t n)
{
	X m = 0;

	for (size_t i = 1; i <= n; ++i)
		m += (f() - m) / i;

	return m;
}

void test_jump_diffusion_cdf()
{
	double variate(R& rng)
	{
		std::normal_distribution Z;
		std::poisson_distribution N(lambda);

		return(a* Z(rng) + b * (N(rng) - lambda));
	}

	//??? Question 6. Use std::normal_distribution and std::poisson_distribution to test jump_diffusion_cdf.
}
test xai_test_jump_diffusion_cdf(test_jump_diffusion_cdf);

void test_jump_diffusion_implied()
{
	//??? Question 7. Test jump_diffusion::implied for the following implied volatilities
	double s[] = { 0.5, 0.1, 0.2, 0.5 };
}
test xai_test_jump_diffusion_implied(test_jump_diffusion_implied);

//??? Questing 8. Write an add-in called FMS.JUMP_DIFFUSION that returns a handle to a fms::jump_diffusion object

AddIn xai_jump_diffusion(
	Function(XLL_HANDLE, L"?xll_jump_diffusion", L"FMS.JUMP_DIFFUSION")
	.Arg(XLL_DOUBLE, L"a", L"is a.")
	.Arg(XLL_DOUBLE, L"lambda", L"is lambda.")
	.Uncalced()
	.FunctionHelp(L"Return handle from jump_diffusion")
	.Category(L"Final")
	.Documentation(L"TBA")
);
HANDLEX WINAPI xll_fms_jump_diffusion(double a, double lambda)
{
#pragma XLLEXPORT
	handlex h;

	try {

		xll::handle<fms::jump_diffusion> h_(new fms::jump_diffusion(a,lambda));
		h = h_.get();
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}
	return h;
}

//??? Questing 9. Write an add-in called FMS.JUMP_DIFFUSION.VALUE that uses the handle above to value a binary put option.
AddIn xai_fms_jump_diffusion_value(
	Function(XLL_DOUBLE, L"?xll_fms_jump_diffusion_value", L"FMS.JUMP_DIFFUSION.VALUE")
	.Arg(XLL_HANDLE, L"handle", L"is handle to an fms::diffusion object.")
	.Arg(XLL_DOUBLE, L"f", L"is the forward price.")
	.Arg(XLL_DOUBLE, L"s", L"is the volatility.")
	.Arg(XLL_DOUBLE, L"k", L"is the strike.")
	.Category(L"Final")
	.FunctionHelp(L"Binary put option value.")
	.Documentation(L"TBA")
);
HANDLEX WINAPI xll_fms_jump_diffusion_value(HANDLEX h, double f, double s, double k)
{
#pragma XLLEXPORT
	double v = std::numeric_limits<double>::quiet_NaN();

	try {
		// i , j < n
		xll::handle<fms::jump_diffusion> h_(h);
		// ensure (h_);
		v = h_->value(f,s,k);
	}
	catch (const std::exception& ex) {
		XLL_ERROR(ex.what());
	}

	return v;
}
//??? Questing 10. Create a spreadsheet that values a binary put option with parameters a = .9, lambda = .1, f = 100, s = 0.2, and k = 100.
// Use xllmonte to compare the closed form and Monte Carlo values.

