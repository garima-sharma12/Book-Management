//BT20CSE040 GARIMA SHARMA
//DSPD ASSIGNMENT-1
//BATCH R2

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct book_list{ //book list
	int id;
	char title[60];
	char author[40];
	char subject[30];
	int num_copy_issued;
	int num_copy_avail;
	struct book_list* book_next;
};

struct request_queue{ //request queue
	char student_name[30];
	char book_title[60];
	char subject[30];
	char author[40];
	int id;
	struct request_queue *stud_next;
};

struct borrower_list{ //borrower list
	int id;
	char name[30];
	char title[60];
	char subject[30];
	char author[40];
	int expected_return;
	int days_return;
	struct borrower_list *next_borrow;
};

struct defaulter{ //defaulters list
	int days;
	char name[30];
	char title[60];
	struct defaulter *next_def;
};


struct book_list * start_lib=NULL; //starting node pointer for book list
struct request_queue * start_req=NULL;//first node pointer for the request queue
struct borrower_list * start_borrow=NULL;// starting node for borrowers list
struct defaulter * start_def=NULL;// starting node for defaulters list

//display functions
void display_lib(struct book_list*);
void display_req(struct request_queue*);
void display_borrow(struct borrower_list *);
void display_defaulter(struct defaulter *);

//different operations for borrow,request,return,add books
struct book_list *initialize_lib(struct book_list *start);
struct request_queue *book_issue(struct request_queue *start_req);
struct borrower_list *book_return(struct borrower_list *start_borrow);
struct book_list *delete_book(int);

void main_menu();

//questions
void books_not_issued(struct book_list*);//book titles that are not issued by anyone
void books_avail(struct book_list*);//displays the requested books that are available
void max_req_stud(struct request_queue*);//student with the maximum requests
void max_book(struct book_list*);// displays the book that is in most demand
void asking_again(struct request_queue *);//displays names of students asking for books if already borrowed
void not_in_defaulter(struct request_queue *);//displays names of students in the request queue who will recieve books
void books_first3days(struct book_list *);// number of books that can be given in 3 days


int main()
{
	start_lib=initialize_lib(start_lib);
	main_menu();
	return 0;
}

void main_menu(){
	int option;
	do{
	printf("Enter your choice:\n");
	printf("1. Issue a book.\n");
	printf("2. List of books.\n");
	printf("3. Students request list.\n");
	printf("4. Return book.\n");
	printf("5. Students books borrowed list.\n");
	printf("6. Books that are not issued by anyone.\n");
	printf("7. Books available for issuing.\n");
	printf("8. Student with maximum requests.\n");
	printf("9. Book issued maximum number of times.\n");
	printf("10. Students requesting for more books after borrowing.\n");
	printf("11. Display defaulters list.\n");
	printf("12. Students who are eligible to get books.\n");
	printf("13. Books issued in 3 days.\n");
	printf("14. Exit\n");

	scanf("%d",&option);
	
	
	if (option==1){
		start_req=book_issue(start_req);
	}
	else if (option==2){
		display_lib(start_lib);
	}
	else if(option==3){
		printf("\nStudents in  request queue:\n");
		display_req(start_req);
	}
	else if(option==4){
		start_borrow=book_return(start_borrow);
	}
	else if(option==5){
		printf("\nBooks borrowed list:\n");
		display_borrow(start_borrow);
	}
	else if(option==6){
		printf("\nBooks which have not been issued by anyone:\n");
	     books_not_issued(start_lib);
	}
	else if(option==7){
		printf("\nAvailable books:\n");
		books_avail(start_lib);
	}
	else if(option==8){
		printf("\nStudent with the maximum requests:\n");
		max_req_stud(start_req);
	}
	else if(option==9){
		printf("\nBook issued maximum number of times:\n");
		max_book(start_lib);
	}
	else if(option==10){
		printf("\nStudents requesting for more books after borrowing:\n");
		asking_again(start_req);
	}
	else if(option==11){
		printf("\nList of defaulters:\n");
		display_defaulter(start_def);
	}
	else if(option==12){
	    printf("\nStudents eligible to make requests:\n");
	    not_in_defaulter(start_req);
	}
	else if(option==13){
		printf("\nNumber of books that can be given to students for a period of 3 days\n");
		books_first3days(start_lib);
	}
	else{
	printf("invalid option\n");
	}
	
	}while(option!=14);
}

