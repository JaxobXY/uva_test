#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>


using namespace std;

int x = 25;
int y = 25;
#define gridsize 50
#define sight 3
char grid[gridsize][gridsize]; // Declaration
string item[gridsize][gridsize] = {"blank"}; // Declaration
bool barrier[gridsize][gridsize] = {false};
string inventory[10] = {"blank","blank","blank","blank","blank","blank","blank","blank","blank","blank"};
int curslot = 1;
void movement(char move)
{
    int nx, ny;
    nx=x;
    ny=y;
    if(move == 'w') ny -= 1; // Standard grid: W is up
    else if(move == 'a') nx -= 1;
    else if(move == 's') ny += 1; // Standard grid: S is down
    else if(move == 'd') nx += 1;
    // Boundary checks
    if(nx >= gridsize) nx = gridsize - 1;
    if(nx < 0) nx = 0;
    if(ny >= gridsize) ny = gridsize - 1;
    if(ny < 0) ny = 0;

    if(barrier[ny][nx]==true)
    {
        nx=x;
        ny=y;
    }

    y=ny;
    x=nx;
}

void printgrid(ofstream &fout)
{
    int height = 4;
    int width = 8;
    
    for(int tile_i = y - sight; tile_i <= y + sight; tile_i++)
    {
        for(int h = 0; h < height; h++)
        {
            for(int tile_j = x - sight; tile_j <= x + sight; tile_j++)
            {
                if(tile_i >= 0 && tile_i < gridsize && tile_j >= 0 && tile_j < gridsize)
                {
                    if(tile_j == x && tile_i == y) 
                    {
                        // Player as repeated 'P' (simpler, works better)
                        for(int w = 0; w < width; w++)
                            fout << 'P';
                    }
                    else 
                    {
                        char tile_char = grid[tile_i][tile_j];
                        for(int w = 0; w < width; w++)
                            fout << tile_char;
                    }
                }
                else
                {
                    // ONLY print border if actually out of bounds
                    fout << string(width, '█');  // Clean 8-char border
                }
            }
            fout << endl;
        }
    }
}


void printinventory(ofstream &fout)
{
    for(int i=1;i<10;i++)
    {
        if(i==curslot)
        {
            fout << "█";
        }
        else
        {
            fout << " ";
        }
        fout << "slot " << i << " is currently " <<  inventory[i] << " " << endl;
    }
    if(0==curslot)
    {
        fout << "█";
    }
    else
    {
        fout << " ";
    }
    fout << "slot 0 is currently " <<  inventory[0] << " " << endl;
}
void inventoryedit(char edit)
{
    if(edit == 'y')
    {
        swap(inventory[curslot], item[x][y]);
    }
    else if(edit == 'u')
    {
        if (item[x][y] == "blank")
        {
            item[x][y] = inventory[curslot];
            inventory[curslot] = "blank";
        }
    }
    else
    {
        curslot = edit-'0';
    }
}
int main()
{
    cout << "instructions:" << endl << "1(movement):wasd" << endl << "2(escape):e" << endl << "3(slot): 1-0 to choose item slot" << endl << "4(item):y to swap current item with item on ground, u to use" << endl << " compile first, then go to output.txt, then run." << endl;
    // FILL THE GRID WITH A CHECKERBOARD BACKGROUND
    for(int i = 0; i < gridsize; i++) {
        for(int j = 0; j < gridsize; j++) {
            if ((i + j) % 2 == 0)
                grid[i][j] = '@';     // light tile
            else
                grid[i][j] = '$';     // dark tile
        }
    }
    // Initialize ALL items to "blank"
    for(int i = 0; i < gridsize; i++) {
        for(int j = 0; j < gridsize; j++) {
            item[i][j] = "blank";
        }
    }



    // MANUALLY PLACING CHARACTERS INTO THE GRID
    grid[22][22] = '#';
    barrier[22][22] = true;
    grid[22][23] = '#';
    barrier[22][23] = true;
    grid[22][24] = '#';
    barrier[22][24] = true;
    grid[28][28] = 'X';
    barrier[28][28] = true; 
    grid[28][27] = 'X';
    barrier[28][27] = true;
    grid[20][30] = 'O';
    barrier[20][30] = true; 
    grid[21][30] = 'O';
    barrier[21][30] = true;
    grid[10][10] = 'T';
    barrier[10][10] = true; 
    grid[10][11] = 'T';
    barrier[10][11] = true;
    grid[40][40] = 'M';
    barrier[40][40] = true;
    grid[5][5]   = '?';
    barrier[5][5] = true;
    item[0][1] = "box";
    item[1][0] = "knife";
    ofstream ofs("output.txt", ios::out | ios::trunc);
    printgrid(ofs);
        // instant single-char input on macOS terminal
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);       // save old settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);     // turn off canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char input = 'm';
    while(input != 'e')
    {
        input = getchar();                // no Enter required
        if(input == 'w' || input == 'a' || input == 's' || input == 'd')
        {
            movement(input);
        }
        if(input == '1' || input == '2' || input == '3' || input == '4' || input == '5' || input == '6' || input == '7' || input == '8' || input == '9'|| input == '0'|| input == 'y'  || input == 'u' )
        {
            inventoryedit(input);
        }
        ofstream ofs("output.txt", ios::out | ios::trunc);
        ofs << x+1 << "," << y+1 << endl;
        printgrid(ofs);
        printinventory(ofs);
        ofs.close();
    }
    // restore terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return 0;
} 