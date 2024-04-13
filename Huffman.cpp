#include "Huffman.h"

void Huffman::compress(string infile, string outfile) {
    // open file
    file.open(infile);

    // Check if file opened successfully
    if (!file.is_open()) {
        cerr << "Error opening file: " << infile << endl;
        return;
    }

    // get character count
    countChar();

    // build queue
    createQueue();

    // build huffman tree
    buildTree();

    // build ascii/binary map
    buildAscii(huffman, "");

    // store compressed file
    store(infile, outfile);

    // close file
    file.close();
}

void Huffman::countChar() {
    char current;
    while(file.get(current)){
        if(char_count.find(current) == char_count.end()){
            char_count[current] = 1;
        } else {
            char_count[current]++;
        }
    }
    char_count.emplace(end_of_text, 1);
    file.close();
    return;
}

void Huffman::createQueue() {
    // Populate priority queue with nodes
    for (auto it = char_count.begin(); it != char_count.end(); it++) {
        nodes.push(new Node(it->first, it->second, nullptr, nullptr));
    }
    return;
}

void Huffman::buildTree() {

    while(nodes.size() > 1){
        Node *left = nodes.top();
        nodes.pop();
        Node *right = nodes.top();
        nodes.pop();
        Node *parent = new Node {deliminator, left->weight + right->weight, left, right};
        nodes.push(parent);
    }
    huffman = nodes.top();

    return;
}

void Huffman::buildAscii(Node *next, string code) {
    //base case
    if(next->zero == nullptr || next->one == nullptr){
        ascii.emplace(next->letter, code);
    }
        else {
        buildAscii(next->zero, code + "0");
        buildAscii(next->one, code + "1");
        }
}

void Huffman::store(string infile, string outfile) {

    // Create a new storage object
    Storage *storage = new Storage();

    if (!storage->open(outfile, "write")) {
        std::cout << "There was an error opening the file." << std::endl;
        exit(0);
    }
    header = "";
    for (auto it = ascii.begin(); it != ascii.end(); it++){
        header = header + it->first + it->second + deliminator;
    }
    // set header
    storage->setHeader(header);

   // cout << header << endl;

    file.open(infile);

    // while there are characters, write the characters binary code into file
    char currentChar;
    while(file.get(currentChar)) {
        // check if character is in ascii map
        if (ascii.find(currentChar) != ascii.end()) {
            auto iter = ascii.find(currentChar);
            string binary = iter->second;
            storage->insert(binary);
        }
    }
    storage->insert(ascii[end_of_text]);
    storage->close();

    return;
}

void Huffman::decompress(string infile, string outfile) {
    // create storage object
    Storage *storage = new Storage();

    if (!storage->open(infile, "read")) {
        std::cout << "There was an error opening the file." << std::endl;
        exit(0);
    }

    // rebuild ascii
    rebuildAscii(storage);

    // extract binary from compressed decode, and output to file
    decode(storage, outfile);

    storage->close();

}

void Huffman::rebuildAscii(Storage *storage) {

    string file_header = "";
    file_header = storage->getHeader();
    // get header and rebuild ascii table

    char current;
    char key;
    string code = "";

    for (int i = 0; i < file_header.length(); ++i) {
        current = file_header.at(i);
        if(current != '1' || current != '0' || current != deliminator){
            key = current;
            current = file_header.at(++i);
            while(current != deliminator){
                code = code + current;
                current = file_header.at(++i);
            }
            rebuilt_ascii.emplace(code, key);
            code = "";
        }
    }
    return;
}

void Huffman::decode(Storage *storage, string outfile) {

    string binary = "";
    string current_code = "";
    string decoded = "";


    // extract all binary string 8 bits at a time until there is nothing left to read
    while(storage->extract(binary)) {
        string code = binary;
        for (int i = 0; i < code.size(); ++i) {
            current_code += code.at(i);
            if (rebuilt_ascii.find(current_code) != rebuilt_ascii.end()){
                if(rebuilt_ascii[current_code] == end_of_text){
                    break;
                }
                auto iter = rebuilt_ascii.find(current_code);
                decoded += iter->second;
                current_code = ""; // Reset current_code for the next character
            }
        }
    }

    ofstream output_file;
    char curr;
    output_file.open(outfile);
    for (int i = 0; i < decoded.size(); ++i) {
        curr = decoded.at(i);
        output_file.put(curr);
    }
    output_file.close();
}