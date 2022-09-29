#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    struct {
        long mestype;
        int bulls;
        int cows;
    } messagefrom;
    struct {
        long mestype;
        long mes;
        char buf[8];
        // int bnc[4];
    } messageto;

    key_t key = -1;
    int mesid;
    long pid = getpid();
    char buf[4];
    printf ("Waiting for connection...\n");
    while (key == -1)
        key = ftok("/tmp/file.txt", 'r');
    mesid = msgget(key, 0666);
    printf ("Connected.\n");
    messageto.mestype = 1;
    messageto.mes = pid;
    printf("Игра Быки коровы. \
    \nПравила игры: загадывается 4-значное число (цифры в нем не повторяются, \
    \nнаходятся в диапазоне 1-6, \
    \nцель игрока — отгадать это число. После каждой попытки бот сообщает игроку, \
    \nсколько цифр угадано с совпадением их позиции в исходном числе (быки) \
    \nи сколько угадано без совпадения с позицией (коровы).\
    \n\
    \nНапишите Y для старта\n");
    
    scanf("%c", buf[0]);
    while (buf[0] != 'Y')
        scanf("%c", buf[0]);
    // fgets(buf, 4, stdin);
    // while (strcmp('Yes', buf) != 0)
    //     gets(buf);
    //strcpy(messageto.buf, );
    msgsnd(mesid, &messageto, sizeof(messageto) - sizeof(long), 0);
    printf("***");
    while(1) {
        while(1) {
            scanf("%c%c%c%c", &messageto.buf[0], &messageto.buf[1], &messageto.buf[2], &messageto.buf[3]);
            msgsnd(mesid, &messageto, sizeof(messageto) - sizeof(long), 0);
            msgrcv(mesid, &messagefrom, sizeof(messagefrom) - sizeof(long), pid, 0);
            printf("\nБыки - %d\nКоровы - %d\n\n", messagefrom.bulls, messagefrom.cows);
            if (messagefrom.bulls == 4)
                break;
        }
        printf("Вы победили, если хотите продолжить - введите Yes");
        gets(messageto.buf);
        msgsnd(mesid, &messageto, sizeof(messageto) - sizeof(long), 0);
    }
    return 0;
}