#include <iostream>
#include <string>
using namespace std;
unsigned int stringtoint(string s);
struct NODEH{string symbol;int key;};
struct NODE{int left;int right;};
static int free_top=1;
static NODE memarray[31];
//memarray is memory with free_top
//free_top is pointing top free value
//and each empty node left is zero and right point to next free node

//hash class for making interpreter
class hash2 {
    
public:
    
    NODEH * elements;
    hash2(int key2=41,int capacity=30){
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
                s;
            }else if(elements[k].symbol==""||capacity-1==temp){
                NODEH h;
                h.symbol="";
                h.key=0;
                "";
            }else{
                k=(k+1)%this->capacity;
                temp++;
            }
        }
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
        
        //int check=0;
        for(int i=0;i<size2;i++){
            
            string nextchar=s->substr(i,1);
            //char tmp;
            if((int(nextchar[0])-65)*(int(nextchar[0]-90))<=0){
                nextchar[0]=nextchar[0]+32;//in ascii lower and upper has 32 between
                
            }
            if(nextchar=="("||nextchar==")"||nextchar==" "||nextchar=="\t"){
                if(nexttoken.size()!=0){//in case we have token and meet not char value
                    *s=s->substr(i);
                    return nexttoken;
                }else{//we already have char value and meet none char value
                    if(nextchar=="("||nextchar==")"){
                        *s=s->substr(i+1);
                        nexttoken=nexttoken+nextchar;
                        return nexttoken;
                    }
                }
            }else if(i==size2-1){
                //we got to the end;
                nexttoken=nexttoken+nextchar;
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






int main() {
 
    
    for(int i=1;i<30;i++){
        memarray[i].right=i+1;
    }memarray[30].right=0;
    hash2* h=new hash2();
    //h->insert("(");
    //h->insert(")");

    while(1){
        cout<<">";
        string s;
        getline(cin,s);
        int root=read(&s,*h,memarray);
        if(root ==-1){
            cout<<"hash is full! exit"<<endl;
            break;
        }else if (root<0){
            cout<<"]hash_value: "<<root-1<<endl;//hash value!!!!!
        }else{
            cout<<"]";
            cout<<"Free list's root =   "<<free_top<<endl;
            cout<<"List's root = "<<root<<endl;
            cout<<endl;
            cout<<"memory table: "<<endl;
            for(int i=1;i<31;i++){
                cout<<"NUM: "<<i<<" left :"<<memarray[i].left<<" right :"<<memarray[i].right<<endl;
            }h->printhash();
            cout<< "print : ";
            print(root,*h,true);
            return_array(memarray, root);
            cout<<endl;
        }
    }
    
	return 0;
}
