#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <climits>
using namespace std;


void display_board(char table[3][3]){
    int rows=3;
    int columns=3;
    system("cls");
    cout<<"PLAYER VS COMPUTER GAME"<<endl;

    cout<<"    ";
    for (int j=0;j<columns;j++){
        cout<<" ("<<j<<")";
    }
    cout<<endl;
    for (int i=0;i<rows;i++){
        cout<<"    ";
        for (int j=0;j<columns;j++){
            cout<<"----";
        }
        cout<<"-";
        cout<<endl;  
        cout<<"("<<i<<") "<<"|"; 
        for (int j=0;j<columns;j++){
            cout<<" "<<table[i][j]<<" |";
        }           
        cout<<endl;   
    }
    cout<<"    ";
    for (int j=0;j<columns;j++){
        cout<<"----";
    }
    cout<<"-"<<endl;
}


bool check_win(char table[3][3],int y,int x){
    int rows=3;
    int columns=3;
    rows--;    //reduce because table's rows indexing start from 0 and end in rows-1 
    columns--; //reduce because table's columns indexing start from 0 and end in columns-1

    if (table[y][x]!=' '){
        //check for row win
        if ((x-2)>=0){     //check if x in 2 positions left,is not out of array's dimensions.
            if ((table[y][x]==table[y][x-1] && table[y][x]==table[y][x-2])){ //check if the current position character is the same as the characters of its 2 left cells of the board (in the same height)
                return true;
            }
        }
        if (x+2<=columns){   //check if x in 2 positions right, is not out of array's dimensions.
            if ((table[y][x]==table[y][x+1] && table[y][x]==table[y][x+2])){ //check if the current position character is the same as the characters of its 2 right cells of the board (in the same height)
                return true;
            }
        }
        if (x-1>=0 && x+1<=columns){ //check if either x in 1 position left or x in 1 position right is not out of array's dimensions.
            if (table[y][x]==table[y][x-1] && table[y][x]==table[y][x+1]){ //check if current position left and right cells have the same characters.
                return true;
            }
        }

        //check for column win
        if (y-2>=0){ //check if y in 2 positions up,is not out of array's dimensions.
            if (table[y][x]==table[y-1][x] && table[y][x]==table[y-2][x]){  //check if the current's position character is the same as the characters of its 2 upper cells of the board (in the same height)
                return true;
            }
        }
        if (y+2<=rows){ //check if y in 2 positions down,is not out of array's dimensions.
            if (table[y][x]==table[y+1][x] && table[y][x]==table[y+2][x]){  //check if the current's position character is the same as the characters of its 2 bottom cells of the board (in the same height)
                return true;
            }
        }
        if (y-1>=0 && y+1<=rows){ //check if either y in 1 position up or y in 1 position down is not out of array's dimensions.
            if (table[y][x]==table[y-1][x] && table[y][x]==table[y+1][x]){ //check if current's position upper and bottom cells have the same characters.
                return true;
            }
        }
                                                            
        //check for diagonal win                                                
        if (x-2>=0 && y-2>=0){ //diagonally 2 left and upper cells of the board  
            if (table[y][x]==table[y-1][x-1] && table[y][x]==table[y-2][x-2]){
                return true;
            }
        }
        if (x-2>=0 && y+2<=rows){ //diagonally 2 left and bottom cells of the board
            if (table[y][x]==table[y+1][x-1] && table[y][x]==table[y+2][x-2]){
                return true;
            }
        }
        if ((x-1>=0 && y-1>=0) && (x+1<=columns && y+1<=rows)){ //diagonally 1 left and upper cell , and 1 right and bottom cell of the board 
            if (table[y][x]==table[y-1][x-1] && table[y][x]==table[y+1][x+1]){
                return true;
            }       
        }
        if (x+2<=columns && y+2<=rows){ //diagonally 2 right and bottom cells of the board
            if (table[y][x]==table[y+1][x+1] && table[y][x]==table[y+2][x+2]){
                return true;
            }
        }
        if (x+2<=columns && y-2<=2){ //diagonally 2 right and upper cells of the board
            if (table[y][x]==table[y-1][x+1] && table[y][x]==table[y-2][x+2]){
                return true;
            }
        }
        if ((x-1>=0 && y+1<=rows) && (x+1<=columns && y-1>=0)){ //diagonally 1 left and bottom cell , and 1 right and upper cell of the board
            if (table[y][x]==table[y+1][x-1] && table[y][x]==table[y-1][x+1]){
                return true;
            }
        }
    }
return false;
}


bool play(char table[3][3],char player_symbol){
    int x,y;
    int rows=3;
    int columns=3;
    while (true){
        cin>>y>>x;
        if (!(y<rows && x<columns))
            cout<<"Give correct coordinates!"<<endl;
        else if (table[y][x]!=' ')
            cout<<"This position is already played.Choose a different one."<<endl;
        else
            break;
    }
    table[y][x]=player_symbol;
    //display the changes in the board.
    display_board(table);
    //check if with this move the player wins
    bool result=check_win(table,y,x);
    return result;
}


