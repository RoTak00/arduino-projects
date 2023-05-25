uint8_t LED_SINE = 6;
uint8_t LED_NORMAL = 9;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_SINE, OUTPUT);
  analogWrite(LED_SINE, 255);

  pinMode(LED_NORMAL, OUTPUT);
  analogWrite(LED_NORMAL, 255);

  Serial.begin(9600);
}

float map_value(float x, float int_start, float int_end, float map_start, float map_end, bool trunc = true)
{
  float a = (map_end - map_start) / (int_end - int_start);
  float b = (int_end * map_start - int_start * map_end) / (int_end - int_start);

  float result = a * x + b;

  if(!trunc) return result;
  
  if(result < map_start) return map_start;
  if(result > map_end) return map_end;
  return result;
}

float linear_sine(float x)
{
  while(x > 3 * PI / 2)
    x -= 2 * PI;
  while(x < - PI / 2)
    x += 2 * PI;

  if(x < PI / 2)
    return 2 * x / PI;
  else
    return -2 * x / PI + 2;
}

uint8_t NO_LIGHT = 0;
uint8_t MAX_LIGHT = 255;

double deltaT = 0;
double speed = 3;
double SLOWER = 1000;
void loop() {
  deltaT = millis();
  double sineValue = sin(deltaT  / SLOWER * speed);
  uint8_t sineAnalogValue = map_value(sineValue, -1, 1, NO_LIGHT, MAX_LIGHT, true);
  
  double linearValue = linear_sine(deltaT / SLOWER * speed);
  uint8_t linearAnalogValue = map_value(linearValue, -1, 1, NO_LIGHT, MAX_LIGHT, true);

  analogWrite(LED_SINE, sineAnalogValue);
  analogWrite(LED_NORMAL, linearAnalogValue);
}
