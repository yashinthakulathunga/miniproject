#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

//hello yashinthayou can always doing anything. try again dont fail.
//I'm Praveen
// ---------------- Base Abstract Class (Abstraction) ----------------

class Entity {
public:
    virtual void display(ofstream &out) const = 0; // Pure virtual function
    virtual ~Entity() {}
};

// ---------------- School Class ----------------
class School : public Entity {
private:
    string name;
    int days;
    int children;
    float consumedRice;
    float remainingRice;

public:
    School(string n, int d, int c) : name(n), days(d), children(c) {
        consumedRice = (75.0 * days * children) / 1000.0;
        float rounded = ceil(consumedRice / 10.0) * 10.0;
        remainingRice = rounded - consumedRice;
    }

    float getRemainingRice() const { return remainingRice; }
    float getConsumedRice() const { return consumedRice; }

    void display(ofstream &out) const override {
        out << "School name: " << name << "\n";
        out << "Number of days: " << days << "\n";
        out << "Number of children: " << children << "\n";
        out << "Rice consumed: " << consumedRice << " KG\n";
        out << "Remaining rice: " << remainingRice << " KG\n\n";
    }
};

// ---------------- Product Base Class ----------------
class Product : public Entity {
protected:
    string name;
    float quantity;
    float kernel;
    float packets;

public:
    Product(string n) : name(n), quantity(0), kernel(0), packets(0) {}
    virtual void process(float flour) = 0; // Abstract method (Abstraction)

    float getPackets() const { return packets; }

    void display(ofstream &out) const override {
        out << "Product: " << name << "\n";
        out << "Quantity: " << quantity << " KG\n";
        out << "Weight after adding kernel: " << kernel << " grams\n";
        out << "100g packets: " << packets << "\n\n";
    }
};

// ---------------- Derived Product Classes (Inheritance + Polymorphism) ----------------
class RiceFlour : public Product {
public:
    RiceFlour() : Product("Rice Flour") {}
    void process(float flour) override {
        quantity = flour * (2.0 / 3.0);
        kernel = quantity * 1000 * 1.2; // +20%
        packets = trunc(kernel / 100);
    }
};

class IdiappaPiti : public Product {
public:
    IdiappaPiti() : Product("IDIAPPA PITI") {}
    void process(float flour) override {
        quantity = flour * (1.0 / 3.0);
        kernel = quantity * 1000 * 1.3; // +30%
        packets = trunc(kernel / 100);
    }
};

class ThosePiti : public Product {
public:
    ThosePiti() : Product("THOSE PITI") {}
    void process(float flour) override {
        quantity = flour * (1.0 / 3.0);
        kernel = quantity * 1000 * 1.4; // +40%
        packets = trunc(kernel / 100);
    }
};

// ---------------- Store Class ----------------
class Store : public Entity {
private:
    string storeName;
    int soldRiceFlour, soldIdiappa, soldThose;
    float income;

public:
    Store(string name, int rf, int ip, int tp)
        : storeName(name), soldRiceFlour(rf), soldIdiappa(ip), soldThose(tp), income(0) {}

    void calculateIncome(float p1, float p2, float p3) {
        income = p1 * soldRiceFlour + p2 * soldIdiappa + p3 * soldThose;
    }

    void display(ofstream &out) const override {
        out << "Store Name: " << storeName << "\n";
        out << "Income: " << income << "\n\n";
    }
};

// ---------------- Main Function ----------------
int main() {
    // ---------------- Project Introduction ----------------
    cout << "\n========================================================================\n";
    cout << "        Rice   Fortification & Distribution   Management System\n";
    cout << "========================================================================\n\n";

    ofstream outputFile("yash.txt");
    if (!outputFile) {
        cout << "Error opening file!\n";
        return 1;
    }

    outputFile << "\tRice Fortifications Project System\n\n";

    int totalSchools;
    cout << "Enter total count of schools: ";
    cin >> totalSchools;

    cout << "\n\n------------- Collecting Schools' Details --------------\n";

    vector<School> schools;
    float totalRemaining = 0;

    for (int i = 0; i < totalSchools; i++) {
        string sName;
        int days, children;

        cout << "\n--- Enter details for SCHOOL " << i + 1 << " ---\n";
        cout << "Enter school name: ";
        cin >> sName;
        cout << "Enter number of days: ";
        cin >> days;
        cout << "Enter number of children: ";
        cin >> children;

        School s(sName, days, children);
        schools.push_back(s);
        totalRemaining += s.getRemainingRice();
        s.display(outputFile);
    }

    outputFile << "Total remaining rice: " << totalRemaining << " KG\n\n";

    // ---------------- Products ----------------
    float flour = trunc(totalRemaining);
    RiceFlour riceFlour;
    IdiappaPiti idiappa;
    ThosePiti those;

    riceFlour.process(flour);
    idiappa.process(flour);
    those.process(flour);

    riceFlour.display(outputFile);
    idiappa.display(outputFile);
    those.display(outputFile);

    // ---------------- Store Details ----------------
    cout << "\n\n------------- Collecting Store's Details --------------\n";
    string storeName;
    int s1, s2, s3;

    cout << "Enter store name: ";
    cin >> storeName;
    cout << "Enter sold Rice Flour packets: ";
    cin >> s1;
    cout << "Enter sold Idiappa Piti packets: ";
    cin >> s2;
    cout << "Enter sold Those Piti packets: ";
    cin >> s3;

    Store st(storeName, s1, s2, s3);

    float price1, price2, price3;
    cout << "\nEnter price per 100g RiceFlour: ";
    cin >> price1;
    cout << "Enter price per 100g Idiappa Piti: ";
    cin >> price2;
    cout << "Enter price per 100g Those Piti: ";
    cin >> price3;

    st.calculateIncome(price1, price2, price3);
    st.display(outputFile);

    outputFile.close();
    cout << "\n✅ Results written to `yash.txt` successfully!\n";
    return 0;
}


