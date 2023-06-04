#include <Rcpp.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace Rcpp;

// Struct to store GO term information
struct GOTerm {
  std::string id;
  std::string name;
  std::string namespace_;
};

// Function to parse OBO file and extract GO terms
std::vector<GOTerm> parseOboFile(std::string filepath) {
  std::vector<GOTerm> goTerms;
  std::ifstream file(filepath);
  std::string line;
  GOTerm goTerm;
  bool skipTypedef = false;

  while (std::getline(file, line)) {
    if (line == "[Term]") {
      goTerm.id = "";
      goTerm.name = "";
      goTerm.namespace_ = "";
    } else if (line.find("id: ") == 0) {
      goTerm.id = line.substr(4);
    } else if (line.find("name: ") == 0) {
      goTerm.name = line.substr(6);
    } else if (line.find("namespace: ") == 0) {
      goTerm.namespace_ = line.substr(11);
    } else if (line.find("[Typedef]") == 0) {
      skipTypedef = true;
    } else if (line.empty()) {
      if (!skipTypedef && !goTerm.id.empty() && !goTerm.name.empty() && !goTerm.namespace_.empty()) {
        goTerms.push_back(goTerm);
      }
      skipTypedef = false;
    }
  }

  return goTerms;
}


// Rcpp wrapper for the parseOboFile function
// [[Rcpp::export]]
DataFrame readOboFile(std::string filepath) {
  std::vector<GOTerm> goTerms = parseOboFile(filepath);

  int numTerms = goTerms.size();
  std::vector<std::string> ids(numTerms);
  std::vector<std::string> names(numTerms);
  std::vector<std::string> namespaces(numTerms);

  for (int i = 0; i < numTerms; i++) {
    ids[i] = goTerms[i].id;
    names[i] = goTerms[i].name;
    namespaces[i] = goTerms[i].namespace_;
  }

  DataFrame result = DataFrame::create(Named("GO") = ids,
                                       Named("Description") = names,
                                       Named("level") = namespaces);

  return result;
}
