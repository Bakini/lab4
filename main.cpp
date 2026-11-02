#include <iostream>
#include <string>
#include <cstdlib>

struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* CreateTree(Node* root,Node* r,int data){
    if(r==nullptr){
        r=(Node*)malloc(sizeof(struct Node));
        if(r==nullptr){
            std::cout<<"Ощибка выделения памяти";
            exit(EXIT_FAILURE);
        }
        r->left=nullptr;
        r->right=nullptr;
        r->data=data;
        if(root==nullptr)return r;
        if(data>root->data)root->right=r;
        else root->left=r;//в поле лефт узла 8 записывается адрес узла 4
        return r;
    }
    if(data>r->data){
        CreateTree(r,r->right,data);
    }
    else if(data<r->data){
        CreateTree(r,r->left,data);
    }
    return root;
}

void print_tree(Node* r,int I){
    if(r==nullptr){
        return;
    }
    print_tree(r->right,I+1);
    for(int i=0;i<I;i++){
        std::cout<<" ";
    }
    std::cout<<r->data<<"\n";
    print_tree(r->left,I+1);
}

bool search(Node* r,int value){
    while(r!=nullptr){
        if(r->data==value){
            return true;
        }
        if(value<r->data){
            r=r->left;
        }
        else{
            r=r->right;
        }
    }
}

int main(){
    int D,start=1;

    Node* root=nullptr;
    std::cout<<"-1 - окончание  построения дерева\n";
    while(start){
        std::cout<<"Введите число: ";
        std::cin>>D;
        if(D==-1){
            std::cout<<"Построение дерева окончено\n\n";
            start=0;
        }
        else{
            root=CreateTree(root,root,D);
        }
    }
    print_tree(root,0);
    std::cout<<"Введите число для поиска: ";
    std::cin>>D;
    if(search(root,D)){
        std::cout<<"Число найдено\n";
    }else{
        std::cout<<"Число не найдено\n";
    }
    return 0;
}
