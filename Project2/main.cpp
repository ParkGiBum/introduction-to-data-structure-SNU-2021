//
//  main.cpp
//  hw2-4
//
//  Created by ParkGi bum on 2020/09/30.
//

#include <iostream>
#include <random>
#include<fstream>
#include<string>
/*
 This code is about making klonedike game and run it by it self.
 
 It is cosist of 3 big chunks.
 
 first:
 stack class, which is basic element of card deck to make card information not available when it is in the deck I have made them private
 it has basic function such as pop,insert,get_len,is_empty,and for wastepile list which has known card on top what_is_on_top function.
 Last but not least shuffle which is for initializing random deck.
 
second:
 card struct and deck class, card struct is very simple with only two element shape and num for example shape0 and num12 means king of heart
 deck class has card stack called elements. And it also has almost same function as stack which just calls function from stack and execute it on elemnts.
  One special function is full deck. It makes one 52cards deck with random order.
 
 third:
 game class structure:
 This is most important class. It has 13 deck total. 1 stock(stock) ,7 playingdeck(deck1) ,4 outputdeck(output), 1wastepile there are all either should not reveal the contents by the rule or don't care information. But the open cards on the playing decks are essential for gameplay. So I have to make anoter array for that which is deck1_open[7][13] they are 7*13 because 7decks and can be 13 card maximum.
 
 game class function:
 First contructor call stock.fulldeck to make deck of 52 random cards. And distribute the card to 7 playing deck from 1 to 7 and reveal top cards. As it PDF it does execute a b c and if no action taken go back to a if there is no move and no card in the stock, it is game over.

Infinite loop:
 This is a most important part of game. I have made it escape from it by recording last 12 moves made by step C which is the only reason why loop exist. If it tries to make same move or reversing move from past it rejects and proceed to other move.
 

 */


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
//simple struct for card
struct card{
    int num;            //0 means 1 ,9means 10 ,12 means king
    int shape;          //Heart:0 Spade:1 Diamond:2 Clover:3
};
//deck class just calls function from stack except for full deck
class deck{
public:
    deck(int shape=0,int num=0);
    ~deck();
    void fulldeck();
    void insert(int shape=0,int num=0);
    int isempty();
    
    int get_len();
    
    card what_is_on_top();
    card pop();
private:
    stack<card> elements;
};

