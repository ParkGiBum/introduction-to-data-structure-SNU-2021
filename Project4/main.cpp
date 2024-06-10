#include <iostream>
#include <string>
using namespace std;
unsigned int stringtoint(string s);
struct NODEH{string symbol;double key;};
struct NODE{int left;int right;};
struct NODESTACK{int hashvalue;int keyvalue;};
static int free_top=1;
static NODE memarray[201];
static bool define_flag;



//memarray is memory with free_top
//free_top is pointing top free value
//and each empty node left is zero and right point to next free node


template <class T>
class stack{
public:
    stack();
    ~stack();
    
    T pop();                //simple pop fuction we did in class
    T what_is_on_top();     //when we need to just look first card(only for wastpile!!!!)
    
    
    void insert(T);         //simple insert function we did in class
    int isempty();          //same as class
    int get_len();          //same as class
    //void shuffle();
private:
    int top;                //top cursor for making stack
    int capacity;           //capacity of class when it is full size doubles
    T *elements;            //list of class
    
    
};


template <class T>
stack<T>::stack(){
    top=-1;                         //when top is -1 it means no card
    capacity=13;                    //13 is perfect for out task since 13*4=52
    elements = new T[capacity];     //making new stack
}

template <class T>
stack<T>::~stack(){
    delete[] elements;
}
//when stack has at least one element it is not empty so it return 0 when it is empty
template<class T>
int stack<T>::isempty(){
    if(top>=0){
        return 1;
    }else{
        return 0;
    }
}
//it returns some value when it is empty but meaningless and returns top element
template <class T>
T stack<T>::pop(){
    if(top>=0){
        T tmp =elements[top];
        top-=1;         //move the one cursor downward
        return tmp;
    }else{
        T tmp2 =elements[top+1];
        std::cout<<"stack is empty!!! returning previous instead!!\n";
        return tmp2;
    }
}
//when we need to just look top element(only for wastpile!!!!)
template<class T>
T stack<T>::what_is_on_top(){
    if(top>=0){
        T tmp =elements[top];
        return tmp;
    }else{
        T tmp2 =elements[top+1];
        //std::cout<<"stack is empty!!! returning previous instead!!\n";
        return tmp2;
    }
}
//put one element in the list and make top 1 larger
template<class T>
void stack<T>::insert(T card){
    if(top+1==capacity){        //incase of capacity is too small
        capacity*=2;            //double the capacity
        T *tmp=new T[capacity];
        memcpy(tmp, elements, capacity*sizeof(T)); //for timesaving copy the memory at once
        delete elements;
        elements = tmp;
    }
    elements[top+1]=card;
    top+=1;
}
//simple function that returns len of stack if it has one element it returns 1
template<class T>
int stack<T>::get_len(){
    return top+1;
}

static stack<NODESTACK> stack2=stack<NODESTACK>();


//hash class for making interpreter
class hash2 {
    
public:
    friend  double eval(int root,hash2* hash2,NODE * free);
    NODEH * elements;
    hash2(int key2=2027,int capacity=2027){
        this->capacity=capacity;
        key=key2;
        elements= new NODEH[capacity];
        for(int i=0;i<key2;i++){
            elements[i].key=0;
        }//when we start we insert basic things
        
    };
    ~hash2(){
    };
    int insert(NODEH H){//incase we insert with node(we will not use it for this hw)
        int k = gethashvalue(H.symbol);
        int temp=0;
        while(1){
            if(elements[k].symbol==""){
                elements[k].key=H.key;
                elements[k].symbol=H.symbol;
                return 0;
            }else if(elements[k].symbol==H.symbol){
                return 0;
            }else if(capacity-1==temp){
                cout<<"no empty space!!!!"<<endl;//if we scan whole hash and did not find empty full!
                return 1;
            }else{
                k=(k+1)%capacity;
                temp++;
            }
        }
    };
    int insert (string s){//inserting with string
        int k = gethashvalue(s);
        int temp=0;
        while(1){
            if(elements[k].symbol==""){
                elements[k].key=0;
                elements[k].symbol=s;
                return 0;
            }else if(s==elements[k].symbol){
                return 0;
            }else if(capacity-1==temp){//if empty we do not have one
                cout<<"no empty space!!!!"<<endl;
                return 1;
            }else{
                k=(k+1)%capacity;
                temp++;
            }
        }
    };
    string search(string s){//searching for certain string
        int k = gethashvalue(s);
        int temp=0;
        while(1){
            if(s==elements[k].symbol){
                //cout<<"1"<<elements[k].symbol<<endl;
               return s;
            }else if(elements[k].symbol==""||capacity-1==temp){
                //cout<<"2"<<elements[k].symbol<<endl;
               return "";
            }else{
                k=(k+1)%this->capacity;
                temp++;
            }
        }
    };
    double getkey(int i){
        return elements[i].key;
    };
    
