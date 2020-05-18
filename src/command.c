#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "command.h"
#include "serial.h"

typedef enum {
    SWITCH_C,
    ROUTE,
    ENGINE,
    TRAIN,
    ACCESSORY,
    _GROUP
} TARGET_TYPE;

bool buildCommand(TARGET_TYPE target, uint_fast8_t address, uint_fast8_t command, uint_fast8_t data);

// Switch Commands (7-bit address)
bool switchThrowThrough(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x00; // 00000
    return buildCommand(SWITCH_C, addr, command, data);
}

bool switchThrowOut(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1F; // 11111
    return buildCommand(SWITCH_C, addr, command, data);
}

bool switchSetAddr(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0B; // 01011
    return buildCommand(SWITCH_C, addr, command, data);
}

bool switchAssignToRouteThrough(uint8_t addr, uint8_t rtaddr)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(rtaddr > 0x1F) return false; // 5-bit data
    uint8_t command = 0x2; // 10
    return buildCommand(SWITCH_C, addr, command, rtaddr);
}

bool switchAssignToRouteOut(uint8_t addr, uint8_t rtaddr)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(rtaddr > 0x1F) return false; // 5-bit data
    uint8_t command = 0x3; // 11
    return buildCommand(SWITCH_C, addr, command, rtaddr);
}

// Route Commands (5-bit address)
bool routeThrow(uint8_t addr)
{
    if(addr > 0x1F) return false; // 5-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1F; // 11111
    return buildCommand(ROUTE, addr, command, data);
}

bool routeClear(uint8_t addr)
{
    if(addr > 0x1F) return false; // 5-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0C; // 01100
    return buildCommand(ROUTE, addr, command, data);
}

// Engine Commands
bool engineFwdDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x00; // 00000
    return buildCommand(ENGINE, addr, command, data);
}

bool engineToggleDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x01; // 00001
    return buildCommand(ENGINE, addr, command, data);
}

bool engineRevDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x03; // 00011
    return buildCommand(ENGINE, addr, command, data);
}

bool engineBoost(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x04; // 00100
    return buildCommand(ENGINE, addr, command, data);
}

bool engineBrake(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x07; // 00111
    return buildCommand(ENGINE, addr, command, data);
}

bool engineOpenFCoupler(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x05; // 00101
    return buildCommand(ENGINE, addr, command, data);
}

bool engineOpenRCoupler(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x06; // 00110
    return buildCommand(ENGINE, addr, command, data);
}

bool engineBlowHorn1(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1C; // 11100
    return buildCommand(ENGINE, addr, command, data);
}

bool engineRingBell(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1D; // 11101
    return buildCommand(ENGINE, addr, command, data);
}

bool engineLetoffSound(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1E; // 11110
    return buildCommand(ENGINE, addr, command, data);
}

bool engineBlowHorn2(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1F; // 11111
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux1Off(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x08; // 01000
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux1Op1(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x09; // 01001
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux1Op2(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0A; // 01010
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux1On(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0B; // 01011
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux2Off(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0C; // 01100
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux2Op1(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0D; // 01101
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux2Op2(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0E; // 01110
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAux2On(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0F; // 01111
    return buildCommand(ENGINE, addr, command, data);
}

bool engineNumeric(uint8_t addr, uint8_t command)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(command > 0x09) return false; // command in [0, 9]; Prevent collision
    uint8_t com = 0x0; // 00
    uint8_t data = 0x10 + command; // 00000
    return buildCommand(ENGINE, addr, com, data);
}


// Engine Extensions
bool engineAssignToTrain(uint8_t addr, uint8_t traddr)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(traddr > 0x0F) return false; // 4-bit train address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x10 | traddr; // 1DDDD
    return buildCommand(ENGINE, addr, command, data);
}

// Single Unit
bool engineAssignSUFwdDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x00; // 00000
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAssignSURevDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x04; // 00100
    return buildCommand(ENGINE, addr, command, data);
}

// Head-end Unit
bool engineAssignHUFwdDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x01; // 00001
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAssignHURevDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x05; // 00101
    return buildCommand(ENGINE, addr, command, data);
}

// Middle Unit
bool engineAssignMUFwdDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x02; // 00010
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAssignMURevDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x06; // 00110
    return buildCommand(ENGINE, addr, command, data);
}

// Rear Unit
bool engineAssignRUFwdDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x03; // 00011
    return buildCommand(ENGINE, addr, command, data);
}

bool engineAssignRURevDir(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x07; // 00111
    return buildCommand(ENGINE, addr, command, data);
}

bool engineMomentumLow(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x08; // 01000
    return buildCommand(ENGINE, addr, command, data);
}

bool engineMomentumMedium(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x09; // 01001
    return buildCommand(ENGINE, addr, command, data);
}

bool engineMomentumHigh(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0A; // 01010
    return buildCommand(ENGINE, addr, command, data);
}

// Not sure what this does either
bool engineSetAddr(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0B; // 01011
    return buildCommand(ENGINE, addr, command, data);
}

// Engine Speed Commands
bool engineSetAbsSpeed(uint8_t addr, uint8_t speed)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(speed > 0x1F) return false; // absolute speed in [0, 1F]
    uint8_t command = 0x3; // 11
    return buildCommand(ENGINE, addr, command, speed);
}

bool engineSetRelSpeed(uint8_t addr, int8_t relSpeed)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(relSpeed < -5 || relSpeed > 5) return false; // relSpeed in [-5, 5]
    uint8_t command = 0x2; // 10
    uint8_t data = relSpeed + 5;
    return buildCommand(ENGINE, addr, command, data);
}

