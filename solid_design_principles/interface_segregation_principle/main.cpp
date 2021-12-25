#include <iostream>
#include <vector>

// The idea about Interface Segregation Principle
// is basically not to create an interface that is too large

struct Document;

// struct IMachine {
//     virtual void print(Document& doc) = 0;
//     virtual void scan(Document& doc) = 0;
//     virtual void fax(Document& doc) = 0;
// };

// // MFP = Multi Function Printer
// struct MFP : IMachine {
//     // Ok, because it's multi functional
//     void print(Document& doc) override;
//     void scan(Document& doc) override;
//     void fax(Document& doc) override;
// };

// // The problem comes when you trynna implement just a printer
// // or just a scan or fax
// struct Scanner : IMachine {
//     void print(Document& doc) override {
//         // but what to put here?
//     }
//     void scan(Document& doc) override {
//         // ok to do here
//     }
//     void fax(Document& doc) override {
//         // or here?
//         // if not put anything here, or just throw exception
//         // the code is still causing confusion
//     }
// };


// That's why we segregate the interfaces like below

struct IPrinter {
    virtual void print(Document& doc) = 0;
};

struct IScanner {
    virtual void scan(Document& doc) = 0;
};

struct IFax {
    virtual void fax(Document& doc) = 0;
};

// Now if you need a printer
struct Printer : IPrinter {
    void print(Document& doc) override {

    }
};

struct Scanner : IScanner {
    void scan(Document& doc) override {

    }
};

// If you need a multi functional machine
struct IMachine : IPrinter, IScanner {};
// no need for body above because you can keep them abstract

// then, you can build a decorator(will discuss later)
struct Machine : IMachine {
    IPrinter& printer;
    IScanner& scanner;

    // then you get a constructor
    Machine(IPrinter& printer, IScanner& scanner) 
        : printer {printer}, scanner {scanner} {}
    
    // then you override and implement the functions
    void print(Document& doc) override {
        printer.print(doc);
    }

    void scan(Document& doc) override {
        scanner.scan(doc);
    }
};

// If you dont want the coder that come next to implement too much, 
// you can just break up the above into separate interfaces
// or at least make them smaller, so it's all coherent

int main (void)
{



    return 0;
}