#include <EEPROM.h>

struct BlockDevice {

    template<typename T>
    vurtual T read(size_t address, size_t size) = 0;

};

class EEPROM : public BlockDevice {

  public:

    template<typename T>
    T read(size_t address)
    {
        T value;

        EEPROM.get(address, value);
    }

};

template<typename T>
class Store {
  
  public:

    template<typename TData>
    TData read(size_t address)
    {
        return _driver.read(address);
    }

  private:

    T _driver;

};

void test()
{
    Storage<EEPROM> storage;
}
