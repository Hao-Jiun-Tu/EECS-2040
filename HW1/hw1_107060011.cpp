#include <iostream>
using namespace std;

struct Node{
    char data;
    Node *preNode;
};
class Stack{
    private:
        Node *top;
    public:
        Stack();
        bool IsEmpty();
        void Push(char val);
        char Pop();
        char Operator();
};
Stack::Stack(){
    top = NULL;
}

bool Stack::IsEmpty(){
        return (top == NULL);
}
void Stack::Push(char val){
    Node *temp = new Node;
    temp->data = val;//record new Node data
    temp->preNode = top;//record the preNode ptr
    top = temp;//new Node
}
char Stack::Pop(){
    if(!IsEmpty()){
        char Pop_val = top->data;
        top = top->preNode; //point to preNode
        return Pop_val;
    }
    else
        return '\0';
}
char Stack::Operator(){
    if(!IsEmpty())
        return top->data;
    else
        return '\0';
}
/*****************************************Build the Output Stack******************************************/
struct Node_out{
    long long int data;
    Node_out *preNode;
};
class Stack_out{
    private:
        Node_out *top;
    public:
        Stack_out();
        bool IsEmpty();

        void Push(long long int val);
        long long int Pop();
};
Stack_out::Stack_out(){
    top = NULL;
}

bool Stack_out::IsEmpty(){
        return (top == NULL);
}
void Stack_out::Push(long long int val){
    Node_out *temp = new Node_out;
    temp->data = val;//record new Node data
    temp->preNode = top;//record the preNode ptr
    top = temp;//new Node
}
long long int Stack_out::Pop(){
    if(!IsEmpty()){
        long long int Pop_val = top->data;
        top = top->preNode;
        return Pop_val;
    }
    else
        return 0;
}
/************************************************************************************************/
int FindPriority(char ch);
int main()
{
    char *infix = new char [2600];
    while(cin >> infix)
    {
        int i = 0, j = 0, last;
        char ch;
        while(infix[i++] != '\0');//counting number!
        infix[i+1] = '\0';
        last = i;
        infix[i--] = ')';
        while(i > 0)
        {
            infix[i] = infix[i-1];
            i--;
        }
        infix[i] = '(';
        i = j = 0;
/********************************************infix_to_postfix**********************************************/
        Stack *s1 = new Stack();
        char *postfix = new char [2600];
        while(infix[i] != '\0')
        {
            if(infix[i] == '('){
               s1->Push(infix[i]);
            }
            else if(infix[i] >= '0' && infix[i] <= '9'){
                postfix[j++] = infix[i];
            }
            else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
            {
                while(s1->Operator() == '+' || s1->Operator() == '-' || s1->Operator() == '*' || s1->Operator() == '/')
                {
                    if(FindPriority(s1->Operator()) >= FindPriority(infix[i])){
                        postfix[j++] = s1->Pop();
                    }
                    else
                        break;
                }
                s1->Push(infix[i]);
            }
            else if(infix[i] == ')')
            {
                while((ch = s1->Pop()) != '(')
                        postfix[j++] = ch;
            }
            i++;
        }
        postfix[j] = '\0';
        cout << postfix << endl;
/********************************************infix_to_prefix**********************************************/
        Stack *s2 = new Stack();
        char *prefix = new char [2600];
        i = last, j = last;
        while(i != -1)
        {
            if(infix[i] == ')'){
               s2->Push(infix[i]);
            }
            else if(infix[i] >= '1' && infix[i] <= '9'){
                prefix[j--] = infix[i];
            }
            else if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
            {
                while(s2->Operator() == '+' || s2->Operator() == '-' || s2->Operator() == '*' || s2->Operator() == '/')
                {
                    if(FindPriority(s2->Operator()) > FindPriority(infix[i])){
                        prefix[j--] = s2->Pop();
                    }
                    else
                        break;
                }
                s2->Push(infix[i]);
            }
            else if(infix[i] == '(')
            {
                while((ch = s2->Pop()) != ')')
                        prefix[j--] = ch;
            }
            i--;
        }
        for(int i = j+1; i <= last; i++)
            cout << prefix[i];
        cout << endl;
/*****************************************Calculating the Output******************************************/
        Stack_out *s3 = new Stack_out();
        long long int output;
        long long int b, a;
        i = 0;
        while(postfix[i] != '\0')
        {
            if(postfix[i] >= '0' && postfix[i] <= '9'){
                s3->Push((long long int)(postfix[i]-'0'));
            }
            else{
                if(postfix[i] == '+'){
                     b = s3->Pop();
                     a = s3->Pop();
                     output = a + b;
                     s3->Push(output);
                }
                if(postfix[i] == '-'){
                     b = s3->Pop();
                     a = s3->Pop();
                     output = a - b;
                     s3->Push(output);
                }
                if(postfix[i] == '*'){
                     b = s3->Pop();
                     a = s3->Pop();
                     output = a * b;
                     s3->Push(output);
                }
                if(postfix[i] == '/'){
                     b = s3->Pop();
                     a = s3->Pop();
                     output = a / b;
                     s3->Push(output);
                }
            }
            i++;
        }
        output = s3->Pop();
        cout << output << endl;

        delete [] postfix;
        delete [] prefix;
        delete s1;
        delete s2;
        delete s3;
    }
    return 0;
}
int FindPriority(char ch){
    switch(ch)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
}
