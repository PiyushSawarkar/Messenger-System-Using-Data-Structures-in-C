#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
void startup();
struct no{
	struct no *ne;
	char name[30],mob[30];
};//for stack ,is with each and every person
struct nod{
	struct nod *nex;
	char name[30],mob[30],msg[30];
};//for Queue , is with each and every person
struct node{
	struct nod *f,*r;
	struct no *top;
	struct node *next,*prev;
	int codeid;
	char name[30],mob[30],status[30];
};//for doubly linked lists --->the main Database
struct node *start = NULL;
void viewAllRec(){
	struct node *ptr;
	printf("\n");
	ptr=start;
	if(ptr==NULL){
		printf("\nNo records found :(\n");
	}
	else{
		while(ptr!=NULL){
			printf(" # [ codeid = %d ,name = %s , Mob. = %s , status = %s ] #\n",ptr->codeid,ptr->name,ptr->mob,ptr->status);
			ptr=ptr->next;
		}
	}	
}	
void searchRec(){
	struct node *ptr;
	int flag=0;
	char mob[30];
	printf("\nEnter Mobile number to be searched : ");
	scanf("%s",mob);
	ptr=start;
	while(ptr!=NULL){
		if(strcmp(ptr->mob,mob)==0){
			printf("\nRecord Found :) !!!\nThe details are :\n");
			printf(" # [ codeid = %d , name = %s , Mob. = %s , status = %s ] #\n",ptr->codeid,ptr->name,ptr->mob,ptr->status);
			ptr=ptr->next;
			flag=1;
			break;
		}
		ptr=ptr->next;
	}
	if(flag==0){
		printf("\nRecord not found :( \n");
	}
}
void leave(){
	char mob[30];
	struct node *ptr;
	printf("Enter Your Mobile Number : ");
	scanf("%s",mob);
	ptr=start;
	while(ptr!=NULL){
		if(strcmp(ptr->mob,mob)==0){
			printf("\nRecord Found.\nRecord deleted successfully.\n");
			strcpy(ptr->name,"0");
			strcpy(ptr->mob,"0");
			strcpy(ptr->status,"unallocated");
			strcpy(ptr->name,"0");
			ptr->f=ptr->r=NULL;ptr->top=NULL;
		}
		ptr=ptr->next;
	}
}
void push(char recMob[],char name[],char mob[]){
	struct no *nn;
	struct node *ptr;
	nn=(struct no*)malloc(sizeof(struct no));
	strcpy(nn->name,name);
	strcpy(nn->mob,mob);
	nn->ne=NULL;
	ptr=start;
	while(ptr!=NULL){
		if(strcmp(ptr->mob,recMob)==0){
			if(ptr->top==NULL){
				nn->ne=NULL;
				ptr->top=nn;
				
			}
			else{
				nn->ne=ptr->top;
				ptr->top=nn;
			}
		}
		ptr=ptr->next;
	}
}//for stack
void pop(char mob[]){
	struct node *ptr;
	struct no *temp;
	int flag=0;
	ptr=start;
	while(ptr!=NULL){
		if(strcmp(ptr->mob,mob)==0){
			if(ptr->top==NULL){
				printf("\nNo recent Contacts left to be viewed . . .");
				flag=1;
			}
			else{
				printf(" # [ name = %s , mob = %s ] # \n",ptr->top->name,ptr->top->mob);
				temp=ptr->top;
				ptr->top=ptr->top->ne;
				free(temp);
				
			}
			if(flag==0){
				pop(mob);
			}
			else if(flag==1){
				break;
			}
		}
		ptr=ptr->next;
	}
}//for stack
void enqueue(char recMob[],char msg[],char name[],char mob[]){
	struct nod *nn;
	struct node *ptr;
	nn=(struct nod*)malloc(sizeof(struct nod));
	//printf("%s %s %s %s",recMob,msg,name,mob);
	strcpy(nn->name,name);
	strcpy(nn->mob,mob);
	strcpy(nn->msg,msg);
	nn->nex=NULL;
	ptr=start;
	while(ptr!=NULL){
		if(strcmp(ptr->mob,recMob)==0){
			if(ptr->f==NULL){
				ptr->f=ptr->r=nn;
				ptr->r->nex=ptr->f->nex=NULL;
				
			}
			else{
				ptr->r->nex=nn;
				ptr->r=nn;
				ptr->r->nex=NULL;
			}
		}
		ptr=ptr->next;
	}
}//for queue
void dequeue(char mob[]){
	struct node *ptr;
	int flag=0;
	struct nod *temp;
	ptr=start;
	while(ptr!=NULL){
		if(strcmp(ptr->mob,mob)==0){
			if(ptr->f==NULL){
				printf("\nNo recent messages left to be viewed . . .");
				flag=1;
			}
			else{
				printf(" # [ name = %s , mob = %s , msg = %s ] # \n",ptr->f->name,ptr->f->mob,ptr->f->msg);
				temp=ptr->f;
				ptr->f=ptr->f->nex;
				free(temp);
				
			}
			if(flag==0){
				dequeue(mob);
			}
			else if(flag==1){
				break;
			}
		}
		ptr=ptr->next;
	}
}//for queue
void login(){
	int flag=0;int opt;
	struct node *ptr,*ptr1;
	char name[30],mob[30],recName[30];
	char recMob[30],msg[30];
	printf("\n< Hint: username is name while signup and password is mobile number >\n");
	printf("\nEnter username : ");
	scanf("%s",name);
	printf("\nEnter password : ");
	scanf("%s",mob);
	ptr=start;
	while(ptr!=NULL){
		if(strcmp(ptr->name,name)==0&&strcmp(ptr->mob,mob)==0){
			flag=1;
			while(1){
			printf("\nEnter your choice:\n1.Send a Message\n2.View All Recieved Msg\n3.view Recent contacts\n4.Logout\n");
			scanf("%d",&opt);
				switch(opt){
					case 1:
							printf("\nWhom do you want to send message ? ... enter mobile number : ");
							scanf("%s",recMob);
							printf("\nEnter Message\n");
							scanf("%s",msg);
							
							enqueue(recMob,msg,name,mob);//enqueue in recievers queue ur name , mob , msg
														
							ptr1=start;
							while(ptr1!=NULL){
								if(strcmp(ptr1->mob,recMob)==0){
									strcpy(recName,ptr1->name);
									strcpy(recMob,ptr1->mob);
								}
								ptr1=ptr1->next;
							}
							//printf("%s %s %s %s %s    ",recMob,msg,name,mob,recName);
							push(mob,recName,recMob);//in ur stack push recevers name , mob 
							push(recMob,name,mob);//in recievers stack	push ur name , mob						
							break;
					case 2:
							//printf("%s",mob);///////////////////////////////////////////////////////////////////////////
							dequeue(mob);//dequeue my queue completely
							break;
					case 3:
							//printf("%s",mob);///////////////////////////////////////////////////////////////////////////
							pop(mob);//pop my stack completely
							break;
					case 4:	
							startup();
							break;
					default:
							printf("\nWrong choice pressed\n");
				}
			}
			break;
		}
		ptr=ptr->next;
	}
	if(flag==0){
		printf("login failed :(\n");
	}
}

