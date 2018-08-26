/*
  Matrix Keypad Example
  By Dhamdhawach Horsuwan
  Bangkok,Thailand
*/
byte keypad_pin [] = {2, 3, 4, 5, 6, 7, 8, 9}; // c1,c2,c3,c4,r1,r2,r3,r4
char keypad_pin_map[] = {'D', '#', '0', '*', 'C', '9', '8', '7', 'B', '6', '5', '4', 'A', '3', '2', '1'};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Matrix Key pads Test!");
  keypad_init();
}
long a = 0;
String input_str = "";
void loop() {
   Serial.println("Enter your number,then press '#'");
  while(1){
    char key = get_key();
    if(key != '#'){
      if(key>='0' && key <= '9'){
        input_str += key;
        Serial.print(key);
      }
      else if(key == '*'){
        input_str = "";
        Serial.println();
        Serial.println("Enter your number,then press '#'");
      }
    }
    
    else{
      Serial.println();
      a = input_str.toInt();
      Serial.print("your number is  ");
      Serial.println(a);
      input_str = "";
      Serial.println("Enter your number,then press '#'");
    }
  }
  
}
char get_key() {
  char pressed_key;
  while (1) {
    unsigned int key = keypad_read();
    char pressed_key_num = 0;

    for (char i = 0; i < 16 ; i++) {
      pressed_key_num += (key & (1 << i)) >> i;
      if ((key & (1 << i)) >> i == 1)pressed_key = i;
    }
    if (pressed_key_num == 1) {
      break;
    }
  }
  while (1) {
    unsigned int key = keypad_read();
    char pressed_key_num = 0;

    for (char i = 0; i < 16 ; i++) {
      pressed_key_num += (key & (1 << i)) >> i;
    }
    if (pressed_key_num == 0) {
      return keypad_pin_map[pressed_key];
    }

  }
}
void print_key_pressed(unsigned int key) {
  for (char i = 0; i < 16; i++) {
    if ((key & (1 << i)) >> i == 1) {
      Serial.print(keypad_pin_map[i]);
      if (i < 15)Serial.print(",");
    }
  }
  Serial.println();
}
void keypad_init() {
  for (char i = 0; i < 4; i++) {
    pinMode(keypad_pin[i], INPUT_PULLUP);
  }
  for (char i = 4; i < 8; i++) {
    pinMode(keypad_pin[i], INPUT);
    digitalWrite(keypad_pin[i], LOW);
  }
}

unsigned int keypad_read() {
  unsigned int result = 0;
  for (char i = 0; i < 4; i++) {
    result |= (read_row(i)) << i * 4;
  }
  return result;
}

unsigned int read_row(byte row) {
  unsigned int result = 0;
  for (char i = 4; i < 8; i++) {
    if (row + 4 != i)pinMode(keypad_pin[i], INPUT);
    else pinMode(keypad_pin[i], OUTPUT);
  }

  for (char i = 0; i < 4; i++) {
    result |= (!digitalRead(keypad_pin[i])) << i;
  }
  return result;
}

void print_bin(unsigned int data) {
  for (char i = 15; i >= 0; i--) {
    Serial.print((data & (1 << i)) >> i);
    if (i > 0)Serial.print(",");
    else Serial.println();
  }
}

