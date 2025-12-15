#include <fstream>
#include <iostream>
using namespace std;

const char UDDER_MAP[3][3] = {
    {'0', '0', '0'},
    {'0', '2', '0'},
    {'0', '0', '0'}
};

class MiniMap {
public:
    char map[3][3];
    MiniMap(ifstream &sensor, int i, int j){
        for(int row = 0; row < 3; row++){
            int curr_row = i + row;
            int location = curr_row*10+j;
            sensor.seekg(location, ios::beg);
            for(int col = 0; col < 3; col++){
                sensor >> map[row][col];
            }
        }
    }

    bool is_udder(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(map[i][j] != UDDER_MAP[i][j]){
                    return false;
                }
            }
        }

        return true;
    }

    void print(){
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                cout << map[i][j];
            }

            cout << endl;
        }
    }

};

void init_map(){
    // initialize the map to test values
    ofstream map = ofstream("dairy.txt");

    // generate a map with at least one udder
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(i % 3 == 0 && j % 3 == 0){
                map << '2';
            } else {
                map << '0';
            }
        }

        map << endl;
    }

    map.close();
}

bool check_milking_cycle(int time){
    if (time % 2 == 0){
        if (time % 7 == 0){
            return false;
        } else if (time % 7 == 1){
            return false;
        } else {
            return true;
        }
    } else {
        if (time % 4 == 1){
            return true;
        } else {
            return false;
        }
    }
}

void report_milking_statistics(int &time, long int& times_milked){
    cout << "*******************" << endl;
    cout << "MILKING STATISTICS" << endl;
    cout << "TIME: " << time << endl;
    cout << "MILK(L): " << times_milked << endl;
    cout << "*******************" << endl;
}

int main(){
    // sensor
    init_map();

    // Statistics

    int time = 0;
    long int times_milked = 0;


    // Milking
    ifstream sensor = ifstream("dairy.txt");
    char sensed;
    // scan 9x9 map with 3x3 mask searching for the udder [000, 010, 000]
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            cout << "Checking " << i << "," << j << endl;
            MiniMap map(sensor, i, j);
            // map.print();
            if(map.is_udder()){
                cout << "UDDER FOUND" << endl;
                if(check_milking_cycle(time)){
                    cout << "MILKING CYCLE IS VALID" << endl;
                    cout << "MILKING COW" << endl;
                    times_milked++;
                    report_milking_statistics(time, times_milked);
                }
            }

            time++;
        }

        cout <<endl;
    }

    return 0;
}
