#include <stdio.h>
#include <stdbool.h>
#include "card.h"
#include <string.h>


getCardHolderName(ST_cardData_t *cardData) {
	uint8_t Name[100];
	bool name=1;
	gets(Name);
	for (int i = 0; i < 20; i++) {
		if (Name[i] == NULL)
		{
			name = 0;
			return  WRONG_NAME;
			break;
		}
	}
	for (int j = 25; j < 100; j++) {
		if (Name[j] == NULL)
		{
			name = 0;
			return  WRONG_NAME;
			break;
		}

	}
	if (name == 1) {
		for (int x = 0; x < 25; x++) {
			(*cardData).cardHolderName[x] = Name[x];
		}
		return CARD_OK;
	}
}
void getCardHolderNameTest(void);

void getCardHolderNameTest(void) {
	ST_cardData_t cardData;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: getCardHolderName\n");

	printf("Test Case 1: \n");
	printf("Input Data(NULL):");
	char result = getCardHolderName(&cardData);
	printf("\nExpected Result:1(From The enum Means:WRONG_NAME)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data(less than 20 characters):");
	result = getCardHolderName(&cardData);
	printf("\nExpected Result:1(From The enum Means:WRONG_NAME)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 3: \n");
	printf("Input Data(20:24 charcters):");
	result = getCardHolderName(&cardData);
	printf("\nExpected Result:0(From The enum Means:CARD_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 4: \n");
	printf("Input Data(more than 24 characters):");
	result = getCardHolderName(&cardData);
	printf("Expected Result:1(From The enum Means:WRONG_NAME)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

}

getCardExpiryDate(ST_cardData_t* cardData) {
	uint8_t Date[20];
	bool date = 1;

	gets(Date);

	for (int i = 0; i < 5; i++) {
		if (Date[i] == NULL)
		{
			date = 0;
			return WRONG_EXP_DATE;
			break;
		}
	}
	for (int j = 6; j < 20; j++) {
		if (Date[j] == NULL)
		{
			date = 0;
			return WRONG_EXP_DATE;
			break;
		}

	}
	if (Date[2] != '/') {
		date = 0;
		return WRONG_EXP_DATE;

	}
	if (date == 1) {
		for (int x = 0; x < 6; x++) {
			(*cardData).cardExpirationDate[x] = Date[x];
		}
		return CARD_OK;
	}
}

	void getCardExpiryDateTest(void);


	void getCardExpiryDateTest(void) {
		ST_cardData_t cardData;
		printf("Tester Name: Ahmed Mohamed Hassan\n");
		printf("Function Name: getCardExpiryDate\n");

		printf("Test Case 1: \n");
		printf("Input Data(NULL):");
		char result = getCardExpiryDate(&cardData);
		printf("\nExpected Result:2(From The enum Means:WRONG_EXP_DATE)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

		printf("Test Case 2: \n");
		printf("Input Data(less than 5 characters):");
		result = getCardExpiryDate(&cardData);
		printf("\nExpected Result:2(From The enum Means:WRONG_EXP_DATE)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

		printf("Test Case 3: \n");
		printf("Input Data(5 charcters but wrong format):");
		result = getCardExpiryDate(&cardData);
		printf("\nExpected Result:2(From The enum Means:WRONG_EXP_DATE)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

		printf("Test Case 4: \n");
		printf("Input Data(5 charcters with correct format):");
		result = getCardExpiryDate(&cardData);
		printf("\nExpected Result:0(From The enum Means:CARD_OK)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

		printf("Test Case 5: \n");
		printf("Input Data(more than 5 characters):");
		result = getCardExpiryDate(&cardData);
		printf("Expected Result:2(From The enum Means:WRONG_EXP_DATE)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");
	}

	getCardPAN(ST_cardData_t* cardData) {

		uint8_t PAN[100];
		bool pan = 1;
		gets(PAN);
		for (int i = 0; i < 16; i++) {
			if (PAN[i] == NULL)
			{
				pan = 0;
				return  WRONG_PAN;
				break;
			}
		}
		for (int j = 20; j < 100; j++) {
			if (PAN[j] == NULL)
			{
				pan = 0;
				return  WRONG_PAN;
				break;
			}

		}
		if (pan == 1) {
			for (int x = 0; x < 20; x++) {
				(*cardData).primaryAccountNumber[x] = PAN[x];
			}
			return CARD_OK;
		}
	}

	void getCardPANTest(void);

	void getCardPANTest(void) {

		ST_cardData_t cardData;
		printf("Tester Name: Ahmed Mohamed Hassan\n");
		printf("Function Name: getCardPAN\n");

		printf("Test Case 1: \n");
		printf("Input Data(NULL):");
		char result = getCardPAN(&cardData);
		printf("\nExpected Result:3(From The enum Means:WRONG_PAN)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

		printf("Test Case 2: \n");
		printf("Input Data(less than 16 characters):");
		result = getCardPAN(&cardData);
		printf("\nExpected Result:3(From The enum Means:WRONG_PAN)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

		printf("Test Case 3: \n");
		printf("Input Data(16:19 charcters):");
		result = getCardPAN(&cardData);
		printf("\nExpected Result:0(From The enum Means:CARD_OK)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

		printf("Test Case 4: \n");
		printf("Input Data(more than 19 characters):");
		result = getCardPAN(&cardData);
		printf("Expected Result:3(From The enum Means:WRONG_PAN)\n");
		printf("Actual Result:");
		printf("%d", result);
		printf("\n");

	}

