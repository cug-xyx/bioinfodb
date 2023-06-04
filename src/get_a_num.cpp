#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
double plus_number(double number) {
  double result = number * 2;

  return result;
}