bool check_if_full(char table[3][3]){
    //check if the board has empty cells
    int rows=3;
    int columns=3;
    for (int i=0;i<rows;i++){
        for (int j=0;j<columns;j++){
            if (table[i][j]==' ')
                return false;
        }
    }
    return true;
}



int min_max(char table[3][3],char player,int y,int x,int depth,int limit){
    int result;
    if (check_win(table,y,x)){
        if (player=='x'){ //computer with 'o' won
            return 1;
        }
        else{
            return -1;
        }
    }
    else if (check_if_full(table) || depth==limit){
        return 0;
    }
    if (player=='o'){  //maximizing player player
        int score=INT_MIN;
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if (table[i][j]==' '){
                    table[i][j]='o';
                    result=min_max(table,'x',i,j,depth+1,limit);
                    table[i][j]=' ';
                    //score=max(score,result[0]);
                    if (result>=score){
                        score=result;
                    }
                    //optimize
                    if (result==1){
                        return 1;
                    }
                }
            }
        }
        return score;
    }
    else{  //minimizing player
        int score=INT_MAX;
        for (int i=0;i<3;i++){
            for (int j=0;j<3;j++){
                if (table[i][j]==' '){
                    table[i][j]='x';
                    result=min_max(table,'o',i,j,depth+1,limit);
                    table[i][j]=' ';
                    score=min(score,result);
                    //optimize
                    if (result==-1){
                        return -1;
                    }
                }
            }
        }
        return score;
    }
} 


void player_vs_computer(char table[3][3]){
    bool result;
    int rows=3,columns=3;
    //////table[0][0]='x';
    //////table[0][2]='o';
    display_board(table);
    while (true){
        cout<<"Where do you want to play? (Give 2 numbers in the form of <y x> where y is the row and x is the column that you want to play )"<<endl;
        //players 1 turn
        result=play(table,'x');
        if (result==true){
            cout<<"Player 1 WON!"<<endl;
            break;
        }
        if (check_if_full(table)){
            cout<<"Board fulled! DRAW!"<<endl;
            break;
        }

        //computers turn 
        bool flag=0,flag1=0;
        int result,best_score=-99,Y,X;
        for (int i=0;i<rows && flag==0;i++){
            for (int j=0;j<columns && flag==0;j++){
                if (table[i][j]==' '){
                    table[i][j]='o';
                    if (check_win(table,i,j)){
                        flag=1;
                    }
                    result=min_max(table,'x',i,j,0,10);
                    //cout<<result<<endl;
                    table[i][j]=' ';

                    if (result>=best_score){
                        best_score=result;
                        Y=i;
                        X=j;
                    }
                }
            }
        }
        // If the result of a move is always defeat, at least delay the enemy player as much as possible , in case he makes a wrong move 
        flag=0;
        if (best_score==-1){
            for (int i=0;i<rows && flag==0;i++){
                for (int j=0;j<columns && flag==0;j++){
                    if (table[i][j]==' '){
                        table[i][j]='x';
                        if (check_win(table,i,j)){
                            //table[k][l]='o';
                            Y=i;
                            X=j;
                            flag=1;
                        }
                        table[i][j]=' ';
                    }
                }
            }
        }
        //if you can win with 1 move, win without delaying the win even more with more moves

        
        table[Y][X]='o';
        if (check_win(table,Y,X)){
            cout<<"Computer WON!"<<endl;
            display_board(table);
            break;
        }
        display_board(table);
        cout<<best_score<<endl;
    }
}

void player_vs_player(char table[3][3]){
    char player1='x',player2='o';
    bool result;
    display_board(table);
    while (true){
        cout<<"Where do you want to play? (Give 2 numbers in the form of <y x> where y is the row and x is the column that you want to play )"<<endl;
        //players 1 turn
        result=play(table,player1);
        if (result==true){
            cout<<"Player 1 WON!"<<endl;
            break;
        }
        if (check_if_full(table)){
            cout<<"Board fulled! DRAW!"<<endl;
            break;
        }

        cout<<"Where do you want to play? (Give 2 numbers in the form of <y x> where y is the row and x is the column that you want to play )"<<endl;
        //players 2 turn
        result=play(table,player2);
        if (result==true){
            cout<<"Player 2 WON!"<<endl;
            break;
        }
        if (check_if_full(table)){
            cout<<"Board fulled! DRAW!"<<endl;
            break;
        }
}
}


int main(){
int x,y,n=3,m=3;
char table[3][3];
//initializing the cells of the table/board with spaces
for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
        table[i][j]=' ';
    }
}
bool answer=1;
char ans;

while (true){
cout<<"Type 0 if you want to play 1v1 with another player"<<endl;
cout<<"Type 1 if you want to play 1v1 with computer"<<endl;
cin>>answer;
if (!answer){
    player_vs_player(table);
}
else{
    player_vs_computer(table);
}
cout<<"Do you want to play again? y/n"<<endl;
cin>>ans;
if (ans=='n' || ans=='N'){
    break;
}
else if (ans=='y' || ans=='Y'){
    for (int i=0;i<m;i++){
    for (int j=0;j<n;j++){
        table[i][j]=' ';
    }
}
}
else{
    cout<<"Please answer with 'y' for yes or 'n' for no"<<endl;
}

}
}

