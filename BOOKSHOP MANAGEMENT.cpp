#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#define MAX 500

void newentry();
void edit(char e_bnam[100]);
void billing();
void search();

void mainmenu()
{
	int ch,ach,flag;
	char unam[100],pw[100];
	char uname[100],pwrd[100],urnam[100],pswrd[100];
	char ebnam[100];
	FILE *fp, *fptr;
	do
	{
		printf("\n\n\t\t\t\t***************WELCOME TO BOOKSHOP****************");
		printf("\n\n\t\tMAIN MENU");
		printf("\n Press <1> if Admin");
		printf("\n Press <2> if Customer");
		printf("\n Press <0> to exit");
		printf("\n\n Enter choice  ::  ");
		scanf("%d",&ch);
	switch(ch)
	{
		case 1 :
			{
			 printf("\n Enter Username  :: ");
			 scanf("%s",unam);
			 printf("\n Enter Password  :: ");
			 scanf("%s",pw);
			 fp=fopen("password.txt","r");
			 fscanf(fp,"%s %s",uname,pwrd);
			 if(((strcmp(unam,uname))==0)&&((strcmp(pw,pwrd))==0))
			 {  
			   do
			    {
			 	printf("\n\n\nPress <1> to create new entry for book");
            	printf("\nPress <2> to edit the record");
	            printf("\nPress <3> to change username and password");
	            printf("\nPress <4> to create sales record");
	            printf("\nPress <0> to go to main menu");
	            printf("\n\nEnter choice  :: ");
	            scanf("%d",&ach);
	            switch(ach)
	               {
	            	case 1 :
	            		{
	            			newentry();
	            			break;
						}
					case 2 :
						{
							printf("\nEnter the exact name of the book  :: ");
							scanf("%s",ebnam);
							edit(ebnam);
							break;
						}
					case 3 :
						{ 
						    printf("\nEnter the new Username   :: ");
						    scanf("%s",urnam);
						    printf("\nEnter the new password   :: ");
						    scanf("%s",pswrd);
						    fclose(fp);
						    flag=1;
							remove("password.txt");
							fptr=fopen("password.txt","a");
							fprintf(fptr,"%s %s",urnam,pswrd);
							fclose(fptr);
							break;
						}
					case 4 :
						{
							billing();
						}
					case 0 :
						{
							mainmenu();
						}
					default :
						{
							printf("\n\n\t\tInvalid selection!!!!!");
						}
			    	}//end of switch
	            }while(ach!=0);
			 }//end of if
			 else
			 {
			 	printf("\n\n\tInvalid Username or Password");
			 }
			 if(flag!=1)
			 {
			 fclose(fp);
             }
			 break;
			}//end of main case 1
		case 2 :
			{
			 search();
			 break;
			}
		case 0 :
		    {
		      exit(0);
			}
		default:
			{
				printf("\t\t\tInvalid choice !!!");
			}
	}//end of main switch
	getch();
    } while(ch!=0);
}

void newentry()
{
	FILE *fp;
	char bnam[100];
	char aut[100];
	char loc[100];
	long int price;
	long int count;
	
	printf("\nEnter Name of the book                 :: ");
	scanf("%s",bnam);
	
	printf("\nEnter Author name                      :: ");
	scanf("%s",aut);
	
	printf("\nEnter location                         :: ");
	scanf("%s",loc);
	
	printf("\nEnter price of the book(numbers only)  :: ");
	scanf("%ld",&price);
	 
	printf("\nEnter count of the book(numbers only)  :: ");
	scanf("%ld",&count);
	
	fp=fopen("Record.txt","a");
	
	fprintf(fp,"\n%s %s %s %ld %ld\n",bnam,aut,loc,price,count);
	fclose(fp);
	printf("\n\tRecord written successfully!!!!");
    
}

