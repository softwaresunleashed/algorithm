#include<iostream>
using namespace std;

class Employee{
    public:
        virtual void raiseSalary()
        {
            /* Common base function that would be replaced with actual function 
            in object's derived class */
        }
};

class Engineer : public Employee {
    public:
    void raiseSalary()
    {
        cout << "Raising Salary of Engineer." << endl;
    }
};

class Manager : public Employee {
    public:
    void raiseSalary()
    {
        cout << "Raising Salary of Manager." << endl;
    }
};

int main()
{
    /* Object of type Employee pointing to Engineer class */
    Employee * objEmp = new Engineer;   
    
    /* object of Employee type, calling raiseSalary() of Engineer - Virtual function*/
    objEmp->raiseSalary();
    
    /* Object is now pointing to type Manager , 
    and calling raiseSalary() of Manager - Virtual function */
    objEmp = new Manager;
    objEmp->raiseSalary();
}

