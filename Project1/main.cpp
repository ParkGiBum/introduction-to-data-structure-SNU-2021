#include <iostream>
//to activate in the terminal press # #(#being number youwant form 0to7 ex) 2 6)
/*
 As the book describes I designed the board as below
 
    0   1   2   3   4   5   6   7
 0  .   .   .   .   .   .   .   .
 1  .   .   .   .   .   .   .   .
 2  .   .   .   .   .   .   .   .
 3  .   .   .   .   .   .   .   .
 4  .   .   .   .   .   .   .   .
 5  .   .   .   .   .   .   .   .
 6  .   .   .   .   .   .   .   .
 7  .   .   .   .   .   .   .   .
 
 horizental axis being y and vertical axis being  x
 For intance when we say 0,7 it means most upper left corner of the board
 This code will show knight travle promblem result with both simple and complex Warnsdorff method and its result whether it is successfull or not.
 When we say simple method it compares possiblity when we made move
 For example when knight start at 4 2 if it moves to +2,-1 it has least amount of possibility with 2 so it decides to move to +2,-1
 If there is a tie with more than two moves it prioritize from 1,-2 to -1,-2 by clock wise direction.
 
 In the complex method it goes one step further when tie happens it compares possiblity of does next tie moves.
 for example when it starts with 4,3 (1,2)(-1,2)(-2,1)(-2-1) ties so we compare if we move to does moves how many total move can be made after two moves later? in (1,2)is 24 (-1,2) 19 (-2,1) 19 (-2,-1)24 so it ties again so we should choose between (-1,2) and (-2,1) and if we prioritize as the simple method we choose (-1,2)
 

 Here is the example input and output
 
 input:
 4 4
output:
 simple scan
 Success
 63    58    11    46    25    4    9    6
 12    47    64    57    10    7    26    3
 59    62    51    48    45    24    5    8
 50    13    56    61    52    27    2    23
 55    60    49    44    1    34    19    28
 14    43    38    53    40    31    22    33
 37    54    41    16    35    20    29    18
 42    15    36    39    30    17    32    21


 complex scan
 Fail
 17    20    15    44    49    22    57    26
 14    43    18    21    0    25    48    23
 19    16    53    50    45    56    27    58
 52    13    42    0    54    59    24    47
 41    38    51    60    1    46    55    28
 12    35    10    39    0    31    2    5
 9    40    37    34    7    4    29    32
 36    11    8    0    30    33    6    3
 Program ended with exit code: 0
 */

class Knight{
    public:
        Knight(int i, int j);
        ~Knight();
        int board[8][8];                        //This act as a board
        int location[2];                        //current loaction
        static int ktmov1[8];                   //moves possibillity
        static int ktmov2[8];                   //ex) if (1,-2) and (1,2) ties we choose (1,-2)
        int npos;                               //moves to be made we will move to (ktmov1[npos],ktmov2[npos]) ex) 0 means we goes to (1,-2)
        int simple_scan();                      //simple scan function
        int complex_scan();                     //complex scan function
        int* scan(int x, int y);                //basic scan function which will be ustiilized both is simple and complex
        int counter;                            //saves how much moves knight has made so far
        int move(int k);                        //move function that simple and complex both use after ways is decided. act similar as nexti
};
int Knight::ktmov2[]={1,2,2,1,-1,-2,-2,-1};
int Knight::ktmov1[]={-2,-1,1,2,2,1,-1,-2};
//simple constructor which gets coordinate as input and initialize the board
Knight::Knight(int i,int j){
    this->location[0]=i;
    this->location[1]=j;
    counter=1;
    for(int k=0;k<64;k++){
        board[k%8][k/8]=0;
    }
    board[i][j]=1;
}

Knight::~Knight(){
}

/*
 move function it does two things
 1.change location
 2.change does location as visisted
 */
int Knight::move(int k){
    if(k==8){
        std::cout<<"WARNING!!!!!!!!!! not legal move!!!!!!!!\n";
    }
    counter++;
    location[0]+=ktmov1[k];
    location[1]+=ktmov2[k];
    board[location[0]][location[1]]=counter;
    return 0;
}

/*
 scan function takes current location as input and
 return
 1. which move has smallest possibility after one move
 2. what is the sum of the possibilities(only used it complex method)
 3. list of tie moves saved as binary ex) 17 means 1 and 4(only used it complex method)
 these three information with array
 */
