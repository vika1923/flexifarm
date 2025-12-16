// Include libraries for random numbers and time
#include <cstdlib>   // For rand() function (random numbers)
#include <ctime>     // For time() function (random seed)
#include <cmath>     // For mathematical functions
#include <iostream>
#include <vector>

using namespace std;

class Hen {
public:
    bool laidEgg;
    bool fertilized;

    Hen() : laidEgg(false), fertilized(false) {}

    void layEgg() {
        laidEgg = (rand() % 2 == 0);  // 50% chance to lay egg
        if (laidEgg) {
            fertilized = (rand() % 2 == 0);  // 50% chance fertilized
        }
    }
};

class Incubator {
public:
    int totalEggsReceived;
    int eggsStage1;  // day 1-10
    int eggsStage2;  // day 10-20
    int eggsStage3;  // day 20-30
    int hatchedEggs;
    int deadEggs;

    Incubator() : totalEggsReceived(0), eggsStage1(0), eggsStage2(0), eggsStage3(0), hatchedEggs(0), deadEggs(0) {}

    void addEggs(int count) {
        totalEggsReceived += count;
        eggsStage1 += count;
    }

    int simulate() {
        // Stage 3 eggs either hatch or die
        for (int i = 0; i < eggsStage3; i++) {
            if (rand() % 2 == 0) {
                hatchedEggs++;
            } else {
                deadEggs++;
            }
        }
        eggsStage3 = 0;

        // Stage 2 eggs move to stage 3 or die
        for (int i = 0; i < eggsStage2; i++) {
            if (rand() % 10 > 1) {  // 80% survive
                eggsStage3++;
            } else {
                deadEggs++;
            }
        }
        eggsStage2 = 0;

        // Stage 1 eggs move to stage 2 or die
        for (int i = 0; i < eggsStage1; i++) {
            if (rand() % 10 > 1) {  // 80% survive
                eggsStage2++;
            } else {
                deadEggs++;
            }
        }
        eggsStage1 = 0;

        cout << "=== Incubator Status ===" << endl;
        cout << "Total eggs received: " << totalEggsReceived << endl;
        cout << "Eggs in stage 1 (day 1-10): " << eggsStage1 << endl;
        cout << "Eggs in stage 2 (day 10-20): " << eggsStage2 << endl;
        cout << "Eggs in stage 3 (day 20-30): " << eggsStage3 << endl;
        cout << "Hatched eggs: " << hatchedEggs << endl;
        cout << "Dead eggs: " << deadEggs << endl;

        return hatchedEggs;
    }
};

class Selector {
public:
    // Pointer to Incubator; the '*' means "pointer to" (i.e., Incubator* is a pointer to an Incubator object)
    Incubator* incubator;

    Selector(Incubator* inc) : incubator(inc) {}

    int checkHens(vector<Hen>& hens) {
        int unfertilized = 0;
        int fertilized = 0;

        for (int i = 0; i < hens.size(); i++) {
            if (hens[i].laidEgg) {
                // Randomly check if fertilized
                bool checkResult = (rand() % 2 == 0) ? hens[i].fertilized : !hens[i].fertilized;
                if (checkResult) {
                    fertilized++;
                } else {
                    unfertilized++;
                }
            }
        }

        incubator->addEggs(fertilized);
        return unfertilized;
    }
};

// Global instances
vector<Hen> hens(5);  // 5 hens
Incubator incubator;
Selector selector(&incubator);

int getNotFertilizedEggs() {
    // Make all hens lay eggs
    for (int i = 0; i < hens.size(); i++) {
        hens[i].layEgg();
    }
    // Check hens and return unfertilized count
    return selector.checkHens(hens);
}

int getHatchedChicks() {
    return incubator.simulate();
}
