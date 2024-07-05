/***************************************************************************************************************************************/
/* !File Name : vehicle_control.c                                                                                                      */
/* !Description: Source file contains function implementation                                                                          */
/* !Author: Hussein El-Shamy                                                                                                           */
/* !Group: 80                                                                                                                          */
/* !Mentor: Mohamed Tarek                                                                                                              */
/***************************************************************************************************************************************/

#include"vehicle_control.h"

/***************************************************************************************************************************************/
// !Function Name : getEngineState
// !Description: This function takes a pointer to struct (Vehicle) and change engine state                                                                          */
// !Parameters:
//     - ptrVechile: Pointer to struct (vehicle).
// !Returns: no thing
/***************************************************************************************************************************************/

void getEngineState(Vehicle *ptrVechile) {

	// to print welcome menu to user
	int8_t userInput = 0;
	printf("\n[1] Turn ON the vehicle engine\n");
	printf("[2] Turn OFF the vehicle engine\n");
	printf("[3] Quit the system\n");
	printf("Please, Enter The Number: ");

	// to Get desired operation from user
	scanf(" %c", &userInput);

	// to switch and change system states
	switch (userInput) {
	case '1':
		printf("\nTurning ON the vehicle engine .......\n\n");
		ptrVechile->Vehicle_Engine = ON;
		return;
		break;
	case '2':
		printf("\nTurning OFF the vehicle engine ......\n\n");
		ptrVechile->Vehicle_Engine = OFF;
		break;
	case '3':
		printf("\nQuitting the system .......");
		ptrVechile->Vehicle_Engine = Quit;
		return;
		break;
	default:
		// In case the user enters number where is not in list (1,2,3)
		printf("Invalid Input\n");
		// [recursion] due to the input is not invalid
		getEngineState(ptrVechile);
		break;
	}

	// to call function itself (recursion) due to the case of [OFF -> ask user again]
	while (ptrVechile->Vehicle_Engine == OFF) {
		getEngineState(ptrVechile);
	}

	return;
}

/***************************************************************************************************************************************/
// !Function Name : getSensorsSetMenu
// !Description: This function takes a pointer to struct (Vehicle) and get input from user and return this input                                                                          */
// !Parameters:
//    - ptrVechile: Pointer to struct (vehicle).
// !Returns: userInput as a int8_t.
/***************************************************************************************************************************************/

int8_t getSensorsSetMenu(Vehicle *ptrVechile) {

	// to exit the function if the engine state is OFF or QUIT
	if (ptrVechile->Vehicle_Engine != ON) {
		return FALSE;
	}

	// to display Sensors Set Menu
	int8_t userInput = 0;
	printf("[1] Turn off the engine\n");
	printf("[2] Set the traffic light color\n");
	printf("[3] Set the room temperature (Temperature Sensor)\n");
#if (WITH_ENGINE_TEMP_CONTROLLER)
	printf("[4] Set the engine temperature (Engine Temperature Sensor)\n");
#endif
	printf("Please, Enter The Number: ");

	// to take an input from user
	scanf(" %c", &userInput);

	// to check which's the input in valid or not
	if (userInput < 1 && userInput > 4) {
		printf("Invaild Input\n");
		// [recursion] due to the input is not invalid
		getSensorsSetMenu(ptrVechile);
	}

	// to return the input that taken from user
	return userInput;
}

/***************************************************************************************************************************************/
// !Function Name : getEngineOFF
// !Description:
// !Parameters:
//    -
// !Returns:
/***************************************************************************************************************************************/

int8_t getEngineOFF(Vehicle *ptrVechile) {
	// to exit the function if the engine state is ON or QUIT
	if (ptrVechile->Vehicle_Engine != OFF) {
		return FALSE;
	}

	// to change state into OFF
	ptrVechile->Vehicle_Engine = OFF;

	// to return that action done
	return TRUE;
}

/***************************************************************************************************************************************/
// !Function Name : readLightChangeSpeed
// !Description:
// !Parameters:
//    -
// !Returns:
/***************************************************************************************************************************************/

int8_t readLight_ChangeSpeed(Vehicle *ptrVechile) {
	int8_t lightSensorInput;
	printf("Please, Enter The Color As a sensor :) {'G','O','R'} : ");
	scanf(" %c", &lightSensorInput);
	switch (lightSensorInput) {
	case 'G':
	case 'g':
		printf("setting vehicle speed to 100 km/hr\n");
		ptrVechile->Vehicle_Speed = 100;
		break;
	case 'O':
	case 'o':
		printf("setting vehicle speed to 30 km/hr\n");
		ptrVechile->Vehicle_Speed = 30;
		break;
	case 'R':
	case 'r':
		printf("setting vehicle speed to 0 km/hr\n");
		ptrVechile->Vehicle_Speed = 0;
		break;
	default:
		// In case the user enters number where is not in list (1,2,3)
		printf("Invalid Input\n");
		// [recursion] due to the input is not invalid
		readLight_ChangeSpeed(ptrVechile);
		break;
	}
	return TRUE;
}

