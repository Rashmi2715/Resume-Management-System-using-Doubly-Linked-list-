#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
typedef struct node {
    char name[30];
    int age;
    char university[100];
    char branch[100];
    char year[100];
    float cgpa;
    char relavent_courses[100];
    char work_experience[100];
    char hobbies[100];
    char email[100];
    struct node *prev;
    struct node *next;
}node;


void signup();
void signin();
void home();
void delay(int number_of_seconds);
void empty(node *head);
void insert(node **last, char name[30], int age, char university[100], char branch[100], char year[100], float cgpa, char relavent_courses[100], char work_experience[100], char hobbies[100], char email[100]);
void display(node *head);
void deleteByExperience(node **head);
void deleteByCGPA(node **head);
void sort_by_cgpa(node **head) ;
void sort_by_name(node **head) ;

int main() 
{
	system("color 03");
    printf("\t\tWELCOME TO RESUME MANAGEMENT SYSTEM\n");
    int n;
    printf("\t\t1.PRESS 1 FOR SIGNUP\n\t\t2.PRESS 2 FOR SIGNIN\n\t\t3.PRESS 3 FOR EXIT\n");
    while (1) {
        printf("\n\t\tENTER YOUR CHOICE: ");
        scanf("%d", &n);

        switch (n) {
        case 1:
            signup();
            break;
        case 2:
            signin();
            break;
        case 3:
            exit(0);
        }
    }
    return 0;
}


void signup() {
    FILE* fp;
	fp = fopen("sign.txt", "a");
    char user[10], pass[10];
    printf("\t\tENTER USERNAME: ");
    scanf("%s", user);
    printf("\t\tENTER PASSWORD: ");
    scanf("%s", pass);
    fprintf(fp, "%s\t%s\n", user, pass);
    fclose(fp);
}


void signin() {
    system("cls");
    char user[10], pass[10];
    char fuser[10], fpass[10];
    int f, i = 0;
    char ch;
    printf("\t\tENTER USERNAME: ");
    scanf("%s", user);
    printf("\t\tENTER PASSWORD (should be maximum of 10 characters): ");
    i = 0;
    while ((ch = getch()) != 13) {
        pass[i] = ch;
        printf("*");
        i++;
    }
    pass[i] = '\0';
    FILE* fp;
    fp = fopen("sign.txt", "r");
    f = 0;
    while (fscanf(fp, "%s\t%s\n", fuser, fpass) != EOF) {
        if (strcmp(user, fuser) == 0 && strcmp(pass, fpass) == 0) {
            f = 1;
            break;
        }
    }
    if (f == 1) {
        printf("\n\t\tloading\n");
        for (i = 0; i < 3; i++)
            delay(1);
        printf("\n\t\tWelcome %s\n", user);
        home();
    } else {
        printf("\n\t\tInvalid Username or Password\n");
    }
    fclose(fp);
}


void delay(int number_of_seconds) 
{
    int milli_seconds = 1000 * number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds)
        ;
}


