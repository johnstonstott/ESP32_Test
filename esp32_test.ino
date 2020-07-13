const int LED_BUILTIN = 2;
int count = 0;
TaskHandle_t lightTask;
TaskHandle_t mathTask;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);

  // xTaskCreatePinnedToCore(taskFunction, taskName, stackSize, taskParam, taskPriority, taskHandle, core);
  // Make lightFunction execute on core 0.
  xTaskCreatePinnedToCore(lightFunction, "Light Task", 10000, NULL, 1, &lightTask, 0);
  // Make mathFunction execute on core 1.
  xTaskCreatePinnedToCore(mathFunction, "Math Task", 10000, NULL, 1, &mathTask, 1);
}

void lightFunction(void * params) {
  while(true) {
    Serial.println("Core " + String(xPortGetCoreID()) + ": turning LED on.");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);

    Serial.println("Core " + String(xPortGetCoreID()) + ": turning LED off.");
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

void mathFunction(void * params) {
  while(true) {
    count += 1;
    Serial.println("Core " + String(xPortGetCoreID()) + ": adding 1, result now " + count + ".");
  }
}

void loop() {
  // Everything in loop is run on core 1 by default.
}
