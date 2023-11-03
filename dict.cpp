// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here
    root=new DictNode('@');
}

DictNode* Burn(DictNode* node){
    for(int i=0 ; i<54 ; i++){
        if((node->bacha[i])){
            node->bacha[i]=Burn(node->bacha[i]);
        }
    }
    delete node;
    return NULL;
}

Dict::~Dict(){
    // Implement your function here
    root=Burn(root);
}

void dalo(DictNode* node,string s){
    if(s.length()==0){
        node->value ++;
        return;
    }
    char ch=s[0];
    if(ch>='A' && ch<='Z'){
        ch=tolower(ch);
    }
    int index=(int)(ch);
    DictNode* temp;
    if(index>=94 && index<=126){
        index= index-94;
    }
    else if(index>=47 && index<=57){
        index= ch-'/'+33;
    }
    else if(index>=60 && index<=62){
        index= ch-'<'+44;
    }
    else if(index>=35 && index<=38){
        index= ch-'#'+47;
    }
    else if(index>=42 && index<=43){
        index= ch-'*'+51;
    }
    else{
        index=53;
    }
    if((node->bacha[index])!=NULL){
        temp=node->bacha[index];
    }
    else{
        temp=new DictNode(ch);
        node->bacha[index]=temp;
    }
    dalo(temp,s.substr(1));
}


void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    string s="";
    int n=sentence.length();
    for(int i=0 ; i<n ; i++){
        char ch=sentence[i];
        int ind=(int)(ch);
        if(ch=='.' || ch==',' || ch=='-' || ch==':' || ch=='!' || ch=='"'  || ch=='(' || ch==')' || ch=='?' || ch=='[' || ch==']' || ch==';' || ch=='@' || ch==' ' || ind==39){
            if(s.length()>0){
                dalo(root,s);
            }
            s.clear();
        }
        else{
            s.push_back(ch);
        }
    }
    if(s.length()!=0){
        dalo(root,s);
    }
}

int khojo(DictNode* node,string s){
    if(s.length()==0){
        return node->value;
    }
    char ch=s[0];
    if (ch>='A' && ch<='Z') {
        ch=tolower(ch);
    }
    int index = (int)(ch);
    DictNode* temp;
    if(index>=94 && index<=126){
        index= index-94;
    }
    else if(index>=47 && index<=57){
        index= ch-'/'+33;
    }
    else if(index>=60 && index<=62){
        index= ch-'<'+44;
    }
    else if(index>=35 && index<=38){
        index= ch-'#'+47;
    }
    else if(index>=42 && index<=43){
        index= ch-'*'+51;
    }
    else{
        index=53;
    }
    if(node->bacha[index]!=NULL){
        temp=node->bacha[index];
    }
    else{
        return 0;
    }
    return khojo(temp,s.substr(1));
}

int Dict::get_word_count(string word){
    // Implement your function here
    return khojo(root,word);
}

void khatm(DictNode* temp , string s, ofstream &abhishek){
    if(temp->value!=0){
        abhishek<<s<<","<<" "<<temp->value<<endl;
    }
    for(int i=0 ; i<54 ; i++){
      if(temp->bacha[i]){
        khatm(temp->bacha[i] , s+temp->bacha[i]->key,abhishek);
      }
    }
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    ofstream abhishek;
    string adarsh=filename;
    abhishek.open(adarsh);
    khatm(root,"",abhishek);
    abhishek.close();
    return;
}
