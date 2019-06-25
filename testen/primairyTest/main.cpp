#include "hwlib.hpp"

int main() {
  hwlib::cout << " test/n";
  namespace target = hwlib::target;

  auto tx = target::pin_out(target::pins::d50);
  // auto rx = target::pin_in(target::pins::d51);
  // auto button = target::pin_in( target::pins::d40 );
  // auto led = target::pin_out( target::pins::d47 );
  // auto scl = target::pin_oc( target::pins::scl );
  // auto sda = target::pin_oc( target::pins::sda );

  // auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

  // auto display = hwlib::glcd_oled( i2c_bus, 0x3c );

  // display.clear();

  // volatile bool pulseBit = false;
  // volatile int tmp = 0;

  // led.write(0); led.flush();
  // bool status = false;
  // int tmp = 0;

  while (true) {
    tx.write(0);
    hwlib::wait_us(900);
    tx.write(1);
    hwlib::wait_us(3000);
    tx.write(0);
    hwlib::wait_us(900);
    tx.write(1);
    hwlib::wait_us(900);
    tx.write(0);
    hwlib::wait_us(900);
    tx.write(1);
    hwlib::wait_us(900);
    hwlib::wait_ms(5000);

  }

  return 0;
}

// tmp = 0;
// for (int i = 0; i < 200; i++)
// {
//     tmp += rx.read();
// }
// hwlib::cout << tmp << "\n";
// hwlib::wait_ms(10);
// if (tmp > 50)
// {
//     for( uint16_t i = 10; i < display.size.x - 10; i++ ){
//         for( uint16_t y = 10; y < display.size.y - 10; y++ ){
//             display.write( hwlib::xy( i, y ) );
//         }
//     }
//     display.flush();
// }
// else
// {
//     display.clear();
//     display.flush();
// }