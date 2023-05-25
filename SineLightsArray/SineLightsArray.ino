const uint8_t N_LEDS = 5;
const uint8_t LEDS[N_LEDS] = {3, 5, 6, 9, 10};
const uint8_t BUTTON_RIGHT = 12;
const uint8_t BUTTON_LEFT = 13;

const float REDUCER = 1000;
const float SPEED = 2;

void setup() {
  for(int i = 0; i < N_LEDS; ++i)
    pinMode(LEDS[i], OUTPUT);


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

void loop() {

  double sineResult = sin(millis() * SPEED / REDUCER);
  double position = map_value(sineResult, -1, 1, 0, 4, true); 

  for(int i = 0; i < N_LEDS; ++i)
    {
      if(abs(float(i) - position) > 1)
        continue;
      
      if(i <= position)
      {
        float value = i - position + 1;
        float light_value = map_value(value, 0, 1, 0, 255, true);
        analogWrite(LEDS[i], light_value);
        continue;
      }
      if(i > position)
      {
        float value = position + 1 - i;
        float light_value = map_value(value, 0, 1, 0, 255, true);
        analogWrite(LEDS[i], light_value);
        continue;
      }

    }

}
