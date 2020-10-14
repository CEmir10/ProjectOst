#include <iostream>
using namespace std;

class shape{
public:
virtual void draw()
{
        cout<<"Which shape"<<endl;
    }
    };
    
class line:public shape{
public:
    void draw(){
        cout<<"line shape"<<endl;
              }  
    };
    
class circle: public shape{
public:
    void draw(){
        cout<<"circle shape"<<endl;
    }
};
int main()
    {
        line l;
        circle c;
        
        shape *ptr=&l;
        ptr->draw();
        
        ptr=&c;
        ptr->draw();
        
        return 0;
    
    }