    void printhash(){//just printing hash
        cout<<"HASH TABLE"<<endl;
        for(int i =0; i<capacity;i++){
            if(elements[i].symbol!=""){//we do not print empty ones
                cout<<" hashvalue : "<<i*-1-1<<"\t symbol : "<<elements[i].symbol<<"\t\t\t link : "<<elements[i].key<<endl;//hash value!!!!!!
            }
        }
    };
    
    int gethashvalue(string s){//hash value calculator
        int k =stringtoint(s);
        k=k%key;
        k=k%capacity;
        
        int temp=0;
        while(1){
            if(elements[k].symbol==""){//when we meet node already taken return next one
                break;
            }else if(s==elements[k].symbol){
                break;
            }else if(capacity-1==temp){
                cout<<"no empty space!!!!"<<endl;
                break;
            }else{
                k=(k+1)%capacity;
                temp++;
            }
        }

        
        return k;
    }
    
private:
    int capacity;
    int key;
    int calculator(int key);
    
};


unsigned int stringtoint (string s){//string to int as we did in class
    
    int l=(int) s.length();
    unsigned int answer =0;
    if(l%2==1){
        answer=s.at(l-1);
        l--;
    }
    for (int i=0; i<l;i+=2){
        answer+=s.at(i);
        answer+=((int)s.at(i+1))<<8;
    }
    return answer;
}

string getnexttoken(string * s){//finind next token
    int size2 = s->size();
    if(size2){
        string nexttoken="";
        for(int i=0;i<size2;i++){
            
            string nextchar=s->substr(i,1);
            if((int(nextchar[0])-65)*(int(nextchar[0]-90))<=0){
                nextchar[0]=nextchar[0]+32;//in ascii lower and upper has 32 between
            }
            if(nextchar=="("||nextchar==")"||nextchar==" "||nextchar=="\t"||nextchar=="'"){
                if(nexttoken.size()!=0){//in case we have token and meet not char value
                    *s=s->substr(i);
                    return nexttoken;
                }else{//we already have char value and meet none char value
                    if(nextchar=="("||nextchar==")"||nextchar=="'"){
                        *s=s->substr(i+1);
                        nexttoken=nexttoken+nextchar;
                        return nexttoken;
                    }
                }
            }else if(i==size2-1){
                nexttoken=nexttoken+nextchar;
                *s=s->substr(i+1);
                return nexttoken;
            }else{
                nexttoken=nexttoken+nextchar;
            }
        }
        
    }
    else{
        return "";
    }
    return "";
}



int alloc(NODE* memarray){//allocate memort
    if(free_top==-1){
        cout<<"ererererererrrrorrrrr"<<endl;
    }else{
        int tmp=free_top;
        free_top=memarray[free_top].right;//we use memory pointed by free_top
        return tmp;
    }
    return 0;
}

void return_array(NODE* memarray,int root){
    int tmp=root;//if empty memory left=0 and right point to next free value
    if(root>0){//so wee make each node under root to pointed by there root
        if(memarray[root].left>0){
            return_array(memarray,memarray[root].left);
        }if(memarray[root].right>0){
            return_array(memarray,memarray[root].right);
        }
        memarray[tmp].right=free_top;//and right value point to next free
        memarray[tmp].left=0;//and leftavalue 0 to indicate it is empty
    }free_top=tmp;//chane free_top to root
}


