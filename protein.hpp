// Protein
// Code to construct a protein from a PDB file and produce a FASTA file

#ifndef PDB2FASTA_UTIL_H
#define PDB2FASTA_UTIL_H

#include <string>
#include <map>
#include <unordered_map>
#include <vector>

class Protein {
public:
  explicit Protein(std::string protein_id);

  // Parses ATOM record from a PDB file and stores the amino acid of a residue.
  // The function is sensitive to the residue identifier.
  // Returns false if it reaches the end of a model (ex: if it reads a record
  // of type "ENDMDL")
  bool ParsePDBRecord(std::string record);

  // Generates the FASTA formatted string of the amino acids.
  std::string GenerateFASTAofAminoAcids();

private:
  // Each pair in the vector below is the chain associated with a residue
  // The first is the pair's identifier and the second is the chain
  std::map<std::string, std::string> amino_acid_chains_;

  // Maps PDB Amino Acid Code to the FASTA equivalent
  // Note: doesn't handle FASTA symbols: X, *, -, or U
  std::unordered_map<std::string, std::string> pdb_acid_to_fasta_acid();
  std::unordered_map<std::string, std::string> acid_map_;

  std::string current_residue_id_ = "";

  std::string protein_id_ = "";

};  // Protein class interface

#endif  // PDB2FASTA_UTIL_H
