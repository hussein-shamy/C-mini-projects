#include"app.h"

ST_cardData_t cardUser = { 0 };
ST_terminalData_t termanalData = { 0 };
ST_transaction_t transactionData = { 0 };
ST_accountsDB_t *accountData = accountsDB;

void appStart(void) {

	char inputNum;
	int adminPassword;
	setMaxAmount(&termanalData, 5000.0);

	while (1) {
printf("###############################################\n");
		printf("Welcome to Bank Misr\n");
printf("###############################################\n");

		printf(
				"[1] to start the service\n[0] to Enter Control Panel (Administrator Password Required): ");

		scanf(" %c", &inputNum);

		switch (inputNum) {

		case '0':
			printf("Enter The Secret Administrator Password: ");
			scanf(" %d", &adminPassword);
			if (adminPassword == 1234) {
				char adminInput = 0;
				printf("[1] to set max amount of ATM\n[2] to turn off ATM\n");
				scanf(" %c", &adminInput);
				switch (adminInput) {
				case '1':
					float maxAmountOfATM = 0.0;
					printf("[1] Set max amount of ATM: \n");
					scanf("%f", &maxAmountOfATM);
					setMaxAmount(&termanalData, maxAmountOfATM);
					break;
				case '2':
					return;
					break;
				default:
					break;
				}
			}
			break;

		case '1':
			/*
			 *
			 *
			 */
			printf("\n[Card]\nPlease, Insert Your Card\n");

			printf("\nReading Bank Card ...\n\n");

			if (getCardHolderName(&cardUser)) {
				printf("WRONG_NAME\n");
				break;
			}

			if (getCardPAN(&cardUser)) {
				printf("WRONG_PAN\n");
				break;
			}

			if (getCardExpiryDate(&cardUser)) {
				printf("WRONG_EXP_DATE\n");
				break;
			}
			/*
			 *
			 *
			 *
			 */
			printf("\n[Terminal]\nChecking Bank Card ...\n\n");

			getTransactionDate(&termanalData);

			if (isCardExpired(&cardUser, &termanalData)) {
				printf("EXPIRED_CARD\n");
				break;
			}

			if (isValidCardPAN(&cardUser)) {
				printf("INVALID_CARD\n");
				break;
			}

			if (getTransactionAmount(&termanalData)) {
				printf("INVALID_AMOUNT\n");
				break;
			}

			if (isBelowMaxAmount(&termanalData)) {
				printf("EXCEED_MAX_AMOUNT\n");
				break;
			}
			/*
			 *
			 *
			 *
			 */
			printf("\n[Server]\nChecking Bank Account ...\n\n");

			if (isValidAccount(&cardUser, accountsDB)) {
				printf("ACCOUNT_NOT_FOUND\n");
				saveTransaction(&transactionData);
				break;
			}

			if (isBlockedAccount(accountData)) {
				printf("BLOCKED_ACCOUNT\n");
				break;
			}


			if (isAmountAvailable(&termanalData, accountData)) {
				printf("LOW_BALANCE\n");
				break;
			}


			int transactionFlag =0;

			transactionFlag= recieveTransactionData(&transactionData);

			if (transactionFlag == 3) {
				printf("FRAUD_CARD\n");
				break;
			}

			if (transactionFlag == 1) {
				printf("DECLINED_INSUFFECIENT_FUND\n");
				break;
			}

			if (transactionFlag == 2) {
				printf("DECLINED_STOLEN_CARD\n");
				break;
			}

			if (transactionFlag== 4) {
				printf("INTERNAL_SERVER_ERROR\n");
				break;
			}

			saveTransaction(&transactionData);

			listSavedTransactions();

			break;

		default:
			appStart();
			break;
		}
	}
	return;
}


