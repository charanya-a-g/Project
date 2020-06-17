#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

//function for writing entry book into file

void write()
{
	FILE *fp;
	char dat[20];
	char unam[20];
	char bnam[20];
	char mn[15];
	long int cos;
	
	printf("\nEnter Date(dd-mm-yyyy)   :: ");
	scanf("%s",dat);
	
	printf("\nEnter Name of Customer   :: ");
	scanf("%s",unam);
	
	printf("\nEnter mobile number      :: ");
	scanf("%s",mn);
	
	printf("\nEnter Name of the book   :: ");
	scanf("%s",bnam);
	
	printf("\nEnter cost of the book   :: ");
	scanf("%ld",&cos);
	
	fp=fopen("Record.txt","a");
	
	fprintf(fp,"\n%s %s %s %s %ld\n",dat,unam,mn,bnam,cos);
	fclose(fp);
	printf("\n\tRecord written successfully!!!!");
}

 //main function
   
  int main()  
  {
        int ch;
        char lm[20];
	char cn[20];
	do
	{
		printf("\n\n\n\t\tWELCOME TO BOOK SHOP\n");
		printf("\n\n\t CHOICE LIST");
		printf("\n\n Press <1> to create entry for book");
		printf("\n Press <2> to display on specific date");
		printf("\n Press <0> to exit");
		printf("\n\nEnter choice  ::");
		scanf("%d",&ch);
		
		switch(ch)
		{
			case 1:
			   {
			   write();
			   break;
		           }
			case 2:
			    {
		            printf("\nPlease enter date in dd-mm-yyyy format\n");
		            printf("Enter the date    :: ");
			    scanf("%s",lm);
			    printf("\nEnter customer name :: ");
			    scanf("%s",cn);
			    display(lm,cn);
			    break;
			    }
			case 0:
			    {
			    exit(0);
			    }
			default:
			   {
			    printf("\nInvalid selection");
			    printf("\nPlease check the choice list!!");
			    }
		}//end of switch case
		getch();
		
	}//end of do while loop
	while(ch !=0);
	
	return 0;
	 
  }