int read(string *s,hash2 hash,NODE * free){//basically almost same as pesudo code
    int root =0;
    bool first = true;
    int temp=0;
    string s2=getnexttoken(s);
    //cout<<"s2::"<<s2<<endl;
    int hashvalue= hash.gethashvalue(s2);
    if(s2=="("){//we start if it start with (
        hash.insert(s2);
        s2=getnexttoken(s);
        int hashvalue= hash.gethashvalue(s2);
        while(s2!=")"){//if we do not meet )
            if(first){
                temp=alloc(free);   //and it is not first
                root=temp;          //we allocate memory and change root
                first=false;
            }else{
                free[temp].right=alloc(free);   //not first we allocat to right since it is not list
                temp=free[temp].right;
            }if(s2=="("){                       //( means next elemnet is list
                int tmp=temp;                   //so we do read recursively
                *s = "(" + (*s);                //but lets save temp value to be sure
                memarray[temp].left=read(s,hash,free);//tnwjdfsadfjkwjlfasdj;fsd
                temp=tmp;
            }else{
                memarray[temp].left=hashvalue*-1-1;//else it is just ordinary symbolhash value!!!!!!!!!!
                if(s2!="("){
                    int k=hash.insert(s2);
                    if(k==1){return -1;}
                }
            }
            if(first==false){
                memarray[temp].right=0;
            }
            s2=getnexttoken(s);
            hashvalue = hash.gethashvalue(s2);
        }if(s2==")"){hash.insert(s2);}
        return root;
    }else{
        //hash.insert(s2);
        return hashvalue*-1;
    }
}
void print(int root,hash2 hash,bool start){
    //also same as pseudo code
    //out<<root<<endl;
    //cout<<root<<endl;
    if(root==0&&start){
        cout<<"() ";
    }else if(root<0){
        cout<<hash.elements[root*-1-1].symbol<<" ";//hash value!!!!!
    }else if(root>0){
        if(start){
            cout<<"(";
        }
        //cout<<"!?"<<endl;
        print(memarray[root].left,hash, true);
        if(memarray[root].right!=0){
            //cout<<"!"<<endl;
            print(memarray[root].right,hash, false);
        }else{
            cout<<")";
        }
    }else{
        
    }
}


//preprocessing convert ordinary define and add lambda exrpession
//if there is ' we make it as quote to make list
string preprocessing(string * command,string * newcommand){

    string token;
    //string newcommand="";
    token=getnexttoken(command);
    define_flag=false;
    while(command->length()){
        //cout<<*command<<endl;
        
        if(token=="define"){
            
            *newcommand=*newcommand+" define ";
            token=getnexttoken(command);
            if(token=="("){
                token=getnexttoken(command);
                *newcommand= *newcommand + token +" (lambda(";
                //cout<<*newcommand<<endl;
                string  newnewcomand;
                newnewcomand="";
                //cout<<*newcommand<<endl;
                *newcommand= *newcommand + preprocessing(command,&newnewcomand) + ")";
                
                
            }
            define_flag=true;
            //if define_flag do not delete the tree
        }else if(token=="'"){
            //cout<<"dsafsdf"<<endl;
            *newcommand=*newcommand + " (quote ";
            int number_of_left_paren=0;
            do{
                token = getnexttoken(command);
                *newcommand= *newcommand+" "+token;
                if(token=="("){
                    number_of_left_paren++;
                }else if(token==")"){
                    number_of_left_paren--;
                }
            }while(number_of_left_paren>0);
            *newcommand=*newcommand+")";
            token=getnexttoken(command);
        }else{
            
            *newcommand = *newcommand+ " " + token;
            token=getnexttoken(command);
        }
            
    }
    *newcommand = *newcommand+ " " + token;
    
    return *newcommand;
}


//this function is called when we evaluate negative value

double hasheval(int root,hash2 hash2,bool isfunction=false){
    double key2 =hash2.elements[-1*root-1].key;
    //if there is no link returns it self
    if(key2==0){
        return root*-1-1;
    }else if(key2<0){
    //if there is link it goes to link
        return hasheval(key2,hash2);
    }else{
        return key2*-1-1;
    }
    return 0;
}




