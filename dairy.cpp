#include <fstream>
#include <iostream>
using namespace std;

const char UDDER_MAP[3][3] = {
    {'0', '0', '0'},
    {'0', '1', '0'},
    {'0', '0', '0'}
};


class ProductionStats {
public:
    int time_period;
    double total_milk;
    double efficiency_rating;
    double revenue_estimate;
};

class FarmAnalytics {
public:
    // Recursive method to calculate growth over cycles
    int calculate_recursive_growth(int cycles, int current_production) {
        if (cycles <= 0) {
            return current_production;
        }

        // Assume 10% growth per cycle
        return calculate_recursive_growth(cycles - 1, current_production * 1.10);
    }

    // Method using pointer to modify object
    void update_stats_via_pointer(ProductionStats* stats, int new_milk) {
        if (stats != nullptr) {
            stats->total_milk += new_milk;
            // Update efficiency based on new total (arbitrary logic for demo)
            stats->efficiency_rating = (stats->total_milk / stats->time_period) * 0.5;
        }
    }

    // Method 1 returning an object
    ProductionStats generate_daily_report(int time, int cows, double milk, double efficiency) {
        ProductionStats stats;
        stats.time_period = time;
        stats.total_milk = milk;
        stats.efficiency_rating = efficiency;
        stats.revenue_estimate = milk * 1.5; // $1.5 per liter
        return stats;
    }

    // Method 2 returning an object
    ProductionStats forecast_yield(int days, double current, double rate, double decay) {
        ProductionStats forecast;
        forecast.time_period = days;

        double projected = current;
        for(int i=0; i<days; i++) {
            projected = projected * (1.0 + rate) - decay;
        }

        forecast.total_milk = projected;
        forecast.efficiency_rating = (projected > current) ? 1.0 : 0.8;
        forecast.revenue_estimate = projected * 1.4; // Future price might be lower
        return forecast;
    }

};

class MiniMap {
public:
    char map[3][3];

    MiniMap(ifstream &sensor, int i, int j){
        for(int row = 0; row < 3; row++){
            int curr_row = i + row;
            int location = curr_row*10+j;
            sensor.seekg(location, ios::beg);
            if (sensor.fail()) {
                cerr << "Error seeking to location " << location << endl;
                return;
            }

            for(int col = 0; col < 3; col++){
                if (sensor.eof()) {
                    cerr << "Error: Reached end of file unexpectedly" << endl;
                    return;
                }

                sensor >> map[row][col];
                if (sensor.fail()) {
                    cerr << "Error reading from file" << endl;
                    return;
                }
            }
        }
    }

    MiniMap(char a1, char a2, char a3, char b1, char b2, char b3, char c1, char c2, char c3){
        map[0][0] = a1;
        map[0][1] = a2;
        map[0][2] = a3;
        map[1][0] = b1;
        map[1][1] = b2;
        map[1][2] = b3;
        map[2][0] = c1;
        map[2][1] = c2;
        map[2][2] = c3;
    }

    void modify_map_if_needed(int i, int j, bool condition, char value){
        if(condition){
            map[i][j] = value;
        } else {
            map[i][j] = '0';
        }
    }

    bool is_udder(){
        int i = 0;
        while(i < 3){
            int j = 0;
            while(j < 3){
                if(map[i][j] != UDDER_MAP[i][j]){
                    return false;
                }

                j++;
            }

            i++;
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

    bool matches_value(
        char a1, char a2, char a3,
        char b1, char b2, char b3,
        char c1, char c2, char c3
        ){
        int a_matches = a1 == b1 && a2 == b2 && a3 == b3;
        int b_matches = b1 == c1 && b2 == c2 && b3 == c3;
        int c_matches = c1 == a1 && c2 == a2 && c3 == a3;
        return a_matches && b_matches && c_matches;
    }

};


class AreaMap {
public:
    char map[9][9];
    AreaMap(){
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                map[i][j] = '0';
            }
        }
    }

    void insert(int i, int j, char value){
        map[i][j] = value;
    }

    void print_and_format_map(int i, int j, int width, int height){
        for(int row = i; row < i + height; row++){
            for(int col = j; col < j + width; col++){
                cout << map[row][col];
            }

            cout << endl;
        }
    }

    int count_udders_in_the_area(){
        int count = 0;
        int i = 0;
        while(i < 7){
            int j = 0;
            while(j < 7){
                MiniMap mini_map(
                    map[i][j], map[i+1][j], map[i+2][j],
                    map[i][j+1], map[i+1][j+1], map[i+2][j+1],
                    map[i][j+2], map[i+1][j+2], map[i+2][j+2]
                    );
                if(mini_map.is_udder()){
                    count++;
                }

                j++;
            }

            i++;
        }

        return count;
    }

};
AreaMap populate_object_manually(){
    AreaMap map;
    cout << "Enter values for the map (0 or 1):" << endl;
    for(int i = 0; i < 9*9; i++){
        char value;
        do {
            cin >> value;
            if(value != '0' && value != '1'){
                cout << "Invalid value" << endl;
            }
        } while(value != '0' && value != '1');
        map.insert(i/9, i%9, value);
    }

    return map;
}

void init_map(int time){
    ofstream map = ofstream("dairy.txt");
    if (!map.good()) {
        cerr << "Error opening dairy.txt for writing" << endl;
        return;
    }

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            // add randomness with time using rand
            //
            if(rand() % 7 == 0){
                map << '1';
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
            return false;
        } else {
            return true;
        }
    }
}

void report_milking_statistics(int &time, int& times_milked){
    cout << "*******************" << endl;
    cout << "MILKING STATISTICS" << endl;
    cout << "TIME: " << time << endl;
    cout << "MILK(L): " << times_milked << endl;
    cout << "*******************" << endl;
}

int times_milked = 0;
int process_milk(int time){
    // sensor
    init_map(time);
    // Milking
    ifstream sensor = ifstream("dairy.txt");
    if (sensor.fail()) {
        cerr << "Error opening dairy.txt for reading" << endl;
    }

    char sensed;
    // scan 9x9 map with 3x3 mask searching for the udder [000, 010, 000]
    for(int i = 0; i < 7; i++){
        for(int j = 0; j < 7; j++){
            // cout << "Checking " << i << "," << j << endl;
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

        // cout <<endl;
    }

    return times_milked;
}

void estimate_expenses(int time){
    FarmAnalytics analytics;

    // Recursive usage
    int projected = analytics.calculate_recursive_growth(3, times_milked);
    cout << "Projected production in 3 cycles: " << projected << endl;

    // Object return usage
    ProductionStats stats = analytics.generate_daily_report(time, 50, times_milked, 0.9);
    cout << "Daily Revenue Estimate: $" << stats.revenue_estimate << endl;

    // Pointer usage
    analytics.update_stats_via_pointer(&stats, 10); // Add 10 liters
    cout << "Updated Efficiency (after pointer mod): " << stats.efficiency_rating << endl;
}
