#include <string>
#include <queue>
#include <fstream>
#include "Node.h"
#include "Storage/Storage.h"
#include "unordered_map"

#ifndef HUFFMAN_H
#define HUFFMAN_H

const char deliminator = '\30';
const char end_of_text = 3;

using namespace std;

/*
 * Huffman Compression
 */
class Huffman {
private:
    unordered_map<char, int> char_count;
    unordered_map<char, string> ascii;
    unordered_map<string, char> rebuilt_ascii;
    priority_queue<Node*, vector<Node*>, compareWeights> nodes;
    fstream file;
    Node *huffman;
    string header;

    /**
     * counts the characters of a file: Stores the characters and their frequencies in char_count map
     */
    void countChar();

    /**
     * uses priority queue of nodes of characters and their frequenicies
     */
    void createQueue();

    /**
     * uses the queue to build a huffman tree
     */
    void buildTree();

    /**
     * recursively calls buildAscii to traverse the tree to the leaf nodes adding either 0 or 1 to string code
     * once a leaf is reached, emplace the <character, code> to build our character/binary code map
     * @param next huffman tree node
     * @param code binary code to insert into map
     */
    void buildAscii(Node *next, string code);

    /**
     * 1. iterate through ascii map to create the header for file
     * 2. open original text file and write the binary codes for each character into our compressed file
     * @param infile file to read from
     * @param outfile file to write to
     */
    void store(string infile, string outfile);

    /**
     * gets header from compressed file and reads the characters and their corresponding binary codes to
     * create a new map of <codes, characters>
     * @param storage pointer to storage object
     */
    void rebuildAscii(Storage *storage);

    /**
     * 1. extract binary from compressed file
     * 2. go through binary and decode the text
     * 3. output decompressed text to outfile
     * @param storage pointer to storage object
     * @param outfile file to decompress to
     */
    void decode(Storage *storage, string outfile);
public:
    /**
     * uses private helper methods to compress a file using huffman compression
     * @param infile file to read from
     * @param outfile file to write to
     */
    void compress(string infile, string outfile);

    /**
     * uses private helper methods to decompress a file
     * @param infile file to read from
     * @param outfile file to write to
     */
    void decompress(string infile, string outfile);
};

#endif //HUFFMAN_H
