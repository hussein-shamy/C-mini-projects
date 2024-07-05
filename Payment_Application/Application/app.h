
#ifndef APP_H_
#define APP_H_

//#include "../Card/card.h"
//#include "../Terminal/terminal.h"
#include "../Server/server.h"

extern ST_accountsDB_t accountsDB[255];

extern ST_transaction_t transactionsDB[255];

extern ST_cardData_t cardUser;
extern ST_terminalData_t termanalData;
extern ST_transaction_t transactionData;
extern ST_accountsDB_t *accountData ;

void appStart(void);

#endif /* APP_H_ */
