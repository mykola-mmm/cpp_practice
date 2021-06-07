#include <cstdlib>
#include <iostream>

class Account {
public:
    Account() {
        _balance = 0.0;
    }
    Account(double d) {
        _balance = d;
    }
    virtual ~Account() {}
    virtual double GetBalance() {return _balance; }
    virtual void PrintBalance() {std::cerr << "Balance not available for the base type\n"; }
    virtual void PrintBbb() {std::cout << "Base Bbb - " << bbb << std::endl; }
    static int bbb;

private:
    double _balance;
};


class CheckingAccount : public Account {
public:
    CheckingAccount(double d) : Account(d) {}
    void PrintBalance() {std::cout << "CHECK Balance - " << GetBalance() << std::endl; }

};

class SavingAccount : public Account {
public:
    SavingAccount(double d) : Account(d) {}
    void PrintBalance() {std::cout << "SAVE Balance - " << GetBalance() << std::endl; }
    virtual void PrintBbb() {std::cout << "Save Bbb - " << bbb << std::endl; }

};

int Account::bbb = 0;


int main(void) {
    CheckingAccount ch(100);
    SavingAccount sv(10);

    Account *pAc = &ch;
    pAc->PrintBalance();

    pAc = &sv;
    pAc->PrintBalance();

    pAc->PrintBbb();

    return EXIT_SUCCESS;
}