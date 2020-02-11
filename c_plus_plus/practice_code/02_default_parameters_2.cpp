#include <iostream> 
using namespace std; 
  
class Base 
{ 
public: 
    virtual void fun ( int x = 20) 
    { 
        cout << "Base::fun(), x = " << x << endl; 
    } 
}; 
  
class Derived : public Base 
{ 
public: 
    virtual void fun ( int x = 10 ) // NOTE THIS CHANGE 
    { 
        cout << "Derived::fun(), x = " << x << endl; 
    } 
}; 
  
  
int main() 
{ 
    Derived d1; 
    Base *bp = &d1; 
    bp->fun(); 	/* Default value would be choosen based on the object type Base / Derived class */
    return 0; 
}  
