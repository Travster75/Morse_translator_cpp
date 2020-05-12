// Travis Bender

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// each node in the tree
struct NODE
{
    char letter;
    NODE * left;
    NODE * right;
};

// class to handle the translation
class MorseTree
{
private:
    NODE * root; // the root node
    
public:
    // default constructor
    MorseTree()
    {
        root = new NODE;
        root->letter = ' ';
        root->left = nullptr;
        root->right = nullptr;
        createTree();
    }
    
    // destructor
    ~MorseTree()
    {
        // deletes the entire tree
        deleteTree(root);
        root = nullptr;
    }
    
    // deletes the tree starting at top
    void deleteTree(NODE * top)
    {
        if (top == nullptr)
        {
            return;
        }
        
        deleteTree(top->left);
        deleteTree(top->right);

        delete top;
    }
    
    // creates the tree from the morse file
    void createTree()
    {
        // the morse code
        string morseSymbols;
        // the corresponding letter
        char morseLetter;
        
        // file object
        ifstream inputFile;
        
        // open the file
        inputFile.open("morse.txt");
        
        // check if file is open
        if (inputFile.is_open())
        {
            // input the data from the file
            int i = 0;
            while (inputFile >> morseLetter >> morseSymbols)
            {
                // insert into the tree
                insertNode(root, morseLetter, morseSymbols);
                i++;
            }
            // close the file
            inputFile.close();
        }
        // if an error occured in opening the file
        else
        {
            cout << "Error in opening the file" << endl;
        }
    }
    
    // inserts a node into the tree
    void insertNode(NODE * temp, char morseLetter, string symbols)
    {
        // if the symbols string is empty (end of the morse code)
        if (symbols.empty())
        {
            // put the letter in the tree
            temp->letter = morseLetter;
        }
        // if the symbols is a dot, go left
        else if (symbols[0] == '.')
        {
            if (temp->left == nullptr)
            {
                NODE * temp2 = new NODE;
                temp2->letter = ' ';
                temp2->left = nullptr;
                temp2->right = nullptr;
                temp->left = temp2;
            }
            
            // remove the first character in the string
            symbols.erase(0, 1);
            insertNode(temp->left, morseLetter, symbols);
        }
        // if the symbol is a dash, go right
        else
        {
            if (temp->right == nullptr)
            {
                NODE * temp2 = new NODE;
                temp2->letter = ' ';
                temp2->left = nullptr;
                temp2->right = nullptr;
                temp->right = temp2;
            }
            
            // remove the first character in the string
            symbols.erase(0, 1);
            insertNode(temp->right, morseLetter, symbols);
        }
    }
    
    // function to handle the recursive translate function
    string interpretMorse(string morseSymbols)
    {
        string result = "";
        result = translate(root, morseSymbols, result);
        return result;
    }
            
    // translates the morse code
    string translate(NODE * temp, string morseSymbols, string result)
    {
        // if reached the end of the morse code
        if (morseSymbols.empty())
        {
            if (temp != nullptr)
            {
                // add to the resulting string
                result += temp->letter;
            }
            // return that string
            return result;
        }
        // if dot, go left
        else if (morseSymbols[0] == '.')
        {
            return translate(temp->left, morseSymbols.erase(0, 1), result);
        }
        // if dash, go right
        else if (morseSymbols[0] == '-')
        {
            return translate(temp->right, morseSymbols.erase(0, 1), result);
        }
        // X represents the end of a letter
        else if (morseSymbols[0] == 'X')
        {
            // add the letter (but not the default space)
            if (temp != nullptr && temp->letter != ' ')
            {
                result += temp->letter;
            }
            // check to see if length is good
            if (morseSymbols.length() > 1)
            {
                // if two X's in a row, add a space
                if (morseSymbols[1] == 'X')
                {
                    result += " ";
                }
            }
            
            // when reached the end of a letter sequence, begin at the top of the tree again
            return translate(root, morseSymbols.erase(0, 1), result);
        }
        // if the character is unknown
        else
        {
            if (temp != nullptr && temp->letter != ' ')
            {
                result += temp->letter;
            }
            result += "?";
            
            // begin at top of tree
            return translate(root, morseSymbols.erase(0, 1), result);
        }
    }
    
};

int main() {
    
    // create the object
    MorseTree mTree;
    
    // string to translate
    string morse = "....X.X.-..X.-..X---XX.--X---X.-.X.-..X-..X.-.-.-X";
    
    // translate the string
    string result = mTree.interpretMorse(morse);
    
    cout << result << endl;
    
    
    return 0;
}
