#include "wiwire.hpp"

int main() {
  namespace target = hwlib::target;

  auto tx = target::pin_out(target::pins::d50);
  auto rx = target::pin_in(target::pins::d51);
  hwlib::wait_ms(1000);

  wiwire wire(tx, rx);
  hwlib::cout << "init" << "\n";

  while(true)
  {
    char msg[256] = {};
    char sizeMsg = wire.blockRead(msg);
    hwlib::cout << "sizeMsg: " <<  (int)sizeMsg << '\n';
    for (int i = 0; i < sizeMsg; i++)
    {
      hwlib::cout << msg[i];
    }
    hwlib::cout << "\n";
    
  }
  return 0;
}