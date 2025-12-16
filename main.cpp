#include "main.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class TimeKeeper {
private:
    int hours;

public:
    TimeKeeper(int initial_hours = 0) : hours(initial_hours) {
    }

    void display() {
        int days = hours / 24;
        int remaining_hours = hours % 24;
        cout << days << ":" << remaining_hours;
    }

    string getDisplayString() {
        int days = hours / 24;
        int remaining_hours = hours % 24;
        return "DAY " + to_string(days) + " : HOUR " + to_string(remaining_hours);
    }

    void increment(int hours_to_add = 1) {
        hours += hours_to_add;
    }

    int getHours() const {
        return hours;
    }

};

int main(){

    // variables
    TimeKeeper timekeeper;

    int balance = 0;
    int eggs = 0;
    int chickens = 0;
    int tomatoes = 0;
    int cucumbers = 0;
    int pumpkin = 0;
    int milk = 0;

    //constants
    const int EGG_PRICE = 12;
    const int CHICKEN_PRICE = 100;
    const float TOMATO_PRICE = 11;
    const float CUCUMBER_PRICE = 10;
    const float PUMPKIN_PRICE = 9;
    const float MILK_PRICE = 8;

    const int MILK_PROCESSING_NEEDED =2;
    const int VEGS_GATHERING_NEEDED = 5;
    const int EGGS_PROCESSING_NEEDED = 3;

    bool looped_already = false;

    while(true){
        cout << "<<< =========================== " << timekeeper.getDisplayString() << " =========================== >>>" << endl;
        if(!looped_already){
            looped_already = true;

            if(timekeeper.getHours() % VEGS_GATHERING_NEEDED == 0) {
                cout << "=== VEGS GATHERING ===" << endl;
                tomatoes += getTomatoKgToday();
                cucumbers += getCucumberKgToday();
                pumpkin += getPumpkinKgToday();
            }

            if(timekeeper.getHours() % MILK_PROCESSING_NEEDED == 0){
                cout << "\n\n=== MILK PROCESSING ===" << endl;
                int t = process_milk(timekeeper.getHours());
                cout << "Milk processed: " << t << endl;
                milk += t;
            }

            if(timekeeper.getHours() % EGGS_PROCESSING_NEEDED == 0){
                cout << "\n\n=== EGGS PROCESSING ===" << endl;
                int t1 = getNotFertilizedEggs();
                int t2 = getHatchedChicks();
                cout << "Not fertilized eggs: " << t1 << endl;
                cout << "Hatched chicks: " << t2 << endl;
                eggs += t1;
                chickens += t2;
            }
        }

        char command;
        cout << "<-> to proceed | <w> to see warehouse | <s> to sell products | <q> to quit" << endl;
        cin >> command;
        cin.get();

        if(command == 'w'){
            cout << "Balance: " << balance << endl;
            cout << "Eggs: " << eggs << endl;
            cout << "Chickens: " << chickens << endl;
            cout << "Tomatoes: " << tomatoes << endl;
            cout << "Cucumbers: " << cucumbers << endl;
            cout << "Pumpkin: " << pumpkin << endl;
            cout << "Milk: " << milk << endl;
        } else if(command == 's'){

            cout << "1. Eggs" << endl;
            cout << "2. Chickens" << endl;
            cout << "3. Tomatoes" << endl;
            cout << "4. Cucumbers" << endl;
            cout << "5. Pumpkin" << endl;
            cout << "6. Milk" << endl;
            cout << "Enter the product you want to sell (1 - 6). <q> to quit" << endl;
            int product;
            cin >> product;

            float amount_to_sell;
            bool transaction_successful = false;
            string product_name;
            float price_per_unit = 0;
            float total_value = 0;

            if(product == 1){
                cout << "How many eggs do you want to sell? ";
                cin >> amount_to_sell;
                if(amount_to_sell <= eggs){
                    price_per_unit = EGG_PRICE;
                    total_value = amount_to_sell * price_per_unit;
                    balance += total_value;
                    eggs -= amount_to_sell;
                    product_name = "Eggs";
                    transaction_successful = true;
                } else {
                    cout << "Not enough eggs! You have " << eggs << " eggs." << endl;
                }
            }else if(product == 2)  {
                cout << "How many chickens do you want to sell? ";
                cin >> amount_to_sell;
                if(amount_to_sell <= chickens){
                    price_per_unit = CHICKEN_PRICE;
                    total_value = amount_to_sell * price_per_unit;
                    balance += total_value;
                    chickens -= amount_to_sell;
                    product_name = "Chickens";
                    transaction_successful = true;
                } else {
                    cout << "Not enough chickens! You have " << chickens << " chickens." << endl;
                }
            }else if(product == 3)  {
                cout << "How much tomatoes do you want to sell? ";
                cin >> amount_to_sell;
                if(amount_to_sell <= tomatoes){
                    price_per_unit = TOMATO_PRICE;
                    total_value = amount_to_sell * price_per_unit;
                    balance += total_value;
                    tomatoes -= amount_to_sell;
                    product_name = "Tomatoes";
                    transaction_successful = true;
                } else {
                    cout << "Not enough tomatoes! You have " << tomatoes << " kg og tomatoes." << endl;
                }
            }else if(product == 4)  {
                cout << "How much cucumbers do you want to sell? ";
                cin >> amount_to_sell;
                if(amount_to_sell <= cucumbers){
                    price_per_unit = CUCUMBER_PRICE;
                    total_value = amount_to_sell * price_per_unit;
                    balance += total_value;
                    cucumbers -= amount_to_sell;
                    product_name = "Cucumbers";
                    transaction_successful = true;
                } else {
                    cout << "Not enough cucumbers! You have " << cucumbers << " kg of cucumbers." << endl;
                }
            }else if(product == 5)  {
                cout << "How much pumpkin do you want to sell? ";
                cin >> amount_to_sell;
                if(amount_to_sell <= pumpkin){
                    price_per_unit = PUMPKIN_PRICE;
                    total_value = amount_to_sell * price_per_unit;
                    balance += total_value;
                    pumpkin -= amount_to_sell;
                    product_name = "Pumpkin";
                    transaction_successful = true;
                } else {
                    cout << "Not enough pumpkin! You have " << pumpkin << " kg of pumpkin." << endl;
                }
            }else if(product == 6)  {
                cout << "How much milk do you want to sell? ";
                cin >> amount_to_sell;
                if(amount_to_sell <= milk){
                    price_per_unit = MILK_PRICE;
                    total_value = amount_to_sell * price_per_unit;
                    balance += total_value;
                    milk -= amount_to_sell;
                    product_name = "Milk";
                    transaction_successful = true;
                } else {
                    cout << "Not enough milk! You have " << milk << " l of milk." << endl;
                }
            }else if(product == 'q'){
                break;
            }else  {
                cout << "Invalid product" << endl;
            }

            if(transaction_successful){
                ofstream report("transactions_report.txt", ios::app);
                if(report.is_open()){
                    // Write a blank line first for clear separation
                    report << endl;
                    // Write timestamp, then entry, then another newline for consistency
                    report << "[" << timekeeper.getDisplayString() << "]" << endl;
                    report << "Product: " << product_name << endl
                           << "Amount: " << amount_to_sell << endl
                           << "Price per unit: " << price_per_unit << endl
                           << "Profit: " << total_value << endl
                           << "Balance: " << balance << endl;
                    report << endl;
                    report.close();
                }
            }
        } else if(command == '-'){
            looped_already = false;
            timekeeper.increment();
        } else if(command == 'q'){
            cout << "Quit" << endl;
            break;
        }
    }

    return 0;
}
