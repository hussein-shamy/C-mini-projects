
#include"Card/card.h"

#include"Terminal/terminal.h"

#include"Server/server.h"

#include"Application/app.h"

int main(void) {

	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	appStart();

	return 0;
}
