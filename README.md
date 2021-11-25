Efficient Frontier
==================

For this assignment, you will write a program to find the efficient
frontier, or optimal set of portfolios, given a universe of assets and
their correlations.

Step 1:
------------------------------

  Write a program "efficient_frontier", which takes two command line
  arguments, the name of a file with a universe of assets and the name
  of a file with the correlation matrix.

  As sample data, you have universe.csv, which gives data on
  international equities, commodities, real estate, investment-grade
  corporate bonds, inflation-linked, medium term (7-10yr) US Treasury
  bonds, and short term (1-3yr) US Treasury bonds. You also have their
  average (annualized) returns and standard deviations. In
  correlation.csv, you have their correlations over the period March
  2009 (the end of the credit crisis bear market) to June 2015.

  As you have learned, the efficient frontier is a hyperbola
  representing the boundary of all possible portfolios that can be
  created from the assets provided. From these assets, we need to find
  the optimal (least risky – i.e. lowest volatility) portfolio for
  each level of expected portfolio return.

  A portfolio has a vector of weights, indicating how much of the
  portfolio is invested in each asset. These weights sum to 1. Your
  task is to estimate the optimal weights, i.e. minimum volatility,
  for each return level between 1% and 26% in 1% increments.

  The formula for portfolio variance is

  var = sum_i sum_j x(i)*x(j)*cov(i,j)

  where x is an element in the vector of weights. The standard
  deviation (or volatility) is the square root of the variance.

  For this step, print a comma-separated list of the return and the
  minimum volatility for that rate of return. In this part, assume
  that short sales are allowed (the weights can be negative).

  For example, the values for 1-4% are:

  ROR,volatility
  1.0%,0.78%
  2.0%,1.09%
  3.0%,1.59%
  4.0%,2.13%

Optimizing this problem is tricky, as it is a constrained quadratic
  optimization problem. You are free to use any method you like to
  implement the optimization, but some explanation and suggestions are
  provided in the document on Sakai.

Step 2:
------------------------------

  In this step, you will add additional functionality to your
  program. If the option "-r" is passed as a command line argument,
  you should implement a restricted optimization, i.e., use an
  additional constraint that no short sales are allowed. That is, all
  weights must be nonnegative. (See the man page for the function
  getopt to make parsing options more convenient.)

  Again, print a comma-separated list of the return and the minimum
  volatility for that rate of return.

  When no short sales are allowed, the values for 1-4% are:

  ROR,volatility
  1.0%,0.96%
  2.0%,1.20%
  3.0%,1.71%
  4.0%,2.28%

The Eigen package
-----------------

  A convenient linear algebra package is available at
  http://eigen.tuxfamily.org. The package is already installed on the
  server, and symlinked under /usr/local/include, so you do not need
  to do anything special with your Makefile to use the package in your
  code. You are free to read the Eigen documentation. If you use any
  sample code, please credit the source in your comments.

A note on object orientation

----------------------------

  Think about what aspects of this program are nouns, what each noun
  has, and what verbs are associated with each.

  An Asset has a standard deviation and expected return. A Portfolio
  has a list of weights and a list of Assets, from which the portfolio
  volatility and rate of return can be calculated. A Portfolio might
  have an optimize functionality.

Testing
-------

We provide a pregrader that will run your tests against our reference
implementation. Before the deadline, when you do 'grade', the
pregrader will look for a file testcases.txt with the following
format:

#error
universe.csv

#success
universe.csv correlation.csv

That is, a section with the #error header containing error test cases,
which should give an appropriate error message and exit with a failure
status. Note: you do not need to specify the program name this time,
since there should only be one executable to test. You are free to
make your own test files. (If you want to test "no command line
arguments," you should put a space on that line because the pregrader
skips blank lines.

The next section has a #success header and is followed by test cases
that should have a success status. For these the pregrader will check
that your results match ours.

You may write as many test cases as you like, but you are limited to
30 seconds of compute time by the pregrader.