# include <stdio.h>
# include <stdlib.h>
# include "Helper.h"

struct Array{
    int* Array;
    int Size;
    int Iterator;
};

struct Node{
    char Value;
    struct Node* Next;
};

struct Queue{
    struct Node* Head;
    struct Node* Tail;
};

struct Queue* Create_queuE(){
    struct Queue* Temp = malloc(sizeof(struct Queue));
    Temp->Head = NULL;
    Temp->Tail = NULL;
    return Temp;
} 

void Destroy_queuE(struct Queue* Queue){
    struct Node* Curr = Queue->Head;
    struct Node* Next = NULL;
    while (Curr != NULL){
        Next = Curr->Next;
        free(Curr);
        Curr = Next;
    }
    free(Queue);
}

char Pop(struct Queue* Queue){
    char Value = Queue->Head->Value;
    struct Node* Temp = Queue->Head;
    Queue->Head = Queue->Head->Next;
    free(Temp);
    return Value;
}

int Add_to_queuE(struct Queue* Queue, char Value){
    struct Node* Temp = malloc(sizeof(struct Node));
    Temp->Value = Value;
    Temp->Next = NULL;
    if (Queue == NULL){
        return 1;
    }else if (Queue->Head == NULL){
        Queue->Head = Temp;
        Queue->Tail = Temp;
        return 0;
    }else{
        Queue->Tail->Next = Temp;
        Queue->Tail = Temp;
        return 0;
    }
}

void Print_queuE(struct Queue* Queue){
    struct Node* Curr = Queue->Head;
    while (Curr != NULL){
        printf("%c", Curr->Value);
        Curr = Curr->Next;
    }
}

struct Array* Create_arraY(int Array_Size){
    struct Array* Temp = malloc(sizeof(struct Array));
    Temp->Array = malloc(sizeof(int) * Array_Size);
	for (int x = 0; x < 30000; x++) {
		Temp->Array[x] = 0;
	}
    Temp->Size = Array_Size;
    Temp->Iterator = 0;
    return Temp;
}

void Destroy_arraY(struct Array* Array){
    free(Array->Array);
    free(Array);
}

// Instruction Reader and Interpreter

int Read_filE(struct Queue* Queue, char* file_name){
    FILE* fin;
    fin = fopen(file_name, "r");
    if(fin == NULL)
        return 1;
    while(1){
        char Input = fgetc(fin);
        if (Input == '>' || Input == '<' || Input == '.' || 
            Input == '+' || Input == '-' || Input == ',' || 
            Input == '[' || Input == ']'){
            Add_to_queuE(Queue, Input);
        }
        if (feof(fin)){
            break;
        }
    }
    fclose(fin);
    return 0;
}

// Not avaliable to user

    void Move_Iterator(struct Array* Array, char Input){
        if (Input == '>'){
            Array->Iterator += 1;
        }else{
            Array->Iterator -= 1;
        }
    }

    void IO (struct Array* Array, char Input){
        int It = Array->Iterator;
        if (Input == '.'){
            printf("%c", Array->Array[It]);
        }else{
            Array->Array[It] = getchar();
        }
    }

    void Inc_deC (struct Array* Array, char Input){
        if (Input == '+'){
            Array->Array[Array->Iterator] += 1;
        }else{
            Array->Array[Array->Iterator] -= 1;
        }
    }

        void Copy_queueS(struct Queue* Q1, struct Queue* Q2){
            struct Node* Temp = Q1->Head;
            while(Temp != NULL){
                Add_to_queuE(Q2, Temp->Value);
                Temp = Temp->Next;
            }
        }

    void Loop (struct Array* Array, struct Queue* Queue, char Input){
        struct Queue* Mem = Create_queuE();
        struct Queue* Copy = Create_queuE();
        char I = ' ';
        int obc = 1;
        while (I != ']' || obc != 0){
            I = Pop(Queue);
            if (I == '['){
                obc += 1;
                Add_to_queuE(Mem, I);
            }else if (I == ']'){
                obc -= 1;
                if (obc > 0){
                    Add_to_queuE(Mem, I);
                }
            }else{
                Add_to_queuE(Mem, I);
            }
        }
        int It = Array->Iterator;
        while(Array->Array[It] != 0){
            Copy_queueS(Mem, Copy);
            Execute_orderS(Array, Copy);
            It = Array->Iterator;
        }
        Destroy_queuE(Copy);
        Destroy_queuE(Mem);
    }

//

void Execute_orderS(struct Array* Array, struct Queue* Queue){
    while (Queue->Head != NULL){
        char Input = Pop(Queue);
        switch(Input){
            case '>':
                Move_Iterator(Array, Input);
                break;
            case '<':
                Move_Iterator(Array, Input);
                break;
            case '.':
                IO(Array, Input);
                break;
            case ',':
                IO(Array, Input);
                break;
            case '+':
                Inc_deC(Array, Input);
                break;
            case '-':
                Inc_deC(Array, Input);
                break;
            case '[':
                Loop(Array, Queue, Input);
                break;
        }
    }
}