#include <fstream>
#include <sstream>
#include <Rcpp.h>

typedef std::vector<std::string> StringVector;
typedef std::vector<int> IntegerVector;

// [[Rcpp::export]]
Rcpp::DataFrame readGOFile(std::string filename) {
  std::ifstream file(filename);
  std::string line;
  std::string formatVersion;
  std::string dataVersion;
  StringVector ids, names, namespaces;

  while (std::getline(file, line)) {
    if (line.find("id: ") == 0) {
      std::string id = line.substr(4);
      ids.push_back(id);
    } else if (line.find("name: ") == 0) {
      std::string name = line.substr(6);
      names.push_back(name);
    } else if (line.find("namespace: ") == 0) {
      std::string ns = line.substr(11);
      namespaces.push_back(ns);
    }
  }

  Rcpp::DataFrame df = Rcpp::DataFrame::create(Rcpp::Named("GO") = ids,
                                               Rcpp::Named("Description") = names,
                                               Rcpp::Named("Level") = namespaces,
                                               Rcpp::_["stringsAsFactors"] = false);
  return df;
}
