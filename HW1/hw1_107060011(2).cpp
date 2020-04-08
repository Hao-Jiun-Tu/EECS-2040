#include <iostream>
#define lln long long int
using namespace std;

class Stack{
    private:
        int top;
        int capacity;
        char *arr;
    public:
        Stack(int BagCapacity);
        bool IsEmpty();
        void Push(char val);
        char Pop();
        void ChangeSize1D();
        char Operator();
        ~Stack();
};
Stack::Stack(int BagCapacity){
	capacity = BagCapacity;
	arr = new char [capacity];
    top = -1;
}

bool Stack::IsEmpty(){
        return (top == -1);
}
void Stack::Push(char val){
	if(capacity == top + 1){
		ChangeSize1D();
		arr[++top] = val;
	}
	else
		arr[++top] = val;
}
char Stack::Pop(){
    if(!IsEmpty()){
		char Pop_char = arr[top--];
		return Pop_char;
    }
    else
        return '\0';
}
void Stack::ChangeSize1D(){
	char *temp = new char [capacity*2];
	for(int i = 0;i < capacity;i++)
		temp[i] = arr[i];
	delete [] arr;
	arr = temp;
	capacity *= 2; 
}
char Stack::Operator(){
    if(!IsEmpty())
        return arr[top];
    else
        return '\0';
}
Stack::~Stack(){
	delete [] arr;
}
/*****************************************Build the Output Stack******************************************/
class Stack_out{
    private:
        int top;
        int capacity;
        lln *arr; 
    public:
        Stack_out(int BagCapacity);
        bool IsEmpty();

        void Push(lln val);
        lln Pop();
        void ChangeSize1D();
        ~Stack_out();
};
Stack_out::Stack_out(int BagCapacity){
    capacity = BagCapacity;
	arr = new lln [capacity];
    top = -1;
}

bool Stack_out::IsEmpty(){
        return (top == -1);
}
void Stack_out::Push(lln val){
	if(capacity == top + 1){
		ChangeSize1D();
		arr[++top] = val;
	}
	else
		arr[++top] = val;
}
lln Stack_out::Pop(){
    if(!IsEmpty()){
		lln Pop_char = arr[top--];
		return Pop_char;
    }
    else
        return 0;
}
void Stack_out::ChangeSize1D(){
	lln *temp = new lln [capacity*2];
	for(int i = 0;i < capacity;i++)
		temp[i] = arr[i];
	delete [] arr;
	arr = temp;
	capacity *= 2; 
}
Stack_out::~Stack_out(){
	delete [] arr;
}
/**************************************************************************************************************/
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
int main()
{
    char *infix = new char [2600];
    while(cin >> infix)
    {
        int i = 0, j = 0, last;
        while(infix[i++] != '\0');//counting number!
		last = i - 1;
		i = j = 0;
        char ch;
/********************************************infix_to_postfix**********************************************/
        Stack *s1 = new Stack(4);
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
        while(!(s1->IsEmpty()))
        	postfix[j++] = s1->Pop();
        	
        postfix[j] = '\0';
        cout << postfix << endl;
/********************************************infix_to_prefix**********************************************/
        Stack *s2 = new Stack(4);
        char *prefix = new char [2600];
        i = j = last;
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
        while(!(s2->IsEmpty()))
			prefix[j--] = s2->Pop();
			
        for(int i = j+1; i <= last; i++)
            cout << prefix[i];
        cout << endl;
/*****************************************Calculating the Output******************************************/
        Stack_out *s3 = new Stack_out(4);
        lln output;
        lln b, a;
        i = 0;
        while(postfix[i] != '\0')
        {
            if(postfix[i] >= '0' && postfix[i] <= '9'){
                s3->Push((lln)(postfix[i]-'0'));
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
