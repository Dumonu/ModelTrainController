#include <stdint.h>
#include <stdio.h>

#ifdef WINDOWS
#include <windows.h>

#include "serial.h"

#define COM ("\\\\.\\COM1")

/* Hanle for the serial port */
extern HANDLE hSerial;

DCB dcbSerialParams = {
    0
};
COMMTIMEOUTS timeouts = {
    0
};

/*
 * Initialize COM1 for serial
 * Return 0 on success
 */
int init_serial () {
    /* Open the port */
    printf("Opening serial port on COM1\n");
    hSerial = CreateFile(COM, GENERIC_READ|GENERIC_WRITE, 0, NULL,
        OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Error opening port\n");

        return 1;
    }

    printf("Port opened\n");

    /*
     * Set parameters for port
     * 9600 baud
     * 1 start bit
     * 1 stop bit
     * no parity
     */
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error getting device state\n");
        CloseHandle(hSerial);

        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error setting device parameters\n");
        CloseHandle(hSerial);

        return 1;
    }

    /* Set timeout settings */
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error setting timeouts\n");
        CloseHandle(hSerial);

        return 1;
    }

    return 0;
}

/* Close the COM port with the serial connection */
void close_serial () {
    printf("Closing the port\n");
    if (!CloseHandle(hSerial)) {
        printf("Oh, poopy! It failed to close!\n");

        return;
    }
    printf("Closed\n");
}

/*
 * Send a command over the serial connection
 * Returns bytes sent
 */
uint32_t send_serial (const uint8_t *cmd) {
    uint32_t ret = 0;

    printf("Sending command: ");
    printf("%02X", *(cmd + 0));
    printf("%02X", *(cmd + 1));
    printf("%02X", *(cmd + 2));
    printf("\n");

    if (!WriteFile(hSerial, cmd, 3, &ret, NULL)) {
        printf("Error writing to port\n");
        ret = 0;
    } else {
        ret = 3;
        printf("%u bytes written\n", ret);
    }

    return ret;
}

#else

int init_serial () {
    printf("Unix version not implemented...");
    return 1;
}

void close_serial () {
    printf("Unix version not implemented...");
}

uint32_t send_serial (const uint8_t *cmd) {
    printf("Sending command: ");
    printf("%02X", *(cmd + 0));
    printf("%02X", *(cmd + 1));
    printf("%02X", *(cmd + 2));
    printf("\n");

    printf("Unix version not implemented...");
}


#endif
