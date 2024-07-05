#include "server.h"

ST_accountsDB_t accountsDB[255] = { { 1000.0, RUNNING, "8989374615436851" }, {
		100000.0, BLOCKED, "5807007076043875" }, { 25000.0, RUNNING,
				"672583219178930829" }, { 215.70, RUNNING, "050692952567371950" }, {
						15.0, BLOCKED, "311468905239981687" } };

ST_transaction_t transactionsDB[255] = { 0 };

EN_transState_t recieveTransactionData(ST_transaction_t *transData) {
/*
	strcpy((char*) transData->cardHolderData.cardExpirationDate,
			(char*) cardUser.cardExpirationDate);

	strcpy((char*) transData->cardHolderData.cardHolderName,
			(char*) cardUser.cardHolderName);

	strcpy((char*) transData->cardHolderData.primaryAccountNumber,
			(char*) cardUser.primaryAccountNumber);

	transData->terminalData.maxTransAmount = termanalData.maxTransAmount;

	transData->terminalData.transAmount = termanalData.transAmount;
*/
	strcpy((char*) transData->terminalData.transactionDate,
			(char*) termanalData.transactionDate);

	int accountIndex = -1;  //Initialized NOT FOUND

	//Linear Search
	for (int i = 0; i < 255; i++) {
		if (!(strcmp(
				(const char*) transData->cardHolderData.primaryAccountNumber,
				(const char*) accountsDB[i].primaryAccountNumber))) {
			accountIndex = i;
			break; //Break looping with the account index
		}
		//after all iterations without finding the account the index will -1
	}

	if (accountIndex == -1) {
		return FRAUD_CARD;
	}


	if (transData->terminalData.transAmount
			> accountsDB[accountIndex].balance) {
		return DECLINED_INSUFFECIENT_FUND;
	}

	if (accountsDB[accountIndex].state == BLOCKED) {
		return DECLINED_STOLEN_CARD;
	}

	if (transData->transactionSequenceNumber > 255) {
		return INTERNAL_SERVER_ERROR;
	}

	/*It will update the database with the new balance*/
	accountsDB[accountIndex].balance -= transData->terminalData.transAmount;

	return APPROVED;

}

void recieveTransactionDataTest(void) {

	ST_transaction_t testcase ;

	printf(
			"Tester Name: Hussein El-Shamy\nFunction Name: recieveTransactionData\n");

	strcpy((char*) testcase.cardHolderData.primaryAccountNumber,
			"8989374615436000"); //NOT FOUND

	printf(
			"\nTest Case 1:\nInput Data: 8989374615436000(NOT Found)\nExpected Result: 3\n");
	printf("Actual Result: %d\n", recieveTransactionData(&testcase));

	strcpy((char*) testcase.cardHolderData.primaryAccountNumber,
			"8989374615436851"); //FOUND RUNNING
	testcase.terminalData.transAmount = 2500; //Exceed Max

	printf(
			"\nTest Case 2:\nInput Data: 2500 (Exceed Max)\nExpected Result: 1\n");
	printf("Actual Result: %d\n", recieveTransactionData(&testcase));

	strcpy((char*) testcase.cardHolderData.primaryAccountNumber,
			"5807007076043875"); //FOUND BLOCKED
	testcase.terminalData.transAmount = 500;

	printf(
			"\nTest Case 3:\nInput Data: 5807007076043875(FOUND BLOCKED)\nExpected Result: 2\n");
	printf("Actual Result: %d\n", recieveTransactionData(&testcase));

	strcpy((char*) testcase.cardHolderData.primaryAccountNumber,
			"8989374615436851"); //FOUND RUNNING
	testcase.terminalData.transAmount = 20;
	testcase.transactionSequenceNumber = 300;

	printf(
			"\nTest Case 4:\nInput Data: (INTERNAL_SERVER_ERROR > 255)\nExpected Result: 4\n");
	printf("Actual Result: %d\n", recieveTransactionData(&testcase));

	strcpy((char*) testcase.cardHolderData.primaryAccountNumber,
			"8989374615436851"); //FOUND RUNNING
	testcase.terminalData.transAmount = 20;
	testcase.transactionSequenceNumber = 1;

	printf(
			"\nTest Case 5:\nInput Data: (8989374615436851 1000$-20$)\nExpected Result: 980$\n");
	recieveTransactionData(&testcase);
	printf("Actual Result: %f\n", accountsDB[0].balance);
}

