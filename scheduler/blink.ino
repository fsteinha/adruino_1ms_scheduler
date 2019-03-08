bool b_blink = true;

void blink_task()
{
  if (b_blink == true)
  {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED on (HIGH is the voltage level)    
  }

  b_blink = ! b_blink;
}
