#ifndef HELPER_H
#define HELPER_H

struct Array;
struct Node;
struct Queue;

struct Queue* Create_queuE();
void Destroy_queuE(struct Queue* Queue);
char Pop(struct Queue* Queue);
int Add_to_queuE(struct Queue* Queue, char Value);
void Print_queuE(struct Queue* Queue);
struct Array* Create_arraY(int Array_Size);
void Destroy_arraY(struct Array* Array);
int Read_filE(struct Queue* Queue, char* file_name);
void Execute_orderS(struct Array* Array, struct Queue* Queue);

#endif