struct book_list *initialize_lib(struct book_list *start)//creating book list
{
	struct book_list *ptr;
	struct book_list *new_book1,*new_book2,*new_book3,*new_book4,*new_book5,*new_book6;
	
    new_book1=(struct book_list *)malloc(sizeof(struct book_list));
    new_book1->book_next=NULL;
	start_lib=new_book1;
	new_book1->id=1;
	strcpy(new_book1->title,"8085 Microprocessor");
	strcpy(new_book1->author,"Ramesh Gaonkar");
	strcpy(new_book1->subject,"DCMP");
	new_book1->num_copy_issued=0;
	new_book1->num_copy_avail=2;
	ptr=new_book1;

	
	new_book2=(struct book_list *)malloc(sizeof(struct book_list));
	new_book2->book_next=NULL;
	new_book2->id=2;
	strcpy(new_book2->title,"C++: The Complete Reference");
	strcpy(new_book2->author,"Herbert Shildt");
	strcpy(new_book2->subject,"IOOM");
	new_book2->num_copy_issued=0;
	new_book2->num_copy_avail=3;
	ptr->book_next=new_book2;
	ptr=new_book2;
	
	new_book3=(struct book_list *)malloc(sizeof(struct book_list));
    new_book3->book_next=NULL;
	new_book3->id=3;
	strcpy(new_book3->title,"Data Structures and Program Design in C");
	strcpy(new_book3->author,"Robert L. Kruse");
	strcpy(new_book3->subject,"DSPD");
	new_book3->num_copy_issued=0;
	new_book3->num_copy_avail=4;
	ptr->book_next=new_book3;
	ptr=new_book3;
	
	new_book4=(struct book_list *)malloc(sizeof(struct book_list));
    new_book4->book_next=NULL;
	new_book4->id=4;	
	strcpy(new_book4->title,"Programming Language Pragmatics");
	strcpy(new_book4->author,"Michael L. Scott");
	strcpy(new_book4->subject,"CPL");
	new_book4->num_copy_issued=1;
	new_book4->num_copy_avail=1;
	ptr->book_next=new_book4;
	ptr=new_book4;
	
	new_book5=(struct book_list *)malloc(sizeof(struct book_list));
    new_book5->book_next=NULL;
	new_book5->id=5;	
	strcpy(new_book5->title,"Linear Algebra Done Right");
	strcpy(new_book5->author,"Sheldon Axler");
	strcpy(new_book5->subject,"Maths");
	new_book5->num_copy_issued=0;
	new_book5->num_copy_avail=2;
	ptr->book_next=new_book5;
	ptr=new_book5;
	
	new_book6=(struct book_list *)malloc(sizeof(struct book_list));
    new_book6->book_next=NULL;
	new_book6->id=6;	
	strcpy(new_book6->title,"Consise Mathematics");
	strcpy(new_book6->author,"RD Sharma");
	strcpy(new_book6->subject,"Maths");
	new_book6->num_copy_issued=0;
	new_book6->num_copy_avail=5;
	ptr->book_next=new_book6;
	ptr=new_book6;
	
	
	return start_lib;
}


struct request_queue *book_issue(struct request_queue *start_req) //book issue for request and borrow
{
    struct book_list *ptr;
    struct request_queue *ptr2,*new_student;
    struct borrower_list *ptr3, *new_borrow;
    struct defaulter *ptr4;
    
