#include"terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {

	const char *compilationDate = __DATE__;
	char str[4];
	char month[2];

	for (int i = 0; i < 3; i++) {
		str[i] = *(compilationDate + i);
	}
	str[3] = '\0';

	if (strcmp(str, "Jan") == 0) {
		month[0] = '0';
		month[1] = '1';
	} else if (strcmp(str, "Feb") == 0) {
		month[0] = '0';
		month[1] = '2';
	} else if (strcmp(str, "Mar") == 0) {
		month[0] = '0';
		month[1] = '3';
	} else if (strcmp(str, "Apr") == 0) {
		month[0] = '0';
		month[1] = '4';
	} else if (strcmp(str, "May") == 0) {
		month[0] = '0';
		month[1] = '5';
	} else if (strcmp(str, "Jun") == 0) {
		month[0] = '0';
		month[1] = '6';
	} else if (strcmp(str, "Jul") == 0) {
		month[0] = '0';
		month[1] = '7';
	} else if (strcmp(str, "Aug") == 0) {
		month[0] = '0';
		month[1] = '8';
	} else if (strcmp(str, "Sep") == 0) {
		month[0] = '0';
		month[1] = '9';
	} else if (strcmp(str, "Oct") == 0) {
		month[0] = '1';
		month[1] = '0';
	} else if (strcmp(str, "Nov") == 0) {
		month[0] = '1';
		month[1] = '1';
	} else if (strcmp(str, "Dec") == 0) {
		month[0] = '1';
		month[1] = '2';
	}

	termData->transactionDate[0] = compilationDate[4];
	termData->transactionDate[1] = compilationDate[5];
	termData->transactionDate[2] = '/';
	termData->transactionDate[3] = month[0];
	termData->transactionDate[4] = month[1];
	termData->transactionDate[5] = '/';
	termData->transactionDate[6] = compilationDate[7];
	termData->transactionDate[7] = compilationDate[8];
	termData->transactionDate[8] = compilationDate[9];
	termData->transactionDate[9] = compilationDate[10];
	termData->transactionDate[10] = '\0';

	return TERMINAL_OK;
}

void getTransactionDateTest(void) {

	ST_terminalData_t testcase;

	printf(
			"Tester Name: Hussein El-Shamy\nFunction Name: getTransactionDate\n");

	printf("\nTest Case 1:\nInput Data: System Date \nExpected Result: 0\n");
	printf("Actual Result: %d\n", getTransactionDate(&testcase));
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData,
		ST_terminalData_t *termData) {

	// Extract card expiration month and year
	int cardExpMonth = (cardData->cardExpirationDate[0] - '0') * 10
			+ (cardData->cardExpirationDate[1] - '0');
	int cardExpYear = (cardData->cardExpirationDate[3] - '0') * 10
			+ (cardData->cardExpirationDate[4] - '0');

	// Extract transaction month, and year
	int transMonth = (termData->transactionDate[3] - '0') * 10
			+ (termData->transactionDate[4] - '0');
	int transYear = (termData->transactionDate[6] - '0') * 1000
			+ (termData->transactionDate[7] - '0') * 100
			+ (termData->transactionDate[8] - '0') * 10
			+ (termData->transactionDate[9] - '0');

	// Check if card has expired
	if (cardExpYear < (transYear % 100)
			|| (cardExpYear == (transYear % 100) && cardExpMonth < transMonth)) {
		return EXPIRED_CARD;
	}

	return TERMINAL_OK;

}

void isCardExpriedTest(void) {

	ST_cardData_t testcase;
	ST_terminalData_t testcase_;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: isCardExpired\n");

	printf("\nTest Case 1:\nInput Data: 08/25\nExpected Result: 0\n");
	strcpy((char*) testcase.cardExpirationDate, "08/25");
	strcpy((char*) testcase_.transactionDate, "23/08/2023");

	printf("Actual Result: %d\n", isCardExpired(&testcase, &testcase_)); //2

	printf("\nTest Case 2:\nInput Data: 08/23\nExpected Result: 0\n");

	strcpy((char*) testcase.cardExpirationDate, "08/23");
	strcpy((char*) testcase_.transactionDate, "23/08/2023");

	printf("Actual Result: %d\n", isCardExpired(&testcase, &testcase_)); //2

	printf("\nTest Case 3:\nInput Data: 08/20\nExpected Result: 2\n");
	strcpy((char*) testcase.cardExpirationDate, "08/20");
	strcpy((char*) testcase_.transactionDate, "23/08/2023");
	printf("Actual Result: %d\n", isCardExpired(&testcase, &testcase_)); //2

}

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {

	printf("Please, Enter the transaction amount: ");

	scanf(" %f", &termData->transAmount);

	if (termData->transAmount == 0 || termData->transAmount < 0) {
		return INVALID_AMOUNT;
	}
	return TERMINAL_OK;
}

