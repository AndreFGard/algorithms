
#include <stdlib.h>
#include <stdio.h>

typedef struct node {
	struct node *next;
	char *data;
    int start;
} node;

node *temp;
typedef struct LList {
	node *head;
	node *tail;
	node *curr;
} LList;


#define endd 3
#define stt 4

LList freelist;

int mygetinput(char dest[]){
    char a;
    int i =0;
    while (((dest[i] = getc(stdin) )!= '\n') && (dest[i] != EOF)){
        i++;
    };
    if (dest[i] ==  EOF){
        dest[i] = '\0';
        return EOF;
    }
    dest[i] = '\0';
    return  1;
}


node *get_node() {
	temp = (node *) malloc(sizeof(node));
	temp->next = NULL;
	return temp;
}

/**/
node *get_freelistnode(){
    if (freelist.head->next != NULL) {
        temp = freelist.head->next;
        freelist.head->next = freelist.head->next->next;
    }
    else temp = get_node();
    return temp;
}

void add_node(LList *l, node *node, char *text, int start) {
	/*/ if (!node){
    //     if (!(temp = get_freelistnode()))
    //         temp = get_node();
    // }
    // else temp = node;*/
    temp = get_node();
	
	if (l->tail == l->curr) l->tail = temp;
	temp->next = l->curr->next;
	l->curr->next = temp;
    temp->data = &text[start];

    temp->start = start;
}

char newline_newlinenot;
void print_list(LList *l, char text[]) {
    //must jump the head, if theres anything to print

    int i = 0;
    //se estiver um nó na lista (sempre haverá?)
    if (l->curr = l->head->next){
        do {
            i += printf("%s", &text[l->curr->start]);
        }  while(l->curr = l->curr->next);
        //printf("%c", newline_newlinenot);
        if (i > 0) /* se caracteres foram printados, terminar a linha*/
            puts(""); // isso tá corretou ou eu so printo newline quando entrar newline?
    }

}


int main() {
    freelist.head = freelist.curr = freelist.tail = get_node();

	LList l;
	l.head = l.curr = l.tail = get_node();
    char line[100001] = "eae"; // 0_0

    int ret;
    char c;

    newline_newlinenot = '\0';

    int j;


    int last = 0;
    int read = 3;
    while((long unsigned int)(fgets(line, 100001, stdin)) > 0) {
        if (line[0] == '\0') break;
        //newline_newlinenot = '\0';
        
        last = 0;

        int i = 0;
        //poderia usar strtok
        for (;;i++){
            c = line[i]; 

            if (c == '\0') break;

            if (c == '['){
                add_node(&l, NULL, line, last);
                line[i] = '\0';            

                //prepare for the next finding
                l.curr = l.curr->next;
                last = i + 1;
                l.curr = l.head;
            }

            else if (c == ']'){
                add_node(&l, NULL, line, last);
                line[i] = '\0';            

                //prepare for the next finding
                l.curr = l.curr->next;
                last = i + 1;
                l.curr = l.tail;
            }
        }
        add_node(&l, NULL, line, last);
        //absolutely EXTERMINATE the DAMNN newline
        //who was o maldito que teve a ideia de tirar a gets da glibc? minha liberdade foi severamente atacada por seja la quem fez isso
        if (i) 
            if (line[i -1] == '\n'){
                //printar newline somente se a linha ja possuia newline (DESATIVADO POR ORA)
                //newline_newlinenot = '\n';
                line[i -1]= '\0';
            }


        print_list(&l, line);
        freelist.tail->next = l.head->next;
        l.head->next = NULL;
        l.tail = l.curr = l.head;
    }

}
