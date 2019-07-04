#include "wiwire.hpp"


int main() {
  namespace target = hwlib::target;

  auto tx = target::pin_out(target::pins::d50);
  auto rx = target::pin_in(target::pins::d51);
  auto button = target::pin_in( target::pins::d40 );
  // auto led = target::pin_out( target::pins::d47 );
  // auto scl = target::pin_oc( target::pins::scl );
  // auto sda = target::pin_oc( target::pins::sda );

  // auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
  // auto display = hwlib::glcd_oled( i2c_bus, 0x3c );
  // display.clear();

  tx.write(0); tx.flush();
  wiwire wire(tx, rx);
  int sizeMsg = 12;
  const char msg[12] = "Hello world";

  while (true) {
    int tmp = wire.send(msg, sizeMsg);
    if(tmp == -1){
      hwlib::cout << "failed to verify message recieved" << "\n";
    }
    else{
      hwlib::cout << "succesfully send in " << tmp << " tries \n";
    }
    hwlib::wait_ms(1000);
    hwlib::cout << "Sending..." << '\n';
  }
  return 0;
}