    char name[30];
    int n_flag;
    int n1,n2,n;
    int j=0,id;
    int i=1,flag=0;
    
    if(start_lib==NULL)
	{
        printf("No books left in the library to issue!\n");
    }
	else
	{
        system("cls");
        ptr=start_lib;
        while(ptr!=NULL)
		{
            printf("\nBook %d",i);
            printf("\nBook Title: %s",ptr->title);
            printf("\nName of Author: %s",ptr->author);
            printf("\nSubject: %s",ptr->subject);
            printf("\nBook ID: %d\n",ptr->id);
            printf("Number of copies available:%d\n",ptr->num_copy_avail);
            printf("Number of copies issued:%d\n",ptr->num_copy_issued);
            ptr=ptr->book_next;
            i++;
        }
       
        
        printf("\n\nEnter Student Details:\n");
        printf("Enter your Name:");
        scanf("%s",&name);
        printf("Enter the number of books to issue:");
        scanf("%d",&n);
        
        if(n<=3)
		{
        	n_flag=1;
		}
		else
		{
			n_flag=0;
		}
		
		if(n_flag==1)
		{
        while(j<n)
		{
		int no_of_days;
        printf("Enter book %d\n",j+1);
        printf("Enter the Book ID:");
        scanf("%d",&id);
        printf("Enter expected number of days for returning the book:");
        scanf("%d",&no_of_days);
        ptr=start_lib;
    	while(ptr!=NULL)
		{
            if(ptr->id==id)
			{
            	if(ptr->num_copy_avail>0)
				{
            		 flag=1;               
				}
               break;
            }
            ptr=ptr->book_next;
        }
	    ptr=start_lib;
        while(ptr!=NULL)
		{
        	if(ptr->id==id)
			{
        		break;
			}
			ptr=ptr->book_next;
		}
        
        new_student=(struct request_queue *)malloc(sizeof(struct request_queue));
        strcpy(new_student->student_name,name);
        strcpy(new_student->book_title,ptr->title);
        strcpy(new_student->author,ptr->author);
        strcpy(new_student->subject,ptr->subject);
        new_student->id=ptr->id;
        new_student->stud_next=NULL;
        if(start_req==NULL)
		{
                start_req=new_student;
        }
		else
		{
                ptr2=start_req;
                while(ptr2->stud_next!=NULL)
				{
                    ptr2=ptr2->stud_next;
                }
                ptr2->stud_next=new_student;
        }    
        int def_flag=1;
		ptr4=start_def;
		while(ptr4!=NULL){
			if(strcmp(ptr4->name,name)==0){
				def_flag=0;
				break;
			}
			ptr4=ptr4->next_def;
		}	
		if(flag==1 && def_flag==1)
		{ 
        ptr=start_lib;
        while(ptr!=NULL)
		{
        	if(ptr->id==id)
			{
        		break;
			}
			ptr=ptr->book_next;
		}
		
            new_borrow=(struct borrower_list *)malloc(sizeof(struct borrower_list));
            new_borrow->id=id;
            strcpy(new_borrow->title,ptr->title);
            strcpy(new_borrow->name,name);
            strcpy(new_borrow->author,ptr->author);
            strcpy(new_borrow->subject,ptr->subject);
            new_borrow->expected_return=no_of_days;
            new_borrow->next_borrow=NULL;
    
		    if(start_borrow==NULL)
			{
                start_borrow=new_borrow;
            }
			else
			{
                ptr3=start_borrow;
                while(ptr3->next_borrow!=NULL)
				{
                    ptr3=ptr3->next_borrow;
                }
                ptr3->next_borrow=new_borrow;
            }
            
			printf("Issue of Book ID %d done successfully!\n",new_borrow->id);
            start_lib=delete_book(new_borrow->id);
            
        }      	
        j++;
        }
    printf("\n Press any key to go to the main menu: ");
    getch();
    system("cls");
	}
	else
	{
		printf("Can't issue more than 3 books at a time");
		printf("\n\n Press any key to go to the main menu: ");
        getch();
        system("cls");
	}
	}
    return start_req;
}

