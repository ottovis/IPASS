#include "hwlib.hpp"

class pin_in_5 : public hwlib::target::pin_in{
  private:
  int counter_5 = 0;
  public:
  pin_in_5(due::pins pin): hwlib::target::pin_in(pin){};
  bool read_10(){
    counter_5 = 0;
    for (int i = 0; i < 50; i++)
    {
      hwlib::wait_us(1);
      counter_5 += read();
    }
    
    return counter_5 < 45 ? true : false;
  }
};

int main() {
  namespace target = hwlib::target;

  auto rx = pin_in_5(target::pins::d50);
  //   auto reciever = target::pin_in(target::pins::d51);
  //   auto button = target::pin_in(target::pins::d40);
  auto led = target::pin_out( target::pins::d53 );
  // auto scl = target::pin_oc( target::pins::scl );
  // auto sda = target::pin_oc( target::pins::sda );

  // auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

  // auto display = hwlib::glcd_oled( i2c_bus, 0x3c );

  // display.clear();

  // volatile bool pulseBit = false;
  // volatile int tmp = 0;
  // int errAllowance = 10;

  led.write(1); led.flush();

  while (true) {


    if (rx.read_10())
    {
      led.write(1); led.flush();
      hwlib::wait_us(50);
    }
    else{
    led.write(0); led.flush();
    hwlib::wait_us(50);
    }

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