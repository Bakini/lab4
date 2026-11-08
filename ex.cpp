#include <iostream>

struct Node{
    int data;
    Node* left;
    Node* right;
};

Node* CreateTree(Node* root,Node* r,int data){
    if(r==nullptr){
        r=new Node{data,nullptr,nullptr};
        if(root==nullptr)return r;
        if(data>root->data)root->right=r;
        else root->left=r;
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

void print_tree(Node* r,int level){
    if(r==nullptr)return;
    print_tree(r->right,level+1);
    for(int i=0;i<level;i++){
        std::cout<<'\t';
    }
    std::cout<<r->data<<'\n';
    print_tree(r->left,level+1);
}

int search(Node* r,int value){
    int depth=0;
    while(r!=nullptr){
        if(r->data==value)return depth;
        if(value<r->data){
            r=r->left;
        }
        else{
            r=r->right;
        }
        depth++;
    }
    return -1;
}

Node* delete_node(Node* r,int value){
    if(r==nullptr)return nullptr;
    if(value<r->data){
        r->left=delete_node(r->left,value);
    }
    else if(value>r->data){
        r->right=delete_node(r->right,value);
    }
    else{
        if(r->left==nullptr){
            Node* temp=r->right;
            delete r;
            return temp;
        }
        if(r->right==nullptr){
            Node* temp=r->left;
            delete r;
            return temp;
        }
        Node* temp=r->right;
        while(temp->left!=nullptr){
            temp=temp->left;
        }
        r->data=temp->data;
        r->right=delete_node(r->right,temp->data);
    }
    return r;
}

int count_occurrences(Node* r,int value){
    if(r==nullptr)return 0;
    int count=0;
    if(r->data==value){
        count=1;
    }
    return count+count_occurrences(r->left,value)
                +count_occurrences(r->right,value);
}

void delete_tree(Node* r){
    if(r==nullptr)return;
    delete_tree(r->left);
    delete_tree(r->right);
    delete r;
}

int main(){
    int D;
    Node* root=nullptr;
    std::cout<<"-1 - окончание построения дерева\n";
    while(true){
        std::cout<<"Введите число: ";
        if(!(std::cin>>D)){
            std::cout<<"Ошибка ввода\n";
            delete_tree(root);
            return 1;
        }
        if(D==-1){
            std::cout<<"Построение дерева окончено\n\n";
            break;
        }
        root=CreateTree(root,root,D);
    }

    print_tree(root,0);
    std::cout<<"Введите число для поиска: ";
    if(!(std::cin>>D)){
        std::cout<<"Ошибка ввода\n";
        delete_tree(root);
        return 1;
    }
    int depth=search(root,D);
    if(depth!=-1){
        std::cout<<"Число найдено. Глубина: "<<depth<<'\n';
    }
    else{
        std::cout<<"Число не найдено\n";
    }
    std::cout<<"Количество вхождений: "
             <<count_occurrences(root,D)<<'\n';

    std::cout<<"Введите число для удаления: ";
    if(!(std::cin>>D)){
        std::cout<<"Ошибка ввода\n";
        delete_tree(root);
        return 1;
    }
    root=delete_node(root,D);
    std::cout<<"Дерево после удаления:\n";
    print_tree(root,0);

    delete_tree(root);
    return 0;
}