EN_serverError_t isValidAccount(ST_cardData_t *cardData,
		ST_accountsDB_t *accountRefrence) {

	accountRefrence = accountsDB;
	int accountIndex = -1;
	for (int i = 0; i < 255; i++) {

		if (!(strcmp((const char*) cardData->primaryAccountNumber,
				(const char*) accountRefrence[i].primaryAccountNumber))) {
			accountIndex = i;
			break; //Break looping with the account index
		}
		//after all iterations without finding the account the index will -1
	}

	if (accountIndex == -1) {
		accountRefrence = NULL;
		return ACCOUNT_NOT_FOUND;
	}

	accountRefrence = accountRefrence + accountIndex;
	return SERVER_OK;
}

void isValidAccountTest(void) {

	ST_cardData_t testcase1;
	ST_accountsDB_t testcase2;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: isValidAccount\n");

	strcpy((char*) testcase1.primaryAccountNumber, "8989374615436851");
	printf(
			"\nTest Case 1:\nInput Data: 8989374615436851(Vaild)\nExpected Result: 0\n");
	printf("Actual Result: %d\n", isValidAccount(&testcase1, &testcase2));

	strcpy((char*) testcase1.primaryAccountNumber, "8989374615436000");
	printf(
			"\nTest Case 2:\nInput Data: 8989374615436000(NOT Vaild)\nExpected Result: 3\n");
	printf("Actual Result: %d\n", isValidAccount(&testcase1, &testcase2));
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence) {

	if (accountRefrence->state == BLOCKED) {
		return BLOCKED_ACCOUNT;
	}
	return SERVER_OK;
}

void isBlockedAccountTest(void) {

	ST_accountsDB_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: isBlockedAccount\n");

	testcase.state = RUNNING;
	printf("\nTest Case 1:\nInput Data: (Running)\nExpected Result: 0\n");
	printf("Actual Result: %d\n", isBlockedAccount(&testcase));

	testcase.state = BLOCKED;
	printf("\nTest Case 2:\nInput Data: (Blocked)\nExpected Result: 5\n");
	printf("Actual Result: %d\n", isBlockedAccount(&testcase));

}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,
		ST_accountsDB_t *accountRefrence) {
	if (termData->transAmount > accountRefrence->balance) {
		return LOW_BALANCE;
	}
	return SERVER_OK;
}

void isAmountAvailableTest(void) {

	ST_accountsDB_t testcase1;
	testcase1.balance = 2500;

	ST_terminalData_t testcase2;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: isAmountAvailable\n");

	testcase2.transAmount = 2000;
	printf("\nTest Case 1:\nInput Data: 2000(2500)\nExpected Result: 0\n");
	printf("Actual Result: %d\n", isAmountAvailable(&testcase2, &testcase1));

	testcase2.transAmount = 3000;
	printf("\nTest Case 2:\nInput Data: 3000(2500)\nExpected Result: 4\n");
	printf("Actual Result: %d\n", isAmountAvailable(&testcase2, &testcase1));

}

