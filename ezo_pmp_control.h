#ifndef EZO_PMP_CONTROL_H
#define EZO_PMP_CONTROL_H

#define CARRIAGE_RETURN '\r'

void initPumpControl();
void executeEzoPmpCommand(String command);
void handleEzoPmpCommand();
bool getPmpStatus();

#endif
