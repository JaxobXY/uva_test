#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Debug print: show all piles
void printAll(vector<int>* v[], int n) {
    cout << "\n--- Current state ---\n";
    for (int i = 0; i < n; ++i) {
        cout << i << ":";
        for (int block : *v[i]) {
            cout << " " << block;
        }
        cout << "\n";
    }
    cout << "---------------------\n";
}

int find(int box, vector<int> &place){

        return place[box];
}

void update_locate(int box, int new_index, vector<int> &place){
    place[box] = new_index;
}

void restore_above(vector<int>* &v, int pile_index, int box){
    int temp;

    if(v->empty())
    { // DEBUG:
        cout << "Unexpected empty vector" << endl;
        exit(-1);
    }

    while(v[pile_index]->last()!=box){
        temp = v[pile_index]->pop_back();
        v[temp]->push_back(temp);
        update_locate(temp, temp);
    }

    return;
}

void move_pile(int old_location, int until_reach, int new_location)
{
    vector<int> temp;

    if(v[old_location]->empty() || v[new_location]->empty())
    { // DEBUG:
        cout << "Unexpected empty vector" << endl;
        exit(-1);
    }

    do{
        int item = v[old_location]->pop_back();
        temp.push_back(item);

        if(item==until_reach)
            break;
    }while(1);

    while(!temp.empty()){
        v[new_location].push_back(temp.pop_back());
    }

    return;
}


void move_onto(vector<int>* &v, int a, int b)
{
    int pile_index_a, pile_index_b;
    
    pile_index_a = find(a); // find which pile a is currently at
    restore_above(pile_index_a, a);
    
    pile_index_b = find(b);
    restore_above(pile_index_b, b);
    
    int temp = v[pile_index_a]->pop_back();
    v[pile_index_b]->push_back(temp);

    update_locate(a, pile_index_b);

}



void move_over(vector<int>* &v, int a, int b)
{
    int pile_index_a, pile_index_b;
    pile_index_a = find(a);
    pile_index_b = find(b);

    restore_above(pile_index_a, a);

    int temp = v[pile_index_a]->pop_back();
    v[pile_index_b]-> push_back(temp);

    update_locate(a, pile_index_b);
}

void pile_onto(int a, int b){
    int pile_index_a, pile_index_b;

    pile_index_a = find(a);
    pile_index_b = find(b);

    restore_above(pile_index_b, b);


    move_pile(pile_index_a, a, pile_index_b);
}

void pile_over(int a, int b){
    int pile_index_a, pile_index_b;

    pile_index_a = find(a);
    pile_index_b = find(b);

    move_pile(pile_index_a, a, pile_index_b);
}  




int main() {
    string action1, action2;
    int a, b, n;
    cin >> n;
    vector<int>* v[n] = {nullptr};
    vector<int> place;

    // Initialize each block in its own pile
    for (int i = 0; i < n; i++) {
        v[i] = new vector<int>;
        v[i]->push_back(i);
        place.push_back(i);
    }

    while (cin >> action1 >> a >> action2 >> b) {
        if (action1 != "move" && action1 != "pile") continue;
        if (action2 != "over" && action2 != "onto") continue;
        if (a < 0 || a > n || b < 0 || b > n) continue; // ✅ fixed
        if (place[a] == place[b]) continue;

        // Prepare pile references
        vector<int>& from = *v[place[a]];
        vector<int>& to = *v[place[b]];


        if(action1=="move" && action2=="onto"){
            move_onto(v, a, b);
        } else if(action1=="pile" && action2=="over"){
            pile_over(a, b);
        } else if(action1=="move" && action2=="over"){
            move_over(a, b);
        } else if(action1=="pile" && action2=="onto") {
            pile_onto(a, b);
        } eles {
            // DEBUG:
            cout << "Unknown action " << action1 << ", " << action2 << endl;
            continue;
        }








        // Return blocks above a (for 'move')
        if (action1 == "move") {

            // 
            // while (from.back() != a) {
            //     int top = from.back();
            //     from.pop_back();
            //     v[top]->push_back(top);
            //     place[top] = top;
            // }
        }

        // Return blocks above b (for 'onto')
        if (action2 == "onto") {
            while (to.back() != b) {
                int top = to.back();
                to.pop_back();
                v[top]->push_back(top);
                place[top] = top;
            }
        }

        if (action1 == "move") {
            // Move a only
            from.pop_back();
            to.push_back(a);
            place[a] = place[b];
        } else if (action1 == "pile") {
            // Move whole pile starting at a
            auto it = find(from.begin(), from.end(), a);
            vector<int> to_move(it, from.end());
            from.erase(it, from.end());
            for (int block : to_move) {
                to.push_back(block);
                place[block] = place[b];
            }
        }

        // 🆕 Debug print entire piles after each operation
        printAll(v, n);
    }

    // Clean up
    for (int i = 0; i < n; ++i) {
        delete v[i];
    }
}