// Train Commands
bool trainFwdDir(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x00; // 00000
    return buildCommand(TRAIN, addr, command, data);
}

bool trainToggleDir(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x01; // 00001
    return buildCommand(TRAIN, addr, command, data);
}

bool trainRevDir(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x03; // 00011
    return buildCommand(TRAIN, addr, command, data);
}

bool trainBoost(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x04; // 00100
    return buildCommand(TRAIN, addr, command, data);
}

bool trainBrake(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x07; // 00111
    return buildCommand(TRAIN, addr, command, data);
}

bool trainOpenFCoupler(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x05; // 00101
    return buildCommand(TRAIN, addr, command, data);
}

bool trainOpenRCoupler(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x06; // 00110
    return buildCommand(TRAIN, addr, command, data);
}

bool trainBlowHorn1(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1C; // 11100
    return buildCommand(TRAIN, addr, command, data);
}

bool trainRingBell(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1D; // 11101
    return buildCommand(TRAIN, addr, command, data);
}

bool trainLetoffSound(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1E; // 11110
    return buildCommand(TRAIN, addr, command, data);
}

bool trainBlowHorn2(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x1F; // 11111
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux1Off(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x08; // 01000
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux1Op1(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x09; // 01001
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux1Op2(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0A; // 01010
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux1On(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0B; // 01011
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux2Off(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0C; // 01100
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux2Op1(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0D; // 01101
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux2Op2(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0E; // 01110
    return buildCommand(TRAIN, addr, command, data);
}

bool trainAux2On(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0F; // 01111
    return buildCommand(TRAIN, addr, command, data);
}

bool trainNumeric(uint8_t addr, uint8_t command)
{
    if(addr > 0x0F) return false; // 4-bit address
    if(command > 0x09) return false; // command in [0, 9]; Prevent collision
    uint8_t com = 0x0; // 00
    uint8_t data = 0x10 + command; // 00000
    return buildCommand(TRAIN, addr, com, data);
}


// Train Extensions
bool trainMomentumLow(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x08; // 01000
    return buildCommand(TRAIN, addr, command, data);
}

bool trainMomentumMedium(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x09; // 01001
    return buildCommand(TRAIN, addr, command, data);
}

bool trainMomentumHigh(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0A; // 01010
    return buildCommand(TRAIN, addr, command, data);
}

// Not sure what this does either
bool trainSetAddr(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0B; // 01011
    return buildCommand(TRAIN, addr, command, data);
}

// probably removes all engines from this train
bool trainClearLashup(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0C; // 01100
    return buildCommand(TRAIN, addr, command, data);
}

// Train Speed Commands
bool trainSetAbsSpeed(uint8_t addr, uint8_t speed)
{
    if(addr > 0x0F) return false; // 4-bit address
    if(speed > 0x1F) return false; // speed in [0, 1F]
    uint8_t command = 0x3; // 11
    return buildCommand(TRAIN, addr, command, speed);
}

bool trainSetRelSpeed(uint8_t addr, int8_t relSpeed)
{
    if(addr > 0x0F) return false; // 4-bit address
    if(relSpeed < -5 || relSpeed > 5) return false; // relSpeed in [-5, 5]
    uint8_t command = 0x2; // 10
    uint8_t data = relSpeed + 5;
    return buildCommand(TRAIN, addr, command, data);
}

// Accessory Commands
bool accAux1Off(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x08; // 01000
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAux1Op1(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x09; // 01001
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAux1Op2(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0A; // 01010
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAux1On(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0B; // 01011
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAux2Off(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0C; // 01100
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAux2Op1(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0D; // 01101
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAux2Op2(uint8_t addr)
{
    // In the documentation, both "AUX2 option 2" and "AUX2 on" give
    // 01111 for the data field. However, following the pattern,
    // it looks like it should be a 01110 for this command.
    // So, by default we'll follow the pattern and avoid the collision,
    // but for the sake of following the documentation to a tee, we have
    // an option to change that
    
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
#ifdef DOCSTRICT
    uint8_t data = 0x0F; // 01111
#else
    uint8_t data = 0x0E; // 01110
#endif
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAux2On(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0F; // 01111
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accNumeric(uint8_t addr, uint8_t command)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(command > 0x08) return false; // command in [0, 8]
    uint8_t com = 0x0;
    uint8_t data = 0x10 | command; // 1DDDD
    return buildCommand(ACCESSORY, addr, com, data);
}


// Accessory Extensions
// These are really borked. Every command collides with at least two others
bool accAllOff(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x00; // 00000
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAllOn(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0F; // 01111
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accSetAddr(uint8_t addr)
{
    if(addr > 0x7F) return false; // 7-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0B; // 01011
    return buildCommand(ACCESSORY, addr, command, data);
}

bool accAssignAux1ToGroup(uint8_t addr, uint8_t graddr)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(graddr > 0x0F) return false; // 4-bit group address
    uint8_t command = 0x1; // 01
    return buildCommand(ACCESSORY, addr, command, graddr);
}

// WHY IS THIS THE SAME AS THE LAST?
bool accAssignAux2ToGroup(uint8_t addr, uint8_t graddr)
{
    if(addr > 0x7F) return false; // 7-bit address
    if(graddr > 0x0F) return false; // 4-bit group address
    uint8_t command = 0x1; // 01
    return buildCommand(ACCESSORY, addr, command, graddr);
}


// Group Commands
bool groupOff(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x08; // 01000
    return buildCommand(_GROUP, addr, command, data);
}

bool groupOp1(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x09; // 01001
    return buildCommand(_GROUP, addr, command, data);
}

bool groupOp2(uint8_t addr)
{
    // see accAux2Op2() for DOCSTRICT justification

    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
#ifdef DOCSTRICT
    uint8_t data = 0x0B; // 01011
#else
    uint8_t data = 0x0A; // 01010
#endif
    return buildCommand(_GROUP, addr, command, data);
}

bool groupOn(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x0; // 00
    uint8_t data = 0x0B; // 01011
    return buildCommand(_GROUP, addr, command, data);
}

bool groupClear(uint8_t addr)
{
    if(addr > 0x0F) return false; // 4-bit address
    uint8_t command = 0x1; // 01
    uint8_t data = 0x0C; // 01100
    return buildCommand(_GROUP, addr, command, data);
}


// System Commands
bool sysHalt(void)
{
    // 1111 1111 1111 1111
    uint8_t toTrain[3] = {0xFE, 0xFF, 0xFF};
    return ((send_serial(toTrain)) ? true : false);
}

bool sysNop(void)
{
    // 1111 1111 1000 0000
    uint8_t toTrain[3] = {0xFE, 0xFF, 0x80};
    return ((send_serial(toTrain)) ? true : false);
}

bool buildCommand(TARGET_TYPE target, uint_fast8_t address, uint_fast8_t command, uint_fast8_t data) {
    uint8_t toTrain[3] = {0};
    toTrain[0] = 0xFE;

    switch (target) {
        case SWITCH_C:
            toTrain[1] = (0b01 << 6) + (((address & 0x7F) >> 1) & 0x3F);
            break;
        case ROUTE:
            toTrain[1] = (0b1101 << 4) + (((address & 0x1F) >> 1) & 0x0F);
            break;
        case ENGINE:
            toTrain[1] = (0b00 << 6) + (((address & 0x7F) >> 1) & 0x3F);
            break;
        case TRAIN:
            toTrain[1] = (0b11001 << 3) + (((address & 0x0F) >> 1) & 0x07);
            break;
        case ACCESSORY:
            toTrain[1] = (0b10 << 6) + (((address & 0x7F) >> 1) & 0x3F);
            break;
        case _GROUP:
            toTrain[1] = (0b1100 << 4) + (((address & 0x0F) >> 1) & 0x07);
            break;
        default:
            printf("INVALID TARGET: %u\n", target);
            break;
    }

    toTrain[2] = ((address & 0x01) << 7) + ((command & 0x03) << 5) + (data & 0x1F);

    return ((send_serial(toTrain)) ? true : false);
}
