#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

class TreeNode
{
public:
    TreeNode(string password);
    int getBalanceFactor();
    TreeNode* left;
    TreeNode* right;
    int leftHeight;
    int rightHeight;
    int level;
    string password;
private:
    int balanceFactor;
};

//constructor
TreeNode::TreeNode(string password)
{
    left = nullptr;
    right = nullptr;
    balanceFactor = 0;
    leftHeight = 0;
    rightHeight = 0;
    level = 1;
    this->password = password;
}

//calculates and returns balance factor of tree node
int TreeNode::getBalanceFactor()
{
    balanceFactor = this->leftHeight - this->rightHeight;
    return balanceFactor;
}

//AVLTree header
class AVLTree
{
public:
    AVLTree();
    void balanceTree();
    void insertNode(TreeNode* node);
    bool search(string inputedPassword, TreeNode* node);
    TreeNode* rotateLeftLeft(TreeNode* node);
    TreeNode* rotateRightRight(TreeNode* node);
    TreeNode* balance(TreeNode* node, int bF);
    TreeNode* root;
private:
    TreeNode* insertNode(TreeNode* currentNode, TreeNode* node);
};

//AVLTree constructor
AVLTree::AVLTree()
{
    root = nullptr;
}

//inserts Node starting at root
void AVLTree::insertNode(TreeNode* node)
{
    this->root = insertNode(this->root, node);
}

//recursive method that inserts a node, goes left if password is less than, goes right if password if greater than current node password
TreeNode* AVLTree::insertNode(TreeNode* currentNode,TreeNode* node)
{
    if (currentNode == nullptr)
    {
        if (root == nullptr)
            root = node;
        return node;
    }

    if (currentNode->password.compare(node->password) == 0)
    {
        return currentNode;
    }
    else if (currentNode->password.compare(node->password) > 0)
    {
        // left
        currentNode->left = insertNode(currentNode->left, node);
        currentNode->rightHeight = 0;
        if (currentNode->right == nullptr)
        {
            currentNode->rightHeight = 0;
        }
        else
        {
            currentNode->rightHeight = currentNode->right->level;
        }

        currentNode->leftHeight = 0;
        if (currentNode->left == nullptr)
        {
            currentNode->leftHeight = 0;
        }
        else
        {
            currentNode->leftHeight = currentNode->left->level;
        }

        currentNode->level = 0;
        if (currentNode->leftHeight > currentNode->rightHeight)
        {
            currentNode->level = currentNode->leftHeight + 1;
        }
        else
        {
            currentNode->level = currentNode->rightHeight + 1;
        }

    }
    else if (currentNode->password.compare(node->password) < 0)
    {
        // right
        currentNode->right = insertNode(currentNode->right, node);

        currentNode->rightHeight = 0;
        if (currentNode->right == nullptr)
        {
            currentNode->rightHeight = 0;
        }
        else
        {
            currentNode->rightHeight = currentNode->right->level;
        }

        currentNode->leftHeight = 0;
        if (currentNode->left == nullptr)
        {
            currentNode->leftHeight = 0;
        }
        else
        {
            currentNode->leftHeight = currentNode->left->level;
        }

        currentNode->level = 0;
        if (currentNode->leftHeight > currentNode->rightHeight)
        {
            currentNode->level = currentNode->leftHeight + 1;
        }
        else
        {
            currentNode->level = currentNode->rightHeight + 1;
        }
    }

    int balanceFactor = currentNode->leftHeight - currentNode->rightHeight;

    if (balanceFactor < -1 || balanceFactor > 1)
    {
        return balance(currentNode, balanceFactor);
    }

    return currentNode;
}

