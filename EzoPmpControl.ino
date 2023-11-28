String input_command = "";
String pump_response = "";

boolean response_complete = false;
boolean is_flowing = false;
float ml;


/**
 * This method serves to initialize all the parameters
 * that will be used to control the EZO PMP
 */
void initPumpControl(){
  input_command.reserve(10);
  pump_response.reserve(30);
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
  Serial.println(pump_response);
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

bool getPmpStatus(){
  return false;
}
