/***************************************************************************************************************************************/
/* !File Name : vehicle_control.h                                                                                                      */
/* !Description: Header file contains function prototypes, included libraries and ...                                                  */
/* !Author: Hussein El-Shamy                                                                                                           */
/* !Group: 80                                                                                                                          */
/* !Mentor: Mohamed Tarek                                                                                                              */
/***************************************************************************************************************************************/

// Include Libraries
#include <stdio.h>
#include <stdint.h>

// define new data types

typedef float float32;
typedef double float64;
#define TRUE 1;
#define FALSE -1;
//#define NULL (void*)0

// Bonus Requirement: Define Macro for using it with #if ... #endif
#define WITH_ENGINE_TEMP_CONTROLLER 1


// Enum Declaration

typedef enum {
	ON, OFF, Quit,
} States;

// Struct Declaration

typedef struct {
	States Vehicle_Engine;
	States Vehicle_AC;
	float32 Vehicle_Speed;
	float32 Room_Temperature;
	States Engine_Temperature_Controller_State;
	float32 Engine_Temperature;
} Vehicle;

// Functions Prototypes

void getEngineState(Vehicle *ptrVechile);

int8_t getSensorsSetMenu(Vehicle *ptrVechile);

int8_t getEngineOFF(Vehicle *ptrVechile);

int8_t readLight_ChangeSpeed(Vehicle *ptrVechile);

int8_t readTemperture_SetAC(Vehicle *ptrVechile);

int8_t readEngineTemperture_SetTempertureController(Vehicle *ptrVechile);

int8_t checkVehicleSpeed(Vehicle *ptrVechile);

void displayCurrentVehileState(Vehicle *ptrVechile);

/***************************************************************************************************************************************/
//                                                     END OF FILE                                                                     */                                                                                                             */
/***************************************************************************************************************************************/