void edit(char e_bnam[20])
{
  	FILE *fp , *fptr1, *fptr2;
    int  linectr = 1,lno=1;
    char str[MAX];        
	char ebname[100],eaut[100],eloc[100],eeloc[100];
	long int ecount,eprice,eecount,eeprice;
	int flag;
  	fp=fopen("Record.txt","r");
  	
  	//while loop to find line number of the date and to check if record exists
  	while(fscanf(fp,"%s %s %s %ld %ld",ebname,eaut,eloc,&eprice,&ecount)!=EOF)
  	{
  		if(strcmp(ebname,e_bnam)==0)
  		{
  		   flag=1;
	       break; 
	    }
	    else
	    {
	    	lno++;
	    	flag=0;
		}
	}
	fclose(fp);
	if(flag==1)
	{
	fptr1=fopen("Record.txt","r");
	fptr2=fopen("temp.txt","w");
	printf("\nEnter the location to be changed        :: ");
	scanf("%s",eeloc);
	printf("\nEnter the price to be changed           :: ");
	scanf("%ld",&eeprice);
	printf("\nEnter the count to be changed           :: ");
	scanf("%ld",&eecount);
	
	    // copy all contents to the temporary file other except specific line
        while (fscanf(fptr1,"%s %s %s %ld %ld",ebname,eaut,eloc,&eprice,&ecount)!=EOF) 
        {
                if (linectr != lno) 
                    {
                        fprintf(fptr2,"\n%s %s %s %ld %ld\n",ebname,eaut,eloc,eprice,ecount);
                        linectr++;
                    } 
                    else 
                    {
                        fprintf(fptr2, "\n%s %s %s %ld %ld\n",ebname,eaut,eeloc,eeprice,eecount);
                        linectr++;
                    }
        }
        fclose(fptr1);
        fclose(fptr2);
        
        //deleting pre-existing record
        remove("Record.txt");
        
        //copying contents of temp to record
        fptr1=fopen("temp.txt","r");
        fptr2=fopen("Record.txt","w");
         while (!feof(fptr1)) 
        {
            fgets(str, MAX, fptr1);
            if (!feof(fptr1)) 
            {  
             fprintf(fptr2, "%s", str);         
            }
        }
        fclose(fptr1);
        fclose(fptr2);
        
        //removing temp file
        remove("temp.txt");
        
        printf(" \n\tReplacement did successfully..!! \n");
    }
    else
    {
    	printf("\n\t\t\tBook not found!!!\n");
	}
	
}