EN_serverError_t saveTransaction(ST_transaction_t *transData) {

	uint32_t i = 0;

	for (; i < sizeof(transactionsDB) / sizeof(transactionsDB[0]); i++) {
		if (transactionsDB[i].transactionSequenceNumber != i) {
			transData->transactionSequenceNumber = i; // Found a gap, return the next number
			break;
		}
	}
	if ((sizeof(transactionsDB) / sizeof(transactionsDB[0])) + 1 == i) {
		transData->transactionSequenceNumber = sizeof(transactionsDB)
						/ sizeof(transactionsDB[0]); // All sequence numbers exist, return the next index
	}

	//printf("\n\n\n%d\n\n\n",transData->transactionSequenceNumber);//1

	transactionsDB[transData->transactionSequenceNumber] = *transData;

	transactionsDB[transData->transactionSequenceNumber].transactionSequenceNumber =
			transData->transactionSequenceNumber;

	strcpy(
			(char*) transactionsDB[transData->transactionSequenceNumber].terminalData.transactionDate,
			(char*) transData->terminalData.transactionDate);

	transactionsDB[transData->transactionSequenceNumber].terminalData.transAmount =
			transData->terminalData.transAmount;

	transactionsDB[transData->transactionSequenceNumber].terminalData.maxTransAmount =
			transData->terminalData.maxTransAmount;

	strcpy(
			(char*) transactionsDB[transData->transactionSequenceNumber].cardHolderData.cardHolderName,
			(char*) transData->cardHolderData.cardHolderName);

	strcpy(
			(char*) transactionsDB[transData->transactionSequenceNumber].cardHolderData.cardExpirationDate,
			(char*) transData->cardHolderData.cardExpirationDate);

	strcpy(
			(char*) transactionsDB[transData->transactionSequenceNumber].cardHolderData.primaryAccountNumber,
			(char*) transData->cardHolderData.primaryAccountNumber);

	//	transactionsDB[0] = *transData;
	return SERVER_OK;
}

void saveTransactionTest(void) {

	ST_transaction_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: saveTransaction\n");

	strcpy((char*) testcase.terminalData.transactionDate, "28/08/2024");
	testcase.terminalData.transAmount = 1000;
	testcase.terminalData.maxTransAmount = 10000;
	strcpy((char*) testcase.cardHolderData.cardHolderName, "Husssein Sobhy");
	strcpy((char*) testcase.cardHolderData.cardExpirationDate, "10/22");
	strcpy((char*) testcase.cardHolderData.primaryAccountNumber,
			"311468905239981687");

	printf("\nTest Case 1:\nInput Data: Many\nExpected Result: 0\n");
	saveTransaction(&testcase);
	printf("Actual Result: %d\n", testcase.transactionSequenceNumber - 1);

	strcpy((char*) testcase.terminalData.transactionDate, "28/08/2024");
	testcase.terminalData.transAmount = 1000;
	testcase.terminalData.maxTransAmount = 10000;
	strcpy((char*) testcase.cardHolderData.cardHolderName, "Husssein Sobhy");
	strcpy((char*) testcase.cardHolderData.cardExpirationDate, "10/22");
	strcpy((char*) testcase.cardHolderData.primaryAccountNumber,
			"311468905239981687");

	printf("\nTest Case 2:\nInput Data: Many\nExpected Result: 1\n");
	saveTransaction(&testcase);
	printf("Actual Result: %d\n", testcase.transactionSequenceNumber - 1);

}

void listSavedTransactions(void) {

	uint32_t i = 0;
	uint32_t NextSequenceNumber = 0;

	for (; i < sizeof(transactionsDB) / sizeof(transactionsDB[0]); i++) {
		if (transactionsDB[i].transactionSequenceNumber != i) {
			NextSequenceNumber = i; // Found a gap, return the next number
			break;
		}
	}
	if ((sizeof(transactionsDB) / sizeof(transactionsDB[0])) + 1 == i) {
		NextSequenceNumber = sizeof(transactionsDB) / sizeof(transactionsDB[0]); // All sequence numbers exist, return the next index
	}

	for (int i = 1; i <= NextSequenceNumber ; i++) {
		printf("#######################################\n");
		printf("Transaction Sequence: %d\n",
				transactionsDB[i].transactionSequenceNumber);
		printf("Transaction Date: %s\n",
				transactionsDB[i].terminalData.transactionDate);
		printf("Transaction Amount: %f\n",
				transactionsDB[i].terminalData.transAmount);
		printf("Transaction State: ");
		if (transactionsDB[i].transState) {
			printf("Declined\n");
		} else {
			printf("Approved\n");
		}
		printf("Terminal Max Amount: %f\n",
				transactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: %s\n",
				transactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN: %s\n",
				transactionsDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration: %s\n",
				transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("#######################################\n");
	}
}

void listSavedTransactionsTest(void) {

	printf(
			"Tester Name: Hussein El-Shamy\nFunction Name: listSavedTransactions\n");

	printf("\nTest Case 1:\nInput Data: Void\nExpected Result: Table\n");
	listSavedTransactions();
}
