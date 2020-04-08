#include <string>
#include <iostream>
#include <cstdio>
using namespace std;

class Node
{
public:
    Node(){
        this->next = NULL;
    }
    Node(const int element , Node *next){
        this->data = element;
        this->next = next;
    }
    ~Node(){
        this->next = NULL;
    }
    friend class Chain;
    Node *next;
    int data;
};


class Chain
{
public:

    Chain(){
        head = NULL;
    }
    Chain(Node *head){
        this->head = head;
    }
    void InsertBack(int data);
    void InsertFront(int data);
    void InsertAfter(int data,int data_ref);
    void InsertBefore(int data,int data_ref);
    void Delete(int data);
    void DeleteFront();
    void DeleteBack();
    void Reverse();
    void Rotate(int k);
    void Swap(int k, int j);


    bool IsEmpty(){
        return this->head == NULL;
    }

    std::string PrintChain(){
        Node *cur = this->head;
        std::string result = "";
        if(cur == NULL){
            result = "Empty";
            return result;
        }
        while(cur != NULL){

            int num = cur->data;
            std::string num_str = std::to_string(num);
            result.append(num_str);
            if(cur -> next){
                result.append("->");
            }
            cur = cur->next;
        }
        return result;
    }


    Node *head;
};

// void Chain::InsertBack(int data){

// }
// ..... implement the operations


int main()
{

    Chain inst = *(new Chain());

    string command;
    int data , data_ref;

    while(cin>>command){
        if(command == "InsertBack"){
            cin>>data;
            inst.InsertBack(data);
        }else if(command == "InsertFront"){
            cin>>data;
            inst.InsertFront(data);
        }else if(command == "InsertAfter"){
            cin>>data>>data_ref;
            inst.InsertAfter(data , data_ref);
        }else if(command == "InsertBefore"){
            cin>>data>>data_ref;
            inst.InsertBefore(data , data_ref);
        }else if(command == "Delete"){
            cin>>data;
            inst.Delete(data);
        }else if(command == "DeleteFront"){
            inst.DeleteFront();

        }else if(command == "DeleteBack"){
            inst.DeleteBack();

        }else if(command == "Reverse"){
            inst.Reverse();
        }else if(command == "Rotate"){
            int k;
            cin>>k;
            inst.Rotate(k);
        }else if(command == "Swap"){
            int j,k;
            cin>>j>>k;
            inst.Swap(j,k);
        }
        else if(command == "PrintChain"){

            cout<<inst.PrintChain()<<endl;
        }
    }
    
    return 0;
}

 

