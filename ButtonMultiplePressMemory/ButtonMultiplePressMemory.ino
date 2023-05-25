uint8_t BUTTON = 2;
uint8_t MEMORY_LED = 3;
uint8_t INPUT_LED = 4;


uint64_t __last_time = 0;







enum ProgramStatus {
  WAITING_INPUT,
  TAKING_INPUT,
  BLINKING_LIGHT
};

uint16_t MAX_PRESS_DELAY = 1000;
uint16_t BUTTON_ON_TIME = 100;
uint16_t BUTTON_OFF_TIME = 200;


ProgramStatus status;
uint16_t time_since_last_press = 0;
uint8_t last_button_state = 0;
uint16_t press_counter = 0;
uint8_t led_state = 0;
uint16_t time_since_last_led_action = 0;

void setup() {
 pinMode(BUTTON, INPUT);
 pinMode(MEMORY_LED, OUTPUT);
 pinMode(INPUT_LED, OUTPUT);
 Serial.begin(9600);


 __last_time = millis();
 status = WAITING_INPUT;
}

void loop() {
  uint16_t deltaT = millis() - __last_time;
  __last_time = millis();

  switch(status)
  {
    case WAITING_INPUT:
      // If we receive input from the button,
      // Begin the taking_input state
      if(digitalRead(BUTTON))
        {
          digitalWrite(INPUT_LED, HIGH);
          last_button_state = 1;
          press_counter += 1;
          status = TAKING_INPUT;
          time_since_last_press = 0;
          break;
        }
        digitalWrite(INPUT_LED, LOW);
      break;
    case TAKING_INPUT:
      time_since_last_press += deltaT;
      if(time_since_last_press > MAX_PRESS_DELAY)
      {
        status = BLINKING_LIGHT;
        led_state = 0;
        time_since_last_led_action = 0;
        break;
      }

      if(digitalRead(BUTTON))
      {
        digitalWrite(INPUT_LED, HIGH);
        time_since_last_press = 0;
        if(last_button_state == 0)
        {
          last_button_state = 1;
          press_counter += 1;
          break;
        }
      }
      else
      {
        digitalWrite(INPUT_LED, LOW);
        last_button_state = 0;
      }
      break;
    case BLINKING_LIGHT:
        time_since_last_led_action += deltaT;
        if(press_counter == 0)
        {
          status = WAITING_INPUT;
          break;
        }
        if(led_state == 0 && time_since_last_led_action >= BUTTON_OFF_TIME)
        {
          time_since_last_led_action = 0;
          led_state = 1;
          digitalWrite(MEMORY_LED, HIGH);
          break;
        }
        if(led_state == 1 && time_since_last_led_action >= BUTTON_ON_TIME)
        {
          time_since_last_led_action = 0;
          led_state = 0;
          digitalWrite(MEMORY_LED, LOW);
          press_counter -= 1;
          break;
        }
      break;
  }

  Serial.println(press_counter);

  
}
