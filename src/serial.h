#ifndef SERIAL_H_20190917_111850
#define SERIAL_H_20190917_111850

#ifdef WINDOWS
HANDLE hSerial;
#endif

int init_serial ();
void close_serial ();

uint32_t send_serial (const uint8_t *cmd);

#endif /* SERIAL_H_20190917_111850 */
