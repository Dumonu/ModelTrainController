#ifndef COMMAND_H_20190917_111805
#define COMMAND_H_20190917_111805

#include <stdint.h>

typedef uint_fast8_t bool;
#define true 1
#define false 0

// Switch Commands
bool switchThrowThrough(uint8_t addr);
bool switchThrowOut(uint8_t addr);
bool switchSetAddr(uint8_t addr); // I'm not sure what this command accomplishes
bool switchAssignToRouteThrough(uint8_t addr, uint8_t rtaddr);
bool switchAssignToRouteOut(uint8_t addr, uint8_t rtaddr);

// Route Commands
bool routeThrow(uint8_t addr);
bool routeClear(uint8_t addr);

// Engine Commands
bool engineFwdDir(uint8_t addr);
bool engineToggleDir(uint8_t addr);
bool engineRevDir(uint8_t addr);
bool engineBoost(uint8_t addr);
bool engineBrake(uint8_t addr);
bool engineOpenFCoupler(uint8_t addr);
bool engineOpenRCoupler(uint8_t addr);
bool engineBlowHorn1(uint8_t addr);
bool engineRingBell(uint8_t addr);
bool engineLetoffSound(uint8_t addr);
bool engineBlowHorn2(uint8_t addr);
bool engineAux1Off(uint8_t addr);
bool engineAux1Op1(uint8_t addr);
bool engineAux1Op2(uint8_t addr);
bool engineAux1On(uint8_t addr);
bool engineAux2Off(uint8_t addr);
bool engineAux2Op1(uint8_t addr);
bool engineAux2Op2(uint8_t addr);
bool engineAux2On(uint8_t addr);
bool engineNumeric(uint8_t addr, uint8_t command);

// Engine Extensions
bool engineAssignToTrain(uint8_t addr, uint8_t traddr);
bool engineAssignSUFwdDir(uint8_t addr); // Single Unit
bool engineAssignSURevDir(uint8_t addr);
bool engineAssignHUFwdDir(uint8_t addr); // Head-end Unit
bool engineAssignHURevDir(uint8_t addr);
bool engineAssignMUFwdDir(uint8_t addr); // Middle Unit
bool engineAssignMURevDir(uint8_t addr);
bool engineAssignRUFwdDir(uint8_t addr); // Rear Unit
bool engineAssignRURevDir(uint8_t addr);
bool engineMomentumLow(uint8_t addr);
bool engineMomentumMedium(uint8_t addr);
bool engineMomentumHigh(uint8_t addr);
bool engineSetAddr(uint8_t addr); // Not sure what this does either

// Engine Speed Commands
bool engineSetAbsSpeed(uint8_t addr, uint8_t speed);
bool engineSetRelSpeed(uint8_t addr, int8_t relSpeed); // relSpeed in [-5, 5]

// Train Commands
bool trainFwdDir(uint8_t addr);
bool trainToggleDir(uint8_t addr);
bool trainRevDir(uint8_t addr);
bool trainBoost(uint8_t addr);
bool trainBrake(uint8_t addr);
bool trainOpenFCoupler(uint8_t addr);
bool trainOpenRCoupler(uint8_t addr);
bool trainBlowHorn1(uint8_t addr);
bool trainRingBell(uint8_t addr);
bool trainLetoffSound(uint8_t addr);
bool trainBlowHorn2(uint8_t addr);
bool trainAux1Off(uint8_t addr);
bool trainAux1Op1(uint8_t addr);
bool trainAux1Op2(uint8_t addr);
bool trainAux1On(uint8_t addr);
bool trainAux2Off(uint8_t addr);
bool trainAux2Op1(uint8_t addr);
bool trainAux2Op2(uint8_t addr);
bool trainAux2On(uint8_t addr);
bool trainNumeric(uint8_t addr, uint8_t command);

// Train Extensions
bool trainMomentumLow(uint8_t addr);
bool trainMomentumMedium(uint8_t addr);
bool trainMomentumHigh(uint8_t addr);
bool trainSetAddr(uint8_t addr); // Not sure what this does either
bool trainClearLashup(uint8_t addr); // probably removes all engines from this train

// Train Speed Commands
bool trainSetAbsSpeed(uint8_t addr, uint8_t speed);
bool trainSetRelSpeed(uint8_t addr, int8_t relSpeed); // relSpeed in [-5, 5]

// Accessory Commands
bool accAux1Off(uint8_t addr);
bool accAux1Op1(uint8_t addr);
bool accAux1Op2(uint8_t addr);
bool accAux1On(uint8_t addr);
bool accAux2Off(uint8_t addr);
bool accAux2Op1(uint8_t addr);
bool accAux2Op2(uint8_t addr);
bool accAux2On(uint8_t addr);
bool accNumeric(uint8_t addr, uint8_t command);

// Accessory Extensions
bool accAllOff(uint8_t addr);
bool accAllOn(uint8_t addr);
bool accSetAddr(uint8_t addr);
bool accAssignAux1ToGroup(uint8_t addr, uint8_t graddr);
bool accAssignAux2ToGroup(uint8_t addr, uint8_t graddr);

// Group Commands
bool groupOff(uint8_t addr);
bool groupOp1(uint8_t addr);
bool groupOp2(uint8_t addr);
bool groupOn(uint8_t addr);
bool groupClear(uint8_t addr);

// System Commands
bool sysHalt(void);
bool sysNop(void);

#endif /* COMMAND_H_20190917_111805 */