void signup(){
	char name[30],mob[30];
	struct node *nn,*ptr;
	int flag=0;
	printf("\nEnter Username : ");
	scanf("%s",name);
	printf("\nEnter Mobile Number : ");
	scanf("%s",mob);
	nn=(struct node *)malloc(sizeof(struct node));
	strcpy(nn->name,name);
	strcpy(nn->mob,mob);
	strcpy(nn->status,"allocated");
	ptr=start;
	if(ptr==NULL){
		start=nn;
		nn->next=NULL;
		nn->prev=NULL;
		nn->f=NULL;nn->r=NULL;nn->top=NULL;
		nn->codeid=1;
		printf("\nSignup Succesfull :)\n");
	}
	else{
		
		while(ptr!=NULL){
			if(strcmp(ptr->status,"unallocated")==0){
				flag=1;
				strcpy(ptr->name,name);
				strcpy(ptr->mob,mob);
				strcpy(ptr->status,"allocated");
				ptr->f=NULL;ptr->r=NULL;ptr->top=NULL;
				break;
			}
			ptr=ptr->next;
		}
		if(flag==1){
			printf("\nSignup Succesfull :)\n");
		}
		else{
			ptr=start;
			while(ptr->next!=NULL){
				ptr=ptr->next;
			}
			nn->prev=ptr;
			ptr->next=nn;
			nn->next=NULL;
			nn->codeid=nn->prev->codeid+1;
			nn->f=NULL;nn->r=NULL;nn->top=NULL;
			printf("\nSignup Succesfull :)\n");
		}
	}	
}
void admin(){
	int opt;
	while(1){
		printf("\nEnter Your Choice :\n");
		printf("\n1.Search a Record\n2.View all Records\n3.logout\n\n");
		scanf("%d",&opt);
		switch(opt){
			case 1:
					searchRec();
					break;
			case 2:
					viewAllRec();
					break;
			case 3:
					startup();
					break;
			default:
					printf("\nWrong Option Pressed :(\n");
					
		}
	}
}
void startup(){
	int opt;
	while(1){
		printf("\nEnter Your Choice :\n");
		printf("\n1.Admin Panel\n2.signup\n3.login\n4.leave\n5.Exit\n");
		scanf("%d",&opt);
		switch(opt){
			case 1:
					admin();
					break;
			case 2:
					signup();
					break;
			case 3:
					login();
					break;
			case 4:
					leave();
					break;
			case 5:
					printf("\nProgram Ended Successfully :) \n\n");
					exit(0);
			default:
					printf("\nWrong Option Pressed :( \n");
					
		}
	}
}
int main(void){
	startup();
	return(0);
}