void display_req(struct request_queue *start_req){
	struct request_queue *ptr;
	ptr=start_req;
	while(ptr!=NULL)
	{
		printf("Student name:%s\n",ptr->student_name);
		printf("Book:%s\n",ptr->book_title);
		printf("Book id:%d\n\n",ptr->id);
		ptr=ptr->stud_next;
	}
	printf("\n\nPress any key to go to main menu");
	getch();
	system("cls");
}

void display_borrow(struct borrower_list *start_borrow){
	struct borrower_list *ptr;
	ptr=start_borrow;
	while(ptr!=NULL)
	{
		printf("Student Name:%s\n",ptr->name);
		printf("Book name:%s\n",ptr->title);
		printf("Book id:%d\n",ptr->id);
		printf("Expected days until book return:%d\n\n",ptr->expected_return);
		ptr=ptr->next_borrow;
	}
	printf("\n\nPress any key to go to main menu\n");
	getch();
	system("cls");
}

void display_defaulter(struct defaulter *start_def){
	struct defaulter *ptr;
	ptr=start_def;
	while(ptr!=NULL)
	{
		printf("Name:%s\n",ptr->name);
		printf("Book Taken:%s\n",ptr->title);
		printf("Number of days:%d\n",ptr->days);
		ptr=ptr->next_def;
	}
	printf("\n\nPress any key to go to main menu\n");
	getch();
	system("cls");
}

struct borrower_list *book_return(struct borrower_list *start_borrow){ //returning the issued books
	struct borrower_list *ptr,*prev;
	struct book_list *ptr2;
	struct defaulter *ptr3,*new_def;
	struct request_queue *ptr4,*prev_4;
	
	char name[30];
	char title[60];
	int n1,n2,id_no;
	int found=0,days;
	int flag=0;

	
	printf("Enter book id:");
	scanf("%d",&id_no);
	printf("Enter your name:");
	scanf("%s",&name);
	printf("Enter number of days since the book was taken:");
	scanf("%d",&days);
	ptr2=start_lib;
	
	while(ptr2!=NULL)
	{
		if(ptr2->id==id_no)
		{
			strcpy(title,ptr2->title);
		}
		ptr2=ptr2->book_next;
	}
	
	if(days>15)
	{
	    int till=1;
		new_def=(struct defaulter*)malloc(sizeof(struct defaulter));
		strcpy(new_def->name,name);
		strcpy(new_def->title,title);
		new_def->days=days;
		new_def->next_def=NULL;
		
		ptr3=start_def;
		if(start_def==NULL)
		{
			start_def=new_def;
		}
		else
		{
			while(ptr3->next_def!=NULL)
			{
				ptr3=ptr3->next_def;
			}
			ptr3->next_def=new_def;
		}
		ptr4=start_req;
	    while(ptr4!=NULL)
		{
		if(ptr4->id=id_no && strcmp(ptr4->student_name,name)!=0)
		{
			till++;
			ptr4=ptr4->stud_next;
		}
		else
		{
			break;
		}
	
	   }
	ptr4=start_req;
	if(till==1)
	{
			start_req=start_req->stud_next;
			free(ptr4);
	}
	else
	{
		ptr4=start_req;
		while(ptr4->id!=id_no && strcmp(ptr4->student_name,name))
		{
			prev_4=ptr4;
			ptr4=ptr4->stud_next;
		}
			prev_4->stud_next=ptr4->stud_next;
			free(ptr4);
	}	
	}
	