void getTransactionAmountTest(void) {

	ST_terminalData_t testcase;

	printf(
			"Tester Name: Hussein El-Shamy\nFunction Name: getTransactionAmount\n");

	printf("\nTest Case 1:\nInput Data: 0\nExpected Result: 4\n");
	printf("Actual Result: %d\n", getTransactionAmount(&testcase));

	printf("\nTest Case 1:\nInput Data: -200\nExpected Result: 4\n");
	printf("Actual Result: %d\n", getTransactionAmount(&testcase));

	printf("\nTest Case 1:\nInput Data: 200\nExpected Result: 0\n");
	printf("Actual Result: %d\n", getTransactionAmount(&testcase));

}

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {

	if (termData->transAmount > termData->maxTransAmount) {

		return EXCEED_MAX_AMOUNT;
	}
	return TERMINAL_OK;
}

void isBelowMaxAmountTest(void) {

	ST_terminalData_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: isBelowMaxAmount\n");

	testcase.maxTransAmount = 2000;
	testcase.transAmount = 1500;
	printf("\nTest Case 1:\nInput Data: 1500(2000)\nExpected Result: 0\n");
	printf("Actual Result: %d\n", isBelowMaxAmount(&testcase));

	testcase.maxTransAmount = 2000;
	testcase.transAmount = 2500;
	printf("\nTest Case 2:\nInput Data: 2500(2000)\nExpected Result: 5\n");
	printf("Actual Result: %d\n", isBelowMaxAmount(&testcase));

}

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount) {

	if (maxAmount < 0 || maxAmount == 0) {
		return INVALID_MAX_AMOUNT;
	}

	termData->maxTransAmount = maxAmount;

	return TERMINAL_OK;
}

void setMaxAmountTest(void) {

	ST_terminalData_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: setMaxAmount\n");

	printf("\nTest Case 1:\nInput Data: 0\nExpected Result: 6\n");
	printf("Actual Result: %d\n", setMaxAmount(&testcase, 0));

	printf("\nTest Case 2:\nInput Data: -200\nExpected Result: 6\n");
	printf("Actual Result: %d\n", setMaxAmount(&testcase, -200));

	printf("\nTest Case 3:\nInput Data: 2000\nExpected Result: 0\n");
	printf("Actual Result: %d\n", setMaxAmount(&testcase, 2000));

}

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData) {

	int len = strlen((const char*) cardData->primaryAccountNumber);
	int sum = 0;
	char alternate = 0;

	for (int i = len - 1; i >= 0; i--) {
		int digit = cardData->primaryAccountNumber[i] - '0';

		if (alternate) {
			digit *= 2;
			if (digit > 9) {
				digit = (digit % 10) + 1;
			}
		}

		sum += digit;
		alternate = !alternate;
	}

	if (sum % 10 == 0) {
		return TERMINAL_OK;
	} else {
		return INVALID_CARD;
	}
}

void isValidCardPANTest(void) {

	ST_cardData_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: setMaxAmount\n");

	strcpy((char*) testcase.primaryAccountNumber, "537700823307898873");
	printf(
			"\nTest Case 1:\nInput Data: 537700823307898873\nExpected Result: 0\n");
	printf("Actual Result: %d\n", isValidCardPAN(&testcase));

	strcpy((char*) testcase.primaryAccountNumber, "537700821007898873");
	printf(
			"\nTest Case 2:\nInput Data: 537700821007898873\nExpected Result: 3\n");
	printf("Actual Result: %d\n", isValidCardPAN(&testcase));

}

