#ifndef IPC_H
#define IPC_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>
#include <time.h>

#define BUFSZ 256

typedef union semuns {
    int val;
} Sem_uns;

extern int get_ipc_id(char *proc_file, key_t key);
extern char *set_shm(key_t shm_key, int shm_num, int shm_flag);
extern int set_sem(key_t sem_key, int sem_val, int sem_flag);
extern int down(int sem_id);
extern int up(int sem_id);

extern key_t table_key;
extern int table_num;
extern int *table_ptr;

extern key_t supplier_key;
extern int supplier_sem;

extern key_t tobacco_key;
extern key_t paper_key;
extern key_t glue_key;
extern int tobacco_sem;
extern int paper_sem;
extern int glue_sem;

extern key_t mutex_key;
extern int mutex_sem;

extern int sem_val;
extern int sem_flg;
extern int shm_flg;

#endif
