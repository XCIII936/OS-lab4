/* 
 * Filename : ipc.c 
 * copyright : (C) 2006 by zhonghonglie 
 * Function : 一组建立 IPC 机制的函数 
*/ 
#include "ipc.h" 
/* 
 * get_ipc_id() 从/proc/sysvipc/文件系统中获取 IPC 的 id 号
 * pfile: 对应/proc/sysvipc/目录中的 IPC 文件分别为
 * msg-消息队列,sem-信号量,shm-共享内存
 * key: 对应要获取的 IPC 的 id 号的键值
*/ 
int get_ipc_id(char *proc_file,key_t key) 
{ 
 FILE *pf; 
 int i,j; 
 char line[BUFSZ],colum[BUFSZ]; 
 if((pf = fopen(proc_file,"r")) == NULL){ 
 perror("Proc file not open"); 
 exit(EXIT_FAILURE); 
 } 
 fgets(line, BUFSZ,pf); 
 while(!feof(pf)){ 
 i = j = 0; 
 fgets(line, BUFSZ,pf); 
 while(line[i] == ' ') i++; 
 while(line[i] !=' ') colum[j++] = line[i++]; 
 colum[j] = '\0'; 
 if(atoi(colum) != key) continue; 
 j=0; 
 while(line[i] == ' ') i++; 
 while(line[i] !=' ') colum[j++] = line[i++]; 
 colum[j] = '\0'; 
 i = atoi(colum); 
 fclose(pf); 
 return i; 
 } 
 fclose(pf); 
 return -1; 
} 
/* 
 * 信号灯上的 down/up 操作
 * semid:信号灯数组标识符
 * semnum:信号灯数组下标
 * buf:操作信号灯的结构
*/ 
int down(int sem_id) 
{ 
 struct sembuf buf; 
 buf.sem_op = -1; 
 buf.sem_num = 0; 
 buf.sem_flg = SEM_UNDO; 
 if((semop(sem_id,&buf,1)) <0) { 
 perror("down error "); 
 exit(EXIT_FAILURE); 
 } 
 return EXIT_SUCCESS; 
} 
int up(int sem_id) 
{ 
 struct sembuf buf; 
 buf.sem_op = 1; 
 buf.sem_num = 0; 
 buf.sem_flg = SEM_UNDO; 
 if((semop(sem_id,&buf,1)) <0) { 
 perror("up error "); 
 exit(EXIT_FAILURE); 
 } 
 return EXIT_SUCCESS; 
} 
/* 
* set_sem 函数建立一个具有 n 个信号灯的信号量
* 如果建立成功，返回 一个信号灯数组的标识符 sem_id 
* 输入参数：
* sem_key 信号灯数组的键值
* sem_val 信号灯数组中信号灯的个数
* sem_flag 信号等数组的存取权限
*/ 
int set_sem(key_t sem_key,int sem_val,int sem_flg) 
{ 
 int sem_id; 
 Sem_uns sem_arg; 
 //测试由 sem_key 标识的信号灯数组是否已经建立
 if((sem_id = get_ipc_id("/proc/sysvipc/sem",sem_key)) < 0 ) 
 { 
 //semget 新建一个信号灯,其标号返回到 sem_id 
 if((sem_id = semget(sem_key,1,sem_flg)) < 0) 
 { 
 perror("semaphore create error"); 
 exit(EXIT_FAILURE); } 
 } 
 return msq_id; 
}
