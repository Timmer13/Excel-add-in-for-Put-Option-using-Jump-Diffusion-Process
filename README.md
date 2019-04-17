# GR5260 2018 final exam

The final exam consists of implementing a model for binary put option using a jump diffusion model,
adding test routines, documenting the code your wrote, and creating a spreadsheet.

A _binary put_ option pays 1(F <= k) at expiration (which we assume is t = 1) where F = f exp(sX - kappa(s))
The forward value is v = E 1(F <= k) = P(F <= k) = P(X <= z) where z = (kappa(s) + log k/f)/s.

The jump diffusion model is X = a Z + b (N - lambda) where Z is standard normal and N is 
Poisson with jump intensity lambda, i.e., P(N = n) = (lambda^n/n!) exp(-lambda), n = 0, 1, ... 

 ??? Question 1. Assuming Z and N are independent, what value of b (in terms of a and lambda) will make Var(X) = 1?

Hint: Recall E(N) = lambda and Var(N) = lambda.

Search for `???Question n.` for n = 2,...,10 in the xlltemplate project.


## Hints

ABC: always be compiling! Keep everything in a working state as you go.

"Copy and paste is code reuse." Use existing code from the GR5260 repository.
