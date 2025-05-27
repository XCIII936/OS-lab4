#include "ipc.h"

int main(int argc, char *argv[]) {
    if(argc < 3) {
        printf("Usage: %s <rate> <material>\n", argv[0]);
        printf("material: 0-tobacco, 1-paper, 2-glue\n");
        exit(EXIT_FAILURE);
    }
    
    int rate = atoi(argv[1]);
    int material = atoi(argv[2]);
    
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
    
    supplier_sem = set_sem(supplier_key, 0, sem_flg);
    tobacco_sem = set_sem(tobacco_key, 0, sem_flg);
    paper_sem = set_sem(paper_key, 0, sem_flg);
    glue_sem = set_sem(glue_key, 0, sem_flg);
    mutex_sem = set_sem(mutex_key, 1, sem_flg);
    
    if(material == 0) up(supplier_sem);
    
    while(1) {
        int my_sem;
        char *material_name;
        
        switch(material) {
            case 0: my_sem = tobacco_sem; material_name = "tobacco"; break;
            case 1: my_sem = paper_sem; material_name = "paper"; break;
            case 2: my_sem = glue_sem; material_name = "glue"; break;
            default: printf("Invalid material\n"); exit(EXIT_FAILURE);
        }
        
        down(my_sem);
        down(mutex_sem);
        
        printf("Smoker %d (has %s) takes materials %d and %d\n", 
               getpid(), material_name, table_ptr[0], table_ptr[1]);
        
        table_ptr[0] = -1;
        table_ptr[1] = -1;
        
        up(mutex_sem);
        
        printf("Smoker %d is smoking...\n", getpid());
        sleep(rate);
        
        up(supplier_sem);
    }
    return EXIT_SUCCESS;
}
