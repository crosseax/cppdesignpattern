#include <iostream>
#include <vector>

// The idea about Interface Segregation Principle
// is basically not to create an interface that is too large

struct Document;

struct IMachine {
    virtual void print(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;
};

// MFP = Multi Function Printer
struct MFP : IMachine {
    // Ok, because it's multi functional
    void print(Document& doc) override;
    void scan(Document& doc) override;
    void fax(Document& doc) override;
};

// The problem comes when you trynna implement just a printer
// or just a scan or fax
struct Scanner : IMachine {
    void print(Document& doc) override {
        // but what to put here?
    }
    void scan(Document& doc) override {
        // ok to do here
    }
    void fax(Document& doc) override {
        // or here?
        // if not put anything here, or just throw exception
        // the code is still causing confusion
    }
};

int main (void)
{



    return 0;
}