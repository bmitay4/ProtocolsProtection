#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT "443"
#define DEFAULT_FLOOD "RST"
#define SWITCH_FLOOD "UDP"

typedef struct Target {
	char* _ip;
	char* _port;
	char* _type;
}Target;

void get_input(Target target);
void get_command_line(int argc, char* argv[], Target target);

void get_input(Target target) {
	char info[100];

	printf("Enter values as follows(all fields are optional):\n-t <target IP address> -p <target port> -r (change attack type RST/UDP flood)\nFor example : -t 188.23.21.21 -p 67 -r\n\n");
	fgets(info, sizeof info, stdin);
	if (info[0] == '\n') {
		printf("There is no input.\nDefault values will be entered\n\n");
	}
	if (scanf_s("%s", &info, 0) == 0)
		printf("There is no input.\nDefault values will be entered\n\n");
	else if (scanf_s("%s", &info, 5) == 5)
		printf("%s", info);
	else {
		printf("Error, too many values or incorrect entry\nSystem will exit");
		exit(1);
	}

	printf("%s\n", target._ip);
	printf("%s\n", target._port);
	printf("%s\n", target._type);
}

void get_command_line(int argc, char* argv[], Target target) {
	switch (argc) {
	case 1:
		printf("There is no input.\nDefault values will be entered\n\n");
		break;
	case 2:
		if (strcmp(argv[1], "-t") == 0)
			target._ip = argv[2];
		else if (strcmp(argv[1], "-p") == 0)
			target._port = argv[2];
		else target._type = SWITCH_FLOOD;
	case 4:
		if (strcmp(argv[3], "-p") == 0)
			target._ip = argv[4];
		else if (strcmp(argv[1], "-r") == 0)
			target._type = SWITCH_FLOOD;
	case 6:
		if (strcmp(argv[1], "-t") == 0)
			target._ip = argv[2];
		if (strcmp(argv[1], "-p") == 0)
			target._port = argv[2];
		if (strcmp(argv[1], "-r") == 0)
			target._type = SWITCH_FLOOD;
	default:
		printf("Error, too many values or incorrect entry\nSystem will exit");
		break;
	}

	printf("%s\n", target._ip);
	printf("%s\n", target._port);
	printf("%s\n", target._type);
}

/*
The following main function can have the following parameters (flags)
-t	The target IP address for the flood attacks, default is 127.0.0.1
-p	The target port, default is 443
-r	Switch from the default sending of RST flood to the UDP flood attack
*/

int main(int argc, char* argv[]) {
	Target target = { ._ip = DEFAULT_IP, ._port = DEFAULT_PORT, ._type = DEFAULT_FLOOD };
	if (argc == 1)
		get_input(target);
	else
		get_command_line(argc, argv, target);

	return 0;
}