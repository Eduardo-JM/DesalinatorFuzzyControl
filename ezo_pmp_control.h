#ifndef EZO_PMP_CONTROL_H
#define EZO_PMP_CONTROL_H

#define CARRIAGE_RETURN '\r'
#define MIN_FLOW_RATE 0.5

void initPumpControl();
void executeEzoPmpCommand(String command);
void handleEzoPmpCommand();
bool getPmpStatus();
void stopDispensing();
void startConstantFlowrate(float);

#endif
