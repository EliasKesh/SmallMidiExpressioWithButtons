/* Buttons to USB MIDI Example

   You must select MIDI from the "Tools > USB Type" menu

   To view the raw MIDI data on Linux: aseqdump -p "Teensy MIDI"

   This example code is in the public domain.
   For the Small Box build
*/

#include <Bounce.h>
#include <MIDI.h>

// the MIDI channel number to send messages
const int channel = 1;
const int PCTimeOut = 10000;
const int ACTimeOut = 5000;
const int TempoTimeOut = 10000;


#if 0
Change Name USB Name
"./hardware/teensy/avr/cores/usb_midi/usb_private.h"
"hardware/teensy/avr/cores/teensy3"
Board: Teensy 3.1 / 3.2
Programmer: USBTiny
#endif

// Create Bounce objects for each button.  The Bounce object
// automatically deals with contact chatter or "bounce", and
// it makes detecting changes very simple.
const int	Debounce = 20;
Bounce button0 = Bounce(0, Debounce);
Bounce button1 = Bounce(1, Debounce);  // 5 = 5 ms debounce time
Bounce button2 = Bounce(2, Debounce);  // which is appropriate for good
Bounce button3 = Bounce(3, Debounce);  // quality mechanical pushbuttons
Bounce button4 = Bounce(4, Debounce);
Bounce button5 = Bounce(5, Debounce);  // if a button is too "sensitive"
#if 0
Bounce button6 = Bounce(6, Debounce);  // to rapid touch, you can
Bounce button7 = Bounce(7, Debounce);  // increase this time.
Bounce button8 = Bounce(8, Debounce);
Bounce button9 = Bounce(9, Debounce);
Bounce button10 = Bounce(10, Debounce);
Bounce button11 = Bounce(11, Debounce);
Bounce button12 = Bounce(12, Debounce);
Bounce button13 = Bounce(13, Debounce);
Bounce button14 = Bounce(14, Debounce);
Bounce button15 = Bounce(15, Debounce);
Bounce button16 = Bounce(16, Debounce);
Bounce button17 = Bounce(17, Debounce);
Bounce button18 = Bounce(18, Debounce);
Bounce button19 = Bounce(19, Debounce);
Bounce button20 = Bounce(20, Debounce);
Bounce button21 = Bounce(21, Debounce);
Bounce button22 = Bounce(22, Debounce);

Bounce button23 = Bounce(23, Debounce);
//Bounce button24 = Bounce(24, Debounce);
//Bounce button25 = Bounce(25, Debounce);
#endif

// the MIDI continuous controller for each analog input
const int controllerA0 = 12; // 12 = expression1
const int controllerA1 = 07; // 07 = volume/expression
const int controllerA2 = 02; // 02 = breath controller

//const int controllerA0 = 10; // 10 = pan position
// const int controllerA2 = 91; // 91 = reverb level
//const int controllerA3 = 93; // 93 = chorus level

// store previously sent values, to detect changes
int previousA0 = -1;
int previousA1 = -1;
int previousA2 = -1;
int previousA3 = -1;
unsigned int ACTime = ACTimeOut;
unsigned int PCTime = PCTimeOut;
unsigned int TempoTime = TempoTimeOut;
elapsedMillis msec = 0;
char Data1;
char Data2;

int LED1 =  6; // Green
int LED2 =  7; // Yellow
int LED3 =  8; // Blue
int LED4 =  9; // Orange
int LED5 =  10; //
int LED6 =  11; //
int LED7 =  12; //
int LED8 =  13; //


int Expression1 = A0;
int Expression2 = A1;
int Expression3 = A2;

void setup() {
  // Configure the pins for input mode with pullup resistors.
  // The pushbuttons connect from each pin to ground.  When
  // the button is pressed, the pin reads LOW because the button
  // shorts it to ground.  When released, the pin reads HIGH
  // because the pullup resistor connects to +5 volts inside
  // the chip.  LOW for "on", and HIGH for "off" may seem
  // backwards, but using the on-chip pullup resistors is very
  // convenient.  The scheme is called "active low", and it's
  // very commonly used in electronics... so much that the chip
  // has built-in pullup resistors!

  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);  // Teensy++ 2.0 LED, may need 1k resistor pullup
