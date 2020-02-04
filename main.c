#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define BUFFER 64
#define SIZE 10



void reader(char* text){
    fgets(text, BUFFER, stdin);
    while (strchr(text, '\n') == NULL) {
        text =  realloc(text, sizeof(char) * (strlen(text) + BUFFER));
        fgets(text + strlen(text), BUFFER, stdin);
    }
}



int conventing(char* text, char** sentences){
    int CounterSent = 0;
    char flag = 1;
    int MaxCounterSent = 10;
    int CounterSymb = 0;
    int MaxCounterSymb = 0;
    for(int i = 0; text[i] != '\n'; i++){
        if(CounterSent == MaxCounterSent){
            MaxCounterSent += SIZE;
            sentences = realloc(sentences, MaxCounterSent * sizeof(char*));
        }
        if (flag == 1){
            CounterSymb = 0;
            MaxCounterSymb = SIZE;
            sentences[CounterSent] = malloc(MaxCounterSymb * sizeof(char));
            flag = 0;
        }
        if (MaxCounterSymb == CounterSymb){
            MaxCounterSymb += SIZE;
            sentences[CounterSent] = realloc(sentences[CounterSent], MaxCounterSymb * sizeof(char));
        }
        if(text[i] != '.'){
            if((text[i] == ' ') && (CounterSymb == 0)){
                continue;
            }
            sentences[CounterSent][CounterSymb] = text[i];
            CounterSymb++;
        }
        else{
            if(CounterSymb == 0) continue;
            sentences[CounterSent] = realloc(sentences[CounterSent], (MaxCounterSymb + 1) * sizeof(char));
            sentences[CounterSent][CounterSymb] = '.';
            CounterSymb++;
            sentences[CounterSent][CounterSymb] = '\0';
            CounterSent++;
            flag = 1;
        }
    }
    free(text);
    return CounterSent;
}



int MrProper(char** sentences, int CounterSent){
    for(int i = 0; i < CounterSent; i++){
        for(int j = 0; j < (CounterSent - 1); j++){
            if(i == j){
                continue;
            } else{
                if(strlen(sentences[i]) == strlen(sentences[j])){
                    char flag = 1;
                    for(int p = 0; p < strlen(sentences[i]); p++){
                        if(toupper(sentences[i][p]) != toupper(sentences[j][p])){
                            flag = 0;
                        }
                    }
                    if (flag == 1){
                        free(sentences[j]);
                        CounterSent--;
                        for(int p = j; p < CounterSent; p++){
                            sentences[p] = sentences[p + 1];
                        }
                        j--;
                    }
                }
            }
        }
    }
    return CounterSent;
}


void CleanerDigit(char** sentences, int CounterSent){
    int CountSymb;
    for(int i = 0; i < CounterSent; i++){
        CountSymb = 0;
        char* text = malloc((strlen(sentences[i]) + 1) * sizeof(char));
        for(int j = 0; j < strlen(sentences[i]); j++){
            if(!isdigit(sentences[i][j])){
                text[CountSymb] = sentences[i][j];
                CountSymb++;
            }
        }
        text[CountSymb] = '\0';
        free(sentences[i]);
        sentences[i] = text;
    }
}


int CleanerIfSymb(char** sentences, int CounterSent){
    for(int i = 0; i < CounterSent; i++){
        if (strlen(sentences[i]) < 3){
            continue;
        }
        int FirstSymb = 0;
        int LastSymb = strlen(sentences[i]) -2;
        if(toupper(sentences[i][FirstSymb]) == toupper(sentences[i][LastSymb])){
            free(sentences[i]);
            CounterSent--;
            for(int p = i; p < CounterSent; p++){
                sentences[p] = sentences[p + 1];
            }
            i--;
        }
    }
    return CounterSent;
}


int len(char* a){
    int Len3Word = 0;
    int Space = 0;
    for(int i = 0; i < strlen(a) - 1; i++){
        if(Space == 2){
            Len3Word++;
        }
        if(a[i] == ' '){
            Space++;
        }
    }
    if(Len3Word == 0){
        return 3;
    }
    return Len3Word;
}


