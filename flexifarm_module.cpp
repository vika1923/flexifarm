
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// -------- internal "shared state" (no class, no struct) --------
static bool heatingOn = false;
static bool mistOn = false;
static bool uvOn = true;

static double tomatoKgToday = 0.0;
static double cucumberKgToday = 0.0;
static double pumpkinKgToday = 0.0;

static double randDouble(double min, double max) {
    return min + (max - min) * (rand() / (RAND_MAX + 1.0));
}

static int randInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

static bool isRipe(const string& crop, const string& color) {
    if (crop == "tomato") {
        return (color == "red" || color == "deep red");
    } else if (crop == "cucumber") {
        return (color == "green" || color == "dark green");
    } else if (crop == "pumpkin") {
        return (color == "orange" || color == "deep orange");
    }
    return false;
}

static string randomColorForCrop(const string& crop) {
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

    uvOn = true;

    // optional log (you can remove prints if leader hates extra output)
    cout << "\n[Environment] Temp=" << tempC
         << "C AirHum=" << airHumidity
         << "% RootHum=" << rootHumidity
         << "% PPM=" << nutrientPPM << "\n";
}

bool harvestAuto(const std::string& crop) {
    string color = randomColorForCrop(crop);

    // random kg ranges per crop 
    double kg = 0.0;
    if (crop == "tomato") kg = randDouble(0.2, 2.0);
    else if (crop == "cucumber") kg = randDouble(0.2, 1.5);
    else if (crop == "pumpkin") kg = randDouble(0.8, 4.0);
    else kg = randDouble(0.1, 1.0);

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
    cout << "Mist: " << (mistOn ? "ON" : "OFF") << "\n";
    cout << "UV: " << (uvOn ? "ON" : "OFF") << "\n";
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
    cout << "UV: " << (uvOn ? "ON" : "OFF") << "\n";
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
    cout << "UV: " << (uvOn ? "ON" : "OFF") << "\n";
    cout << "Pumpkin harvested today: " << pumpkinKgToday << " kg\n";
    cout << "---------------------------------\n";

    return pumpkinKgToday;
}