//Not Yet made----------------------------------------------------------------
double eval(int root,hash2* hash2,NODE * free);
void display(int root,hash2* hash2 ,NODE * free,bool first=false){
    if(first){
        
        if(memarray[root].left<0&&memarray[root].right==0){
            cout<<hash2->elements[(int)hasheval(memarray[root].left,*hash2,false)*-1-1].symbol<<endl;
        }else{
            cout<<"( ";
            display(root,hash2,free);
            cout<<" )";
        }
    }else{
        cout<<"( ";
        while(memarray[root].right!=0){
            if(memarray[root].left<0){
                cout<<hash2->elements[memarray[root].left*-1-1].symbol<<" ";
            }else if(memarray[root].left>0){
                display(memarray[root].left,hash2,free);
            }root = memarray[root].right;
        }
        cout<<" )";
    }
}


//this is almost same as pseudo code
//when the tree root is inserted as we follow tree it
double eval(int root,hash2* hash2,NODE * free){
    
    if(root<0){
        return (hasheval(root,*hash2));
    }else{
        int next=memarray[root].left;
        if(root==0){return 0;}
        else {
            //when we calculate + we evaluate value from each side
            if((*hash2).elements[next*-1-1].symbol=="+"){
                int x=eval(memarray[memarray[root].right].left,hash2, free);
                int y=eval(memarray[memarray[memarray[root].right].right].left,hash2, free);
                //w
                double z=stof((*hash2).elements[x].symbol);
                double w=stof((*hash2).elements[y].symbol);
                //cout<<z<<" :"<<w<<to_string(z+w)<<endl;
                hash2->insert(to_string(z+w));
                //and return the hash where answer is stored
                double k=(*hash2).gethashvalue(to_string(z+w));
                
                return k;
                
                //- * is same as +
            }else if((*hash2).elements[next*-1-1].symbol=="-"){
                int x=eval(memarray[memarray[root].right].left,hash2, free);
                int y=eval(memarray[memarray[memarray[root].right].right].left,hash2, free);
                //w
                double z=stof((*hash2).elements[x].symbol);
                double w=stof((*hash2).elements[y].symbol);
                //cout<<z<<" :"<<w<<to_string(z+w)<<endl;
                hash2->insert(to_string(z-w));
                //and return the hash where answer is stored
                double k=(*hash2).gethashvalue(to_string(z-w));
                
                return k;
                
                //- * is same as +
            }else if((*hash2).elements[next*-1-1].symbol=="*"){
                int x=eval(memarray[memarray[root].right].left,hash2, free);
                int y=eval(memarray[memarray[memarray[root].right].right].left,hash2, free);
                //w
                double z=stof((*hash2).elements[x].symbol);
                double w=stof((*hash2).elements[y].symbol);
                //cout<<z<<" :"<<w<<to_string(z+w)<<endl;
                hash2->insert(to_string(z*w));
                //and return the hash where answer is stored
                double k=(*hash2).gethashvalue(to_string(z*w));
                
                return k;
                
                //- * is same as +
            }else if((*hash2).elements[next*-1-1].symbol=="define"){
                int k =memarray[memarray[memarray[memarray[root].right].right].left].left;
                if(k<0&&(*hash2).elements[k*-1-1].symbol=="lambda"){
                    //look for lambda to find out if it is function or not
                    (*hash2).elements[memarray[memarray[root].right].left*-1-1].key=(memarray[memarray[memarray[root].right].right].left);
                    //if function build tree
                }else{
                    (*hash2).elements[memarray[memarray[root].right].left*-1-1].key=eval(memarray[memarray[memarray[root].right].right].left,hash2, free)*-1-1;
                    //else just store value
                    return 0;
                    
                }
            }else if((*hash2).elements[next*-1-1].symbol=="number?"){
                string s5 = hash2->elements[(int)eval(memarray[memarray[root].right].left,hash2,free)].symbol;
                //I used Try to see if it is number or not
                int k;
                try{
                    k=stoi(s5);
                    hash2->insert("#t");
                    return hash2->gethashvalue("#t");
                    
                }catch(...){
                    hash2->insert("#f");
                    return hash2->gethashvalue("#f");
                }
                
            }else if((*hash2).elements[next*-1-1].symbol=="symbol?"){
                //it is just reverse of number?
                string s5 = hash2->elements[(int)eval(memarray[memarray[root].right].left,hash2,free)].symbol;
                int k;
                try{
                    k=stoi(s5);
                    hash2->insert("#f");
                    return hash2->gethashvalue("#f");
                    
                }catch(...){
                    hash2->insert("#t");
                    return hash2->gethashvalue("#t");
                }
                
            }else if((*hash2).elements[next*-1-1].symbol=="null?"){
                /*
                if its link is 0
                 or evaluation value is 0 than it is null
                */
                int k =memarray[memarray[root].right].left;
                //cout<<k<<endl;
                int y =eval(k,hash2,free);
               
                //cout<<y<<endl;
                if(k*(y+1)==0){
                    hash2->insert("#t");
                    return hash2->gethashvalue("#t");
                }else{
                    hash2->insert("#f");
                    return hash2->gethashvalue("#f");
                }
                
            }else if((*hash2).elements[next*-1-1].symbol=="cons"){
                int newmemory= free_top;
                alloc(free);
                memarray[newmemory].left=eval(memarray[memarray[root].right].left,hash2,free)*-1-1;
                memarray[newmemory].right=eval(memarray[memarray[memarray[root].right].right].left,hash2,free)*-1-1;
                //we make a new root and
                //retun hash value of new root
                return newmemory*-1-1;
            }else if((*hash2).elements[next*-1-1].symbol=="cond"){
                while(memarray[memarray[root].right].right!=0){
                    root=memarray[root].right;
                    //we follow evert conditions
                    if(hash2->elements[(int)eval(memarray[memarray[root].left].left,hash2,free)].symbol=="#t"){
                        return eval(memarray[memarray[memarray[root].left].right].left,hash2,free);
                    }
                }string s8=hash2->elements[(memarray[memarray[memarray[memarray[root].right].left].left].left)*-1-1].symbol;
                //cout<<(memarray[memarray[memarray[memarray[root].right].left].left].left)<<endl;
                if(s8!="else"){
                    //if there is no else at the end there is an error
                    //cout<<"ERRORRRRRR!!!!!!!!!!!!!!"<<endl;
                }return eval(memarray[memarray[memarray[memarray[root].right].left].right].left,hash2,free);
                //returning else evaluation if there is none
            }else if((*hash2).elements[next*-1-1].symbol=="car"){
                    //return first hash
                return memarray[(int)eval(memarray[memarray[root].right].left,hash2,free)*-1-1].left*-1-1;
            }else if((*hash2).elements[next*-1-1].symbol=="cdr"){
                    //cdr returns rest of it
                return memarray[(int)eval(memarray[memarray[root].right].left,hash2,free)*-1-1].right*-1-1;
            }else if((*hash2).elements[next*-1-1].symbol=="quote"){
                    //get the head of list
                return memarray[memarray[root].right].left*-1-1;
            }else if((*hash2).elements[next*-1-1].symbol=="display"){
                //not yet finished
                return 0;
            }else{
                //if none of above it must be custom function
                int how_much_variable=0;
                int function_location=hash2->elements[(memarray[root].left)*-1-1].key;
                int search=memarray[memarray[function_location].right].left;
                int search_value=memarray[root].right;
                //to backup every value first count howmuch variable there is
                if(search!=0){
                    how_much_variable++;
                }
                while(memarray[search].right!=0){
                    search=memarray[search].right;
                    how_much_variable++;
                }
                
                
                search=memarray[memarray[function_location].right].left;
                //after count reset
                
                double* variable=new double[how_much_variable];
                //store does value and swap with original valu
                for(int i=0;i<how_much_variable;i++){
                    variable[i]=eval(memarray[search_value].left,hash2,free)*-1-1;
                    search_value=memarray[search_value].right;
                }
                
                //
                double tmp;
                for(int i=0;i<how_much_variable;i++){
                    tmp=hash2->elements[memarray[search].left*-1-1].key;
                    hash2->elements[memarray[search].left*-1-1].key=variable[i];
                    variable[i]=tmp;
                    search=memarray[search].right;
                }
                search=memarray[memarray[function_location].right].left;
                //after swap evaluate
                int ans=eval(memarray[memarray[memarray[function_location].right].right].left,hash2,free);
                tmp=hash2->elements[memarray[search].left].key;
                //restore value
                for(int i=0;i<how_much_variable;i++){
                    tmp=hash2->elements[memarray[search].left*-1-1].key;
                    hash2->elements[memarray[search].left*-1-1].key=variable[i];
                    variable[i]=tmp;
                    search=memarray[search].right;
                }
                delete[] variable;
                if(how_much_variable==0){
                    return 0;
                }
                return ans;
            }
        }
    }
    return 0;
}

