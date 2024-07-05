#include"card.h"

ST_cardData_t cardData;

EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
	printf("Please, Enter the  cardholder's name\n");
	scanf(" %[^\n]", cardData->cardHolderName);
	//fgets((char *)cardData->cardHolderName,sizeof(cardData->cardHolderName),stdin);
	if (strlen((const char*) cardData->cardHolderName) < 20
			|| strlen((const char*) cardData->cardHolderName) > 24) {
		return WRONG_NAME;
	}
	return CARD_OK;
}

void getCardHolderNameTest(void) {

	ST_cardData_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: getCardHolderName\n");

	printf("\nTest Case 1:\nInput Data: Hussein\nExpected Result: 1\n");

	printf("Actual Result: %d\n", getCardHolderName(&testcase));

	printf(
			"\nTest Case 2:\nInput Data: HusseinSobhySobhyEl-Shamy\nExpected Result: 1\n");

	printf("Actual Result: %d\n", getCardHolderName(&testcase));

	printf(
			"\nTest Case 3:\nInput Data: HusseinSobhyEl-Shamy\nExpected Result: 0\n");

	printf("Actual Result: %d\n", getCardHolderName(&testcase));

}

EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {

	printf("Please, Enter the card expiry date\n");
	scanf("%s", cardData->cardExpirationDate);
	if (strlen((const char*) cardData->cardExpirationDate) != 5) {
		return WRONG_EXP_DATE;
	}

	//Check month

	int8_t *ptrChar = (int8_t*) cardData->cardExpirationDate;

	if (*ptrChar != '0' && *ptrChar != '1') {
		return WRONG_EXP_DATE;
	}

	ptrChar++;

	if (*ptrChar < '0' && *ptrChar > '9') {
		return WRONG_EXP_DATE;
	}

	// Check symbol (/)

	ptrChar++;

	if (*ptrChar != '/') {
		return WRONG_EXP_DATE;
	}

	// Check year

	int16_t *ptrShort = (int16_t*) cardData->cardExpirationDate;

	ptrShort++;

	(void*) ptrShort++;

	if ((int16_t) *ptrShort < 23 && (int16_t) *ptrShort > 30) {
		return WRONG_EXP_DATE;
	}

	return CARD_OK;
}

void getCardExpiryDateTest(void) {
	ST_cardData_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: getCardExpiryDate\n");

	printf("\nTest Case 1:\nInput Data: 05/23\nExpected Result: 0\n");

	printf("Actual Result: %d\n", getCardExpiryDate(&testcase));

	printf("\nTest Case 2:\nInput Data: Husse\nExpected Result: 2\n");

	printf("Actual Result: %d\n", getCardExpiryDate(&testcase));

	printf("\nTest Case 3:\nInput Data: 05&23\nExpected Result: 2\n");

	printf("Actual Result: %d\n", getCardExpiryDate(&testcase));

	printf("\nTest Case 4:\nInput Data: 0/23\nExpected Result: 2\n");

	printf("Actual Result: %d\n", getCardExpiryDate(&testcase));

	printf("\nTest Case 5:\nInput Data: 5/32\nExpected Result: 2\n");

	printf("Actual Result: %d\n", getCardExpiryDate(&testcase));

	printf("\nTest Case 6:\nInput Data: 05/270\nExpected Result: 2\n");

	printf("Actual Result: %d\n", getCardExpiryDate(&testcase));
}

EN_cardError_t getCardPAN(ST_cardData_t *cardData) {

	printf("Please, Enter the card's Primary Account Number\n");
	scanf(" %s", cardData->primaryAccountNumber);

	if (strlen((const char*) cardData->primaryAccountNumber) < 16
			|| strlen((const char*) cardData->primaryAccountNumber) > 19) {
		return WRONG_PAN;
	}
	if (cardData->primaryAccountNumber == 0) {
		return WRONG_PAN;
	}
	return CARD_OK;
}

void getCardPANTest(void) {

	ST_cardData_t testcase;

	printf("Tester Name: Hussein El-Shamy\nFunction Name: getCardPAN\n");

	printf(
			"\nTest Case 1:\nInput Data: 12345678912345678\nExpected Result: 0\n");

	printf("Actual Result: %d\n", getCardPAN(&testcase));

	printf(
			"\nTest Case 2:\nInput Data: 12345678912345678912\nExpected Result: 3\n");

	printf("Actual Result: %d\n", getCardPAN(&testcase));

	printf("\nTest Case 3:\nInput Data: 123456789\nExpected Result: 3\n");

	printf("Actual Result: %d\n", getCardPAN(&testcase));
}
