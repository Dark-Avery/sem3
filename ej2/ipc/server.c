#include <sys/types.h>
#include <sys/ipc.h>
#include <time.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    struct {
        long mestype;
        int bulls;
        int cows;
    } messageto;
    struct {
        long mestype;
        long mes;
        char buf[8];
        // int bnc[4];
    } messagefrom;

    key_t key;
    int mesid;
    char bnc[4];

    FILE* file = fopen ("/tmp/file.txt", "a+");
    fprintf (file, "My file for bulls and cows.");
    fclose (file);
    key = ftok("/tmp/file.txt", 'r');
    mesid = msgget(key, 0666 | IPC_CREAT);
    
    msgrcv(mesid, &messagefrom, sizeof(messagefrom) - sizeof(long), 1, 0);
    messageto.mestype = messagefrom.mes;
    
    while(1) {
        srandom(time(NULL));
        for (int i = 0; i < 4; i++) {
            bnc[i] = (char)random () % (6 + 1);
            for (int j = 0; j < i; j++)
                if (bnc[j] == bnc[i]) {
                    i--;
                    break;
                }
        }
        bnc[4] = '\0';
        printf("%s\n", bnc);
        // for (int i = 0; i < 4; i++) 
        //     printf("%c", bnc[i]);
        printf("\n");
        while(1) {
            if (strcmp(bnc, messagefrom.buf))
                break;
            msgrcv(mesid, &messagefrom, sizeof(messagefrom) - sizeof(long), 1, 0);
            messageto.bulls = 0;
            for (int k = 0; k < 4; k++)
                if (messagefrom.buf[k] == bnc[k])
                    messageto.bulls ++;
            messageto.cows = 0;
            for (int k = 0; k < 4; k++)
                for (int j = 0; j < 4; j++) {
                    if (j == k) 
                        continue;
                    if (messagefrom.buf[k] == bnc[j]) {
                        messageto.cows++;
                        break;
                    }
                }
            msgsnd(mesid, &messageto, sizeof(messageto) - sizeof(long), 0);
        }
        msgrcv(mesid, &messagefrom, sizeof(messagefrom) - sizeof(long), 1, 0);
        if (strcmp("Yes", messagefrom.buf) != 0)
            break;
    }
    msgctl(mesid, IPC_RMID, NULL);
    return 0;
}