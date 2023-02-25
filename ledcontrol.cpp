#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>

using namespace std;


void newTrigger (string LED_PATH, int trigger_option){
    LED_PATH.append("/brightness");
    fstream fs;
    if (trigger_option == 1){
        fs.open(LED_PATH, fstream::out);
        fs << "1";
        fs.close();
    }
    else if (trigger_option == 2){
        fs.open(LED_PATH, fstream::out);
        fs << "0";
        fs.close();
    }
    else {
        cout << "WRONG TRIGGER SELECTION!!!" << endl;
    }
}

int main (int argc, char* argv[]){
    string LED_PATH  = "/sys/class/leds/";
    //string LED_PATH = "/sys/class/leds/";
    //define a variable for flashing option
    int flash_number;
    int led_selector;
    // this condition checks that the user call this program by correct arg or not
    if (argc!=2){
        cout << "For using this program, you should call it like below" << endl;
        cout << "(sudo ./ledcontrol on) for turning on the led " << endl;
        cout << "(sudo ./ledcontrol off) for turning off the led" << endl;
        cout << "(sudo ./ledcontrol flash) for flashing the led" << endl;
        cout << "(sudo ./ledcontrol status) for showing current LED trigger details" <<endl;
    }

    //create command string from calling argument
    string command (argv[1]);
    //create a file stream for changing values in LED_PATH
    fstream fs;

    cout << "Welcome to LED control program" << endl;
    cout << "Enter number of LED you want to control: " << endl;
    cout << "1.capslock LED (FOR ALL LAPTOPS)" << endl;
    cout << "2.HDD LED (JUST FOR HP LAPTOPS)" << endl;
    cin >> led_selector;

    switch (led_selector){
        case 1 :
            LED_PATH.append("input3::capslock");
            break;
        case 2 :
            LED_PATH.append("hp::hddprotect");
            break;
        default:
            cout << "WRONG LED!!!" << endl;
    }
     cout << "The LED path that you want to control it is " << LED_PATH << endl;



    if(command == "on"){
       cout << "You are turning ON the LED!!!" << endl;
    //call newTrigger function with LED_PATH and 1 for turning OFF
        newTrigger(LED_PATH, 1);
    }

    else if (command == "off"){
        cout << "You are turning OFF the LED!!!" << endl;
    //call new trigger function with LED_PATH and 2 for turning OFF
        newTrigger(LED_PATH , 2);
    }

    else if (command == "flash"){
        cout << "You are flashing the LED" << endl;
        cout << "How many times do you want to flash the LED :";
        cin >> flash_number;
        //turn off the led first
        newTrigger(LED_PATH, 2);
        //flashing the led by changing brightness value
        //set a value for turning the LED ON
        while (flash_number != 0){
            //LED ON
            newTrigger(LED_PATH, 1);
            sleep(1);
            //set a value for turning the LED OFF\
            //LED OFF
            newTrigger(LED_PATH, 2);
            flash_number--;
            sleep (1);
        }

    }
    else if (command == "status"){
    cout << "You select to see current trigger details" << endl;
        //display the current trigger details
        //reading from trigger part of LED_PATH
        fs.open(LED_PATH.append("/trigger"), fstream::in);
        //build a string for reading details
        string detail;
        while (getline(fs, detail)) cout << detail << endl;
        fs.close();
    }

    else {
        cout << "You called this program by a WRONG command \n Please try again later" << endl;
    }

    cout << "End of LED CONTROL PROGRAM :) " << endl;
    return 0;



}
