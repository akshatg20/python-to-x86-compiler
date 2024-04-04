/* 
This is a model file that demonstrates the logic used to make AST:

Assumptions:
1. hierarchy of operands is maintained
2. hierarchy of operators, unless they are used with operands are not maintained
3. all operators and operands are propagated upwards unless they destroy hierarchy or they are useful to disambiguate things
3. all operators in a production are assumed to have same precedence (precedence is disambiguated using CFG of parser)
5. operands when used without an explicit operator are assumed to have an implicit operator
6. Unspecified optr/operand flag is assumed to be operand. Similarly we assume operand when both optr and operand flags are set to true

Usage: For each production, send the node corresponding to all ternimals and non-terminals with optional content and mandatory specification of optr/operand;
Example 
S : a B {$$ = processNode("S",2,$1,createNode("B",$1,operand=true))};

*/


#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct ASTNode {
    std::string type;
    std::string content;
    std::vector<ASTNode*> children;

    bool optr;
    bool operand;

    ASTNode(std::string type, std::string content = "", bool optr=false,bool operand = false) : type(type), content(content), optr(optr),  operand(operand) {}
};
typedef struct ASTNode ASTNode;

ASTNode* createNode(std::string type, std::string content = "",bool optr=false,bool operand = false) 
{

    return new ASTNode(type, content,optr,operand);
}

int counter = 0;
ASTNode* root;

ASTNode* processNodes(string name,int numNodes, ...) 
{
    std::vector<ASTNode*> arr;
    
    va_list args;
    va_start(args, numNodes);

    for (int i = 0; i < numNodes; ++i) 
    {
        ASTNode* arg = va_arg(args, ASTNode*);
        arr.push_back(arg);
    }

    va_end(args);

    ASTNode* node = nullptr;
    std::vector<ASTNode*> optrs;
    std::vector<ASTNode*> operands;
    bool flag = false;
    std::string content = "";

    // populate vector (do loop for it)
    for(int x=0;x<arr.size();x++)
    {
        ASTNode* i = arr[x];
        if(i!=NULL)
        {
                if(i->optr && !i->operand)
                {
                        optrs.push_back(i);
                }
                else // operand set, none set or both set
                {
                        operands.push_back(i);
                }
        }
    }

    for(int x=0;x<optrs.size();x++)
    {
        ASTNode* i = optrs[x];
        cout<<"HEY"<<endl;

        if(flag)
        {
                content += " [SEP] " + i->content;
        }
        else
        {
            cout<<content<<endl;
                content += i->content;
        }
        flag=true;
    }

    // Single Case:
    if((optrs.size() + operands.size())==1)
    {
            if(optrs.size()==1)
            {
                    node = optrs[0];
                    node->optr = true;
            }
            else
            {
                    node = operands[0];
                    node->operand = true;
            }
    }
    else
    {
            cout<<"Doer"<<endl;
            cout<<content<<endl;

            node = createNode(name, content);
            node->optr = flag;

            for(int x=0;x<operands.size();x++)
            {
                ASTNode* i = operands[x];

                node->children.push_back(i);
                node->operand = true;
            }
    }

    optrs.clear();
    operands.clear();

    return node;
}


int getNewId() 
{
    cout<<counter<<endl;
    return ++counter;
}

string dquote_to_html(string s)
{
    string temp = "";
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='"')
            temp = temp + "&quot;";
        else
            temp = temp + s[i]; 
    }
    return temp;
}

// write tree to dot file with node, id and filename
pair<string,string> writeTree2(ASTNode* node,int id) 
{
    string def = "";
    string arr = "";

    def = def +  "node" + std::to_string(id) + " [label=\"" + node->type + " (" + dquote_to_html(node->content) + ")\"];\n";

    for (int i = 0; i < node->children.size(); i++) 
    {
        int childId = getNewId();
        arr = arr + "node" + std::to_string(id) + " -- node" + std::to_string(childId) + ";\n";

        pair<string,string> p = writeTree2(node->children[i], childId);
        
        def = def + p.first;
        arr = arr + p.second;
    }
    return pair<string,string>(def,arr);
}

// write tree to dot file with node, id and filename
void writeTree(ASTNode* node,int id, std::string filePath) 
{

    // writing it as string
    string def = "";
    string arr = "";

    def = def +  "node" + std::to_string(id) + " [label=\"" + node->type + " (" + dquote_to_html(node->content) + ")\"];\n";

    for (int i = 0; i < node->children.size(); i++) 
    {
        int childId = getNewId();
        arr = arr + "node" + std::to_string(id) + " -- node" + std::to_string(childId) + ";\n";

        pair<string,string> p = writeTree2(node->children[i], childId);
        
        def = def + p.first;
        arr = arr + p.second;
    }
    string stringContent = def + "\n" + arr;
    // over with string
    
    std::ofstream file;
    file.open(filePath, std::ios_base::app);
    file << stringContent<<endl;
    file.close();
}


int main()
{
    // // Example 1:
    // ASTNode* a = createNode("num","5");
    // a->operand = true;
    // ASTNode* b = createNode("num","10");
    // b->operand = true;
    // ASTNode* c = createNode("plus","+");
    // c->optr = true;
    // root = processNodes("expr",3,a,c,b);


    // // Example 2:
    // ASTNode* a = createNode("num","5");
    // a->operand = true;
    // ASTNode* root = processNodes("num",1,a);

    // // Example 3:
    // ASTNode* a = createNode("num","5");
    // a->operand = true;
    // ASTNode* b = processNodes("num",1,a);
    // ASTNode* c =processNodes("num",1,b);

    // // Example 4:
    // ASTNode* a = createNode("plus","+");
    // a->optr = true;
    // ASTNode* b = processNodes("exp",1,a);
    // ASTNode* c =processNodes("exp",1,b);

    // // Example 5:
    // ASTNode* a = createNode("plus","+");
    // a->optr = true;
    // ASTNode* b = createNode("minus","-");
    // b->optr = true;
    // ASTNode* c =processNodes("exp",2,a,b);
    // ASTNode* d = createNode("into","*");
    // d->optr = true;
    // ASTNode* e =processNodes("exp",2,c,d);

    // // Example 6:
    // ASTNode* a = createNode("plus","+");
    // a->operand = true;
    // ASTNode* b = createNode("minus","-");
    // b->operand = true;
    // ASTNode* c =processNodes("exp",2,a,b);
    // ASTNode* d = createNode("into","*");
    // d->operand = true;
    // ASTNode* e =processNodes("exp",2,c,d);

    // Example 7:
    ASTNode* a = createNode("plus","+");
    a->operand = true;
    ASTNode* b = createNode("minus","-");
    b->operand = true;
    ASTNode* z = createNode("num","5");
    z->optr = true;
    ASTNode* c =processNodes("exp",3,a,b,z);
    ASTNode* d = createNode("into","*");
    d->operand = true;
    ASTNode* e =processNodes("exp",2,c,d);


    writeTree(e, getNewId(), "parse_tree.dot");


}