void home ()
{
    node *head = NULL;
    node *p = NULL;
    node *temp;
    FILE *infile = fopen("resume3.txt", "r");

    if (infile == NULL) {
        printf("Unable to open the file.\n");
        
    }

    int fileEmpty = 1;
    int scannedItems;

    while (1) {
        p = (node *)malloc(sizeof(node));
        scannedItems = fscanf(infile, "%29s", p->name);
        if (scannedItems == EOF) {
            free(p);
            break; // End of file
        }

        fileEmpty = 0; // File is not empty
        fscanf(infile, "%d", &p->age);
        fscanf(infile, "%99s", p->university);
        fscanf(infile, "%99s", p->branch);
        fscanf(infile, "%99s", p->year);
        fscanf(infile, "%f", &p->cgpa);
        fscanf(infile, "%99s", p->relavent_courses);
        fscanf(infile, "%99s", p->work_experience);
        fscanf(infile, "%99s", p->hobbies);
        fscanf(infile, "%99s", p->email);

        if (head == NULL) 
        {
            head = temp = p;
            head->next = head->prev = NULL;
        } 
        else 
        {
            temp->next = p;
            p->prev = temp;
            temp = temp->next;
        }
    }

    fclose(infile);
    int ch;
    char n[100], rc[100], u[100], y[100], e[100], h[100], we[100], b[100], re[100];
    int a;
    float cg;

    while (1) {
        printf("\n0. Exit\n1. Insert\n2. Delete candidates based on CGPA\n3. Delete candidates based on Work Experience\n4. Display the sorted list of candidates based on CGPA\n5. Display the sorted list of candidates based on Work Experience\n6. Display the entire list of candidates\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 0:
                empty(head);
                exit(0);
                break;
            case 1:
                printf("Name of applicant : ");
                scanf("%s", n);
                printf("Age : ");
                scanf("%d", &a);
                printf("University : ");
                scanf("%s", u);
                printf("Branch: ");
                scanf("%s", b);
                printf("The duration of course : ");
                scanf("%s", y);
                printf("CGPA: ");
                scanf("%f", &cg);
                printf("Relevant Courses: ");
                scanf("%s", re);
                printf("Work Experience: ");
                scanf("%s", we);
                printf("Hobbies: ");
                scanf("%s", h);
                printf("Email: ");
                scanf("%s", e);
                insert(&head, n, a, u, b, y, cg, re, we, h, e);
                break;
			case 2:
                deleteByCGPA(&head);
                printf("Deleting people with CGPA less than 7.5......\nCOmpleted");
                display(head);
				break;
			case 3:
                deleteByExperience(&head);
                printf("Deleting people with zero expereince....\nCompleted");
                display(head);
				break;
			case 4:
                sort_by_cgpa(&head);
                display(head);
				break;
			case 5:
                sort_by_name(&head);
                display(head);
				break;
            case 6:
                if (fileEmpty) {
                    printf("File is empty.\n");
                } else {
                    display(head);
                }
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

}


void empty(node *head) {
     node *p;
    while (head != NULL) {
        p = head;
        head = head->next;
        free(p);
    }
}


void display(node *head) {
    node *current = head;
	int applicant_no=0;
	do{
		++applicant_no;
		printf("Applicant no.:%d\n",applicant_no);
        printf("Name: %s\n", current->name);
        printf("Age: %d\n", current->age);
        printf("University: %s\n", current->university);
        printf("Branch: %s\n", current->branch);
        printf("Year: %s\n", current->year);
        printf("CGPA: %.2f\n", current->cgpa);
        printf("Relavent courses: %s\n", current->relavent_courses);
        printf("Work Experience: %s\n", current->work_experience);
        printf("Hobbies: %s\n", current->hobbies);
        printf("Email: %s\n", current->email);
        printf("\n");
        current = current->next;
    }while (current != NULL); 
    printf("Total number of applicants: %d\n",applicant_no);
}


void insert(node **head, char name[30], int age, char university[100], char branch[100], char year[100], float cgpa, char relavent_courses[100], char work_experience[100], char hobbies[100], char email[100]) 
{
	node *temp, *p;
    p = (*head);
    temp = (node *)malloc(sizeof(node));
    strcpy(temp->name, name);
    temp->age = age;
    strcpy(temp->university, university);
    strcpy(temp->branch, branch);
    strcpy(temp->year, year);
    temp->cgpa = cgpa;
    strcpy(temp->relavent_courses, relavent_courses);
    strcpy(temp->work_experience, work_experience);
    strcpy(temp->hobbies, hobbies);
    strcpy(temp->email, email);
    temp->next = NULL;
    if(*head == NULL)
    {
        *head = temp;
    }
    else
    {
        while(p->next!=NULL)
        {
            p = p->next;
        }
        p->next = temp;
        temp->prev = p;
    }
}


void deleteByExperience(node** head) {
    node* current = *head;

    while (current != NULL) {
        if (strcmp(current->work_experience, "NULL") == 0) {
            if (current->prev == NULL) {
                *head = current->next;
                if (current->next) {
                    current->next->prev = NULL;
                }
                free(current);
                current = *head;
            } else {
                current->prev->next = current->next;
                if (current->next) {
                    current->next->prev = current->prev;
                }
                free(current);
                current = current->prev->next;
            }
        } else {
            current = current->next;
        }
    }
}


void deleteByCGPA(node** head) {
    node* current = *head;

    while (current != NULL) {
        if (current->cgpa < 7.5) {
            if (current->prev == NULL) {
                *head = current->next;
                if (current->next) {
                    current->next->prev = NULL;
                }
                free(current);
                current = *head;
            } else {
                current->prev->next = current->next;
                if (current->next) {
                    current->next->prev = current->prev;
                }
                free(current);
                current = current->prev->next;
            }
        } else {
            current = current->next;
        }
    }
}


void sort_by_cgpa(node **head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    node *temp;
    
    do {
        swapped = 0;
        node *curr = *head;

        while (curr->next != NULL) {
            if (curr->cgpa < curr->next->cgpa) {
                temp = curr->next;
                
                if (curr->prev != NULL) {
                    curr->prev->next = temp;
                } else {
                    *head = temp;
                }
                
                if (temp->next != NULL) {
                    temp->next->prev = curr;
                }
                
                curr->next = temp->next;
                temp->prev = curr->prev;
                temp->next = curr;
                curr->prev = temp;
                
                swapped = 1;
            }
            else {
                curr = curr->next;
            }
        }
    } while (swapped);
}

void sort_by_name(node **head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    node *temp;
    
    do {
        swapped = 0;
        node *curr = *head;

        while (curr->next != NULL) {
            if (strcmp(curr->name,curr->next->name)>0) {
                temp = curr->next;
                
                if (curr->prev != NULL) {
                    curr->prev->next = temp;
                } else {
                    *head = temp;
                }
                
                if (temp->next != NULL) {
                    temp->next->prev = curr;
                }
                
                curr->next = temp->next;
                temp->prev = curr->prev;
                temp->next = curr;
                curr->prev = temp;
                
                swapped = 1;
            }
            else {
                curr = curr->next;
            }
        }
    } while (swapped);
}
