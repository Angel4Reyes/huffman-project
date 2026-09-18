# Huffman Coding — Class Lab

This repository contains my implementation of a Huffman coding text-compression program completed as part of a C++ class lab.

The program allows the user to:

* Compress a text file using Huffman coding
* Decompress a previously compressed file
* Choose the input file path
* Choose where to save the resulting file

## How to Use

When the program starts, it prompts the user to choose whether they want to compress or decompress a file.

The user is then asked to provide:

1. The path to the input file
2. The path and filename for the output file

After completing the selected operation, the program exits.

## Implementation

To compress a file, the program first reads the file and counts the number of occurrences of each character. These character frequencies are stored in a map.

Next, the program creates a priority queue containing Huffman nodes. Each node stores a character and its frequency. The nodes with the lowest frequencies are repeatedly combined to construct the Huffman tree.

After the tree is created, the program traverses it to generate a unique binary code for each character. These codes are stored in a map, where each character is associated with its Huffman binary code.

The program then creates a header containing the information needed to reconstruct the Huffman tree during decompression. The original text is converted into a binary string using the generated codes and saved to the compressed output file.

To decompress a file, the program reads the header and reconstructs the character-to-code mapping. It then reads the encoded binary data, translates the binary codes back into their original characters, and writes the decoded text to a new file.

## Binary File Storage

The project uses binary file storage to save compressed data. The storage functionality allows the program to:

* Write binary strings to a file
* Read binary data in eight-bit chunks
* Store and retrieve header information
* Reconstruct the Huffman tree during decompression

## Technologies

* C++
* Huffman coding
* Binary trees
* Priority queues
* Maps
* Binary file input/output
* Standard Template Library containers