void printlist(int k,hash2* h,int root,bool first = true){ //function for printing list called when it get single input which is list
    cout<<"( ";
    int left = 0;
    left = k;
    
    while(memarray[left].right!=0){
        if(memarray[left].right>0){

            if(memarray[left].left<0){
                
                cout<<h->elements[memarray[left].left*-1-1].symbol;
                left=memarray[left].right;
                
            }
            else{
                printlist(memarray[left].left,h,root,false);
                left=memarray[left].right;
            }
            if(memarray[left].right!=0){
                cout<<" , ";
            }
            
        }
        else{
            return;
        }
    }
    cout<<" , ";
    if(memarray[left].left<0){
        
        cout<<h->elements[memarray[left].left*-1-1].symbol;
        
    }
    else{
        printlist(memarray[left].left,h,root);
    }
    
    cout<<" )";
}

int main() {
 
    
    for(int i=1;i<200;i++){
        memarray[i].right=i+1;
    }memarray[200].right=0;
    hash2* h=new hash2();
    h->insert("#t");
    h->insert("#f");

    while(1){
        
        cout<<">";
        string s;
        getline(cin,s);
        string s4=s;
        string s2="";
        string s3=preprocessing(&s, &s2);
        //preprocess first
        
        int root=read(&s3,*h,memarray);
        if(root ==-1){
            cout<<"hash is full! exit"<<endl;
            //hash full
            break;
        }else if (root<0){
            //if return value is hashvalue
            string k= h->search(s4);
            if(k==""){
                cout<<"NOT IN HASH "<<endl;//hash value!!!!!
            }else{
                string s5 = (h->elements[(int)eval(root-1,h,memarray)]).symbol;
                double k = h->elements[root*-1].key;
                //cout<<"]hash_value: "<<root-1<<endl;//hash value!!!!!
                //cout<<"key value: "<< k<<endl;
                if(k<=0){
                    double k5=0;
                    try{
                        k5=stoi(s5);
                        cout<<k5<<endl;
                    }catch(...){
                        cout<<""<<endl;
                    }
                }else{
                    
                    printlist(k,h,root);
                    cout<<"\n";
                }
            }
        }else{
            
            cout<<"]";
            //cout<<"Free list's root =   "<<free_top<<endl;
            //cout<<"List's root = "<<root<<endl;
            //cout<<endl;
            double k =eval(root,h,memarray);
            double k2 = h->elements[root*-1].key;
            //
            string s =(h->elements[(int)k]).symbol;
            //cout<<"memory table: "<<endl;
            //for(int i=1;i<201;i++){
                //print only stored value
            //    if(memarray[i].left!=0){
            //        cout<<"NUM: "<<i<<" left :"<<memarray[i].left<<" right :"<<memarray[i].right<<endl;
            //    }
            //}
            
            
            //h->printhash();
            cout<< "print : ";
            print(root,*h,true);
            if(s!=""){
                cout<<"\nvalue: "<<s<<endl;
            }//when there is retunr value of int print does value
                
            if(k<0){
                cout<<endl;
                printlist(k*-1-1,h,root);
                cout<<endl;
                //printlist(k2,h,root);
                //cout<<"\n";
                //cout<<"\nlisthead:"<<k*-1-1<<" (for list operation cdr,cons)"<<endl;
            }else{
                
            }
            //delete tree if not defining function
            if(define_flag==false){
                
                cout<<"delete not defined value"<<endl;
                return_array(memarray, root);
            }
            cout<<""<<endl;
        }
    }
    
	return 0;
}
