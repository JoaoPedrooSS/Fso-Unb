#include <stdio.h>
#include <stdlib.h>

typedef struct ComandElement {
    struct ComandElement *next;
    struct ComandElement *prev;
    int comand;
} ComandElement;

typedef struct ProcessElement {
    struct ProcessElement *next;
    struct ProcessElement *prev;
    ComandElement *comands;
    int process;
} ProcessElement;

int main() {
    int process_quantity;
    scanf("%d", &process_quantity);
    int *comand_quantity = malloc(process_quantity * sizeof(int));
    
    for (int i = 0; i < process_quantity; i++) {
        scanf("%d", &comand_quantity[i]);
    }
    
    ProcessElement head = {NULL, NULL, NULL, 1};
    head.next = &head;
    head.prev = &head;
    ProcessElement *last_process = &head;
    
    for (int i = 0; i < process_quantity; i++) {
        ProcessElement *new_process = (i == 0) ? &head : malloc(sizeof(ProcessElement));
        if (i != 0) {
            *new_process = (ProcessElement){&head, last_process, NULL, i + 1};
            last_process->next = new_process;
            head.prev = new_process;
            last_process = new_process;
        }
        
        ComandElement *first_command = NULL, *last_command = NULL;
        for (int j = 0; j < comand_quantity[i]; j++) {
            int comand;
            scanf("%d", &comand);
            
            ComandElement *new_comand = malloc(sizeof(ComandElement));
            *new_comand = (ComandElement){NULL, last_command, comand};
            
            if (j == 0) {
                first_command = new_comand;
                new_process->comands = new_comand;
            } else {
                last_command->next = new_comand;
            }
            
            new_comand->next = first_command;
            first_command->prev = new_comand;
            last_command = new_comand;
        }
    }
    
    ProcessElement *current = &head;
    int total_time = 0;
    
    while (current) {
        ComandElement *current_comand = current->comands;
        
        while (current_comand) {
            if (current_comand->comand == 1) {
                current_comand->comand = 0;
                break;
            } else {
                total_time += 10;
                ComandElement *to_delete = current_comand;
                
                if (current_comand->next == current_comand) {
                    current->comands = NULL;
                    free(to_delete);
                    break;
                }
                
                current_comand->prev->next = current_comand->next;
                current_comand->next->prev = current_comand->prev;
                current_comand = current_comand->next;
                free(to_delete);
            }
        }
        
        if (!current->comands) {
            ProcessElement *to_delete = current;
            printf("%d (%d)\n", current->process, total_time);
            
            if (current->next == current) {
                break;
            }
            
            current->prev->next = current->next;
            current->next->prev = current->prev;
            current = current->next;
            
            if (to_delete != &head) {
                free(to_delete);
            }
        } else {
            current->comands = current_comand;
            current = current->next;
        }
    }
    
    free(comand_quantity);
    return 0;
}