#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Node {
    char data;             
    int frequency;          
    Node* left;
    Node* right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

void printTree(Node* root, int depth = 0) {
    if (root == nullptr) {
        return;
    }

    
    printTree(root->right, depth + 1);

   
    for (int i = 0; i < depth; i++) {
        cout << "   ";
    }
    cout << root->data << "(" << root->frequency << ")" << endl;

   
    printTree(root->left, depth + 1);
}

struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};


Node* buildHuffmanTree(vector<Node*>& nodes) {
    while (nodes.size() > 1) {
        
        sort(nodes.begin(), nodes.end(), [](const auto& a, const auto& b) { return a->frequency < b->frequency; });

        Node* left = nodes.front();
        nodes.erase(nodes.begin());

        Node* right = nodes.front();
        nodes.erase(nodes.begin());

        
        Node* parent = new Node('O', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;
        nodes.push_back(parent);
    }

    return nodes.front();
}


void buildHuffmanCodes(Node* root, string code, vector<string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->data != 'O') {
        huffmanCodes[root->data] = code;
    }

    buildHuffmanCodes(root->left, code + "0", huffmanCodes);
    buildHuffmanCodes(root->right, code + "1", huffmanCodes);
}


string encodeText(string text, vector<string>& huffmanCodes) {
    string encodedText = "";
    for (char c : text) {
        encodedText += huffmanCodes[c];
    }
    return encodedText;
}


string decodeText(string encodedText, Node* root) {
    string decodedText = "";
    Node* current = root;

    for (char c : encodedText) {
        if (c == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->data != 'O') {
            decodedText += current->data;
            current = root;
        }
    }

    return decodedText;
}

int main() {
    string text;
   
    
    vector<Node*> nodes;
    int frequency[256] = { 0 };
    frequency['a'] = 4;
    frequency['b'] = 7;
    frequency['c'] = 5;
    frequency['d'] = 2;
    frequency['e'] = 9;

    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            nodes.push_back(new Node(i, frequency[i]));
        }
    }

    Node* root = buildHuffmanTree(nodes);
    printTree(root);
  
    vector<string> huffmanCodes(256);
    buildHuffmanCodes(root, "", huffmanCodes);

    for (int i = 0; i < 256; i++) {
        if (!huffmanCodes[i].empty()) {
            cout << static_cast<char>(i) << ": " << huffmanCodes[i] << endl;
        }
    }
    cout << "please enter the huffman codes"<<endl;
    
    string encodedText;
    cin >> encodedText;
   
    string decodedText = decodeText(encodedText, root);
    cout << "decodedText: " << decodedText << endl;

    return 0;
}
