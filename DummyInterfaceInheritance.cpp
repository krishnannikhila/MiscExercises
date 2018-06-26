#include <iostream>
#include <string>
using namespace std;

class Interface {
public:
    virtual void onSuccess() = 0;
    virtual void onFailure(const std::string& error) = 0;
};

class DummyInterface: public Interface {
public:
    virtual void dummyOnSuccess() = 0;
    virtual void dummyOnFailure(const std::string& error) = 0;
    void onSuccess() { 
        cout << "onSuccess" << endl; 
        dummyOnSuccess();
        
    }
    
    void onFailure(const std::string& error) {
        cout << "onFailure:" << error << endl;
        dummyOnFailure(error);
    }
};

class InterfaceImpl : public DummyInterface {
public:
    void dummyOnSuccess() {
        cout << "dummyOnSuccess" << endl;
    }
    
    void dummyOnFailure(const std::string& error) {
        cout << "dummyOnFailure:" << error << endl;
    }
};

class UsingInterface {
public:
    UsingInterface(Interface* interface) : m_int(interface) {}
    void callOnSuccess() {
        m_int->onSuccess();
    }
    void callOnFailure(const std::string& error) {
        m_int->onFailure(error);
    }
private:
    Interface* m_int;
};

int main()
{
    DummyInterface* interface = new InterfaceImpl;
    UsingInterface callInterface(interface);
    callInterface.callOnSuccess();
    callInterface.callOnFailure("Aaarh");
    return 0;
}
