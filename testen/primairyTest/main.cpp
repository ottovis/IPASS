#include "hwlib.hpp"
#include "array"

#define STARTBYTE 0b11011011
#define STOPBYTE 0b10001001
#define BROADCASTBYTE 0b00000011
#define SENDBYTE 0b00001100
#define ACKBYTE 0b00110000
#define RESENDBYTE 0b11000000


class wiwire{
  private:
  hwlib::target::pin_out txPin;
  hwlib::target::pin_in rxPin;
  void sendByte(char byte);
  void waitForStartByte();
  char readByte();
  bool verify(const char * msg, int sizeMsg, char byte);
  char checksum(const char * msg, int sizeMsg);
  hwlib::target::pin_out testProbe;
  
  public:
  wiwire(hwlib::target::pin_out txPin, hwlib::target::pin_in rxPin)
  : 
  txPin(txPin),
  rxPin(rxPin),
  testProbe(hwlib::target::pin_out(hwlib::target::pins::d46))
  {};
  int broadcast(const char * msg, const int & sizeMsg);
  int send();
  char blockRead(char &msg, int &size);
};

int wiwire::broadcast(const char * msg, const int & sizeMsg){
  sendByte(STARTBYTE);
  sendByte(BROADCASTBYTE);
  sendByte(sizeMsg);
  for (int i = 0; i < sizeMsg; i++)
  {
    sendByte(*(msg+i));
  }
  sendByte(checksum(msg, sizeMsg));
  sendByte(STOPBYTE);
  return 0;
}

char wiwire::checksum(const char * msg, int sizeMsg){
  char tmp = *msg;
  if(sizeMsg <= 1){
    return tmp;
  }
  for (int i = 1; i < sizeMsg; i++)
  {
    tmp ^= msg[i];
  }
  return tmp;
}

void wiwire::sendByte(char byte){
  testProbe.write(1); testProbe.flush();
  for (int i = 0; i < 8; i++)
  {
    if((byte >> i) % 2){
      txPin.write(1);txPin.flush();
      hwlib::wait_us(1500);
      txPin.write(0);txPin.flush();
      hwlib::wait_us(500);
    }
    else{
      txPin.write(1);txPin.flush();
      hwlib::wait_us(500);
      txPin.write(0);txPin.flush();
      hwlib::wait_us(1500);
    }
     
  }
  testProbe.write(0); testProbe.flush();
}

char wiwire::blockRead(char &msg, int &size){
  
}


// class wiwire{
//   private:
//   hwlib::target::pin_out txPin;
//   public:
//   wiwire(hwlib::target::pin_out txPin):
//   txPin(txPin)
//   {}

//   int write(const char * msg){
//     hwlib::cout << msg;   
//     for (int i = 0; i < 12; i++)
//     {
//       for (int j = 0; j < 8; j++)
//       {
//         char tmp = *(msg+i);
//       }
      
//       hwlib::cout << *(msg+i);
//     }
    
//     return 0; 
//   }

// };

int main() {
  hwlib::cout << " test/n";
  namespace target = hwlib::target;

  auto tx = target::pin_out(target::pins::d50);
  auto rx = target::pin_in(target::pins::d51);
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

  wiwire wire(tx, rx);
  int sizeMsg = 12;

  const char msg[12] = "Hello world";

  while (true) {
    
    wire.broadcast(msg, sizeMsg);
    hwlib::wait_ms(500);
  //   for (int i = 0; i < 100; i++)
  //   {
  //     tx.write(1); tx.flush();
  //   hwlib::wait_ms(1);
  //   tx.write(0); tx.flush();
  //   hwlib::wait_ms(1);
  //   }
    
  //   tx.write(1); tx.flush();
  //   hwlib::wait_us(1500);
  //   tx.write(0); tx.flush();
  //   hwlib::wait_us(500);
  
  // for (int i = 0; i < 100; i++)
  //   {
  //     tx.write(1); tx.flush();
  //   hwlib::wait_ms(1);
  //   tx.write(0); tx.flush();
  //   hwlib::wait_ms(1);
  //   }
    
  //   tx.write(1); tx.flush();
  //   hwlib::wait_us(500);
  //   tx.write(0); tx.flush();
  //   hwlib::wait_us(1500);

  //   tx.write(1); tx.flush();
  //   hwlib::wait_us(500);
  //   tx.write(0); tx.flush();
  //   hwlib::wait_us(1500);
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