#include <iostream>
#include <fstream>
#include "conio.h"
#include <unistd.h>

using namespace std;
using namespace conio;

bool escape(int row, int col, char maze[10][10]);
void printMaze(int row, int col, char maze[10][10]);

int main() {

    char fileName[256];
    char maze[10][10];
    char originalMaze[10][10];
    cout << "Enter maze name: ";
    cin >> fileName;
    ifstream mazeFile;

    mazeFile.open(fileName);

    if (! mazeFile.is_open()) {
        cerr << "error opening"<<fileName << endl;
        return 1;
    }

    for (int row=0; row<10; row++){
        for (int col=0; col<10; col++){
            mazeFile >> maze[row][col];
            originalMaze[row][col] = maze[row][col];
        }
            
    }
    int r;
    int c;
    bool quit = false;
    string input;
    while (!quit){
        
        clrscr();
        
        mazeFile.open(fileName);


        printMaze(0,0,originalMaze);

        cout << "Enter a row: ";
        cin >> r;
        cout << "Enter a col: ";
        cin >> c;
        cout << conio::gotoRowCol(r+2,c+2) << "@\b" << flush;
        bool survive;
        survive = escape( r, c, maze);
        if (survive){
             cout << gotoRowCol(15,1) << "ESCAPED!" << endl;
        }

        else if (! survive){
             cout << gotoRowCol(15,1) << "NO ESCAPE" << endl;
        }
        cout << gotoRowCol(16,1) << conio::resetAll() << flush;

        cout << "Type QUIT to quit or CONTINUE to try again: ";
        cin >> input;
        if (input == "QUIT"){
            quit = true;
        }  else { printMaze(0,0,originalMaze); }
    }
    
    cout << clrscr() << gotoRowCol(1,1) << conio::resetAll() << flush;
   
    
    return 0;

}

bool escape(int row, int col, char maze[10][10]){
        if ( row>=10 || col>=10 || row<0 || col<0 ){
            //base case #1
            return false;
        }
        else if (maze[row][col] == 'E'){
            //base case #2
            cout << gotoRowCol(row+2,col+2) << conio::bgColor(conio::GREEN) << "@\b" << flush;
            usleep(250000);
            return true;
        }
        else if (maze[row][col] == '#'){
            //base case #3
            return false;
        }
        else if (maze[row][col] == '!'){
            //base case #4
            return false;
        }
        maze[row][col] = '!';
        cout << gotoRowCol(row+2,col+2) << conio::bgColor(conio::YELLOW) << "@\b" << flush;
        usleep(250000);

        //recursion

        //down 1
        if (escape(row+1, col, maze)){
            cout << gotoRowCol(row+2,col+2) << conio::bgColor(conio::GREEN) << "@\b" << flush;
            usleep(250000);
            return true;
        }
        //right 1
        else if (escape(row, col+1, maze)){
            cout << gotoRowCol(row+2,col+2) << conio::bgColor(conio::GREEN) << "@\b" << flush;
            usleep(250000);
            return true;
        }
        //up 1
        else if (escape(row-1, col, maze)){
            cout << gotoRowCol(row+2,col+2) << conio::bgColor(conio::GREEN) << "@\b" << flush;
            usleep(250000);

            return true;
        }
        //left 1
        else if (escape(row, col-1, maze)){
            cout << gotoRowCol(row+2,col+2) << conio::bgColor(conio::GREEN) << "@\b" << flush;
            usleep(250000);

            return true;
        }
        
        else{
            cout << gotoRowCol(row+2,col+2) << conio::bgColor(conio::RED) << "@\b" << flush;
            usleep(250000);

            return false;
        }



}


void printMaze(int row, int col, char maze[10][10]){
	cout << conio::clrscr() << flush;
	cout << gotoRowCol(1,1);
	cout << " 0123456789" << endl;
	for (int row=0; row<10; row++){
		cout << row;
		for (int col=0; col<10; col++){
			cout <<  maze[row][col];
		}
		cout << endl;
	}
}


