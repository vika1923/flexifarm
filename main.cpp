#include <iostream>
using namespace std;

string printTime(int hours) {
    int days = hours / 24;
    int remaining_hours = hours % 24;
    return "DAY " + to_string(days) + " : HOUR " + to_string(remaining_hours);
}

int main(){

    // variables
    int time = 0;
    
    int balance = 0;
    int eggs = 0;
    int chickens = 0;
    float tomatoes = 0;
    float cucumbers = 0;
    float pumpkin = 0;
    float milk = 0;

    //constants
    const int EGG_PRICE = 12;
    const int CHICKEN_PRICE = 100;
    const float TOMATO_PRICE = 11;
    const float CUCUMBER_PRICE = 10;
    const float PUMPKIN_PRICE = 9;
    const float MILK_PRICE = 8;


    while(true){
        cout << "<<< =========================== " << printTime(time) << " =========================== >>>" << endl;
        char command;
        cout << "<-> to proceed | <w> to see weardrobe | <s> to sell products | <q> to quit" << endl;
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
            if(product == 1){
                cout << "How many eggs do you want to sell? ";
                int eggs_to_sell;
                cin >> eggs_to_sell;
                if(eggs_to_sell <= eggs){
                    balance += eggs_to_sell * EGG_PRICE;
                    eggs -= eggs_to_sell;
                } else {
                    cout << "Not enough eggs! You have " << eggs << " eggs." << endl;
                }
            }
            else if(product == 2){
                cout << "How many chickens do you want to sell? ";
                int chickens_to_sell;
                cin >> chickens_to_sell;
                if(chickens_to_sell <= chickens){
                    balance += chickens_to_sell * CHICKEN_PRICE;
                    chickens -= chickens_to_sell;
                } else {
                    cout << "Not enough chickens! You have " << chickens << " chickens." << endl;
                }
            }
            else if(product == 3){
                cout << "How much tomatoes do you want to sell? ";
                float tomatoes_to_sell;
                cin >> tomatoes_to_sell;
                if(tomatoes_to_sell <= tomatoes){
                    balance += tomatoes_to_sell * TOMATO_PRICE;
                    tomatoes -= tomatoes_to_sell;
                } else {
                    cout << "Not enough tomatoes! You have " << tomatoes << " kg og tomatoes." << endl;
                }
            }
            else if(product == 4){
                cout << "How much cucumbers do you want to sell? ";
                float cucumbers_to_sell;
                cin >> cucumbers_to_sell;
                if(cucumbers_to_sell <= cucumbers){
                    balance += cucumbers_to_sell * CUCUMBER_PRICE;
                    cucumbers -= cucumbers_to_sell;
                } else {
                    cout << "Not enough cucumbers! You have " << cucumbers << " kg of cucumbers." << endl;
                }
            }
            else if(product == 5){
                cout << "How much pumpkin do you want to sell? ";
                float pumpkin_to_sell;
                cin >> pumpkin_to_sell;
                if(pumpkin_to_sell <= pumpkin){
                    balance += pumpkin_to_sell * PUMPKIN_PRICE;
                    pumpkin -= pumpkin_to_sell;
                } else {
                    cout << "Not enough pumpkin! You have " << pumpkin << " kg of pumpkin." << endl;
                }
            }
            else if(product == 6){
                cout << "How much milk do you want to sell? ";
                float milk_to_sell;
                cin >> milk_to_sell;
                if(milk_to_sell <= milk){
                    balance += milk_to_sell * MILK_PRICE;
                    milk -= milk_to_sell;
                } else {
                    cout << "Not enough milk! You have " << milk << " l of milk." << endl;
                }
            }else if(product == 'q'){
                break;
            }
            else{
                cout << "Invalid product" << endl;
            }
            
        } else if(command == 'q'){
            cout << "Quit" << endl;
            break;
        }
        time += 1;
    }
    return 0;
}
