#include <iostream>
#define lln long long int
using namespace std;

struct Node
{
    int data;
    Node* leftchild;
    Node* rightchild;
    lln QQvalue = -20;
};

class tree
{
public:
    Node* root;
    int Node_num;
    tree(){
        root = NULL;
        Node_num = 0;
    };
    Node* Construct(char* A);
    void Inorder(Node* current);
    void Preorder(Node* current);
    void Postorder(Node* current);
    int height(Node* current);
    bool IsComplete(Node* current, int index);
    bool IsFoldable(Node* current);
    bool IsFoldable_recur(Node* leftNode, Node* rightNode);
    void DeleteLeaf(Node* current);
};

Node* tree::Construct(char* A)
{
    if(A[1] == ')') //**setting A[0] is '(';**
        return NULL;
    else {
        char num_char[8];
        int x = 1;
        int digits = 0;

        while(A[x] != '(')  num_char[digits++] = A[x++];//until num[x] = '('

        int num_int = 0;
        int digit_weight = 1;
        int index = digits - 1;

        if(num_char[0] == '-'){
            while(index != 0){
                num_int = num_int + digit_weight * (num_char[index--] - '0');
                digit_weight *= 10;
            }
            num_int = -num_int;
        }
        else{//num_char[0] != '-'
            while(index != -1){
                num_int = num_int + digit_weight * (num_char[index--] - '0');
                digit_weight *= 10;
            }
        }

        Node* NewNode = new Node;
        NewNode->data = num_int;
        Node_num++;

        int temp_left = x;//&A[temp_right]->right tree address

        int n_right = 0;//numbers of right parentheses
        int n_left = 1;//numbers of left parentheses
        while(n_right != n_left)
        {
            x++;
            if(A[x] == '(')
                n_left++;
            else if(A[x] == ')')
                n_right++;
        }

        int temp_right = ++x;//&A[temp_left]->left tree address

        NewNode->leftchild = Construct(&A[temp_left]);
        NewNode->rightchild = Construct(&A[temp_right]);
        return NewNode;
        }
}

void tree::Inorder(Node* current)
{
    if(current){
        Inorder(current->leftchild);
        cout << current->data << " ";
        Inorder(current->rightchild);
    }
    else
        return;
}

void tree::Preorder(Node* current)
{
    if(current){
        cout << current->data << " ";
        Preorder(current->leftchild);
        Preorder(current->rightchild);
    }
    else
        return;
}
void tree::Postorder(Node* current)
{
    if(current){
        Postorder(current->leftchild);
        Postorder(current->rightchild);
        cout << current->data << " ";
    }
    else
        return;
}

int tree::height(Node* current)
{
    if(!current)
        return 0;
    else
        return 1 + max((height(current->leftchild)),(height(current->rightchild)));
}

bool tree::IsComplete(Node* current, int index)
{
    if(current == NULL)
        return 1;
    if(index > Node_num)
        return 0;
    return (IsComplete(current->leftchild, 2*index) && IsComplete(current->rightchild, 2*index + 1));
}

bool tree::IsFoldable(Node* current)
{
    if(!current)
        return true;
    else
        return IsFoldable_recur(current->leftchild, current->rightchild);
}
bool tree::IsFoldable_recur(Node* leftNode, Node* rightNode)
{
    if(leftNode == NULL && rightNode == NULL)
        return true;
    else if(leftNode == NULL || rightNode == NULL)
        return false;
    else
        return (IsFoldable_recur(leftNode->leftchild, rightNode->rightchild) && IsFoldable_recur(leftNode->rightchild, rightNode->leftchild));
}

void tree::DeleteLeaf(Node* current)
{
    if(!current)
        return;
    if(current->leftchild == NULL && current->rightchild == NULL){
        delete current;
        root = NULL;
        return;
    }
    if(current->leftchild){
        if(current->leftchild->leftchild == NULL && current->leftchild->rightchild == NULL){
            delete current->leftchild;
            current->leftchild = NULL;
        }
        else
            DeleteLeaf(current->leftchild);
    }
    if(current->rightchild){
        if(current->rightchild->leftchild == NULL && current->rightchild->rightchild == NULL){
            delete current->rightchild;
            current->rightchild = NULL;
        }
        else
            DeleteLeaf(current->rightchild);
    }
}

lln MaxQQ(Node* current);

lln QQ_Cal(Node* current)
{
    lln QQ = 0;
    if (current->leftchild)
        QQ = QQ + MaxQQ(current->leftchild->leftchild) + MaxQQ(current->leftchild->rightchild);
    if (current->rightchild)
        QQ = QQ + MaxQQ(current->rightchild->leftchild) + MaxQQ(current->rightchild->rightchild);
    return QQ;
}

lln MaxQQ(Node* current)
{
    lln pick, notpick;
    if (current == NULL)
        return 0;
    if (current->QQvalue >= 0)
        return current->QQvalue;

    if(current->data >= 0)
        pick = current->data + QQ_Cal(current);
    else
        pick = QQ_Cal(current);

    notpick = MaxQQ(current->leftchild) + MaxQQ(current->rightchild);

    if(pick >= notpick) {
        current->QQvalue = pick;
        return pick;
    }
    else {
        current->QQvalue = notpick;
        return notpick;
    }
}

int main (){
    char* str = new char [10000000];
    while(cin >> str){
        tree T;
        T.root = T.Construct(&str[0]);
        T.Preorder(T.root);
        cout << endl;
        T.Inorder(T.root);
        cout << endl;
        T.Postorder(T.root);
        cout << endl;

        cout << T.height(T.root) << endl;

        if(T.IsComplete(T.root, 1))
            cout << "Complete" << endl;
        else
            cout << "Not complete" << endl;

        if(T.IsFoldable(T.root))
            cout << "Foldable" << endl;
        else
            cout << "Not foldable" << endl;

        cout << MaxQQ(T.root) << endl;

        T.DeleteLeaf(T.root);

        T.Preorder(T.root);
        cout << endl;
        T.Inorder(T.root);
        cout << endl;
        T.Postorder(T.root);
        cout << endl;
    }
    return 0;
}