	ptr=start_borrow;
while(ptr!=NULL)
{
	if(ptr->id==id_no)
	{
		flag=1;
		if(strcmp(name,ptr->name)==0)
		{
		found=1;
		break;
	    }
	}	
	ptr=ptr->next_borrow;
}	

if (found==1)
{
	int c=0,d=1;
	ptr2=start_lib;
	
	while(ptr2!=NULL)
	{
		if(ptr2->id==id_no)
		{
			n1=ptr2->num_copy_avail;
			n1=n1+1;
			ptr2->num_copy_avail=n1;	
		}
		ptr2=ptr2->book_next;
	}
	ptr=start_borrow;
	while(ptr!=NULL)
	{
		c++;
		ptr=ptr->next_borrow;
	}
	ptr=start_borrow;
	while(ptr!=NULL)
	{
		if(ptr->id!=id_no && strcmp(ptr->name,name)!=0)
		{
			d++;
			ptr=ptr->next_borrow;
		}
		else
		{
			break;
		}
	}
	ptr=start_borrow;
	if(d==1)
	{
			printf("Student Name:%s\n",name);
			printf("Book Name:%s\n",title);
			printf("Book id:%d\n",id_no);
			printf("Book returned\n\n");
			start_borrow=start_borrow->next_borrow;
			free(ptr);
	}
	else
	{
		ptr=start_borrow;
		while(ptr->id!=id_no && strcmp(ptr->name,name))
		{
			prev=ptr;
			ptr=ptr->next_borrow;
		}
			printf("Student Name:%s\n",name);
			printf("Book Name:%s\n",title);
			printf("Book id:%d\n",id_no);
			printf("Book returned\n\n");
			prev->next_borrow=ptr->next_borrow;
			free(ptr);
	}

	
	
	printf("Press any key to go to main menu\n");
	getch();
	system("cls");
	
}
else
{
	printf("Sorry we couldn't find the book id!PLease recheck.\n");
	printf("Press any key to go back to main menu\n");
	getch();
	system("cls");
}	
	return start_borrow;
}



struct book_list *delete_book(int id) //decrementing the available book when it is borrowed
{
	struct book_list *ptr,*prev;
	int c=0,n1,n2;
	ptr=start_lib;
 
	ptr=start_lib;
	while(ptr!=NULL)
	{
		if(ptr->id==id)
		{
			n1=ptr->num_copy_avail;
			n2=ptr->num_copy_issued;
			if(n1>0)
			{
			n1--;
			ptr->num_copy_avail=n1;
			n2++;
			ptr->num_copy_issued=n2;
	    	}
			break;	
    	}
	ptr=ptr->book_next;
	}
	return start_lib;
}

void display_lib(struct book_list *start_lib)
{
	struct book_list *ptr;
	ptr=start_lib;
		while(ptr!=NULL)
		{
			printf("\nBOOK %d\n",ptr->id);
			printf("Title:%s\n",ptr->title);
			printf("Author:%s\n",ptr->author);
			printf("Subject:%s\n",ptr->subject);
			printf("Number of copies available:%d\n",ptr->num_copy_avail);
			printf("Number of copies issued:%d\n",ptr->num_copy_issued);
			printf("\n");
			ptr=ptr->book_next;
		}

}


void books_not_issued(struct book_list* start_lib)
{
	struct book_list *ptr;
	ptr=start_lib;
	while(ptr!=NULL)
	{
		if (ptr->num_copy_issued==0)
		{
			printf("%s\n",ptr->title);
		}
		ptr=ptr->book_next;
	}
	printf("\n\n");
		
 	printf("\nPress any key to go to main menu\n");
	getch();
	system("cls");
}


void books_avail(struct book_list *start_lib)
{
	struct book_list *ptr;
	ptr=start_lib;
	while(ptr!=NULL)
	{
		if(ptr->num_copy_avail>0)
		{
			printf("%s\n",ptr->title);
		}
		ptr=ptr->book_next;
	}
	printf("\n\n");
	
	printf("\nPress any key to go to main menu\n");
	getch();
	system("cls");
}


