#include <iostream>

using namespace std; 

class GasTank {
    private:
        int tankSize = 20;
        int tankFuel = 0;
        bool isLow = false; 

    public:
        //initiates tank with 0 litres
        GasTank() {
            tankSize = 20; 
            tankFuel = 0;
            isLow = true;
        }
        //initiates tank with input# litres
        GasTank(int input) {
            tankSize = input;
            tankFuel = 0;
            isLow = true; 
        }


        //fill sets tankFuel to equal tankSize
        int fill(){
            int temp;
            if ((tankSize - tankFuel) > 0){
                isLow = false;
                temp = tankSize - tankFuel; 
                tankFuel = tankSize;
            }
            else if (tankSize - tankFuel == 0) {
                temp = 0; //tank has not been filled but this is okay
            }
            else {
                cout << "error: negative amounts not possible!" << endl;  //refuse to fill negative amount; no siphoning
                temp = 0;
            }
            return temp;
        }

        //overload of fill to fill a partial tank
        int fill(int input) {
            if(tankSize < (tankFuel + input)) {
                tankFuel = tankSize;
                if (tankFuel * 4 > tankSize){
                    isLow = false;
                    return input;
                }
            }
            else {
                tankFuel = tankFuel + input;
                return tankSize - tankFuel;
            }
        }

        //returns remaining tankFuel of object
        int left() {
            return tankFuel;
        }

        //decrements an amount from the tank, after checking for non-usable values
        void useFuel(int input) {
            if(input <= 0){
                cout << "Error: used input less than zero" << endl;
            }
            else {
				tankFuel = tankFuel - input;
            }
        }

        //returns whether the tank is low
        bool getLow() {
            isLow = (tankFuel * 4 < tankSize) ? true : false;
            return isLow;
        }
};


int main() {

    GasTank tank1;
    GasTank tank2(5);

    cout << "Gallons filled tank 1 -> " << tank1.fill() << endl;
    cout << "Gallons filled tank 2 -> " << tank2.fill() << endl;

    tank1.useFuel(10);

    if (tank1.getLow())
    {
        cout << "Low fuel light" << endl;
        cout << "gallons left ->" << tank1.left() << endl;
    }
    else
        cout << "fuel OK" << endl;

    tank1.useFuel(6);

    if (tank1.getLow())
    {
        cout << "Low fuel light" << endl;
        cout << "gallons left ->" << tank1.left() << endl;
    }
    else
        cout << "fuel OK";
        cout << "Gallons filled tank 1 -> " << tank1.fill() << endl;
        cout << "Gallons filled tank 2 -> " << tank2.fill() << endl;
    cin.ignore();
    return 0;
}