/***************************************************************************************************************************************/
// !Function Name : readTemperture_SetAC
// !Description:
// !Parameters:
//    -
// !Returns:
/***************************************************************************************************************************************/

int8_t readTemperture_SetAC(Vehicle *ptrVechile) {
	printf("Please, Enter The Room_Temperature As a sensor :) : ");
	scanf(" %f", &ptrVechile->Room_Temperature);

	if (ptrVechile->Room_Temperature < 10) {
		ptrVechile->Vehicle_AC = ON;
		ptrVechile->Room_Temperature = 20;
	} else if (ptrVechile->Room_Temperature > 30) {
		ptrVechile->Vehicle_AC = ON;
		ptrVechile->Room_Temperature = 20;
	} else {
		ptrVechile->Vehicle_AC = OFF;
	}
	return TRUE;
}

/***************************************************************************************************************************************/
// !Function Name : readEngineTemperture_SetTempertureController
// !Description:
// !Parameters:
//    -
// !Returns:
/***************************************************************************************************************************************/
#if (WITH_ENGINE_TEMP_CONTROLLER)
int8_t readEngineTemperture_SetTempertureController(Vehicle *ptrVechile) {
	printf("Please, Enter The Engine_Temperature As a sensor :) : ");
	scanf(" %f", &ptrVechile->Engine_Temperature);

	if (ptrVechile->Engine_Temperature < 100) {
		ptrVechile->Engine_Temperature_Controller_State = ON;
		ptrVechile->Engine_Temperature = 125;
	} else if (ptrVechile->Engine_Temperature > 150) {
		ptrVechile->Engine_Temperature_Controller_State = ON;
		ptrVechile->Engine_Temperature = 125;
	} else {
		ptrVechile->Engine_Temperature_Controller_State = OFF;
	}

	return TRUE;

}
#endif

/***************************************************************************************************************************************/
// !Function Name : checkVehicleSpeed
// !Description:
// !Parameters:
//    -
// !Returns:
/***************************************************************************************************************************************/

int8_t checkVehicleSpeed(Vehicle *ptrVechile) {

	if (ptrVechile->Vehicle_Speed != 30) {
		return FALSE;
	}

	if (ptrVechile->Vehicle_AC == OFF) {
		ptrVechile->Vehicle_AC = ON;
		ptrVechile->Room_Temperature = ptrVechile->Room_Temperature * (5 / 4)
						+ 1;
	}
#if (WITH_ENGINE_TEMP_CONTROLLER)
	if (ptrVechile->Engine_Temperature_Controller_State == OFF) {
		ptrVechile->Engine_Temperature_Controller_State = ON;
		ptrVechile->Room_Temperature = ptrVechile->Room_Temperature * (5 / 4)
						+ 1;
	}
#endif

	return TRUE;
}

/***************************************************************************************************************************************/
// !Function Name : displayCurrentVehileState
// !Description:
// !Parameters:
//    -
// !Returns:
/***************************************************************************************************************************************/

void displayCurrentVehileState(Vehicle *ptrVechile) {

	printf("\n********************************************************\n");
	printf("	        Current Vehicle State\n");
	printf("********************************************************\n");

	if (ptrVechile->Vehicle_Engine == ON) {
		printf("\n[1] Engine state: ON\n\n");
	} else {
		printf("[2] Engine state: OFF\n\n");
	}

	if (ptrVechile->Vehicle_AC == ON) {
		printf("[2] AC: ON\n\n");
	} else {
		printf("[2] AC: OFF\n\n");
	}

	printf("[3] Vehicle Speed: %f Km/Hr \n\n", ptrVechile->Vehicle_Speed);

	printf("[4] Room Temperature: %f C\n\n", ptrVechile->Room_Temperature);

#if (WITH_ENGINE_TEMP_CONTROLLER)
	if (ptrVechile->Engine_Temperature_Controller_State == ON) {
		printf("[5] Engine Temperature Controller State: ON\n\n");
	} else {
		printf("[5] Engine Temperature Controller State: OFF\n\n");
	}

	printf("[6] Engine Temperature: %f C\n\n", ptrVechile->Engine_Temperature);
#endif

	printf("********************************************************\n");
}

/***************************************************************************************************************************************/
//                                                     END OF FILE                                                                     */                                                                                                             */
/***************************************************************************************************************************************/
