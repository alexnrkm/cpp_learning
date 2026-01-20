#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
using namespace std;

void print_2d_array(vector<vector<int>> arr);
int count_neighbors(vector<vector<int>> arr, int x, int y);

int main(){
    int grind_size;
    int num_of_points;
    int rounds;
    cout << "Grind size (5-20): ";
    cin >> grind_size;
    cout << "How many points you want to enter? ";
    cin >> num_of_points;
    cout << "How many rounds do you want to play? ";
    cin >> rounds;

    //creating a dynamic 2dim array for the grind
    vector<vector<int>> grind0(grind_size, vector<int>(grind_size, 0)); // vector<vector<int>> -> a vector of vectors 
    for (int i = 0; i < grind_size; i++){
        for (int j = 0; j < grind_size; j++){
            grind0[i][j] = 0;
        }
    }

    //asking coordinates from a user and assigning "1" to these coordinates
    vector<vector<int>> coordinates(num_of_points, vector<int>(1, 0));
    for (int runs = 0; runs < num_of_points;runs++){
        int user_input_x;
        int user_input_y;

        cout << "Enter x of the point " << runs + 1 << ": ";
        cin >> user_input_x; 
        coordinates[runs][0] = user_input_x;

        cout << "Enter y of the point: " << runs + 1 << ": ";
        cin >> user_input_y; 
        coordinates[runs][1] = user_input_y;

        grind0[user_input_y - 1][user_input_x - 1] = 1;
    }
    system("cls");

    // printing the grind0 with points
    print_2d_array(grind0);

    vector<vector<int>> grind1(grind_size, vector<int>(grind_size, 0));
    grind1 = grind0;
    for (int times = 0; times < rounds; times++){
        for (int row = 0; row < grind_size; row++){
            for(int column = 0; column < grind_size; column++){
                int num_of_neighbors = count_neighbors(grind0, row, column); // count neighbors of each cell {count_neighbors(array, x of the point, y of the point)}
                if (grind0[row][column] > 0){
                    if (num_of_neighbors < 2 || num_of_neighbors > 3){
                        grind1[row][column] = 0; //die condition
                    }
                }
                if (num_of_neighbors == 3){
                    grind1[row][column] = 1; //reproduce condition
                }
            }
        }
        grind0=grind1;
        cout << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system("cls");
        print_2d_array(grind1);
        cout << endl << "Round " << times + 1;
    }
    cout << "\n" << "THE GAME IS OVER";
    return 0;
}

//function for printing a 2d array
void print_2d_array(vector<vector<int>>arr){

    int num_rows = arr.size();
    int num_columns = arr[0].size();

    for (int row = 0; row < num_rows; row++){
        for (int column = 0; column < num_columns; column++){
            if(arr[row][column] == 0){
                cout << ". ";
            } 
            else{
                cout << "# ";
            }
        }
        cout << "\n";
    }
}

//function fot counting neighbors
int count_neighbors(vector<vector<int>>arr, int x, int y){
    int counter = 0;
    int beginning_r = x - 1;
    int last_r = x+1;
    int beginning_c = y - 1;
    int last_c = y+1;

    int grid_size = arr.size();

    if (beginning_r < 0){
                beginning_r = 0;
            }

    if (beginning_c < 0){
        beginning_c = 0;
    }

    if (last_r >= grid_size){
        last_r = grid_size - 1;
    }

    if (last_c >= grid_size){
        last_c = grid_size - 1;
    }
    
    for(int row = beginning_r; row <= last_r; row++){
            for(int column = beginning_c; column <= last_c; column++){
                if (arr[row][column] != 0){
                    counter++;
            }
        }
    }
    return counter - arr[x][y];
    
}