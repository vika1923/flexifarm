#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool heatingOn = false;
bool mistOn = false;

double tomatoKgToday = 0.0;
double cucumberKgToday = 0.0;
double pumpkinKgToday = 0.0;

double randDouble(double min, double max) {
    // The RAND_MAX macro in C++ is an integer constant expression that represents the maximum value that can be returned by the std::rand() function. 
    return min + (max - min) * (rand() / (RAND_MAX + 1.0)); 
    // Adding 1.0 to RAND_MAX to ensure the result is less than max
    // rand() / (RAND_MAX + 1.0) is in [0, 1)
}

int randInt(int min, int max) {
    return min + rand() % (max - min + 1);
    // min + rand % range gives [min, max]
}

bool isRipe(const string& crop, const string& color) { // string& crop - reference to cell with crop
    if (crop == "tomato") {
        return (color == "red" || color == "deep red");
    } else if (crop == "cucumber") {
        return (color == "green" || color == "dark green");
    } else if (crop == "pumpkin") {
        return (color == "orange" || color == "deep orange");
    }
    return false;
}

string randomColorForCrop(const string& crop) {
    // includes both ripe and not-ripe colors
    if (crop == "tomato") {
        int x = randInt(1, 4);
        if (x == 1) return "green";
        if (x == 2) return "yellow";
        if (x == 3) return "red";
        return "deep red";
    } else if (crop == "cucumber") {
        int x = randInt(1, 4);
        if (x == 1) return "light green";
        if (x == 2) return "green";
        if (x == 3) return "dark green";
        return "yellow";
    } else if (crop == "pumpkin") {
        int x = randInt(1, 4);
        if (x == 1) return "green";
        if (x == 2) return "pale orange";
        if (x == 3) return "orange";
        return "deep orange";
    }
    return "unknown";
}

void checkEnvironmentAuto() {
    double tempC = randDouble(14.0, 28.0);
    double airHumidity = randDouble(30.0, 70.0);
    double rootHumidity = randDouble(40.0, 80.0);
    double nutrientPPM = randDouble(500.0, 1100.0);

    // Heating
    if (tempC < 18.0) heatingOn = true;
    else heatingOn = false;

    // Mist/Watering
    if (rootHumidity < 55.0 || airHumidity < 45.0) {
        mistOn = true;
    } else {
        mistOn = false;
    }

    // optional log (you can remove prints if leader hates extra output)
    cout << "\n[Environment] Temp=" << tempC
         << "C AirHum=" << airHumidity
         << "% RootHum=" << rootHumidity
         << "% PPM=" << nutrientPPM << "\n";
}

bool harvestAuto(const string& crop) {
    string color = randomColorForCrop(crop);

    // random kg ranges per crop 
    double kg = 0.0;
    if (crop == "tomato") kg = randDouble(0.2, 2.0);
    else if (crop == "cucumber") kg = randDouble(0.2, 1.5);
    else if (crop == "pumpkin") kg = randDouble(0.8, 4.0);

    cout << "\nCrop: " << crop << " | Color: " << color << "\n";

    if (isRipe(crop, color)) {
        cout << "Ripe -> Harvesting...\n";
        cout << "Weight: " << kg << " kg\n";

        if (crop == "tomato") tomatoKgToday += kg;
        else if (crop == "cucumber") cucumberKgToday += kg;
        else if (crop == "pumpkin") pumpkinKgToday += kg;

        return true;
    } else {
        cout << "Not ripe -> Skipping.\n";
        return false;
    }
}

double getTomatoKgToday() {
    checkEnvironmentAuto();
    harvestAuto("tomato");
    cout << "\n--- FlexiFarm Status (Tomato) ---\n";
    cout << "Heating: " << (heatingOn ? "ON" : "OFF") << "\n"; 
    /*
    (heatingOn ? "ON" : "OFF")

    is same as

    if (heatingOn){
        cout << "ON";
    } else{
        cout << "OFF"; 
    }
    */
    cout << "Mist: " << (mistOn ? "ON" : "OFF") << "\n";
    cout << "Tomato harvested today: " << tomatoKgToday << " kg\n";
    cout << "--------------------------------\n";

    return tomatoKgToday;
}

double getCucumberKgToday() {
    checkEnvironmentAuto();
    harvestAuto("cucumber");
    cout << "\n--- FlexiFarm Status (Cucumber) ---\n";
    cout << "Heating: " << (heatingOn ? "ON" : "OFF") << "\n";
    cout << "Mist: " << (mistOn ? "ON" : "OFF") << "\n";
    cout << "Cucumber harvested today: " << cucumberKgToday << " kg\n";
    cout << "----------------------------------\n";

    return cucumberKgToday;
}

double getPumpkinKgToday() {
    checkEnvironmentAuto();
    harvestAuto("pumpkin");
    cout << "\n--- FlexiFarm Status (Pumpkin) ---\n";
    cout << "Heating: " << (heatingOn ? "ON" : "OFF") << "\n";
    cout << "Mist: " << (mistOn ? "ON" : "OFF") << "\n";
    cout << "Pumpkin harvested today: " << pumpkinKgToday << " kg\n";
    cout << "---------------------------------\n";

    return pumpkinKgToday;
}

