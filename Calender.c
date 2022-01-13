
/*

6. Calendar
The program must have (at least) following operations:
1. initialize (empty the database)
2. save database to file
3. read database from file
4. add an event: user enters description, date, time and duration of an event
5. remove an event
6. print a report which prints all events sorted by date and time
7. search for a free time in the range of dates that user specifies


By student: Ahmed Al-Tuwaijari
date: 24.10.2021

*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>


#define SIZE 30
#define MAX_SIZE 100
#define FILE_NAME "CalendarDatabase.bin"

struct calendar{

    int id;
    char description[SIZE]; 
    char date[SIZE];
    char time[SIZE];
    char duration[SIZE];
};


void initializeDatabase(struct calendar *event, size_t size);
void printAll(struct calendar *event, size_t size);
void sortEvent(struct calendar *event, size_t size);
void addEvent(struct calendar *event, size_t size);
void removeEvent(struct calendar *event, size_t size);
void deleteSpace (char *word);
void searchfree(struct calendar *event, size_t size);


int main(){

    int option;
    int choice;
    struct calendar event[MAX_SIZE];
     
    while (1)
    {
        printf("\n\t\t****THE CALENDAR PROJECT****\n");
        printf("\n\t--------------------------------------------\n");
        printf("\n[1] Initialize database. \n[2] Print all events. \n[3] Add an event. \n[4] Remove an event. \n[5] Print all events stored by date and time. \n[6] Search for free time. \n[7] Quit the program. \nEnter your option:  ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            initializeDatabase( event, MAX_SIZE);
            printf("\n\tThe database has been initialized named %s.\n", FILE_NAME);
            break;
        case 2:
            printAll(event, MAX_SIZE);   // Printing all events
            break;
        case 3:
            addEvent(event, MAX_SIZE);   //adding new events
            break;
        case 4:
            removeEvent(event, MAX_SIZE);   //Removing events
            break;
        case 5:
            sortEvent(event, MAX_SIZE);  //sorting by date and time        
            break;
        case 6:
            searchfree(event, MAX_SIZE); // search free time
            break;
        case 7:
            printf("\n\tYou have succesfully quited the program.\n\n");
            return 0;
            break;
        default:
            printf("\n\tPlease choose an option above\n");
        }        
    }


    return 0;
}


void initializeDatabase(struct calendar *event, size_t size){
    FILE *fp = fopen(FILE_NAME, "wb");
    fclose(fp);

}
void addEvent(struct calendar *event, size_t size){
    int amount, i =1, j=0;
    
    while (i == 1)
    {
        printf("\n\n\tHow many event will you enter? ");
        scanf("%i", &amount);
        if (amount > size)
        {
            printf("\n\n\tThe allowed events to entered should be less or equal to %d ", MAX_SIZE);
            i=1;
        }else{
            i=0;
        }
        
    }
    
    
    
    while(j < amount && j < size){

        FILE *fp = fopen(FILE_NAME, "rb");
        srand(time(NULL));
        int r = (rand() % (100 - 1 + 1)) + 1;
        while (fread( &event[i], sizeof( struct calendar ), 1, fp))
        {
            if (r == event[i].id)
            {
                int r = (rand() % (100 - 1 + 1)) + 1;
            }
            i++;
        
            
        }
        event[j].id = r;
        fclose(fp);

        printf("\t\tEnter %d event description: ", j+1);
        fflush(stdin);
        fgets(event[j].description,SIZE,stdin);
        deleteSpace(event[j].description);
        

        printf("\t\tEnter %d event date [yyyy.mm.dd]: ", j+1);
        fflush(stdin);
        fgets(event[j].date,SIZE,stdin);
        deleteSpace(event[j].date);


        printf("\t\tEnter %d event time [hh:mm]: ", j+1);
        fflush(stdin);
        fgets(event[j].time,SIZE,stdin);
        deleteSpace(event[j].time);

        printf("\t\tEnter %d event duration [hh:mm]: ", j+1);
        fflush(stdin);
        fgets(event[j].duration,SIZE,stdin);
        deleteSpace(event[j].duration);
                 

        printf("\n\t\tThe %i event has been saved with ID %i.\n\n", j+1 ,event[j].id);

        FILE *ftp = fopen(FILE_NAME, "ab");
        fwrite( &event[j], sizeof( struct calendar ), 1, ftp);
        fclose(ftp);
    
        j++;       
    }  
}

void deleteSpace (char *word){
    word[strlen(word)-1] = 0;
}

void printAll(struct calendar *event, size_t size){
    int i=0;
    FILE *fp = fopen(FILE_NAME, "rb");
    printf("\n\t\t\t    *** LIST OF ALL EVENTS ***\n");
	printf("-----------------------------------------------------------------------------------\n");
	printf("%-5s%-5s%10s%23s%19s%20s\n", "NUM", "ID", "DESCRIPTION", "DATE", "TIME", "DURATION");
	printf("-----------------------------------------------------------------------------------\n");


    while(fread( &event[i], sizeof( struct calendar ), 1, fp)){
        printf("%-5i%-5i%-30s%-15s%9s%16s\n", i+1, event[i].id, event[i].description,
        event[i].date, event[i].time, event[i].duration);
        i++;
    }
    fclose(fp);
}

void removeEvent(struct calendar *event, size_t size){
    int ID, k=1 ;
    char answer;
    int count=0, h;
    
    while (k)
    {    
        int j=1, i =0;
        FILE *fp = fopen(FILE_NAME, "rb");

        printf("\n\n\tEnter event's ID you want to delete: ");
        scanf("%d",&ID);

        while (fread( &event[i], sizeof( struct calendar ), 1, fp) && i < size)
        {
            if(event[i].id != ID){
                FILE *ftp = fopen("copy.bin", "ab");
                fwrite( &event[i], sizeof( struct calendar ), 1, ftp);
                fclose(ftp);

            }
            if (event[i].id == ID)
            {
                printf("\nEvent found\n");
                printf("-----------------------------------------------------------------------------------\n");
	            printf("%-5s%10s%23s%19s%20s\n", "ID", "DESCRIPTION", "DATE", "TIME", "DURATION");
             	printf("-----------------------------------------------------------------------------------\n");
                printf("%-5i%-30s%-15s%9s%9s\n", event[i].id, event[i].description,
                event[i].date, event[i].time, event[i].duration);
                printf("\nThe event with the ID %d id deleted.\n ", ID);

                j = 0;  

            }
            
            i++;
        }
        remove(FILE_NAME);
        rename("copy.bin", FILE_NAME);
        fclose(fp);
        if( j == 1 ){
            printf("\n\tThe ID %i does not match to any of the events' IDs.\n", ID);

        }
        printf("\n\tDo you wish to keep deleting more events? [Y/N]: ");
        fflush(stdin);
        scanf("%c",&answer);

        if(answer== 'N'||answer =='n'){
            k = 0;
        }

        count = 0;
        
    }      
}
// Function to sort event first by date and if two events in same date then will sort them by time.
int date_cmp(const void* a, const void* b) {
    struct calendar *ia = (struct calendar*)a;
    struct calendar *ib = (struct calendar*)b;
    if (strcmp(ia->date , ib->date) == 0)
    {
        return strcmp(ia->time , ib->time);
    }else{
        return strcmp(ia->date , ib->date);
    }

}


void sortEvent(struct calendar *event, size_t size){
    int count=0;

    FILE *fp = fopen(FILE_NAME, "rb");
    while (fread( &event[count], sizeof( struct calendar ), 1, fp))
    {
            
        count++;
                   
    }

    qsort(event, count, sizeof(struct calendar), date_cmp);
    
    printf("\n\t\t\t    ==> REPORT OF ALL EVENTS SORTED BY DATE  & TIME <==\n");
	printf("-----------------------------------------------------------------------------------\n");
	printf("%-5s%-5s%10s%23s%19s%20s\n", "NUM", "ID", "DESCRIPTION", "DATE", "TIME", "DURATION");
	printf("-----------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++)
    {
        printf("%-5i%-5i%-30s%-15s%9s%16s\n", i+1, event[i].id, event[i].description,
        event[i].date, event[i].time, event[i].duration);
    }
    fclose(fp);
}

void searchfree(struct calendar *event, size_t size){
    int x=1, count=0, hh, mm, dh, dm, xh, ym, year, month, day;
    char answer;
    char date[15];
    bool found = true;
    bool something = true;
    FILE *fp = fopen(FILE_NAME, "rb");
    while (x == 1)
    {
        printf("\nEnter the day date to know if you have free time in that day [yyyy.mm.dd] : ");
        fflush(stdin);
        fgets(date, 12, stdin);
        deleteSpace(date);
        sscanf(date, "%4d.%2d.%2d", &year, &month, &day);
        
       
        while (fread( &event[count], sizeof( struct calendar ), 1, fp))
        {
            if (strcmp(event[count].date, date) == 0)
            {
                sscanf(event[count].time, "%2d:%2d", &hh, &mm);
                sscanf(event[count].duration, "%2d:%2d", &dh, &dm);
                xh = hh+dh;
                ym = mm+dm;
                if (ym >= 60)
                {
                    xh = xh + 1;
                    ym = ym - 60;
                }
                if (xh >= 24)
                {
                    
                    xh = xh - 24;
                    day = day +1;
                    printf("\nYou have [ %s ] event at %s which starts at %s and ends at %d.%d.%d, %d:%d \n\n", event[count].description, event[count].date, event[count].time, year, month, day, xh, ym );
                    something = false;

                }
                
                if (something)
                {
                    printf("\nYou have [ %s ] event at %s which starts at %s and ends at %d:%d \n\n", event[count].description, event[count].date, event[count].time, xh, ym );
                }
                
                
   
                found = false;
            }

            
            count++;
                   
        }
        
        if (found)
        {
            printf("\nYou have all the %s day free.\n\n", date);
        }

        printf("\nDo you wish to keep looking for free time? [Y/N]: ");
        fflush(stdin);
        scanf("%c",&answer);

        if(answer== 'N'||answer =='n'){
            x = 0;
        }
    }
    fclose(fp);
    
}