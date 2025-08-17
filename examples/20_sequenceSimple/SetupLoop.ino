void setup(){
  Serial.begin(115200);
  while( ! Serial){}
  delay(100);
  Serial.println();
  Serial.println(F( __DATE__"," __TIME__));

  pinMode(A0_pin,    INPUT_PULLUP);
  pinMode(A1_pin,    INPUT_PULLUP);
  pinMode(D0_pin,             OUTPUT);
  pinMode(LED_BUILTIN_pin,    OUTPUT);


  //The S0_DoNothing is active from the constructor of the class. But to start, we have to set it to step 1 (S1_Output_D0):
  simple_1.set_nextStep(Step::S1_Output_D0);  
}

void loop(){
   //This two calls are all you need in loop():
  simple_1.sequenceProcess(); 
  sequenceLoopSimple();

//This is only for Serial print:
  static Step oldStep = Step::VeryLastEnum;
  if(oldStep != simple_1.get_actualStep()){ //If the step change, print the actual step
    oldStep = simple_1.get_actualStep();
    Serial.print(F("Actual Step (int): "));
    Serial.println(uint32_t(simple_1.get_actualStep())); //to convert the type "Step" to int use uint32_t(...
  }
}