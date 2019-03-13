program HELLO_WORLD_PROG {
	version HELLO_WOLRD_VERS {
		string HW(void) = 1;
		int start(string) = 2;
		int sendMessage(string) = 3;
		string getMessages(int) = 4;
		int pot(int) = 5;
	} = 1;
} = 0x30129999;
