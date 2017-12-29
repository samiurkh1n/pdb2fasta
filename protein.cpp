// Implementation of PDB To Fasta Utilities

#include "protein.h"
#include <algorithm>

std::vector<std::string>
vectorize_string(std::string input, char delimiter = ' ') {
  std::vector<std::string> vectorized;
  std::string::const_iterator start = input.begin();
  std::string::const_iterator end = input.end();
  std::string::const_iterator split_point = find(start, end, delimiter);
  while (split_point != end) {
      if (start != split_point)
	vectorized.push_back(std::string(start, split_point));
      start = split_point + 1;
      split_point = std::find(start, end, delimiter);
  }

  // also insert the last substring past the delimiter
  if (start != split_point) {
    vectorized.push_back(std::string(start, split_point));
  }
  return vectorized;
}

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

void Protein::ParsePDBRecord(std::string record) {
  std::vector<std::string> split_record = vectorize_string(record);

  // Ignore non-ATOM records
  if (split_record.front() != "ATOM") {
    return;
  }

  if (current_residue_id_ != std::stoi(split_record[5])) {
    amino_acid_chains_[split_record[4]].append(acid_map_[split_record[3]]);
    current_residue_id_ = std::stoi(split_record[5]);
  }

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
