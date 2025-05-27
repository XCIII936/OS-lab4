#include "ipc.h"

int main(int argc, char *argv[]) {
    int rate = argc > 1 ? atoi(argv[1]) : 3;
    
    table_key = 101;
    table_num = 2;
    shm_flg = IPC_CREAT | 0644;
    table_ptr = (int *)set_shm(table_key, table_num, shm_flg);
    
    supplier_key = 201;
    tobacco_key = 301;
    paper_key = 302;
    glue_key = 303;
    mutex_key = 401;
    sem_flg = IPC_CREAT | 0644;
    
    tobacco_sem = set_sem(tobacco_key, 0, sem_flg);
    paper_sem = set_sem(paper_key, 0, sem_flg);
    glue_sem = set_sem(glue_key, 0, sem_flg);
    mutex_sem = set_sem(mutex_key, 1, sem_flg);
    supplier_sem = set_sem(supplier_key, 1, sem_flg);
    
    srand(time(NULL));
    int materials[3] = {0, 1, 2};

    while(1) {
        down(supplier_sem);
        int first = rand() % 3;
        int second;
        do {
            second = rand() % 3;
        } while(second == first);
        
        down(mutex_sem);
        table_ptr[0] = first;
        table_ptr[1] = second;
        printf("Supplier %d puts materials %d(tobacco) and %d(paper)\n", 
               getpid(), first, second);
        
        if((first == 1 && second == 2) || (first == 2 && second == 1)) {
            up(tobacco_sem);
        } else if((first == 0 && second == 2) || (first == 2 && second == 0)) {
            up(paper_sem);
        } else {
            up(glue_sem);
        }
        
        up(mutex_sem);
        sleep(rate);
    }
    return EXIT_SUCCESS;
}
