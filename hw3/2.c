#include <stdio.h>
#include <stdlib.h>
#define N 4

char *get_string() {
    int len = 0, capacity = 0;
    char *s = (char*) malloc(sizeof(char));
    char c, ok;

    ok = scanf("%c", &c);

    while (c != '\n' && ok != -1) {
        s[len++] = c;

        if (len >= capacity * N) {
            capacity += 1;
            s = (char*) realloc(s, N * capacity * sizeof(char));
        }

        ok = scanf("%c", &c);          
    }

    s[len] = 0;

    return s;
}

char *sub_str(char *str, char *substr) {
	char *str_, *substr_;
	while (*str != 0){
		str_ = str;
		substr_ = substr;
		char ok = 1;
		while (*str_ != 0 && *substr_ != 0) {
			if(*str_++ != *substr_++) {
				ok = 0;
				break;
			}
		}
		if (*substr_ == 0 && ok)
			return str;
		if (*str_ == 0)
			return NULL;
		str++;
	}
	return NULL;
}

int main() {
	printf("Enter your string: \n");
	char *mainstr = get_string();
	printf("Enter your substring: \n");
	char *substr = get_string();
	mainstr = sub_str(mainstr, substr);
	if (mainstr == NULL){
		printf("\nNo substrings\n");
		return 0;
	}
	printf("\nAll the substring tails: \n");
	for (;;) {
		if (mainstr == NULL)
			break;
		printf("%s\n", mainstr);
		if (++mainstr == 0)
			break;
		mainstr = sub_str(mainstr, substr);
	}
	return 0;
}