//rotate right for left left case
TreeNode* AVLTree::rotateLeftLeft(TreeNode* node)
{
    TreeNode* grandparent = node;
    TreeNode* parent = node->left;
    TreeNode* childLeft = parent->left;
    TreeNode* childRight = parent->right;

    parent->right = grandparent;
    grandparent->left = childRight;

    grandparent->leftHeight = 0;
    if (grandparent->left == nullptr)
    {
        grandparent->leftHeight = 0;
    }
    else
    {
        grandparent->leftHeight = grandparent->left->level;
    }

    grandparent->rightHeight = 0;
    if (grandparent->right == nullptr)
    {
        grandparent->rightHeight = 0;
    }
    else
    {
        grandparent->rightHeight = grandparent->right->level;
    }

    grandparent->level = 0;
    if (grandparent->leftHeight > grandparent->rightHeight)
    {
        grandparent->level = grandparent->leftHeight + 1;
    }
    else
    {
        grandparent->level = grandparent->rightHeight + 1;
    }

    parent->leftHeight = 0; if (parent->left == nullptr)
    {
        parent->leftHeight = 0;
    }
    else
    {
        parent->leftHeight = parent->left->level;
    }
    parent->rightHeight = 0; if (parent->right == nullptr)
    {
        parent->rightHeight = 0;
    }
    else
    {
        parent->rightHeight = parent->right->level;
    }

    parent->level = 0;
    if (parent->leftHeight > parent->rightHeight)
    {
        parent->level = parent->leftHeight + 1;
    }
    else
    {
        parent->level = parent->rightHeight + 1;
    }

    return parent;
}

//rotate left for right right case
TreeNode* AVLTree::rotateRightRight(TreeNode* node)
{
    TreeNode* grandparent = node;
    TreeNode* parent = node->right;
    TreeNode* childLeft = parent->left;
    TreeNode* childRight = parent->right;

    parent->left = grandparent;
    grandparent->right = childLeft;

    grandparent->leftHeight = 0;
    if (grandparent->left == nullptr)
    {
        grandparent->leftHeight = 0;
    }
    else
    {
        grandparent->leftHeight = grandparent->left->level;
    }

    grandparent->rightHeight = 0;
    if (grandparent->right == nullptr)
    {
        grandparent->rightHeight = 0;
    }
    else
    {
        grandparent->rightHeight = grandparent->right->level;
    }

    grandparent->level = 0;
    if (grandparent->leftHeight > grandparent->rightHeight)
    {
        grandparent->level = grandparent->leftHeight + 1;
    }
    else
    {
        grandparent->level = grandparent->rightHeight + 1;
    }

    parent->leftHeight = 0;
    if (parent->left == nullptr)
    {
        parent->leftHeight = 0;
    }
    else
    {
        parent->leftHeight = parent->left->level;
    }

    parent->rightHeight = 0;
    if (parent->right == nullptr)
    {
        parent->rightHeight = 0;
    }
    else
    {
        parent->rightHeight = parent->right->level;
    }
    parent->level = 0;
    if (parent->leftHeight > parent->rightHeight)
    {
        parent->level = parent->leftHeight + 1;
    }
    else
    {
        parent->level = parent->rightHeight + 1;
    }

    return parent;
    grandparent->rightHeight = parent->leftHeight;
}

//balances the current node performing the proper rotations depending on balance factor
TreeNode* AVLTree::balance(TreeNode* node, int bF)
{
    TreeNode* child = nullptr;
    TreeNode* rootNode = nullptr;

    if (node == nullptr)
    {
        return nullptr;
    }
    else if (bF > 1)
    {
        child = node->left;
        int bfLeft = 0;
        if (child->left == nullptr)
        {
            bfLeft = 0;
        }
        else
        {
            bfLeft = child->left->level;
        }

        int bfRight = 0;
        if (child->right == nullptr)
        {
            bfRight = 0;
        }
        else
        {
            bfRight = child->right->level;
        }

        int balanceFactor = bfLeft - bfRight;
        if (balanceFactor > 0)
        {
            // left case
            return rotateLeftLeft(node);
        }
        else
        {
            // left right case
            node->left = rotateRightRight(child);
            return rotateLeftLeft(node);
        }
    }
    else if (bF < -1)
    {
        child = node->right;

        int bfLeft = 0;
        if (child->left == nullptr)
        {
            bfLeft = 0;
        }
        else
        {
            bfLeft = child->left->level;
        }

        int bfRight = 0;
        if (child->right == nullptr)
        {
            bfRight = 0;
        }
        else
        {
            bfRight = child->right->level;
        }

        int balanceFactor = bfLeft - bfRight;
        if (balanceFactor < 1)
        {
            // right right case
            return rotateRightRight(node);
        }
        else
        {
            // right left case
            node->right = rotateLeftLeft(child);
            return rotateRightRight(node);
        }
    }
}

