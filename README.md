# pdb2fasta

Author: Samiur Khan, samkhan@umich.edu
Ackowledgements: Zhang Lab, Department of Computational Medicine and
Bioinformatics at University of Michigan

## Purpose

Binary to convert a PDB formatted file and its protein data into a
FASTA formatted file. If the PDB file contains multiple amino acid chains,
the resulting FASTA file will contain seperate chains split by the `>`
character.

## Installation
Clone the repository and, in your terminal, run
```bash
make main
```
This should create a `pdb2fasta` binary.

## Usage
```bash
./pdb2fasta [path/to/pdb_file]
```
Running this will produce a fasta file with the name of the protein sequence.

For example, running
```bash
./pdb2fasta ./1tpo.pdb
```
will produce a `1tpo.fasta` file.

### Assumptions about the PDB file

- The program assumes that the input PDB filename ends with ".pdb".
- The program assumes that, within the PDB file, the residue sequence identifier
is an integer and that the residue chain identifier is a character.
