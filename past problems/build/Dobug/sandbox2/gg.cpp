#include <iostream>
#include <fstream>
#include <string>
#include <termios.h>
#include <unistd.h>

using namespace std;

#define gridsize 50
#define sight 50

// PLAYER POSITIONS
int x1 = 25, y1 = 25;      
int x2 = 30, y2 = 25;      

// LAST FACING DIRECTIONS
int dirx1 = 0, diry1 = -1; 
int dirx2 = 0, diry2 = -1; 

// FASTER MOVEMENT COOLDOWN
int moveCooldownP1 = 0;
int moveCooldownP2 = 0;
const int MOVE_COOLDOWN_TICKS = 1;

// HEALTH SYSTEM
int p1Health = 1000;
int p2Health = 1000;
const int MAX_HEALTH = 1000;

// TEMPORARY ATTACK VISUALS
int attackTick[gridsize][gridsize] = {0};
const int ATTACK_FADE_TICKS = 2;

char grid[gridsize][gridsize];
bool barrier[gridsize][gridsize] = {false};

int p1Slot = 1;
int p2Slot = 1;

bool inBounds(int gx, int gy)
{
    return gx >= 0 && gx < gridsize && gy >= 0 && gy < gridsize;
}

void movement(int &x, int &y, int dx, int dy)
{
    int nx = x + dx;
    int ny = y + dy;

    if(nx >= gridsize) nx = gridsize - 1;
    if(nx < 0) nx = 0;
    if(ny >= gridsize) ny = gridsize - 1;
    if(ny < 0) ny = 0;

    if(barrier[ny][nx]) {
        return;
    }
    x = nx;
    y = ny;
}

void damagePlayer(int player)
{
    if(player == 1) {
        p1Health -= 25;
        if(p1Health < 0) p1Health = 0;
    } else {
        p2Health -= 25;
        if(p2Health < 0) p2Health = 0;
    }
}

void attackLine3(int cx, int cy, int dx, int dy)
{
    for(int i = 1; i <= 3; ++i) {
        int tx = cx + dx * i;
        int ty = cy + dy * i;
        if(!inBounds(tx, ty)) break;
        if(barrier[ty][tx]) break;
        
        if(tx == x2 && ty == y2) damagePlayer(2);
        else if(tx == x1 && ty == y1) damagePlayer(1);
        
        attackTick[ty][tx] = ATTACK_FADE_TICKS;
        grid[ty][tx] = '*';
    }
}

void attackRing(int cx, int cy)
{
    for(int dy_ = -1; dy_ <= 1; ++dy_) {
        for(int dx_ = -1; dx_ <= 1; ++dx_) {
            if(dx_ == 0 && dy_ == 0) continue;
            int tx = cx + dx_;
            int ty = cy + dy_;
            if(!inBounds(tx, ty)) continue;
            if(barrier[ty][tx]) continue;
            
            if(tx == x2 && ty == y2) damagePlayer(2);
            else if(tx == x1 && ty == y1) damagePlayer(1);
            
            attackTick[ty][tx] = ATTACK_FADE_TICKS;
            grid[ty][tx] = '*';
        }
    }
}

void playerAttack(int player)
{
    if(player == 1) {
        if(p1Slot == 1) {
            attackLine3(x1, y1, dirx1, diry1);
        } else {
            attackRing(x1, y1);
        }
    } else {
        if(p2Slot == 1) {
            attackLine3(x2, y2, dirx2, diry2);
        } else {
            attackRing(x2, y2);
        }
    }
}

void updateAttacks(int tick)
{
    for(int i = 0; i < gridsize; i++) {
        for(int j = 0; j < gridsize; j++) {
            if(attackTick[i][j] > 0) {
                attackTick[i][j]--;
                if(attackTick[i][j] == 0) {
                    if ((i + j) % 2 == 0)
                        grid[i][j] = '.';
                    else
                        grid[i][j] = ' ';
                }
            }
        }
    }
}

