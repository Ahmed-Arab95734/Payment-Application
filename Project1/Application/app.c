#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "../Card/card.h"
#include "../Terminal/terminal.h"
#include "../Server/server.h"
#include "app.h"

void appStart(void) {
	ST_cardData_t cardData;

	printf("Enter Your Card Name\n");
	getCardHolderName(&cardData);

	printf("Enter Your Card Expiry Date\n");
	getCardExpiryDate(&cardData);

	printf("Enter Your Card PAN\n");
	getCardPAN(&cardData);

	ST_terminalData_t termData;
	
	printf("Enter Transiction Date\n");
	getTransactionDate(&termData);

	if (isCardExpired(&cardData, &termData)== EXPIRED_CARD) {

		printf("\nDeclined Expired Card\n");
		goto End;
	}

	printf("Enter Transiction Amount\n");
	getTransactionAmount(&termData);

	if ((isBelowMaxAmount(&termData)) == EXCEED_MAX_AMOUNT) {
		printf("\nDeclined Declined Amount Exceeding Limit\n");
		goto End;
	}

	ST_accountsDB_t accountRefrence;
	ST_accountsDB_t accountsDB[255] = { {2000.0, RUNNING, "8989374615436851"} ,{100000.0, BLOCKED, "5807007076043875"} ,{6000.0, RUNNING, "9544625498765498"} ,{4500.0, BLOCKED, "4598745621456987"} ,{8750, RUNNING, "1597564235478954"} };

	if ((isValidAccount(&cardData, &accountRefrence)) == ACCOUNT_NOT_FOUND) {
		printf("\nDeclined Invalid account\n");
		goto End;
	}

	if ((isBlockedAccount(&accountRefrence) == BLOCKED_ACCOUNT)) {
		printf("\nDeclined Stolen Card\n");
		goto End;
	}

	if ((isAmountAvailable(&termData, &accountRefrence)) == LOW_BALANCE) {
		printf("\nDeclined Insuffecient funds\n");
		goto End;
	}


	else {
		printf("\nYor Ex Balance (before transiction) was = %f \n",accountRefrence.balance);
		accountRefrence.balance = accountRefrence.balance - termData.transAmount;
		printf("\nthe transaction is approved and yor account balance is reduced by the withdrawn amount.\n");
		printf("\nYor New Balance (arter transiction) is = %f \n", accountRefrence.balance);
	}

	ST_transaction_t transData;
	transData.transactionSequenceNumber = 0;
	saveTransaction(&transData);


	End:;
}