#include <string>
#include <queue>
#include <fstream>
#include "Node.h"
#include "Storage/Storage.h"
#include "unordered_map"

#ifndef HUFFMAN_H
#define HUFFMAN_H

const char deliminator = '\30';

using namespace std;

class Huffman {
private:
    unordered_map<char, int> char_count;
    unordered_map<char, string> ascii;
    unordered_map<string, char> rebuilt_ascii;
    priority_queue<Node*, vector<Node*>, compareWeights> nodes;
    fstream file;
    Node *huffman;
    string header;
    void countChar();
    void createQueue();
    void buildTree();
    void buildAscii(Node *next, string code);
    void store(string infile, string outfile);
    void rebuildAscii(Storage *storage);
    void decode(Storage *storage, string outfile);
public:
    void compress(string infile, string outfile);
    void decompress(string infile, string outfile);


};

#endif //HUFFMAN_H