void max_book(struct book_list*start_lib)
{
	struct request_queue *ptr,*next;
	struct book_list *ptr2;
	int max_id;
	int check=0;
	int sum=1,count=0;
	int max=-1;
	ptr=start_req;
	while(ptr!=NULL)
	{
	    next=ptr->stud_next;
	    while(next!=NULL)
		{
	    	if(next->id==ptr->id)
			{
	    	sum=sum+1;
	    	}
		
			next=next->stud_next;
		}
	    
		if(sum>max)
		{
			max=sum;
		}
		
		max_id=ptr->id;
		ptr=ptr->stud_next;
	}
	
	ptr2=start_lib;
	while(ptr2!=NULL){
		if(ptr2->id==max_id){
			check=1;
			printf("%s\n",ptr2->title);
		}
		ptr2=ptr2->book_next;
		
	}
	if(check==0){
		printf("Many books have the same number of requests.\n");
	}
	printf("\n\n");
}


void max_req_stud(struct request_queue *start_req)
{
	struct request_queue *ptr,*next;
	char name[30];
	int count;
	int check=0;
	char max_name[30];
	int max=-1;
	ptr=start_req;
	while(ptr!=NULL)
	{
		strcpy(name,ptr->student_name);
		next=ptr->stud_next;
		while(next!=NULL)
		{
				if(strcmp(name,next->student_name)==0)
				{
			        count=count+1;
	        	}
	        	next=next->stud_next;
		}
		if(count>max)
		{
			max=count;
			strcpy(max_name,name);
		}
	ptr=ptr->stud_next;
	}
	ptr=start_req;
	while(ptr!=NULL)
	{
		if(strcmp(max_name,ptr->student_name)==0)
		{
			check=1;
			printf("%s\n",max_name);
			break;
		}
		ptr=ptr->stud_next;
	}
	if(check==0){
		printf("Many students may have the same number of maximum requests.\n");
	}
	printf("\n\n");
}


void asking_again(struct request_queue *start_req)
{
	struct request_queue*ptr;
	struct borrower_list *ptr2;
	char name[30];
	
	ptr=start_req;
	ptr2=start_borrow;
	
	while(ptr2!=NULL)
	{
	int count=0;
		strcpy(name,ptr2->name);
		while(ptr!=NULL)
		{
			if(strcmp(name,ptr->student_name)==0){
				count=count+1;
			}
			ptr=ptr->stud_next;
		}
		if(count>1){
			printf("%s\n",name);
		}
		ptr2=ptr2->next_borrow;
	}
}



void not_in_defaulter(struct request_queue *start_req)
{
	struct request_queue *ptr;
	struct defaulter *ptr2;
	char name[30];
	
	ptr=start_req;
    while(ptr!=NULL)
	{
    	int flag=1;	
    	strcpy(name,ptr->student_name);
    	ptr2=start_def;
    	while(ptr2!=NULL)
		{
    		if(strcmp(name,ptr2->name)==0)
			{
    			flag=0;
    			break;
			}
			ptr2=ptr2->next_def;
		}
		
		if(flag==1)
		{
			printf("%s will get the book %s\n",name,ptr->book_title);
		}
		
    	ptr=ptr->stud_next;
	}
	printf("\n\n");
}



void books_first3days(struct book_list *start_lib)
{
	struct book_list *ptr;
	struct borrower_list *ptr2;
	ptr=start_lib;
	int n=0,n1,n2;

	while(ptr!=NULL)
	{
		n1=ptr->num_copy_avail;
		n=n+n1;
		ptr=ptr->book_next;
		
	}

	if(start_borrow!=NULL)
	{
		ptr2=start_borrow;
		while(ptr2!=NULL)
		{
		n2=ptr2->expected_return;
		if(n2<=3)
		{
			n=n+1;
		}
		ptr2=ptr2->next_borrow;
		}	
	}
	printf("Number of books that can be given:%d\n\n\n",n);
}
