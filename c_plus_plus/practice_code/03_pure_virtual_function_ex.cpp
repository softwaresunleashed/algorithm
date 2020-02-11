#include <iostream> 
using namespace std; 
  
class Base
{
    private:
        int x;
    public:
        virtual void fun() = 0;     /* Can't create instance of Base class - since it has an abstract  (pure virtual) function */
};

class Derived
{
    private:
        int y;
    public:
        void fun()
        {
            cout << "Derived fun() called..." << endl;
        }
};

int main()
{
    /* Can't create instance of Base class - since it has an abstract  (pure virtual) function */
    //Base objBase;     --> Not valid statement. will generate compiler error. 
    
    Derived objDerived;
    objDerived.fun();       // Valid statement. Derived class has implemented abstract / pure-virtual function

    return 0;
}