int cmp(const void* a, const void* b){
    if(len(*(char**)a) > len(*(char**)b)) return 1;
    if(len(*(char**)a) == len(*(char**)b)) return 0;
    if(len(*(char**)a) < len(*(char**)b)) return -1;
    return 0;
}


void sort(char** sentence, int CounterSent){
    qsort(sentence, CounterSent, sizeof(char**), cmp);
}


void ispalindrom(char** sentence, int CounterSent){
    char flag;
    for(int i = 0; i < CounterSent; i++){
        flag = 1;
        for(int j = 0; j < (strlen(sentence[i]) - 1) / 2; j++){
            if(sentence[i][j] != sentence[i][strlen(sentence[i]) - 2 - j]){
                flag = 0;
            }
        }
        if(flag == 1){
            printf("Palindrome\n");
        } else{
            printf("Nothing interesting\n");
        }
    }

}

void additional(char** sentence, int CounterSent) {
    char voc [12] = "aeiouyAEIOUY";
    int changed = 0;

    for (int i = 0; i < CounterSent; ++i) {
        changed = 0;
        for (int j = 0; j < strlen(sentence[i]); ++j) {
            char letter = sentence[i][j];
            int length = strlen(sentence[i]);
            for (int k = 0; k < 12; ++k) {
                if (letter == voc[k]) {
                    changed = 1;
                    sentence[i] = realloc(sentence[i], strlen(sentence[i]) + 4);
                    sentence[i][length+3] = '\0';
                    for (int l = length; l >= j; l--) {
                        sentence[i][l+3] = sentence[i][l];
                    }
                    sentence[i][j] = 'G';
                    sentence[i][j+1] = ',';
                    sentence[i][j+2] = ' ';
                    sentence[i][j+3] = 'G';
                }
            }
        }

        if (!changed) {
            printf("\e[4m%s\e[0m\n", sentence[i]);
        } else {

        }
    }
}


void printer(char** sentences, int counter){
    for (int i = 0; i < counter; i++){
        printf("%s\n", sentences[i]);
    }

}

int main(){
    char* text = malloc(sizeof(char) * BUFFER);
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");
    printf("\tEnter your text\n");
    printf("//////////////////////////////////////////////////////////////////////////////////////////\n");
    reader(text);
    char **sentences = malloc(SIZE * sizeof(char*));
    int CounterSent = conventing(text,sentences);
    CounterSent = MrProper(sentences, CounterSent);
    int flag = 0;
    int flag1;
    while (flag != 10){
        printf("//////////////////////////////////////////////////////////////////////////////////////////\n");
        printf("\t0: Puts all text.\n");
        printf("\t1: Delete digit.\n");
        printf("\t2: Is palindrome?\n");
        printf("\t3: Delete sentences with same begin and end\n");
        printf("\t4: Sort\n");
        printf("\t5: Additional"); //так же для курсача
        printf("Press else to end\n");
        printf("//////////////////////////////////////////////////////////////////////////////////////////\n");
        flag1 = scanf("%d", &flag);
        if(flag1 != 1){
            flag = 10;
        }
        switch (flag) {
            case 0:
                printer(sentences, CounterSent);
                break;
            case 1:
                CleanerDigit(sentences, CounterSent);
                printer(sentences, CounterSent);
                break;
            case 2:
                ispalindrom(sentences, CounterSent);
                break;
            case 3:
                CounterSent = CleanerIfSymb(sentences, CounterSent);
                printer(sentences, CounterSent);
                break;
            case 4:
                sort(sentences, CounterSent);
                printer(sentences, CounterSent);
                break;
            case 5:
                additional(sentences, CounterSent);
                //printer(sentences, CounterSent);
                break;

            default:
                for(int i = 0; i < CounterSent; i++){
                    free(sentences[i]);
                }
                free(sentences);
                printf("goodbye!\n");
                flag = 10;
                break;

        }
    }

    return 0;
}