#if 0
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);
  pinMode(14, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  pinMode(16, INPUT_PULLUP);
  pinMode(17, INPUT_PULLUP);
  pinMode(18, INPUT_PULLUP);
  pinMode(19, INPUT_PULLUP);
  pinMode(20, INPUT_PULLUP);
  pinMode(21, INPUT_PULLUP);
  pinMode(22, INPUT_PULLUP);
  pinMode(23, INPUT_PULLUP);
  //  pinMode(24, INPUT_PULLUP);
  //  pinMode(25, INPUT_PULLUP);
#endif

  // The LEDs are outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
  pinMode(LED7, OUTPUT);
  pinMode(LED8, OUTPUT);

  // Analog Inputs for the expression pedals.
  pinMode(Expression1, INPUT);
  pinMode(Expression2, INPUT);
  pinMode(Expression3, INPUT);

  ACTime = 50000;
  PCTime = 50000;
  TempoTime = 50000;

  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);
  digitalWrite(LED8, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);
  delay(1000);
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
  digitalWrite(LED6, HIGH);
  digitalWrite(LED7, HIGH);
  digitalWrite(LED8, HIGH);
  delay(1000);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  digitalWrite(LED6, LOW);
  digitalWrite(LED7, LOW);
  digitalWrite(LED8, LOW);


}

