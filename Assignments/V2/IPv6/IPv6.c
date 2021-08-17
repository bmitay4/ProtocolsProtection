
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void IPv6_Generator(char result[]) {
    char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char ch;
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            for (int k = 0; k < 4; k++) {
                ch = str[rand() % 16];
                printf("%c", ch);
                strncat(result, &ch, 1);
            }
            if (j < 7) {
                printf(":");
                char sem = ':';
                strncat(result, &sem, 1);
            }
        }
        printf("\n");
    }
}
void mixing() {
    // //BAD IDEA, SAME IPV6 ALL OVRT AGAIN
    // srand(time(NULL));

    // char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    // char target_ip_address[48];
    // __u_int source_port;

    // sprintf(target_ip_address,
    //         "%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c",
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16]);
    // source_port = (rand() & 0xFFFF);
    // for (size_t i = 0; i < 5; i++) {
    //     printf("%s\n", target_ip_address);
    // }

    ////
    char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    char* target_ip_address[48];
    __u_int source_port;
    for (size_t i = 0; i < 5; i++) {
        sprintf(target_ip_address + i, octet());
    }
    printf("%s\n", *target_ip_address);
}
char* restrict octet() {
    char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

    char* restrict ans;
    sprintf(ans, str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16]);
    return ans;
}
int main(int argc, char const* argv[]) {
    // char str[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    // char target_ip_address[48];
    // __u_int source_port;
    // sprintf(target_ip_address,
    //         "%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c::%c%c%c%c",
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16],
    //         str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16], str[rand() % 16]);
    // source_port = (rand() & 0xFFFF);

    // printf("%s-%d\n", target_ip_address, source_port);

    mixing();
    return 0;
}
