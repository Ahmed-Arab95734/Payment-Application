#include <stdio.h>
#include <stdbool.h>
#include "server.h"
#include <string.h>
ST_accountsDB_t accountsDB[255] = { {2000.0, RUNNING, "8989374615436851"} ,{100000.0, BLOCKED, "5807007076043875"} ,{6000.0, RUNNING, "9544625498765498"} ,{4500.0, BLOCKED, "4598745621456987"} ,{8750, RUNNING, "1597564235478954"} };

ST_transaction_t transaction[255] = { 0 };

recieveTransactionData(ST_transaction_t *transData) {
	ST_cardData_t cardData;
	char result1 = getCardPAN(&cardData);
	int i = 0;
	int j;
	for (j = 0; j < 5; j++) {
		A:
		if (cardData.primaryAccountNumber[i] == accountsDB[j].primaryAccountNumber[i]&&i<16) {
			i++;
			goto A;							
		}
		if (i == 16) {
			break;
		}
		
	}
	if (i != 16) {
		return FRAUD_CARD;
		goto B;
	}

	ST_terminalData_t termData;
	char result2 = getTransactionAmount(&termData);
	
	if (termData.transAmount> accountsDB[j].balance){
		return DECLINED_INSUFFECIENT_FUND;
		goto B;
	}

	if (accountsDB[j].state == BLOCKED) {
		return DECLINED_STOLEN_CARD;
		goto B;
	}

	if (result1 != 0) {
		return INTERNAL_SERVER_ERROR;
		goto B;
	}
	else {
		accountsDB[j].balance = accountsDB[j].balance - termData.transAmount;
		return APPROVED;

	}

B:;
}
void recieveTransactionDataTest(void);
void recieveTransactionDataTest(void) {
	ST_transaction_t transData;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: recieveTransactionData\n");

	printf("Test Case 1: \n");
	printf("Input Data(Enter PAN  does not exist)(enter card PAN):");
	char result = recieveTransactionData(&transData);
	printf("\nExpected Result:3(From The enum Means:FRAUD_CARD)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data(enter amount is not available in account)(Enter card PAN Then trans Amount):");
	result = recieveTransactionData(&transData);
	printf("\nExpected Result:1(From The enum Means:DECLINED_INSUFFECIENT_FUND)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	result = recieveTransactionData(&transData);
	printf("Test Case 3: \n");
	printf("Input Data(if the account is blocked)(Enter card PAN Then trans Amount):");
	result = recieveTransactionData(&transData);
	printf("\nExpected Result:2(From The enum Means:DECLINED_STOLEN_CARD)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	result = recieveTransactionData(&transData);
	printf("Test Case 4: \n");
	printf("Input Data(if the payment approved)(Enter card PAN Then trans Amount):");
	result = recieveTransactionData(&transData);
	printf("\nExpected Result:0(From The enum Means:APPROVED)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

}

isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t* accountRefrence) {
//	char result1 = getCardPAN(cardData);
	int i = 0;
	int j;
	for (j = 0; j < 5; j++) {
	A:
		if ((*cardData).primaryAccountNumber[i] == accountsDB[j].primaryAccountNumber[i] && i < 16) {
			i++;
			goto A;
		}
		if (i == 16) {
			break;
		}

	}
	if (i != 16) {
		return ACCOUNT_NOT_FOUND;

	}
	else {
		(*accountRefrence) = accountsDB[j];
		return SERVER_OK;
	}

}
void isValidAccountTest(void);
void isValidAccountTest(void) {
	ST_cardData_t cardData;
	ST_accountsDB_t accountRefrence;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: isValidAccount\n");

	printf("Test Case 1: \n");
	printf("Input Data(Enter PAN  does not exist):");
	char result = isValidAccount(&cardData,&accountRefrence);
	printf("\nExpected Result:3(From The enum Means:ACCOUNT_NOT_FOUND)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Dat(Enter correct card PAN ):");
	result = isValidAccount(&cardData, &accountRefrence);
	printf("\nExpected Result:0(From The enum Means:SERVER_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}

isBlockedAccount(ST_accountsDB_t* accountRefrence) {
	ST_cardData_t cardData;
//	isValidAccount(&cardData, accountRefrence);
	if ((*accountRefrence).state== BLOCKED) {
		return BLOCKED_ACCOUNT;
	}
	else {
		return SERVER_OK;
	}
}

void isBlockedAccountTest(void);
void isBlockedAccountTest(void) {
	
	ST_accountsDB_t accountRefrence;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: isBlockedAccount\n");

	printf("Test Case 1: \n");
	printf("Input Data(Enter Blocked account PAN):");
	char result = isBlockedAccount(&accountRefrence);
	printf("\nExpected Result:5(From The enum Means:BLOCKED_ACCOUNT)\n");
	printf("Actual Result:");
	printf("%d",result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Dat(Enter RUNNING account PAN ):");
	result = isBlockedAccount(&accountRefrence);
	printf("\nExpected Result:0(From The enum Means:SERVER_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}

isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence) {
	ST_cardData_t cardData;
//	isValidAccount(&cardData, accountRefrence);

//	char amount = getTransactionAmount(termData);

	if ((*termData).transAmount >( *accountRefrence).balance) {
		return LOW_BALANCE;
	
	}
	else {
		return SERVER_OK;
	}
}

void isAmountAvailableTest(void);

void isAmountAvailableTest(void) {
	ST_terminalData_t termData;
	ST_accountsDB_t accountRefrence;
	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: isAmountAvailable\n");

	printf("Test Case 1: \n");
	printf("Input Data(trans amount lager than blalancr)(Enter PAN account then trnans amount):");
	char result = isAmountAvailable(& termData,& accountRefrence);
	printf("\nExpected Result:4(From The enum Means:LOW_BALANCE)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");

	printf("Test Case 2: \n");
	printf("Input Data(trans amount lesser than blalancr)(Enter new trnans amount):");
	result = isAmountAvailable(&termData, &accountRefrence);
	printf("\nExpected Result:0(From The enum Means:SERVER_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}

saveTransaction(ST_transaction_t* transData) {
	ST_cardData_t cardData;
	getCardHolderName(&cardData);
	getCardExpiryDate(&cardData);
	getCardPAN(&cardData);
	(*transData).cardHolderData = cardData;

	ST_terminalData_t termData;
	getTransactionDate(&termData);
	getTransactionAmount(&termData);
	setMaxAmount(&termData, 6000.0);
	(*transData).terminalData = termData;

	(*transData).transState = recieveTransactionData(transData);

	transaction[(*transData).transactionSequenceNumber] = *transData;

	(*transData).transactionSequenceNumber = (*transData).transactionSequenceNumber + 1;
	
	return SERVER_OK;
}

saveTransactionTest(void);

saveTransactionTest(void) {
	ST_transaction_t transData;
	transData.transactionSequenceNumber = 0;

	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: saveTransaction\n");

	printf("Test Case 1: \n");
	printf("Input Data(all card & terminal data)(card name then card expiry date then card pan then trans date then trens amount ):");
	char result = saveTransaction(& transData);
	printf("\nExpected Result:0(From The enum Means:SERVER_OK)\n");
	printf("Actual Result:");
	printf("%d", result);
	printf("\n");
}

void listSavedTransactions(void) {
	int NumOfTrans=1;
	for (int i = 0; i < NumOfTrans; i++) {
		printf("\n#########################\n");

		printf("Transaction Sequence Number: %d\n", transaction[i].transactionSequenceNumber);
		
		printf("Transaction Date: %s\n", (transaction[i].terminalData).transactionDate);
		printf("Transaction Amount: %f\n", (transaction[i].terminalData).transAmount);

		printf("Transaction State: %d\n", transaction[i].transState);

		printf("Terminal Max Amount: %f\n", (transaction[i].terminalData).maxTransAmount);

		printf("Cardholder Name: %s\n", (transaction[i].cardHolderData).cardHolderName);
		printf("PAN: %s\n", (transaction[i].cardHolderData).primaryAccountNumber);
		printf("Card Expiration Date: %s\n", (transaction[i].cardHolderData).cardExpirationDate);

		printf("#########################\n");
	}
}
void listSavedTransactionsTest(void);
void listSavedTransactionsTest(void) {
	ST_transaction_t transData;
	transData.transactionSequenceNumber = 0;

	printf("Tester Name: Ahmed Mohamed Hassan\n");
	printf("Function Name: listSavedTransactions\n");

	printf("Test Case 1: \n");
	printf("Input Data(all card & terminal data)(card name then card expiry date then card pan then trans date then trens amount ):");
	saveTransaction(&transData);
	printf("\nExpected Result:(Print all enterd data)\n");
	printf("Actual Result:");
	listSavedTransactions();
	printf("\n");
}