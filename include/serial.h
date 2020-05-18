#ifndef SERIAL_H_20190917_111850
#define SERIAL_H_20190917_111850

HANDLE hSerial;

int init_serial ();
void close_serial ();

uint32_t send_serial (const char *cmd);

#endif /* SERIAL_H_20190917_111850 */
