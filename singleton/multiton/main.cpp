// a multi-ton is another variation of the singleton 
// that is not directly related to singleton

// it sets up the key value store 
// where you can optionally restrict the number of elements which are actually stored

#include <map>
#include <memory>
#include <iostream>

enum class Importance {
    primary, secondary, tertiary
};

template <typename T, typename Key = std::string>
class Multiton {
public:
    static std::shared_ptr<T> get(const Key& key) {
        // below is a C++17 syntax
        if (const auto it = instances.find(key); it != instances.end()) {
            return it->second;
        }

        auto instance = std::make_shared<T>();
        instances[key] = instance;
        return instance;
    }

protected:
    Multiton() = default;
    virtual ~Multiton() = default;
    // multiton is NOT meant to be instantiated
    // it's meant to be used via a static mechanism
    
private:
    static std::map<Key, std::shared_ptr<T>> instances;
};

// initializing the map
template<typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances;

class Printer {
public:
    Printer() {
        ++Printer::totalInstanceCount;
        std::cout << "A total of " << Printer::totalInstanceCount << " instances created so far\n";
    }
private:
    static int totalInstanceCount;
};
int Printer::totalInstanceCount = 0;

int main(void)
{
    // again, you dont instantiate a multiton
    // instead you just use it
    typedef Multiton<Printer, Importance> mt;

    auto main = mt::get(Importance::primary);
    auto another = mt::get(Importance::secondary);

    // even when doing below
    auto another2 = mt::get(Importance::secondary);
    // the result is still total of 2 instances created only

    return 0;
}