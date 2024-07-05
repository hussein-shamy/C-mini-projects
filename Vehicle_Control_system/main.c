/***************************************************************************************************************************************/
/* !File Name : main.c                                                                                                                 */
/* !Description: main file to run program                                                                                              */
/* !Author: Hussein El-Shamy                                                                                                           */
/* !Group: 80                                                                                                                          */
/* !Mentor: Mohamed Tarek                                                                                                              */
/***************************************************************************************************************************************/

#include"vehicle_control.h"

int main(void) {

	// to clear buffers to make printf() function work correctly
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	// to create array of struct (Vehicle)
	Vehicle volkswagen_Golf[10] = { { ON, OFF, 0, 35, OFF, 90 }, { OFF, ON, 50,
			70, ON, 150 }, { Quit, OFF, 30, 0, OFF, 80 },
			{ OFF, ON, 0, 0, ON, 0 }
	// Add more elements here
	};

	// to point to any struct in the array as I need (More Flexibility)
	Vehicle *ptrStructVechile = &volkswagen_Golf[0];

	// to get the menus of system as required

	// to get first menu
	// if select Engine ON the state will change to ON and the the another part of code will execute (the condition of while will be true)
	// if select Engine OFF the function will call itself (recursion)
	// if select Quit System the function will change state to OFF and the remaining lines of code will not execute (the condition of while will be false)
	getEngineState(ptrStructVechile);

	//to check system state
	// if ON it will be true
	// if Quit it will be false
	while (ptrStructVechile->Vehicle_Engine != Quit) {

		// second menu to choose what the user need
		switch (getSensorsSetMenu(ptrStructVechile)) {

		// if the user select turn off
		case '1':

			// this function will make the state of engine off
			getEngineOFF(ptrStructVechile);

			// this function will display the first menu again
			// if select Engine ON the state will change to ON and the the another part of code will execute (the condition of while will be true)
			// if select Engine OFF the function will call itself (recursion)
			// if select Quit System the function will change state to OFF and the remaining lines of code will not execute (the condition of while will be false)
			getEngineState(ptrStructVechile);
			break;

		case '2':

			// this function to change the speed after read the light color from user (act as light sensor)
			readLight_ChangeSpeed(ptrStructVechile);
			// this function to check if the speed equal 30 Km/Hr
			checkVehicleSpeed(ptrStructVechile);
			// this function to display the vehicle states
			displayCurrentVehileState(ptrStructVechile);
			break;

		case '3':

			// this function to change the AC state after read the room temperature from user (act as temperature sensor)
			readTemperture_SetAC(ptrStructVechile);
			// this function to check if the speed equal 30 Km/Hr
			checkVehicleSpeed(ptrStructVechile);
			// this function to display the vehicle states
			displayCurrentVehileState(ptrStructVechile);
			break;

		case '4':

#if (WITH_ENGINE_TEMP_CONTROLLER)
			// this function to Set Temperture Controller state after read the engine temperature from user (act as temperature sensor)
			readEngineTemperture_SetTempertureController(ptrStructVechile);
#endif
			// this function to check if the speed equal 30 Km/Hr
			checkVehicleSpeed(ptrStructVechile);
			// this function to display the vehicle states
			displayCurrentVehileState(ptrStructVechile);
			break;

		default:

			printf("InVaild Input\n");
		}

	}

	return 0;
}

/***************************************************************************************************************************************/
//                                                     END OF FILE                                                                     */                                                                                                             */
/***************************************************************************************************************************************/
