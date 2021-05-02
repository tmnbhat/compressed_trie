#include <iostream>
#include <string>

using namespace std;
    
// trie node
struct TrieNode
{
    struct TrieNode *zeroChild;
    struct TrieNode *oneChild;

    string node;
};
  
// Returns new trie node (initialized to NULLs)
struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;
  
    pNode->zeroChild = NULL;
    pNode->oneChild = NULL;
    pNode->node="";
  
    return pNode;
}
  
// If not present, inserts key into trie
// If the key is prefix of trie node, just
// marks leaf node
void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        if('0' == key[i])
        {
            if (NULL == pCrawl->zeroChild)
                pCrawl->zeroChild = getNode();
            pCrawl = pCrawl->zeroChild;    
        }
        else
        {
            if (NULL == pCrawl->oneChild)
                pCrawl->oneChild = getNode();
            pCrawl = pCrawl->oneChild;
        }
    }
}
  
// Returns true if key presents in trie, else
// false
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        if('0' == key[i])
        {
            if (NULL == pCrawl->zeroChild)
                return false;
            pCrawl = pCrawl->zeroChild;
        }
        else
        {
            if (NULL == pCrawl->oneChild)
                return false;
            pCrawl = pCrawl->oneChild;
        }
    }
    if (pCrawl != NULL &&
       (NULL == pCrawl->zeroChild || NULL == pCrawl->oneChild))
    {
        return true;
    }
    else
        return false;
}

bool isPrefix(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        if('0' == key[i])
        {
            if (NULL == pCrawl->zeroChild)
                return false;
            pCrawl = pCrawl->zeroChild;
        }
        else
        {
            if (NULL == pCrawl->oneChild)
                return false;
            pCrawl = pCrawl->oneChild;
        }
    }

    return true;    
}

void compressTrie(TrieNode *root)
{
    struct TrieNode *pCrawl = root;
    string nodeSoFar = "";
    bool isLeafNode = false;
    struct TrieNode *temp;

    if( (pCrawl->zeroChild != NULL) && (pCrawl->oneChild == NULL) )
    {
        nodeSoFar.append("0");
        pCrawl = pCrawl->zeroChild;
        while(true)
        {
            if( (pCrawl->zeroChild != NULL) && (pCrawl->oneChild == NULL) )
            {
                nodeSoFar.append("0");
                temp = pCrawl->zeroChild;
                delete pCrawl;
                //std::cout << "deleted node was 0" << endl;
                pCrawl = temp;
            } 
            else if( (pCrawl->zeroChild == NULL) && (pCrawl->oneChild != NULL) )
            {
                nodeSoFar.append("1");
                temp = pCrawl->oneChild;
                delete pCrawl;
                //std::cout << "deleted node was 1" << endl;
                pCrawl = temp;
            }
            else if( (pCrawl->zeroChild == NULL) && (pCrawl->oneChild == NULL) )
            {
                isLeafNode = true;
                break;
            }
            else
            {
                break;
            }
        }
        root->node = nodeSoFar;
        std::cout << "node added " << root->node << endl;
        root->zeroChild = pCrawl->zeroChild;
        root->oneChild = pCrawl->oneChild;
    }
    else if( (pCrawl->zeroChild == NULL) && (pCrawl->oneChild != NULL) )
    {
        nodeSoFar.append("1");
        pCrawl = pCrawl->oneChild;
        while(true)
        {
            if( (pCrawl->zeroChild != NULL) && (pCrawl->oneChild == NULL) )
            {
                nodeSoFar.append("0");
                temp = pCrawl->zeroChild;
                delete pCrawl;
                //std::cout << "deleted node was 0" << endl;
                pCrawl = temp;
            } 
            else if( (pCrawl->zeroChild == NULL) && (pCrawl->oneChild != NULL) )
            {
                nodeSoFar.append("1");
                temp = pCrawl->oneChild;
                delete pCrawl;
                //std::cout << "deleted node was 1" << endl;
                pCrawl = temp;
            }
            else if( (pCrawl->zeroChild == NULL) && (pCrawl->oneChild == NULL) )
            {
                isLeafNode = true;
                break;
            }
            else
            {
                break;
            }
        }
        root->node = nodeSoFar;
        std::cout << "node added " << root->node << endl;
        root->zeroChild = pCrawl->zeroChild;
        root->oneChild = pCrawl->oneChild;
    }
    else if( (pCrawl->zeroChild == NULL) && (pCrawl->oneChild == NULL) )
    {
        isLeafNode = true;
    }

    if(false == isLeafNode)
    {
        temp = root->oneChild;
        compressTrie(root->zeroChild);
        compressTrie(temp);
    }

    return;
}

void printCompressedTrieNodes(TrieNode *root)
{
    struct TrieNode *pCrawl = root;

    std::cout << "node = " << pCrawl->node << endl;
    if (pCrawl->zeroChild != NULL)
    {
        printCompressedTrieNodes(pCrawl->zeroChild); 
    }
    pCrawl = root;
    if (pCrawl->zeroChild != NULL)
    {
        printCompressedTrieNodes(pCrawl->oneChild); 
    }
}
  
// Driver
int main()
{
    // Input keys (use only '0' or '1'
    string keys[] = {"001001010", "0010011010010", "00100110101"};
    int n = sizeof(keys)/sizeof(keys[0]);
  
    struct TrieNode *root = getNode();
  
    // Construct trie
    for (int i = 0; i < n; i++)
        insert(root, keys[i]);
  
    // Search for different keys
    search(root, "00100110101")? std::cout << "Yes\n" :
                                   std::cout << "No\n";
    search(root, "001001011")? std::cout << "Yes\n" :
                          std::cout << "No\n";

    isPrefix(root, "0010011010")? std::cout << "Yes\n" :
                          std::cout << "No\n";

    struct TrieNode *pCrawl = root;
    compressTrie(pCrawl);
    pCrawl = root;
    printCompressedTrieNodes(pCrawl);

    return 0;
}