void billing()
{
	FILE *fptr1,*fptr2,*fptr3,*fp;
	char da[20],cnam[30],book[200][100],bn[100];
	char ebname[100],eaut[100],eloc[100];
	char str[MAX];
	long int ecount,eprice,cou,newcou,ccou,total=0;
	int ch=1,i=0,n=0,price[200],count[200],cost[200],flag;
	int  linectr = 1,lno=1;
	printf("\nEnter date (dd-mm-yyyy)              ::  ");
	scanf("%s",da);
	printf("\nEnter Customer name(capital letters) ::  ");
	scanf("%s",cnam);
	do
	{
		printf("\nPress <1> for new book");
		printf("\nPress <0> to terminate");
		printf("\nEnter the choice::");
		scanf("%d",&ch);
	
		switch(ch)
		{
			case 1 :
		    {
		        printf("\nEnter book name     :: ");
		        scanf("%s",bn);
	        	fp=fopen("Record.txt","r");
		        while(fscanf(fp,"%s %s %s %ld %ld",ebname,eaut,eloc,&eprice,&ecount)!=EOF)
     	        {
  	               if(strcmp(ebname,bn)==0)
  		           {
  		              flag=1;
  		              ccou=ecount;
	                  break; 
	               }
	               else
	               {
	    	          lno++;
	    	          flag=0;
		           }
	            }
	            fclose(fp);
	            if (flag==1)
	            {       
	                printf("\nEnter the count of book required   :: ");
		            scanf("%ld",&cou);
		            if(ccou<cou)
		            {
		   	           printf("\nStock availability is %ld",ccou);
		   	           printf("\nAvailability of book is less!!!You can change your order according to stock availability...do you want to continue?");
		   	           break;
		            }
		            else
		            { 
		                count[i]=cou;
		   	            newcou=ccou-cou;
		                fptr1=fopen("Record.txt","r");
	                    fptr2=fopen("temp.txt","w");	
	       
	                     // copy all contents to the temporary file other except specific line
                        while (fscanf(fptr1,"%s %s %s %ld %ld",ebname,eaut,eloc,&eprice,&ecount)!=EOF) 
                        {
                           if (linectr != lno) 
                           {
                              fprintf(fptr2,"\n%s %s %s %ld %ld\n",ebname,eaut,eloc,eprice,ecount);
                              linectr++;
                           } 
                           else 
                           {
                               fprintf(fptr2, "\n%s %s %s %ld %ld\n",ebname,eaut,eloc,eprice,newcou);
                               strcpy(book[i],ebname);
                               price[i]=eprice;
                               cost[i]=price[i]*count[i];
                               i++;
                               linectr++;
                               n++;
                           }
                       }
                       fclose(fptr1);
                       fclose(fptr2);
                       lno=1;
                       linectr=1;
                       //deleting pre-existing record
                       remove("Record.txt");
        
                       //copying contents of temp to record
                       fptr1=fopen("temp.txt","r");
                       fptr2=fopen("Record.txt","w");
                       while (!feof(fptr1)) 
                       {
                          fgets(str, MAX, fptr1);
                          if (!feof(fptr1)) 
                          {  
                              fprintf(fptr2, "%s", str);         
                          }
                       }
                       fclose(fptr1);
                       fclose(fptr2);
        
                       //removing temp file
                      remove("temp.txt");
                   }
		       }
		       else
               {
    	           printf("\n\t\t\tBook not found!!!\n");
	           }
	           break;
	       }
	       case 0:
	       	{
		        fptr3=fopen("sales.txt","a");
		        fprintf(fptr3,"\n\n%s %s",da,cnam);
		        printf("\n\n%s %s",da,cnam);
		        for(i=0;i<n;i++)
	        	{
			       printf("\n\t%s  %ld * %ld  = %ld",book[i],price[i],count[i],cost[i]);
			       fprintf(fptr3,"\n\t%s  %ld * %ld  = %ld",book[i],price[i],count[i],cost[i]);
			       total=total+cost[i];
		        }
		        printf("\n\t\t\t\tTOTAL AMOUNT IS %ld",total);
		        fprintf(fptr3,"\n\t\t\t\tTOTAL AMOUNT IS %ld",total);
		        fclose(fptr3);
		        break;
           }
           getch();
        }    	
	}while(ch!=0);
}
void search()
{
	FILE *fp;
	char b_a_nam[100],bnam[100],aut[100],loc[100],*b,*a;
	int price,count,flag;
	printf("\nEnter related book name or author name  :: ");
	scanf("%s",b_a_nam);
	fp=fopen("Record.txt","r");
	while(fscanf(fp,"%s %s %s %ld %ld",bnam,aut,loc,&price,&count)!=EOF)
	{
		b = strstr(bnam,b_a_nam);
		a = strstr(aut,b_a_nam);
		if((b)||(a))
		{
			flag=1;
			printf("\n\nName of the Book                                                 :: %s",bnam);
			printf("\nName of the Author                                               :: %s",aut);
			printf("\nBook location (Alphabet refers the rack number refers the shelf) :: %s",loc);
			printf("\nPrice of the book                                                :: %ld Rs/-",price);
			printf("\nAvailablity of stock                                             :: %ld numbers",count);
			
		}
	} //end of while loop
	if(flag!=1)
	{
		printf("\n\t\t\t\tNo such record found!!!!!");
		printf("\n\tPlease enter the choice as <1> in the choice list to create a record!! ");
	}
	fclose(fp);
}

int main()
{
	mainmenu();
	return 0;
}
