#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct pipe_data{
    char pid[1024];
    float front_dia;
    float tail_dia;
    struct pipe_data *next;
};
struct pipe_data *head_pd = NULL;

struct pipe_data *alloc_pipe_data(char *name, float front, float tail) {
    struct pipe_data *pd;
    pd = (struct pipe_data*) malloc(sizeof(struct pipe_data));
    memset(pd->pid, '\0', 1024);
    strcpy(pd->pid, name);
    pd->front_dia = front;
    pd->tail_dia = tail;
    return pd;
}

void insert_pd(struct pipe_data* new){
           
        struct pipe_data *tmp1 = NULL, *tmp2 = head_pd;
        while (tmp2) {
            if (tmp2->front_dia < new->tail_dia) {
                break;
            }
            tmp1 = tmp2;
            tmp2 = tmp2->next;
        }

        if (tmp1 == NULL) {
            new->next = tmp2;
            head_pd = new;
        } else {
            tmp1->next = new;
            new->next = tmp2;
        } 
}

void display_pd() {
    struct pipe_data *tmp;
    tmp = head_pd;
    while(tmp != NULL)
    {
        printf("%s\t %f\t %f\n",tmp->pid,tmp->front_dia,tmp->tail_dia);       
        tmp = tmp->next;                      
    }
    
}

static void build_pipe_data(char *input_file) {
    char str[1024];
    char *token;
    FILE *fp = fopen(input_file, "r");
    if (fp == NULL) {
        printf("input file %s failed to open \n",input_file);
        return;
    }

    char *tmp1, *tmp2, *tmp3;
    char pd_name[256], f_str[256], t_str[256];
    float f,t;
    struct pipe_data *pd;
    while (fscanf(fp, "%[^\n] ", str) != EOF) {
        tmp1 = strchr(str, ',');
        strncpy(pd_name, str, tmp1-str);
        pd_name[tmp1-str] = '\0';

        tmp1 = strchr(tmp1+1, ',');
        tmp1 = strchr(tmp1+1, ',');
        tmp1 = strchr(tmp1+1, ',');
        tmp2 = strchr(tmp1+1, ',');

        strncpy(f_str, tmp1+1, tmp2-tmp1);
        f_str[tmp2-tmp1-1] = '\0';
        

        tmp1 = strchr(tmp1+1, ',');
        tmp1 = strchr(tmp1+1, ',');
        tmp1 = strchr(tmp1+1, ',');
        tmp1 = strchr(tmp1+1, ',');
        tmp1 = strchr(tmp1+1, ',');
        tmp1 = strchr(tmp1+1, ',');
        tmp3 = strchr(tmp1+1, ',');

        strncpy(t_str, tmp1+1, tmp3-tmp1);
        t_str[tmp3-tmp1-1] = '\0';
	float x,y;
        x = atof(f_str);
        y = atof(t_str);
        pd = alloc_pipe_data(pd_name,x,y);
	insert_pd(pd);
   }
} 
int main(int argc, char *argv[]) {

     char *input_file = argv[1];

     build_pipe_data(input_file);
     printf("Display the pipe infomation in the sorted order\n");
     display_pd();
}