deck::deck(int shape,int num): elements(){
}
deck::~deck(){
}
//full deck just make one 52 card set and mix it
//after that is insert it to the elements stack.
void deck::fulldeck(){
    std::string shape2[4]={"♥","♣","♦","♠"};
    std::string num2[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    std::ofstream out("test.txt",std::ios::app);
    card tmp[52];
    //card tmp2[52];
    for(int k=0;k<52;k++){
        card tmp_card;
        tmp_card.shape=k/13;
        tmp_card.num=k%13;
        tmp[k]=tmp_card;
    }
    //used <random>for mixing card
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(&tmp[0], &tmp[52],g);
    for(int k=0;k<52;k++){
        elements.insert(tmp[k]);
    }
    out<<"initial setting:\nplayingdeck: most right is card on the top\n";
    int j=0;int l=1;
    for(int k=0;k<52;k++){
        
        if(k<28&&j==k){
            if(j!=0){
                out<<"<==card on the top\nplayingdeck"<<l<<":";
            }else{
                out<<"\nplayingdeck"<<l<<":";
            }
            j=j+l;
            l++;
            out<<shape2[tmp[51-k].shape]<<" "<<num2[tmp[51-k].num]<<"\t";
        }else{
            out<<shape2[tmp[51-k].shape]<<" "<<num2[tmp[51-k].num]<<"\t";
        }
        if((k+1)%7==0&&k>=28){
            out<<"\n";
        }
        if(k+1==28){
            out<<"<==card on the top\n-----------cards in the stock-----------------\n";
            
        }
    }out<<"<=card on the bottom\n\n";
}
//just put the card in the stack.
void deck::insert(int shape,int num){
    if(num<=12&num>=0&shape<=3&shape>=0){
        card insertingcard;                 //making card to insert
        insertingcard.shape= shape;
        insertingcard.num=num;
        elements.insert(insertingcard);     //function from stack
    }else{
        std::cout<<"shape and number does not exist!\n";
    }
}
//If deck is not empty get one more card
card deck::pop(){
    if(elements.isempty()){ //if not empty
        card a;
        a=elements.pop();
        return a;
    }else{
        std::cout<<"no more card!!\n";
        card a;
        a.shape=0;
        a.num=0;
        return a;       //if empty return impossible card
    }
}
//just a function from stack
int deck::isempty(){
    return elements.isempty();
}
//just a function from stack AGAIN ONLY FOR WASTEPILE!!!!!!!!!
card deck::what_is_on_top(){
    return elements.what_is_on_top();
}
//just a function from stack
int deck::get_len(){
    return elements.get_len();
}


class game{
    
public:
    game();
    ~game(){};
    
    
    
    //As in pdf I have made three major step as function
    // If the move was made by 3 it returns TRUE.
    bool step_a();
    bool step_b();
    bool step_c();
    bool step_abc();    //jut for executing three at once it move is made in either 3 it returns true
    void record(int a,int b,int c,int d,int e); //for sensing same move it record move to
    int move_record[1000][5]; //this array it records last 5 move
    int loop_sensin=0;      //If loop size is too big It cannot be detected by move_record so it is last method to escape
    int move=0;             //for recording moves
    bool record_scan(int a,int b,int c,int d,int e);    //Every time we try C we will check that move was made in previous 5 moves.
    
    int score;              //simple score record
    void current_situation();   //printing current situation
    bool draw();                //drawing card and if drawn return true
    bool flip();                //check 7 playing deck it there is no open card and at least one closed card flip one
    void fileoutput(int shape,int num,int dest,int source);
    std::string shape2[4]={"♥","♣","♦","♠"};   //For printing current situation each representing Heart Clover Diamond Spade
    std::string num2[13]={"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
    
private:
    deck wastepile;     //12 deck need for game
    deck deck1[7];
    deck output[4];
    deck stock;
    
    card deck1_open[7][13];     //open cards on playing deck
    int deck1_open_end[7];      //for efficient search top cursor
};
void game::fileoutput(int shape,int num,int dest,int source){
    std::string out_line;
    std::ofstream out("test.txt",std::ios::app);
    
    std::string ouput_candid[12]={"playing#1","playing#2","playing#3","playing#4","playing#5","playing#6",
        "playing#7","output#1","output#2","output#3","output#4","wastepile"};
        
        out<<shape2[shape]<<" ";
        out<<num2[num];
        out<<" moved from ";
        out<<ouput_candid[source];
        out<<" to ";
        out<<ouput_candid[dest];
        out<<out_line<<"\n"<<std::endl;
        
        current_situation();
}
//first make a random deck and distribute the card to 7 playing deck and draw one card.
game::game(){
    
    score =-52;
    //initializing one random deck
    stock.fulldeck();
    for(int k=0;k<7;k++){       //distribute the card
        for(int i=0;i<k+1;i++){
            card a=stock.pop();
            deck1[k].insert(a.shape,a.num);
        }
        card b=deck1[k].pop();
        deck1_open[k][0]=b;
        deck1_open_end[k]=1;
    }
    //draw one card
    card b=stock.pop();
    wastepile.insert(b.shape,b.num);
    current_situation();
}
// recording last 5 moves record moved card and where it moved to and moved from
void game::record(int a, int b, int c,int d,int e){
    //loop_sensin;
    move_record[loop_sensin][0]=a;     // where is it moved from
    move_record[loop_sensin][1]=b;     // where is it moved to
    move_record[loop_sensin][2]=c;     // backup if additional information needs(do nothing for now
    move_record[loop_sensin][3]=d;     // what kind of card(top one) is moved ex)10 of spade is 13*1+10
    move_record[loop_sensin][4]=e;     // backup if additional information needs(do nothing for now
    
}
// scan move where that move has made in 5 moves
bool game::record_scan(int a, int b, int c,int d,int e){
    for(int k=0;k<loop_sensin+1;k++){
        // if it tries to make same move from past it returns false
        // But it make reverse move from past also false
        // What is reverse move? if three of dia was moved from 1 to 5
        // than moving same card 5 to 1 in prohibited as well
        if(((move_record[k][0]==a&&move_record[k][1]==b)||(move_record[k][1]==a))&&move_record[k][2]==c&&move_record[k][3]==d&&move_record[k][4]==e){
            return false;
        }
    }
    return true;
}
// as mentioned scan playing card and open if there is only closed card
bool game::flip(){
    bool rval=false;
    for(int k=0;k<7;k++){
        if(deck1_open_end[k]==0&&deck1[k].get_len()>0){
            rval=true;
            deck1_open[k][0]=deck1[k].pop();
            deck1_open_end[k]=1;
        }
    }
    return rval;
}
// draw a card put it on waste pile return true if succeded
bool game::draw(){
    current_situation();
    std::ofstream out("test.txt",std::ios::app);
    out<<"draw has happen:";
    if(stock.get_len()!=0){
        card a = stock.pop();
        out<<shape2[a.shape]<<" "<<num2[a.num]<<"\n";
        wastepile.insert(a.shape,a.num);
        //current_situation();
        return true;
    }else{
        return false;
    }
}
//scan playing decks and wastepile if it can go into output deck
//one condtion:it has to have same shape
//and has to have +1 .num element
bool game::step_a(){
    //first lets scan playing deck
    for(int j=0;j<4;j++){
        for(int k=0;k<7;k++){       //scaning all 7 playing deck
            if(deck1_open_end[k]>0&&deck1_open[k][deck1_open_end[k]-1].shape==j&&
               deck1_open[k][deck1_open_end[k]-1].num==output[j].isempty()*(output[j].what_is_on_top().num+1)){
                //if the card is insertable as rule insert it
                card a= deck1_open[k][deck1_open_end[k]-1];
                deck1_open_end[k]-=1;
                //if the move was made move the cursor of open card
                output[j].insert(a.shape,a.num);
                //std::cout<<a.shape<<"   "<<a.num<<"\n";
                score+=5;
                flip();
                fileoutput(a.shape, a.num, j, k);
                //if only one card or moved end the step
                return true;
            }
        }//scaning for wastepile can go into the output
        if(wastepile.get_len()>0&&wastepile.what_is_on_top().shape==j&&
           wastepile.what_is_on_top().num==output[j].isempty()*(output[j].what_is_on_top().num+1)){
            card a= wastepile.pop();       // call the first card on top of waste pile
            output[j].insert(a.shape,a.num);
            score+=5;                      //insert the card.
            flip();
            fileoutput(a.shape, a.num, j, 11);
            return true;
        }
    }

    flip();
    return false;
}

// step b scans if card on wastpile can go into the playing card
//there is a condition card should have different color from existing open card
//and has to have one less card.num
bool game::step_b(){
    if(wastepile.get_len()==0&&stock.get_len()>0){
        draw();
    }for(int k=0;k<7;k++){  //checking if card can go below existing open playing card
        if(wastepile.get_len()>0&&
           wastepile.what_is_on_top().num+1==deck1_open[k][deck1_open_end[k]-1].num
           &&wastepile.what_is_on_top().shape%2!=deck1_open[k][deck1_open_end[k]-1].shape%2){
            card a=wastepile.pop();
            deck1_open_end[k]+=1;
            deck1_open[k][deck1_open_end[k]-1]=a;
            fileoutput(a.shape, a.num, k, 11);
            return true;
        }else if(wastepile.get_len()>0&&wastepile.what_is_on_top().num==12&&deck1_open_end[k]==0&&deck1[k].get_len()==0){
            // or it can go in the blank spot if it is king card
            card a=wastepile.pop();
            deck1_open_end[k]+=1;
            deck1_open[k][deck1_open_end[k]-1]=a;
            fileoutput(a.shape, a.num, k, 11);
            return true;
        }
    }
    return false;
}
//step C is most important it moves card from one to another playing decks
//there is a condition card should have different color from existing open card
//and has to have one less card.num
bool game::step_c(){
    for(int source=0;source<7;source++){                        //scan for every playing deck
        if(deck1_open_end[source]!=0){                          //if there is any open card from source
            for(int dest=0;dest<7;dest++){                      //scanning destination
                if(dest!=source&&deck1_open_end[dest]!=0){      //if source is not destination(no moving from 6 to 6
                    for(int foo=0;foo<deck1_open_end[source];foo++){        //scaning all combination(if D7 S6 H5 try for all D7top S6top H5top move)
                        if(deck1_open[source][foo].num+1==deck1_open[dest][deck1_open_end[dest]-1].num&&
                           deck1_open[source][foo].shape%2!=deck1_open[dest][deck1_open_end[dest]-1].shape%2&&
                           loop_sensin++<1000&&
                           record_scan(dest,
                                       source,
                                       0,
                                       deck1_open[source][foo].num+13*deck1_open[source][foo].shape,
                                       deck1_open[source][deck1_open_end[source]-1].num+13*deck1_open[source][deck1_open_end[source]-1].shape)){
                            //if it fullfill the condition from above
                            //and not a same move frop past
                            card a=deck1_open[source][foo];
                            for(int k=0;k<deck1_open_end[source]-foo;k++){
                                deck1_open[dest][deck1_open_end[dest]+k]=deck1_open[source][k+foo];
                            }//moving the card
                           // fileoutput(a.shape, a.num, dest, source);
                            record(dest,
                                   source,
                                   0,
                                   deck1_open[source][foo].num+13*deck1_open[source][foo].shape,
                                   deck1_open[source][deck1_open_end[source]-1].num+13*deck1_open[source][deck1_open_end[source]-1].shape);                            deck1_open_end[dest]+=deck1_open_end[source]-foo;
                            //record the move
                            deck1_open_end[source]=foo;
                            //change the cursor for open card
                            if(flip()){
                                loop_sensin=0;
                            }
                            //score+=4;
                            fileoutput(a.shape, a.num, dest, source);
                            return true;
                        }
                    }
                }else if(dest!=source&&deck1_open_end[dest]==0){        //this one is relatively simple
                    if(deck1_open[source][0].num==12&&deck1[source].get_len()!=0){  //If there is a blank spot and top of destination is top
                        card a=deck1_open[source][0];
                        
                        for(int k=0;k<deck1_open_end[source];k++){                  //and there is a card to disclose in the source
                            deck1_open[dest][deck1_open_end[dest]+k]=deck1_open[source][k];
                        }                                                           //move the whole stack
                        deck1_open_end[dest]+=deck1_open_end[source];
                        deck1_open_end[source]=0;
                        flip();
                        loop_sensin=0;                                  //if this move was made it means no loop
                        fileoutput(a.shape, 12, dest, source);
                        return true;
                    }
                }
            }
        }
        
    }loop_sensin=0; //if no move was made it means no loop
    return false;
}
//execute all three moves and
bool game::step_abc(){
    bool a = step_a();
    //std::cout<<"A  \n";
    if(a){//current_situation();
        
    }
    bool b = step_b();
    //std::cout<<"B  \n";
    if(b){//current_situation();
        
    }
    bool c = step_c();
    //std::cout<<"C  \n";
    if(c){//current_situation();
        
    }
    return a||b||c;//return true if at least one moves were made
}
//Just a function for debuging it make a output to describ a current situation
/*
 EX)
 STCK    7 WAST: 8 TC: D K |     H: 0     C: 1     D: 0     S:1
 d1:0    d2:1    d3:1     d4:3     d5:4     d6:4     d7:5
 o1:H J  o2:S 6  o3:S K   o4:D J   o5:C 7   o6:S 5   o7:S 3
         o2:D 5  o3:H Q            o5:H 6   o6:H 4   o7:D 2
         o2:S 4  o3:S J                     o6:C 3
                 o3:D X
                 o3:C 9
                                                         
 SCORE: -42

 H:heart K:king C :clover D:diamond
 A:ace X:10
 */
void game::current_situation(){
    std::ofstream out2("test.txt",std::ios::app);
    out2<<"STCK\t"<<stock.get_len()<<
    " WAST: "<<wastepile.get_len();
    if(wastepile.get_len()){out2<<" TC: "<<shape2[wastepile.what_is_on_top().shape]<<" "<<num2[wastepile.what_is_on_top().num];}
    out2<<" |\t ♥: "<<output[0].get_len()<<
    "\t ♣: "<<output[1].get_len()<<
    "\t ♦: "<<output[2].get_len()<<
    "\t ♠:"<<output[3].get_len()<<" \n";
    
    out2<<"d1:"<<deck1[0].get_len()<<
    " \td2:"<<deck1[1].get_len()<<
    " \td3:"<<deck1[2].get_len()<<
    " \td4:"<<deck1[3].get_len()<<
    " \td5:"<<deck1[4].get_len()<<
    " \td6:"<<deck1[5].get_len()<<
    " \td7:"<<deck1[6].get_len()<<"\n";
    for(int i=0;i<13;i++){
        int chek=7;
        for(int k=0;k<7;k++){
            if(i<deck1_open_end[k]){
                out2<<"o"<<k+1<<":"<<shape2[deck1_open[k][i].shape]<<" "<<num2[deck1_open[k][i].num]<<"\t";
                
                //out2<<"o1:"<<deck1_open[k][i].shape<<" "<<deck1_open[k][i].num<<"\t";

            }else{
                out2<<"\t";
                chek-=1;
            }
        }
        out2<<"\n";
        if(chek==0){
            break;
        }
    }
    out2<<"SCORE: "<<score<<"\n\n";
}


int main()
{
    int iter =2;
    int record[iter];
    int i208_count=0;
    //int i5000_avg=0;
    int isum=0;
    std::ofstream out("test.txt");
    for(int k=0;k<iter;k++){
        std::cout<<k<<"\n";
        game game1=game();
        while(1==1){                    //loop while there is a way
            bool abc =game1.step_abc(); //execute a b c once in order
            //std::cout<<"abc?"<<abc<<"\n\n";
            if(abc){        //execute ABC in order and IF move was made it will be true
            }else{          //incase of no move lets try draw
                bool draw = game1.draw();
                if(!draw){  //if it card cannot be drwan while no move availabe it is gameover
                    std::ofstream out("test.txt",std::ios::app);
                    out<<"GAME OVER"<<std::endl;
                    break;  //no moves are available
                }
            }
        }
        isum+=game1.score;
        if(game1.score==208){
            i208_count++;
        }
        record[k]=game1.score;
    }
    for(int k=0;k<iter;k++){
        std::cout<<record[k]<<"\n";
        
    }std::cout<<i208_count<<"\n";
    std::cout<<isum/iter<<"\n";
}
