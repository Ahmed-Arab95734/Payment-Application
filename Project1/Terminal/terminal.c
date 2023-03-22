#include <stdio.h>
#include <stdbool.h>
#include "terminal.h"
#include <string.h>

getTransactionDate(ST_terminalData_t *termData) {
	uint8_t Date[100];
	bool date = 1;
	gets(Date);

	if (Date[10] != NULL)
		{
			date = 0;
			return WRONG_DATE;
		}

	else if (Date[2] != '/'|| Date[5] != '/') {
	
		return WRONG_DATE;

	}

	else {
		for (int x = 0; x < 11; x++) {
			(*termData).transactionDate[x] = Date[x];
		}
		return CARD_OK;
	}
}
void getTransactionDateTest(void);
void getTransactionDateTest(void) {
	ST_terminalData_t termData;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: getTransactionDate\n");

	printf("Test Case 1: \n");
	printf("Input Data(NULL):");
	char result = getTransactionDate(&termData);
	printf("\nExpected Result:1(From The enum Means:WRONG_DATE)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data(less than 10 characters):");
	result = getTransactionDate(&termData);
	printf("\nExpected Result:1(From The enum Means:WRONG_DATE)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 3: \n");
	printf("Input Data(10 charcters but wrong format):");
	result = getTransactionDate(&termData);
	printf("\nExpected Result:1(From The enum Means:WRONG_DATE)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 4: \n");
	printf("Input Data(10 charcters with correct format):");
	result = getTransactionDate(&termData);
	printf("\nExpected Result:0(From The enum Means:TERMINAL_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 5: \n");
	printf("Input Data(more than 10 characters):");
	result = getTransactionDate(&termData);
	printf("Expected Result:1(From The enum Means:WRONG_DATE)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}

isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData) {
//	char result1 = getCardExpiryDate(cardData);
	char card_year[3], terminal_year[3], card_month[3], terminal_month[3];

	card_month[0]=(*cardData).cardExpirationDate[0];
	card_month[1] = (*cardData).cardExpirationDate[1];
	card_month[2] = NULL;

	card_year[0] = (*cardData).cardExpirationDate[3];
	card_year[1] = (*cardData).cardExpirationDate[4];
	card_year[2] = NULL;

//	char result2 = getTransactionDate(termData);

	terminal_month[0] = (*termData).transactionDate[3];
	terminal_month[1] = (*termData).transactionDate[4];
	terminal_month[2] = NULL;

	terminal_year[0] = (*termData).transactionDate[8];
	terminal_year[1] = (*termData).transactionDate[9];
	terminal_year[2] = NULL;

	if (atoi(terminal_year) < atoi(card_year)) {
		return TERMINAL_OK;

	}
	else if (atoi(terminal_year) > atoi(card_year)){
		return EXPIRED_CARD;
	}
	else {
		if (atoi(terminal_month) < atoi(card_month)) {
			return TERMINAL_OK;

		}
		else if (atoi(terminal_month) > atoi(card_month)) {
			return EXPIRED_CARD;
		}

	}

}

void isCardExpriedTest(void);
void isCardExpriedTest(void) {
	ST_terminalData_t termData;
	ST_cardData_t cardData;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: isCardExpried\n");

	printf("Test Case 1: \n");
	printf("Input Data(expiration date is before the transaction date)(CardExpiryDate then TransactionDate):");
	char result = isCardExpired(&cardData,&termData);
	printf("\nExpected Result:2(From The enum Means:EXPIRED_CARD)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data((expiration date is after the transaction date)(CardExpiryDate then TransactionDate)):");
	result = isCardExpired(&cardData, &termData);
	printf("\nExpected Result:0(From The enum Means:TERMINAL_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}

getTransactionAmount(ST_terminalData_t *termData) {
	float amount;
	scanf_s("%f", &amount);
	if (amount <= 0) {
		return INVALID_AMOUNT;
	}
	else {
		(*termData).transAmount = amount;
		return TERMINAL_OK;
	}
}

void getTransactionAmountTest(void);
void getTransactionAmountTest(void) {
	ST_terminalData_t termData;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: getTransactionAmount\n");

	printf("Test Case 1: \n");
	printf("Input Data(amount is less than 0):");
	char result = getTransactionAmount(&termData);
	printf("\nExpected Result:4(From The enum Means:INVALID_AMOUNT)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data(amount is equal to 0):");
	result = getTransactionAmount(&termData);
	printf("\nExpected Result:4(From The enum Means:INVALID_AMOUNT)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 3: \n");
	printf("Input Data(amount is more than 0):");
	result = getTransactionAmount(&termData);
	printf("\nExpected Result:0(From The enum Means:TERMINAL_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}









setMaxAmount(ST_terminalData_t *termData, float maxAmount) {

	if (maxAmount <= 0) {
		return INVALID_MAX_AMOUNT;
	}
	else {
		(*termData).maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
}

void setMaxAmountTest(void);
void setMaxAmountTest(void) {
	ST_terminalData_t termData;
	float input_maxAmount;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: setMaxAmount\n");

	printf("Test Case 1: \n");
	printf("Input Data(max amount is less than 0):");
	scanf_s("%f", &input_maxAmount);
	char result = setMaxAmount(&termData, input_maxAmount);
	printf("\nExpected Result:6(From The enum Means:INVALID_MAX_AMOUNT)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data(max amount is equal to 0):");
	scanf_s("%f", &input_maxAmount);
	result = setMaxAmount(&termData, input_maxAmount);
	printf("\nExpected Result:6(From The enum Means:INVALID_MAX_AMOUNT)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 3: \n");
	printf("Input Data(max amount is more than 0):");
	scanf_s("%f", &input_maxAmount);
	result = setMaxAmount(&termData, input_maxAmount);
	printf("\nExpected Result:0(From The enum Means:TERMINAL_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}

isBelowMaxAmount(ST_terminalData_t *termData) {
//	char result1 = getTransactionAmount(termData);
	char result2 = setMaxAmount(termData,6000.0);

	if ((*termData).transAmount > (*termData).maxTransAmount) {
		return EXCEED_MAX_AMOUNT;
	}
	else {
		return TERMINAL_OK;
	}
}

void isBelowMaxAmountTest(void);
void isBelowMaxAmountTest(void) {
	ST_terminalData_t termData;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: isBelowMaxAmount\n");

	printf("Test Case 1: \n");
	printf("Input Data(transaction amount is larger than the terminal max allowed amount ):");
	char result = isBelowMaxAmount(&termData);
	printf("\nExpected Result:5(From The enum Means:EXCEED_MAX_AMOUNT)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data(transaction amount is lower than the terminal max allowed amount):");
	result = isBelowMaxAmount(&termData);
	printf("\nExpected Result:0(From The enum Means:TERMINAL_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

}