void printgrid(ofstream &fout)
{
    int height = 1;
    int width = 1;

    // **MOVING CAMERA** - follows players dynamically
    int cx = (x1 + x2) / 2;
    int cy = (y1 + y2) / 2;
    
    // Clamp camera to grid bounds
    if(cx < sight) cx = sight;
    if(cx > gridsize - 1 - sight) cx = gridsize - 1 - sight;
    if(cy < sight) cy = sight;
    if(cy > gridsize - 1 - sight) cy = gridsize - 1 - sight;

    for(int tile_i = cy - sight; tile_i <= cy + sight; tile_i++)
    {
        for(int h = 0; h < height; h++)
        {
            for(int tile_j = cx - sight; tile_j <= cx + sight; tile_j++)
            {
                if(tile_i >= 0 && tile_i < gridsize && tile_j >= 0 && tile_j < gridsize)
                {
                    if(tile_j == x1 && tile_i == y1) {
                        for(int w = 0; w < width; w++) fout << '1';
                    } else if(tile_j == x2 && tile_i == y2) {
                        for(int w = 0; w < width; w++) fout << '2';
                    } else {
                        char tile_char = grid[tile_i][tile_j];
                        if(attackTick[tile_i][tile_j] > 0) {
                            tile_char = '*';
                        }
                        for(int w = 0; w < width; w++) fout << tile_char;
                    }
                }
                else
                {
                    fout << string(width, '█');
                }
            }
            fout << endl;
        }
    }

    fout << "CAMERA: (" << cx+1 << "," << cy+1 << ")  ";
    fout << "HEALTH P1:" << p1Health << " P2:" << p2Health << "\n";
    fout << "POS    P1:" << x1+1 << "," << y1+1 << " P2:" << x2+1 << "," << y2+1 << "\n";
    fout << "SLOT   P1:" << p1Slot << " P2:" << p2Slot << "\n";
    fout << "CTRL: WASD/q/1-2 | Arrows/p/9-0 | e:quit\n";
}

int main()
{
    cout << "2-PLAYER GRID COMBAT - MOVING CAMERA\n";
    cout << "P1: WASD(move) q(attack) 1/2(slots)\n";
    cout << "P2: ARROWS(move) p(attack) 9/0(slots)\n";
    cout << "ESC: e\n";

    // checkerboard
    for(int i = 0; i < gridsize; i++) {
        for(int j = 0; j < gridsize; j++) {
            if ((i + j) % 2 == 0)
                grid[i][j] = '.';
            else
                grid[i][j] = ' ';
        }
    }

    ofstream ofs("output2.txt", ios::out | ios::trunc);
    printgrid(ofs);
    ofs.close();

    // raw input
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    int tick = 0;
    char input = 'm';

    while(input != 'e' && p1Health > 0 && p2Health > 0)
    {
        ++tick;
        int c = getchar();
        input = (char)c;

        int dx1 = 0, dy1 = 0;
        int dx2 = 0, dy2 = 0;

        // P1 input
        if(c == 'w') { dy1 = -1; }
        else if(c == 'a') { dx1 = -1; }
        else if(c == 's') { dy1 = 1; }
        else if(c == 'd') { dx1 = 1; }
        else if(c == 'q') { playerAttack(1); }
        else if(c == '1') { p1Slot = 1; }
        else if(c == '2') { p1Slot = 2; }

        // P2 arrows
        else if(c == 27) {  // ESC
            int c2 = getchar();
            int c3 = getchar();
            if(c2 == '[') {
                if(c3 == 'A') dy2 = -1;
                else if(c3 == 'B') dy2 = 1;
                else if(c3 == 'C') dx2 = 1;
                else if(c3 == 'D') dx2 = -1;
            }
        }
        else if(c == 'p') { playerAttack(2); }
        else if(c == '9') { p2Slot = 1; }
        else if(c == '0') { p2Slot = 2; }

        // update facing
        if(dx1 != 0 || dy1 != 0) {
            dirx1 = dx1;
            diry1 = dy1;
        }
        if(dx2 != 0 || dy2 != 0) {
            dirx2 = dx2;
            diry2 = dy2;
        }

        // move with cooldown
        if((dx1 != 0 || dy1 != 0) && tick >= moveCooldownP1) {
            movement(x1, y1, dx1, dy1);
            moveCooldownP1 = tick + MOVE_COOLDOWN_TICKS;
        }
        if((dx2 != 0 || dy2 != 0) && tick >= moveCooldownP2) {
            movement(x2, y2, dx2, dy2);
            moveCooldownP2 = tick + MOVE_COOLDOWN_TICKS;
        }

        updateAttacks(tick);

        ofstream ofs2("output2.txt", ios::out | ios::trunc);
        printgrid(ofs2);
        ofs2.close();

        usleep(100000);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    
    if(p1Health <= 0) cout << "P2 WINS!\n";
    else if(p2Health <= 0) cout << "P1 WINS!\n";
    else cout << "Game ended.\n";
    return 0;
}
 