int* Knight::scan(int x,int y){
    int min=8;
    int minval=64;
    int sum=0;
    int tie =0;
    int tie_counter=1;
    for(int c=0;c<8;c++){
        int way=0;
        int loaction_candidate[2];
        loaction_candidate[0]=x+ktmov1[c];
        loaction_candidate[1]=y+ktmov2[c];
        /*if below find whether each move is valid
        1.If it I make move is it within the 8*8 board?
        2.Is it unvisited?*/
        if(loaction_candidate[0]<8&&loaction_candidate[1]<8&&
        loaction_candidate[1]>=0&&loaction_candidate[0]>=0&&
        board[loaction_candidate[0]][loaction_candidate[1]]==0){
            for(int s=0;s<8;s++){
                if(loaction_candidate[0]+ktmov1[s]<8&&
                   loaction_candidate[1]+ktmov2[s]<8&&
                   loaction_candidate[1]+ktmov2[s]>=0&&
                   loaction_candidate[0]+ktmov1[s]>=0&&
                   board[loaction_candidate[0]+ktmov1[s]][loaction_candidate[1]+ktmov2[s]]==0){
                    way++;
                    sum++;
                }
            }
            if(way==0){
                min=c;
            }
        }else{
            way=-1;
        }
        if(minval>way&&way!=-1){
            //If it is smallter than former minimum value switch way and sum
            minval=way;
            min=c;
            //And reset tie points
            tie=tie_counter;
        }else if(minval==way){
            tie+=tie_counter;
        }
        tie_counter*=2;
    }
    static int result[3];
    result[0]=min;
    result[1]=sum;
    result[2]=tie;
    return result;
}
/*
 Simple function that moves as result of scan()
 */
int Knight::simple_scan(){
    for(int count=0;count<64;count++){
        npos = scan(location[0],location[1])[0];
        //incase of success it will just move 63 times and end.
        if (count==63){
            //incase of failure stop right away and output fail meesage and
            //board structure
            std::cout<<"success \n";
            for(int k=0;k<8;k++){
                for(int j=0;j<8;j++){
                    std::cout<<board[k][j]<<"\t";
                }std::cout<<"\n";
            }break;
        }else if(npos==8){
            //incase of success stop right away and output success meesage and
            //board structure
            std::cout<<"fail \n";
            for(int k=0;k<8;k++){
                for(int j=0;j<8;j++){
                    std::cout<<board[k][j]<<"\t";
                }std::cout<<"\n";
            }
            
            break;
        }
        move(npos);
    }
    return 0;
}
/*
 In case of complex scan it first do simple scans and if there is no tie
 it just do as simple scan
 But if tie happens it goes one move further
 */
int Knight::complex_scan(){
    for(int counter1=0;counter1<64;counter1++){
        int eval=100;
        npos=8;
        // lets do a simple scan first
        int* scan_result=scan(location[0],location[1]);
        int tie=scan_result[2];
        int numberofsimple=0;       //this is number of smallest move in simplescan
        int tovisit[8];             //and this is array of does moves
        for(int k=0;k<8;k++){
            if(tie%2==1){
                tovisit[k]=1;
                numberofsimple++;
            }else{
                tovisit[k]=0;
            }tie=tie/2;
        }//it translate decimal number to binary ex)tie 17->[0,0,0,1,0,0,0,1]
        //it means in case it has more than one 1s it means tie happens
        
        //In case of no tie it is same as simple scan
        //Otherwise it goes one step further
        if(numberofsimple>1){
            //complex
            for(int i=0;i<8;i++){
                if(tovisit[i]==1){
                    board[location[0]+ktmov1[i]][location[1]+ktmov2[i]]=counter1;
                    //to calculte precisely lets say tie simple move is visited
                    int *value=scan(location[0]+ktmov1[i],location[1]+ktmov2[i]);
                    //than do a simple scans
                    if(value[1]<eval&&value[1]!=0){
                        //if it is in the tie list comapre with those value
                        eval=value[1];
                        npos=i;
                    }board[location[0]+ktmov1[i]][location[1]+ktmov2[i]]=0;
                    //and restore the unvisited satets
                }
            }
        }else{
            //same as simple from below
            npos=scan_result[0];
        }
        if(counter1==63){
            std::cout<<"success \n";
            for(int k=0;k<8;k++){
                for(int j=0;j<8;j++){
                    std::cout<<board[k][j]<<"\t";
                }std::cout<<"\n";
            }break;
        }else if(npos==8){
            std::cout<<"fail \n";
            for(int k=0;k<8;k++){
                for(int j=0;j<8;j++){
                    std::cout<<board[k][j]<<"\t";
                }std::cout<<"\n";
            }break;
        }
        move(npos);
    }

    return 0;
}




/*
 Below is the main function to activate in the terminal press # #(#being number youwant form 0to7 ex) 2 6
 
 
 */
int main(int argc, const char * argv[]) {
    // insert code here…
    int i,j;
    std::cin>>i>>j;
    Knight *knigth = new Knight(i,j);
    
    std::cout<<"simple scan\n" ;
    knigth->simple_scan();
    Knight *knigth2 = new Knight(i,j);
    std::cout<<"\n\n";
    std::cout<<"complex scan \n";
    knigth2->complex_scan();
    delete knigth;
    delete knigth2;
    return 0;
}
