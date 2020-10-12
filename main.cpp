#include <iostream>
#include <string>

using namespace std;

class Vehicle{
    
public:
    void svirena();
 
    };
    
 void  Vehicle::svirena()
{
    cout<<"Svirena: TUUUT"<<endl;
}
   

class Car : public Vehicle{
public:
    string brand, model;
    int year;
    int hoursepower;
    int speed(int max_speed);
    
    Car(string x, int y, int z){
        
        model=x;
        year=y;
        hoursepower=z;
        }
    
    };

class Truck : public Vehicle {
public: 
    string model;
    int speed;
    string color;
    Truck(string x, int y, string z)
    {
     model=x;
     speed=y;
     color=z;
    }   
    
   }; 
    
int Car::speed(int max_speed) // function
{
    return max_speed;
}


int main(int argc, char **argv) {

    Car Audi("A6",2012,220);
    Truck Mercedes("E",120,"red");
  
    cout<<"Audi model is " <<Audi.model<<", year is "<<Audi.year<<", hoursepower: "<<Audi.hoursepower<<endl;
    cout<<"Audi maximum speed is "<< Audi.speed(220)<<endl;
    Audi.svirena();
    cout<<"Mercedes model is " <<Mercedes.model<<", speed is "<<Mercedes.speed<<", and color is: "<<Mercedes.color<<endl;

    Mercedes.svirena();
    
    
    
    return 0;
}
