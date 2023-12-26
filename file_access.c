#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#define MAX (31)
#define FILE_NAME ("text.txt")
#define MIN(a,b) (((a)<(b))? (a):(b))
typedef struct person
{
    char name[MAX];
    char sex;
    double score;
}person;
char *get_line(FILE *fptr)
{
    char *line = (char*)calloc(MAX, MAX*sizeof(char));
    int i = 0;
    char temp = getc(fptr);
    while(temp != '\n' && temp != EOF)
    {
        line[i] = temp;
        i++;
        temp = getc(fptr);
    }
    line[i] = '\0';
    return line;
}
void list_all_name()
{
    int person_count = 0;
    char *str;
    FILE *fptr = fopen(FILE_NAME,"r");
    if(!fptr)
        printf("failed to open file.\n");
    else
    {
        fscanf(fptr, "%d\n", &person_count);
        printf("List all %d data.\n", person_count);
        printf("---------------------------\n");
        for(int i = 0; i < person_count; i++)
        {
            str = get_line(fptr);
            printf("Name:\t%s\n",str);
            str = get_line(fptr);
            printf("Sex:\t%s\n",str);
            str = get_line(fptr);
            printf("Score:\t%s\n",str);
        printf("---------------------------\n");

        }
        fclose(fptr);
    }
}
void find_name(char *name)
{
    printf("result of find name: %s.\n", name);
    int flag = 0;
    FILE *fptr = fopen(FILE_NAME, "r");
    if(!fptr)
    {
        printf("failed to open file.\n");
        return;
    }
    else
    {
        int person_count = 0;
        char *str;
        fscanf(fptr, "%d\n", &person_count);

        for(int i = 0; i < person_count; i++)
        {
            str = get_line(fptr);
            if(strstr(str, name))
            {
                flag = 1;
                printf("%s\n",str);
                str = get_line(fptr);
                printf("%s\n",str);
                str = get_line(fptr);
                printf("%s\n",str);
            }
            else
            {
                str = get_line(fptr);
                str = get_line(fptr);
            }
        }
        if(!flag)
            printf("name: %s not founded.\n", name);
    }
    fclose(fptr);
}
person *get_all_data()
{
    int person_count = 0;
    FILE *fptr = fopen(FILE_NAME, "r");
    fscanf(fptr, "%d\n", &person_count);
    char *str;
    person *origin_data = (person*)malloc(person_count*sizeof(person));
    for(int i = 0; i < person_count; i++)
    {
        str = get_line(fptr);
        strncpy(origin_data[i].name, str, MIN(MAX-1,strlen(str)));
        str = get_line(fptr);
        origin_data[i].sex =  str[0];
        str = get_line(fptr);
        origin_data[i].score = strtod(str, &str);
    }
    fclose(fptr);

    return origin_data;
}
void insert_data(char *name, char sex, double score)
{
    printf("this is insert function\n");
    printf("name:%s, sex: %c, score: %lf\n", name, sex, score);
    person new;
    memset(&new.name, '\0', MAX);
    printf("strlen(name) = %d\n", strlen(name));
    strncpy(new.name, name, MIN(MAX-1,strlen(name)));
    new.sex = sex;
    new.score = score;
    FILE *fptr = fopen(FILE_NAME, "r");
    int person_count = 0;
    if(!fptr)
    {
        printf("\ncreate new file.\n");
        fptr = fopen(FILE_NAME, "w");
        person_count = 1;
        fprintf(fptr, "%d\n", person_count);
        fprintf(fptr, "%s\n", new.name);
        fprintf(fptr, "%c\n", new.sex);
        fprintf(fptr, "%lf\n", new.score);
    }
    else
    {
        printf("\nopen existed file.\n");
        fscanf(fptr, "%d\n", &person_count);
        fclose(fptr);
        person *origin_data = get_all_data();
        fptr = fopen(FILE_NAME, "w");
        fprintf(fptr, "%d\n", person_count+1);
        for(int i = 0; i < person_count; i++)
        {
            fprintf(fptr, "%s\n", origin_data[i].name);
            fprintf(fptr, "%c\n", origin_data[i].sex);
            fprintf(fptr, "%lf\n", origin_data[i].score);
        }
        fprintf(fptr, "%s\n", new.name);
        fprintf(fptr, "%c\n", new.sex);
        fprintf(fptr, "%lf", new.score);
        free(origin_data);
    }
    fclose(fptr);
}
void delete_data(char *target)
{
    printf("this is delete function\n");
    printf("target name:%s\n", target);
    FILE *fptr = fopen(FILE_NAME, "r");
    if(!fptr)
    {
        printf("Target not found.\n");
        fclose(fptr);
        return;
    }
    else
    {
        int person_count = 0;
        //printf("\nopen existed file.\n");
        fscanf(fptr, "%d\n", &person_count);
        if(person_count == 0)
        {
            printf("Target not found.\n");
        }
        else
        {
            fclose(fptr);
            person *origin_data = get_all_data();
            int temp = person_count;
            for(int i = 0; i < person_count; i++)
            {
                if(strcmp(origin_data[i].name, target) == 0)
                    temp --;
            }
            if(temp == person_count)
            {
                printf("Target not found.\n");
            }
            else
            {
                fptr = fopen(FILE_NAME, "w");
                fprintf(fptr, "%d\n", temp);
                for(int i = 0; i < person_count; i++)
                {
                    if(strcmp(origin_data[i].name, target) != 0)
                    {
                        fprintf(fptr, "%s\n", origin_data[i].name);
                        fprintf(fptr, "%c\n", origin_data[i].sex);
                        fprintf(fptr, "%lf\n", origin_data[i].score);
                    }
                    
                }
                printf("Target %s is deleted\n", target);
            free(origin_data);
            }
        }
        fclose(fptr);
    }
}
void modify_data(char *target, char *name, char sex, double score)
{
    printf("this is modify function\n");
    printf("target name:%s\n", target);
    printf("modify to: name:%s, sex: %c, score: %lf", name, sex, score);
    FILE *fptr = fopen(FILE_NAME, "r");
    if(!fptr)
    {
        printf("Target not found.\n");
        fclose(fptr);
        return;
    }
    else
    {
        int person_count = 0;
        printf("\nopen existed file.\n");
        fscanf(fptr, "%d\n", &person_count);
        if(person_count == 0)
        {
            printf("Target not found.\n");
        }
        else
        {
            fclose(fptr);
            person *origin_data = get_all_data();
            int flag = 0;

            fptr = fopen(FILE_NAME, "w");
            fprintf(fptr, "%d\n", person_count);
            for(int i = 0; i < person_count; i++)
            {
                if(strcmp(origin_data[i].name, target) != 0)
                {
                    fprintf(fptr, "%s\n", origin_data[i].name);
                    fprintf(fptr, "%c\n", origin_data[i].sex);
                    fprintf(fptr, "%lf\n", origin_data[i].score);
                }
                else
                {
                    flag = 1;
                    fprintf(fptr, "%s\n", name);
                    fprintf(fptr, "%c\n", sex);
                    fprintf(fptr, "%lf\n", score);
                }
            }
            if(flag == 1)
                printf("Target %s is modified\n", target);
            else
                printf("Target %s is not found\n", target);
            free(origin_data);
        }
        fclose(fptr);
    }
}
int main()
{
    
    char ch;
    char *name = (char*)calloc(MAX, MAX*sizeof(char));
    char *target = (char*)calloc(MAX, MAX*sizeof(char));
    char sex;
    double score;
    while(1)
    {
        printf("\nCommand(h for help):");
        ch = _getche();
        switch(ch)
        {
            case 'h':
                printf("\n");
                printf("h to show this help;\n");
                printf("f to find a record by name;\n");
                printf("l to list all names in the file;\n");
                printf("i to insert a new record;\n");
                printf("d to delete a specified record;\n");
                printf("m to modify a specified record;\n");
                printf("q to quit.\n");
                break;
            case 'f':
                printf("\nEnter name:");
                scanf("%s", name);
                find_name(name);
                fflush(stdin);
                break;
            case 'l':
                printf("\n");
                list_all_name();
                break;
            case 'i':
                printf("\n");
                printf("Enter name:");
                gets(name);
                printf("Enter sex:");
                scanf("%c", &sex);
                printf("Enter score:");
                scanf("%lf", &score);
                insert_data(name, sex, score);
                fflush(stdin);
                printf("Insert finished.\n");
                break;
            case 'd':
                printf("\n");
                printf("Enter the name to be delete:");
                gets(target);
                delete_data(target);
                fflush(stdin);
                break;
            case 'm':
                printf("\n");
                printf("Enter the name to be modify:");
                gets(target);
                printf("Enter new name:");
                gets(name);
                printf("Enter new sex:");
                scanf("%c", &sex);
                printf("Enter new score:");
                scanf("%lf", &score);
                modify_data(target, name, sex, score);
                fflush(stdin);
                break;
            case 'q':
                printf("\nleaving process.\n");
                free(name);
                free(target);
                return 0;
                break;
            default:
                printf("\ninvalid command.");
                break;
        }
    }

    printf("leaving main\n");
    return 0;
}