String input_command = "";
String pump_response = "";

boolean response_complete = false;
boolean is_flowing = false;
float ml;
float max_flowrate = 105.0;


/**
 * This method serves to initialize all the parameters
 * that will be used to control the EZO PMP
 */
void initPumpControl(){
  input_command.reserve(10);
  pump_response.reserve(30);
  max_flowrate = getMaxFlow();
  if (max_flowrate < MIN_FLOW_RATE)
    Serial.println("ERROR ENCOUNTERED WHILE SETTING MAX FLOWRATE. MAX FLOW RATE CAN NOT BE LESS THAN MIN FLOW RATE");
    
  executeEzoPmpCommand("L,0");
}

/**
 * This method executes everytime serial port_0
 * receives a char. This method will read the inputString 
 * until a CR (delimiter) is received.
 * 
 * This method also sets response_complete to true
 */
void serialEvent3() {
  pump_response = Serial3.readStringUntil(CARRIAGE_RETURN);
  response_complete = true;
}

/**
 * This method sends a string to the EZO PMP
 * this method doesn't handle any errors.
 */
void executeEzoPmpCommand(String command){
  Serial.println(command);
  Serial3.print(command);
  Serial3.print(CARRIAGE_RETURN);
}

/**
 * 
 */
void handleEzoPmpCommand() {
  if (!response_complete)
    return;
    
  if (isdigit(pump_response[0]) || pump_response[0]== '-')
    ml = pump_response.toFloat();
  
  pump_response = "";
  response_complete = false;
}

/**
 * @returns true if pump is dispensing, false otherwise
 */
bool getPmpStatus(){
  executeEzoPmpCommand("D,?");
  delay(50);
  if (response_complete)
    return pump_response.indexOf("1") >= 0;
  return false;
}

/**
 * When executed, the pump stop dispensing
 */
void stopDispensing() {
  executeEzoPmpCommand("X");
}

void startConstantFlowrate(float ml_per_min){
  if (ml_per_min < MIN_FLOW_RATE) {
    stopDispensing();
    return;
  }
  if (ml_per_min > max_flowrate){
    stopDispensing();
    return;
  }
  
  String value2dispense = String(ml_per_min, 1);
  String command = "DC,";
  command.concat(value2dispense);
  command.concat(",*");
  executeEzoPmpCommand(command);
}

float getMaxFlow(){
  executeEzoPmpCommand("DC,?");
  String valueStr = pump_response.substring(pump_response.indexOf(',') + 1);
  if (isdigit(valueStr[0]) || valueStr[0]== '-')
    return valueStr.toFloat();
  return 0.0;
}
