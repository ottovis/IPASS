#include "hwlib.hpp"

class pin_in_x : public hwlib::target::pin_in{
  private:
  uint8_t counter_x = 0;
  public:
  pin_in_x(due::pins pin): hwlib::target::pin_in(pin){};
  uint8_t read_x(int times){
    counter_x = 0;
    for (int i = 0; i < times; i++)
    {
      hwlib::wait_us(1);
      counter_x += read();
    }
    
    return counter_x; // return confidance
  }
};



int main() {
  namespace target = hwlib::target;

  auto rx = pin_in_x(target::pins::d50);
  //   auto reciever = target::pin_in(target::pins::d51);
  //   auto button = target::pin_in(target::pins::d40);
  auto led = target::pin_out( target::pins::d46 );
  auto pulse = target::pin_out( target::pins::d47 );
  auto high = target::pin_out( target::pins::d48 );
  auto low = target::pin_out( target::pins::d49 );
  // auto scl = target::pin_oc( target::pins::scl );
  // auto sda = target::pin_oc( target::pins::sda );

  // auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

  // auto display = hwlib::glcd_oled( i2c_bus, 0x3c );

  // display.clear();

  // volatile bool pulseBit = false;
  // volatile int tmp = 0;
  // int errAllowance = 10;

  led.write(1); led.flush();
  // uint64_t counter = 0;
  int highLow = 0;
  bool last = false;
  bool pulseSpeed = false;
  int sizeBuffer = 10;
  char rollingBuffer[sizeBuffer];
  int buffCounter = 0;
  for (int i = 0; i < sizeBuffer; i++)
    {
      rollingBuffer[i] = rx.read();
    }
  while (true) {
    //sync:
    // int size = 1000;
    // uint8_t array[size];
     int readValue = rx.read();
    rollingBuffer[buffCounter] = readValue;
    int tmp = 0;
    for (int i = 0; i < sizeBuffer; i++)
    {
      tmp += rollingBuffer[i];
    }
    if (buffCounter < sizeBuffer - 1)
    {
      buffCounter++;
    }
    else
    {
      buffCounter = 0;
    }

    pulse.write(pulseSpeed); pulse.flush();

    pulseSpeed = !pulseSpeed;
    
    if (tmp <= 2)
    {
      led.write(1); led.flush();
      if (!last)
      {
        if(highLow < 18){
          low.write(1); low.flush();
        }
        if(highLow > 35){
          high.write(1); high.flush();
        }
        highLow = 0;
      }
      highLow++;
      last = true;
      
    }
    else{
      led.write(0); led.flush();
      last = false;
      high.write(0); high.flush();
      low.write(0); low.flush();
    }
    
    
    
    // for (int i = 0; i < size; i++)
    // {
    //     hwlib::cout << array[i] << " ";
    // }
    


    // if (rx.read_x())
    // {
    //   led.write(1); led.flush();
    //   hwlib::wait_us(50);
    //  if (!tmp){
    //     hwlib::cout << counter++ << "\n";
    //     tmp = true;
    //   }
    // }
    // else{
    // led.write(0); led.flush();
    // hwlib::wait_us(50);
    
    //    tmp = false;
    // }
  
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