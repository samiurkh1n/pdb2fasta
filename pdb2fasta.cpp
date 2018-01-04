// PDB to FASTA Converter
// - Converts a pdb file into a fasta file
// - If PDB file contains multiple amino acid chains, resulting FASTA file will
//   place them into their own sections
// Usage:
// ./pdb2fasta [pdb file]

#include "protein.hpp"

#include <fstream>
#include <iostream>

int main(int argc, char* argv[]) {

  if (argc != 2) {
    std::cerr << "Invalid input" << std::endl;
    std::cerr << "Usage:" << std::endl;
    std::cerr << "./pdb2fasta [pdb file]" << std::endl;
    return -1;
  }

  std::string pdb_file_name = argv[1];
  std::string protein_id = pdb_file_name.substr(0, pdb_file_name.size() - 4);
  std::ifstream pdb_file(pdb_file_name.c_str());
  if (!pdb_file.is_open()) {
    std::cerr << "Error opening PDB file" << std::endl;
    return -1;
  }

  std::string fasta_filename = protein_id + ".fasta";
  std::ofstream fasta_file;
  fasta_file.open(fasta_filename.c_str());

  Protein protein(protein_id);
  std::string record = "";
  bool model_read = false;
  while(std::getline(pdb_file, record)) {
    protein.ParsePDBRecord(record, model_read);
    if (model_read) break;
  }

  fasta_file << protein.GenerateFASTAofAminoAcids();

  pdb_file.close();
  fasta_file.close();

  return 0;
}
