#include <iostream>
#include <string>

using namespace std;
    
// Compressed trie node
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
void insertCompressed(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
  
    for (int i = 0; i < key.length(); i++)
    {
        if (pCrawl->node != "")
        {
            for (int j = 0; j < pCrawl->node.length() && i < key.length(); j++)
            {
                if(key[i] == pCrawl->node[j])
                    i++;
                else
                {
                    struct TrieNode *pNodeSplit =  getNode();
                        
                    pNodeSplit->zeroChild = pCrawl->zeroChild;
                    pNodeSplit->oneChild = pCrawl->oneChild;
                    pNodeSplit->node = pCrawl->node.substr(j+1, pCrawl->node.length()-(j+1));

                    struct TrieNode *pNodeNew =  getNode();
                    
                    pNodeNew->node = key.substr(i+1, key.length()-(i+1));
                    if('0' == pCrawl->node[j])
                    {
                        pCrawl->zeroChild = pNodeSplit;
                        pCrawl->oneChild = pNodeNew;
                    }
                    else
                    {
                        pCrawl->zeroChild = pNodeNew;
                        pCrawl->oneChild = pNodeSplit;
                    }
                    std::cout << "new node added " << pNodeNew->node << endl;
                    std::cout << "split node " << pCrawl->node;
                    std::cout << " into " << pCrawl->node.substr(0, j);
                    std::cout << " and " << pNodeSplit->node << endl;
                    pCrawl->node = pCrawl->node.substr(0, j);

                    return;
                }
            }
        }
        if('0' == key[i])
        {
            if(pCrawl->zeroChild != NULL)
                pCrawl = pCrawl->zeroChild;
            else
            {
                pCrawl->node = key.substr(i, key.length()-i);
                std::cout << "new node added " << pCrawl->node << endl;
                return;
            }
        }
        else
        {
            if(pCrawl->oneChild != NULL)
                pCrawl = pCrawl->oneChild;
            else
            {
                pCrawl->node = key.substr(i, key.length()-i);
                std::cout << "new node added " << pCrawl->node << endl;
                return;
            }
        }
    }
}

// Returns true if key is present in the compressed trie if prefixSearch is set to false, else
// false
// If prefixSearch is set to true, returns true also when the key
// is a prefix of any element in the compressed trie
bool searchCompressed(struct TrieNode *root, string key, bool prefixSearch)
{
    struct TrieNode *pCrawl = root;
    int nodeIndex = 0, keyIndex = 0; 
  
    for (; keyIndex < key.length(); keyIndex++)
    {
        if (pCrawl->node != "")
        {
            
            for (nodeIndex = 0; nodeIndex < pCrawl->node.length() && keyIndex < key.length(); nodeIndex++)
            {
                if(key[keyIndex] == pCrawl->node[nodeIndex])
                    keyIndex++;
                else
                    return false;
            }
        }

        if(keyIndex < key.length())
        {
            if('0' == key[keyIndex])
            {
                if(pCrawl->zeroChild != NULL)
                    pCrawl = pCrawl->zeroChild;
                else
                    return false;
            }
            else
            {
                if(pCrawl->oneChild != NULL)
                    pCrawl = pCrawl->oneChild;
                else
                    return false;
            }
        }
    }

    if(false == prefixSearch)
    {
        if((NULL == pCrawl->zeroChild) && (NULL == pCrawl->oneChild) &&
           (nodeIndex >= pCrawl->node.length()))
            return true;
        else
            return false;
    }
    
    return true;
}

// Prints the nodes present in the compressed trie
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
    // Input keys (use only '0' or '1')
    string keys[] = {"001001010", "0010011010010", "00100110101", "00100101111"};
    int n = sizeof(keys)/sizeof(keys[0]);
  
    struct TrieNode *root = getNode();

    for (int i = 0; i < n; i++)
        insertCompressed(root, keys[i]);

    std::cout << endl;
    printCompressedTrieNodes(root);

    std::cout << endl;
    searchCompressed(root, "0010011010010", false)? std::cout << "Yes\n" :
                          std::cout << "No\n";
    searchCompressed(root, "00100110101", false)? std::cout << "Yes\n" :
                                   std::cout << "No\n";
    searchCompressed(root, "001001011", false)? std::cout << "Yes\n" :
                          std::cout << "No\n";

    searchCompressed(root, "00100110100", true)? std::cout << "Yes\n" :
                          std::cout << "No\n";

    return 0;
}