//search function for AVLTree
bool AVLTree::search(string inputPassword, TreeNode* node)
{
    bool result = false;
    if(node->left == nullptr && node->right == nullptr && inputPassword.compare(node->password) != 0)
    {
        return result;
    }

    if(inputPassword.compare(node->password) == 0)
    {
        result = true;
        return result;
    }else if(inputPassword.compare(node->password) > 0)
    {
        result = search(inputPassword, node->right);
        return result;
    }else if(inputPassword.compare(node->password) < 0)
    {
        result = search(inputPassword, node->left);
        return result;
    }
}

int main()
{
    AVLTree myTree = AVLTree();
    string line;
    string value = "";
    string temp = "";
    string password;
    bool isKey = false;
    int numWords = 0;
    int index;
    fstream myfile;
    myfile.open("rockyou-original.txt");
    map<string, string> pwdKeeper;
    cout << "Initializing ...\n\n";

    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            // Finds the start index of line
            for (int i = 0; i < line.size(); i++)
            {
                if (line[i] != ' ')
                {
                    index = i;
                    break;
                }
            }

            // Finds count of words in password
            for (int i = index; i < line.size(); i++)
            {
                if (line[i] == ' ')
                {
                    numWords++;
                }
            }

            if (numWords > 1)
            {
                // Gets password uses and stores in value
                for (int i = index; i < line.size(); i++)
                {
                    if (line[i] == ' ')
                    {
                        index = i;
                        value = temp;
                        temp = "";
                        break;
                    }
                    else
                    {
                        temp += line[i];
                    }
                }

                // Gets password and stores in temp
                for (int i = index + 1; i < line.size(); i++)
                {
                    temp += line[i];

                    if (i == line.size() - 1)
                    {
                        pwdKeeper.emplace(temp, value);
                        temp = "";
                    }
                }
                index = -1;
            }
            else // if password only one word
            {
                // Grabs password uses and password for map
                for (int i = index; i < line.size() + 1; i++)
                {
                    if (line[i] != ' ' && isKey == false)
                    {
                        temp += line[i];
                    }
                    else if (line[i] == ' ' && isKey == false)
                    {
                        isKey = true;
                        value = temp;
                        temp = "";
                    }
                    else if (line[i] != ' ' && isKey == true)
                    {
                        temp += line[i];
                        if (i == line.size() - 1)
                        {
                            pwdKeeper.emplace(temp, value);
                            temp = "";
                            isKey = false;
                        }
                    }
                }
                index = -1;
                numWords = 0;
            }
        }
        myfile.close();
    }

    //stores value from map into the tree
    for(auto iter=pwdKeeper.begin(); iter!=pwdKeeper.end(); iter++)
    {
        TreeNode* node = new TreeNode(iter->first);
        myTree.insertNode(node);
    }

    string choice = "-1";
    cout << "Welcome to Password Strength Checker!" << endl;
    cout << "-------------------------------------" << endl << endl;

    bool toggleMap = true;
    while (choice != "6")
    {
        cout << endl;
        cout << "                   Password Menu" << endl;
        cout << "=====================================================" << endl;
        cout << "1. Generate a Strong Password for me                |" << endl;
        cout << "2. Check the strength of a password for me          |" << endl;
        cout << "3. Add a weak password to our database              |" << endl;
        cout << "4. Get number of accounts associated for a password |" << endl;
        cout << "5. Toggle search data structure (initialize as map) |" << endl;
        cout << "6. Exit                                             |" << endl;
        cout << "=====================================================\n" << endl;
        cout << "     Enter a menu choice option: ";
        getline(cin, choice);
        cout << endl;

        if (choice == "1")
        {
            //has no actual character limit, but encourages password of max length 80
            int num;
            int numChar;
            int specialChar;
            int uppercase;
            int lowercase;
            string tempStr;
            char special[] = "!#$\"%&\'\\()*+,-./:;<=>?@[]^_`{|}~";
            string pwd = "";

            cout << "Please enter the number of characters (between 0 and 20) for the following options." << endl;
            cout << "Number of digits [0-9]: ";
            getline(cin,tempStr);
            numChar = stoi(tempStr);

            cout << "Number of special characters (enter -1 to see special characters): ";
            getline(cin,tempStr);
            specialChar = stoi(tempStr);

            if (specialChar == -1)
            {
                cout << "Special characters include: ";
                // Prints special characters with spaces
                for (int i = 0; i < sizeof(special); i++)
                {
                    cout << special[i] << " ";
                }
                cout << endl;
                cout << "Number of special characters (enter -1 to see special characters): ";
                getline(cin, tempStr);
                specialChar = stoi(tempStr);
            }

            cout << "Number of uppercase characters: ";
            getline(cin, tempStr);
            uppercase = stoi(tempStr);

            cout << "Number of lowercase characters: ";
            getline(cin, tempStr);
            lowercase = stoi(tempStr);

            cout << "Generating a strong password for you ..." << endl;
            // Guarantees a strong password not included in the weak password database
            // makes a pseudorandom password for the count of characters chosen
            while (numChar != 0 || specialChar != 0 || uppercase != 0 || lowercase != 0)
            {
                // chooses type of character
                num = rand() % 4 + 1;
                // chooses random digit character
                if (num == 1 && numChar != 0)
                {
                    num = rand() % 10 + 48;
                    pwd += (char)num;
                    numChar--;
                }

                // chooses random special character
                else if (num == 2 && specialChar != 0)
                {
                    num = rand() % sizeof(special) + 0;
                    pwd += special[num];
                    specialChar--;
                }

                // chooses random Uppercase letter
                else if (num == 3 && uppercase != 0)
                {
                    num = rand() % 26 + 65;
                    pwd += (char)num;
                    uppercase--;
                }

                // chooses random Lowercase letter
                else if (num == 4 && lowercase != 0)
                {
                    num = rand() % 26 + 97;
                    pwd += (char)num;
                    lowercase--;
                }
            }

            cout << "\n*****************************************" << endl;
            cout << "* Your new password: " <<  pwd << endl;
            cout << "* " << endl;
            cout << "* \tPassword length: " << pwd.size() << endl;
            cout << "*****************************************" << endl;
        }
            // Tries to find user password in weak password database
        else if (choice == "2")
        {
            string p;
            cout << "Please enter a password: ";
            getline(cin, p);

            if(toggleMap)
            {
                if (pwdKeeper.find(p) == pwdKeeper.end())
                {
                    cout << "Not found in Map! You have a strong password!" << endl;
                } else
                    cout << "Found in Map! You have a weak password!" << endl;
            } else
            {
                if(myTree.search(p, myTree.root))
                {
                    cout << "Found in Tree! You have a weak password!" << endl;
                } else
                    cout << "Not found in Tree! You have a strong password!" << endl;
            }
        }
            // Adds a unique password to weak password data base
        else if (choice == "3")
        {
            string pwd;
            cout << "Please enter a unique password: ";
            getline(cin, pwd);

            if (pwdKeeper.find(pwd) == pwdKeeper.end())
            {
                pwdKeeper.emplace(pwd, "1");
                TreeNode* newPassword = new TreeNode(pwd);
                myTree.insertNode(newPassword);
                cout << "Database has been updated!" << endl;
            }
            else
                cout << "Password already found in database" << endl;
        }
            // Prints password uses for user's password if in weak password database
        else if (choice == "4")
        {
            string pwd;
            cout << "Please enter a password: ";
            getline(cin, pwd);

            if(pwdKeeper.find(pwd) != pwdKeeper.end())
                cout << "The password \"" << pwd << "\" protects " << pwdKeeper[pwd] << " accounts!" << endl;
            else
                cout << "Password not found in database." << endl;
        }
            //toggles choice between map and tree data structure
        else if (choice == "5")
        {
            if(toggleMap)
            {
                toggleMap = false;
                cout << "You have switched to search in Tree." << endl;
            } else
            {
                toggleMap = true;
                cout << "You have switched to search in Map." << endl;
            }
        }
            //exits the program
        else if (choice == "6")
        {
            cout << "Have a good day!" << endl;
        }
            //if user enters a invalid choice
        else
        {
            cout << "Invalid Option! Please select a number below." << endl;
        }
    }
}