void loop() {

 
  if ( PCTime )
    PCTime--;
  else {
    digitalWrite(LED1, LOW);
  }

  // Turn off the LEDs since the trigger turns them on.
  if ( ACTime )
    ACTime--;
  else {
    digitalWrite(LED2, LOW);
  }

#if 0
  if ( TempoTime )
    TempoTime--;
  else {
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
  }
 #endif

  // Update all the buttons.  There should not be any long
  // delays in loop(), so this runs repetitively at a rate
  // faster than the buttons could be pressed and released.
  button0.update();
  button1.update();
  button2.update();
  button3.update();
  button4.update();
  button5.update();
#if 0
  button6.update();
  button7.update();
  button8.update();
  button9.update();
  button10.update();
  button11.update();
  button12.update();
  button13.update();
  button14.update();
  button15.update();
  button16.update();
  button17.update();
  button18.update();
  button19.update();
  button20.update();
  button21.update();
  button22.update();
  button23.update();
  //  button24.update();
  //  button25.update();
#endif

  // Check each button for "falling" edge.
  // Send a MIDI Note On message when each button presses
  // Update the Joystick buttons only upon changes.
  // falling = high (not pressed - voltage from pullup resistor)
  //           to low (pressed - button connects pin to ground)

  if (button0.fallingEdge()) {
    usbMIDI.sendProgramChange(0, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }

  if (button1.fallingEdge()) {
    usbMIDI.sendProgramChange(1, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }

  if (button2.fallingEdge()) {
    usbMIDI.sendProgramChange(2, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }

  if (button3.fallingEdge()) {
    usbMIDI.sendProgramChange(3, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }

  if (button4.fallingEdge()) {
    usbMIDI.sendProgramChange(119, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  //   usbMIDI.sendNoteOn(note, velocity, channel);
  //   usbMIDI.sendNoteOff(note, velocity, channel);

#if 0
  if (button5.fallingEdge()) {
    usbMIDI.sendProgramChange(5, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button6.fallingEdge()) {
    usbMIDI.sendProgramChange(6, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button7.fallingEdge()) {
    usbMIDI.sendProgramChange(7, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button8.fallingEdge()) {
    usbMIDI.sendProgramChange(8, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button9.fallingEdge()) {
    usbMIDI.sendProgramChange(9, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button10.fallingEdge()) {
    usbMIDI.sendProgramChange(10, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button11.fallingEdge()) {
    usbMIDI.sendProgramChange(11, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button12.fallingEdge()) {
    usbMIDI.sendProgramChange(12, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button13.fallingEdge()) {
    usbMIDI.sendProgramChange(13, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button14.fallingEdge()) {
    usbMIDI.sendProgramChange(14, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button15.fallingEdge()) {
    usbMIDI.sendProgramChange(15, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button16.fallingEdge()) {
    usbMIDI.sendProgramChange(16, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button17.fallingEdge()) {
    usbMIDI.sendProgramChange(17, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button18.fallingEdge()) {
    usbMIDI.sendProgramChange(18, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button19.fallingEdge()) {
    usbMIDI.sendProgramChange(19, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button20.fallingEdge()) {
    usbMIDI.sendProgramChange(20, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button21.fallingEdge()) {
    usbMIDI.sendProgramChange(21, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button22.fallingEdge()) {
    usbMIDI.sendProgramChange(22, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }

  if (button23.fallingEdge()) {
    usbMIDI.sendProgramChange(23, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button24.fallingEdge()) {
    usbMIDI.sendProgramChange(14, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
  if (button25.fallingEdge()) {
    usbMIDI.sendProgramChange(1, channel);
    digitalWrite(LED1, HIGH);
    PCTime = PCTimeOut;
  }
#endif

  if (button4.risingEdge()) {
    usbMIDI.sendProgramChange(120, channel);
  }
  
  #if 0
  // Check each button for "rising" edge
  // Send a MIDI Note Off message when each button releases
  // For many types of projects, you only care when the button
  // is pressed and the release isn't needed.
  // rising = low (pressed - button connects pin to ground)
  //          to high (not pressed - voltage from pullup resistor)
  if (button0.risingEdge()) {
    usbMIDI.sendNoteOff(60, 0, channel);  // 60 = C4
  }
  if (button1.risingEdge()) {
    usbMIDI.sendNoteOff(61, 0, channel);  // 61 = C#4
  }
  if (button2.risingEdge()) {
    usbMIDI.sendNoteOff(62, 0, channel);  // 62 = D4
  }
  if (button3.risingEdge()) {
    usbMIDI.sendNoteOff(63, 0, channel);  // 63 = D#4
  }
  if (button4.risingEdge()) {
    usbMIDI.sendNoteOff(64, 0, channel);  // 64 = E4
  }
  if (button5.risingEdge()) {
    usbMIDI.sendNoteOff(65, 0, channel);  // 65 = F4
  }
  if (button6.risingEdge()) {
    usbMIDI.sendNoteOff(66, 0, channel);  // 66 = F#4
  }
  if (button7.risingEdge()) {
    usbMIDI.sendNoteOff(67, 0, channel);  // 67 = G4
  }
  if (button8.risingEdge()) {
    usbMIDI.sendNoteOff(68, 0, channel);  // 68 = G#4
  }
  if (button9.risingEdge()) {
    usbMIDI.sendNoteOff(69, 0, channel);  // 69 = A5
  }
  if (button10.risingEdge()) {
    usbMIDI.sendNoteOff(70, 0, channel);  // 70 = A#5
  }
  if (button11.risingEdge()) {
    usbMIDI.sendNoteOff(71, 0, channel);  // 71 = B5
  }
#endif

#if 1
  // only check the analog inputs 100 times per second,
  // to prevent a flood of MIDI messages
  if (msec >= 100) {
    msec = 0;
    int n0 = analogRead(Expression1) / 8;
    int n1 = analogRead(Expression2) / 8;
    int n2 = analogRead(Expression3) / 8;
    //   int n3 = analogRead(A3) / 8;

    // only transmit MIDI messages if analog input changed
    if (n0 >  (1.10 * previousA0) || (n0 < (0.90 * previousA0)) ) {
      usbMIDI.sendControlChange(controllerA0, n0, channel);
      previousA0 = n0;
      digitalWrite(LED2, HIGH);
      ACTime = ACTimeOut;
    }

    //     if (n1 != previousA1) {
    if (n1 >  (1.10 * previousA1) || (n1 < (0.90 * previousA1)) ) {
      usbMIDI.sendControlChange(controllerA1, n1, channel);
      previousA1 = n1;
      digitalWrite(LED2, HIGH);
      ACTime = ACTimeOut;
    }

    //    if (n2 != previousA2) {
    if (n2 >  (1.10 * previousA2) || (n2 < (0.90 * previousA2)) ) {
      usbMIDI.sendControlChange(controllerA2, n2, channel);
      previousA2 = n2;
      digitalWrite(LED2, HIGH);
      ACTime = ACTimeOut;
    }
  }
#endif
  // MIDI Controllers should discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash

  if (usbMIDI.read()) {                    // Is there a MIDI message incoming ?
        Data1 = usbMIDI.getData1();
        Data2 = usbMIDI.getData2();
    
    switch (usbMIDI.getType()) {		// Get the type of the message we caught
        case usbMIDI.NoteOn:
        if ( Data1 != 44 ) {
          digitalWrite(LED4, HIGH); // Yellow
          TempoTime = TempoTimeOut;
        }


        if ( Data1 != 44 ) {
          digitalWrite(LED3, HIGH);
          TempoTime = TempoTimeOut;
        }

        //      case usbMIDI.ProgramChange:               // If it is a Program Change
        //	BlinkLed(MIDI.getData1());	// Blink the LED a number of times
        // correponding to the program number
        // (0 to 127, it can last a while..)
        break;

      case usbMIDI.ControlChange:
      if ( Data1 == 4 )
          switch (Data2) {
            case 0:
              digitalWrite(LED1, HIGH);
              digitalWrite(LED2, HIGH);
              digitalWrite(LED3, HIGH);
              digitalWrite(LED4, HIGH);
              digitalWrite(LED5, HIGH);
              digitalWrite(LED6, HIGH);
              digitalWrite(LED7, HIGH);
              digitalWrite(LED8, HIGH);
              break;

            case 1:
              digitalWrite(LED1, LOW);
              digitalWrite(LED2, LOW);
              digitalWrite(LED3, LOW);
              digitalWrite(LED4, LOW);
              digitalWrite(LED5, LOW);
              digitalWrite(LED6, LOW);
              digitalWrite(LED7, LOW);
              digitalWrite(LED8, LOW);
              break;

            case 2:
              digitalWrite(LED1, HIGH);
              break;

            case 3:
              digitalWrite(LED1, LOW);
              break;

            case 4:
              digitalWrite(LED2, HIGH);
              break;

            case 5:
              digitalWrite(LED2, LOW);
              break;

            case 6:
              digitalWrite(LED3, HIGH);
              break;

            case 7:
              digitalWrite(LED3, LOW);
              break;

            case 8:
              digitalWrite(LED4, HIGH);
              break;

            case 9:
              digitalWrite(LED4, LOW);
              break;

            case 10:
              digitalWrite(LED5, HIGH);
              break;

            case 11:
              digitalWrite(LED5, LOW);
              break;

            case 12:
              digitalWrite(LED6, HIGH);
              break;

            case 13:
              digitalWrite(LED6, LOW);
              break;

            case 14:
              digitalWrite(LED7, HIGH);
              break;

            case 15:
              digitalWrite(LED7, LOW);
              break;

            case 16:
              digitalWrite(LED8, HIGH);
              break;

            case 17:
              digitalWrite(LED8, LOW);
              break;
          }

        break;

      // See the online reference for other message types
      default:
        break;
    }
  }
}


#if 0
#use PWM pins
int redPin =  12;
int greenPin =  15;
int bluePin =  14;

void setup()   {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

int redIntensity = 0;

void loop()
{
  // set all 3 pins to the desired intensity
  analogWrite(redPin, redIntensity);
  analogWrite(greenPin, 255 - redIntensity);
  analogWrite(bluePin, 0);
#endif

