#include "hwlib.hpp"

int main( void ){	
   
   namespace target = hwlib::target;
   target::board board; 
   
   auto leds = hwlib::all(
      board.led1, board.led2, board.led3, board.led4, 
      board.led5, board.led6, board.led7, board.led8, board.led9 );
   board.green.write(1);
   board.green.flush();  
   
   
   for(;;){
      // while(!board.sw1.read()){
         for (int i = 0; i < 20; i++)
         {
            leds.write(1); leds.flush();
            hwlib::wait_ms(5);
            leds.write(0); leds.flush();
            hwlib::wait_ms(5);
         }
            leds.write(0); leds.flush();
            hwlib::wait_ms(5);
            leds.write(0); leds.flush();
            hwlib::wait_ms(5);
         
      // }
   }
}
