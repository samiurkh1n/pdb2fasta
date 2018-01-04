// Implementation of PDB To Fasta Utilities

#include "protein.hpp"
#include <algorithm>

std::unordered_map<std::string, std::string> Protein::pdb_acid_to_fasta_acid() {
  std::unordered_map<std::string, std::string> acid_mapping;
  acid_mapping["ALA"] = "A";
  acid_mapping["ARG"] = "R";
  acid_mapping["ASN"] = "N";
  acid_mapping["ASP"] = "D";
  acid_mapping["ASX"] = "B";
  acid_mapping["CYS"] = "C";
  acid_mapping["GLN"] = "Q";
  acid_mapping["GLU"] = "E";
  acid_mapping["GLX"] = "Z";
  acid_mapping["GLY"] = "G";
  acid_mapping["HIS"] = "H";
  acid_mapping["ILE"] = "I";
  acid_mapping["LEU"] = "L";
  acid_mapping["LYS"] = "K";
  acid_mapping["MET"] = "M";
  acid_mapping["PHE"] = "F";
  acid_mapping["PRO"] = "P";
  acid_mapping["SER"] = "S";
  acid_mapping["THR"] = "T";
  acid_mapping["TRP"] = "W";
  acid_mapping["TYR"] = "Y";
  acid_mapping["UNK"] = "";
  acid_mapping["VAL"] = "V";
  // TODO(samiurkh1n): Do I need a mapping to U/selenocysteine?
  return acid_mapping;
}


Protein::Protein(std::string protein_id): protein_id_(protein_id) {
  acid_map_ = pdb_acid_to_fasta_acid();
}

bool Protein::ParsePDBRecord(std::string record) {

  std::string record_name = record.substr(0, 4);
  // Ignore non-ATOM records. Return true because we keep reading
  // Return false if we hit an ENDMDL record
  if (record_name != "ATOM") {
    if (record.substr(0,6) == "ENDMDL") {
      return false;
    }
    return true;
  }

  std::string reading_residue_id = record.substr(22, 5);
  std::string chain_identifier = record.substr(21, 1);
  std::string residue = record.substr(17, 3);
  
  if (current_residue_id_ != reading_residue_id) {
    amino_acid_chains_[chain_identifier].append(acid_map_[residue]);
    current_residue_id_ = reading_residue_id;
  }
  return true;
}

std::string Protein::GenerateFASTAofAminoAcids() {
  std::string chain = "";
  std::string line = "";
  for (auto chain_it = amino_acid_chains_.begin();
       chain_it != amino_acid_chains_.end(); ++chain_it) {
    line = ">" + protein_id_ + ":" + chain_it->first + "\n";
    chain.append(line);
    line = chain_it->second + "\n";
    chain.append(line);
  }
  return chain;
}
