#include "data.h"

static student_t school[SCHOOL_MAX_SIZE] ; 
static s16 current_std = 0 ;
static u8 y_axis = 0 ;  
static u8 search_choice ;
static u8 student_name[20];
static s16 Index=-1 ; 
static u8 call_choice ;
static u8 edit_choice ;
static u8 sort_choice ;
static u8 Total_bro ;
FILE *database = NULL ;

/************************** Private Fuctions ************************/

static void school_determine_Student_index (void) ;
static void school_Search_student(void);
static void General_call (void) ;
static void print_choices (void);
static void string_scan (u8 *s , u8 max);
static void Phone_scan (u8 *s , u8 max);
static void string_print (u8 *s);
static void print_student_data (void);
static void school_add_student (void);
static void Father_Call(void) ;
static u8 string_compare_for_sorting (u8 *s1,u8 *s2);
static void student_call(void) ;
static void Mother_Call(void) ;
static void swapp_Two_students (student_t *s1 , student_t *s2);
static u8 string_compare_not_case_sensitive (u8 *s1,u8 *s2) ;
static school_t School_empty(void) ;
static void student_edit_data (void);
static void print_All_school_data (void);
static void print_student_data_no_asking_for_info (void);
static void school_student_sort_general(void);
static void school_sort_alphbetically(void);
static void school_sort_age(void);
static void school_sort_Grade(void);
static void school_remove_student(void);
static void school_shift_left (void) ;
static void School_store_database(void);


/***********************************************************************/

static void School_store_database(void)
{
	u16 i  ;
	u8 j ;	
	 
	database = fopen("School_Data.txt","w");
	fputs("\n\n******************** School Data_Base ********************\n\n\n",database);
	fputs ("==================================================\n\n",database);
	for (i=0;i<current_std;i++)
	{
		Total_bro = school[i].Brothers_no ;
		fprintf(database,"Student's Name : %s\n",school[i].name);
		fprintf(database,"Student's Phone Number : %s\n",school[i].phone);
		fprintf(database,"Student's Age : %d\n",school[i].age);
		fprintf(database,"Student's degree : %c\n\n",school[i].degree);
		
		fprintf(database,"Father's Name : %s\n",school[i].father.name);
		fprintf(database,"Father's Phone Number : %s\n",school[i].father.phone);
		fprintf(database,"father's Age : %d\n\n",school[i].father.age);
		
		fprintf(database,"mother's Name : %s\n",school[i].mother.name);
		fprintf(database,"mother's Phone Number : %s\n",school[i].mother.phone);
		fprintf(database,"mother's Age : %d\n\n",school[i].mother.age);
		for(j=0;j<Total_bro;j++)
		{
			fprintf(database,"Brother's name : %s\n",school[i].Brother_ptr[j].name);
			fprintf(database,"Brother's age : %d\n\n",school[i].Brother_ptr[j].age);
			
		}
		fputs ("==================================================\n\n",database);
	}
	
	fclose (database);
}

/************************************************************************************/
static void school_shift_left (void)
{
	s16 i ;
	u16 L_ind = Index ;
	for (i=0;i<current_std-Index;i++)
	{
		school[L_ind]=school[L_ind+1];
		L_ind++ ; 
	}
}
/*************************************************************************/
static void school_remove_student(void)
{
	if (School_empty()==sch_empty)
	{
		return ;
	}
	else 
	{
		print_All_school_data();
		school_determine_Student_index();
		
		if (Index==current_std-1)
		{
			
			current_std-- ;
			print_All_school_data();
			return ; 
		}
		else 
		{
			school_shift_left();
			current_std-- ;
			print_All_school_data();
			School_store_database();
		}
	}
	
}
/*************************************************************************/
static void school_sort_alphbetically(void)
{
	u16 i , j , max , last = current_std - 1  ;
	for (i=0;i<current_std;i++)
	{
		max = 0 ;
		for (j=0;j<current_std-i;j++)
		{
			if (1==string_compare_for_sorting(school[j].name,school[max].name))
			{
				max = j ; 
			}
		}
		swapp_Two_students(&school[max],&school[last]);
		last-- ; 
	}
}
/*************************************************************************/
static void school_sort_age(void)
{
	s16 i , j , max , last = current_std - 1  ;
	for (i=0;i<current_std;i++)
	{
		max = 0 ;
		for (j=0;j<current_std-i;j++)
		{
			if (school[max].age<school[j].age)
			{
				max = j ; 
			}
		}
		swapp_Two_students(&school[max],&school[last]);
		last-- ; 
	}
}
/*************************************************************************/
static void school_sort_Grade(void)
{
	s16 i , j , max , last = current_std - 1  ;
	for (i=0;i<current_std;i++)
	{
		max = 0 ;
		for (j=0;j<current_std-i;j++)
		{
			if (school[max].degree<school[j].degree)
			{
				max = j ; 
			}
		}
		swapp_Two_students(&school[max],&school[last]);
		last-- ; 
	}
}
/*************************************************************************/
static void school_student_sort_general(void)
{
	if (School_empty()==sch_empty)
	{
		return ;
	}
	else if (1==current_std)
	{
		cmdGoToXY(10,15);
		printf("Only One Student In school");
		cmdGoToXY(10,18);
		printf("============================");
		cmdDelay(3000);
	}
	else 
	{
		print_All_school_data();
		cmdSetConsoleColour(TEXT_Green);
		while(1)
		{
			cmdGoToXY(10,3);
			printf("1.Sort alphabetically");
			cmdGoToXY(10,4);
			printf("2.Sort By age");
			cmdGoToXY(10,5);
			printf("3.Sort By Degree");
			cmdGoToXY(10,7);
			printf("=====================");
			cmdGoToXY(10,10);
			printf("Enter Your Choice (From 1 To 3): ");
			scanf("%d",&sort_choice);
			if ((sort_choice<4)&&(sort_choice!=0))
			{
				cmdClearScreen();
				break ; 
			}
			else 
			{
				cmdGoToXY(10,10);
				printf("Enter Valid Choice (From 1 To 3): ");
				cmdGoToXY(10,13);
				system("pause");
				cmdClearScreen();
			}
		}
		
		switch (sort_choice)
		{
			case alphabet :
				school_sort_alphbetically();
			break ;
			
			case std_age :
				school_sort_age();
			break ;
			
			case std_degree :
				school_sort_Grade();
			break ;
		}
	}
		print_All_school_data();
}
/*************************************************************************/
static void print_student_data_no_asking_for_info (void)
{
	u16 i ; 
	cmdSetConsoleColour(TEXT_LYellow);
	
	cmdGoToXY(10,3);
	printf("Student's Name: ");
	string_print(school[Index].name);
	cmdGoToXY(10,5);
	printf("Student's Phone Number : ");
	string_print(school[Index].phone);
	cmdGoToXY(10,7);
	printf("Student's age : %d",school[Index].age);
	cmdGoToXY(10,9);
	printf("Student's degree: %c",school[Index].degree);
	cmdGoToXY(10,11);
		
	/***************** Father *********************/
	printf("Student's Father name : ");
	string_print(school[Index].father.name);
	cmdGoToXY(10,13);
	printf("Student's Father Phone Number : ");
	string_print(school[Index].father.phone);
	cmdGoToXY(10,15);
	printf("Student's Father Age : %d",school[Index].father.age);
		
	/***************** Mother ***********************/
	cmdGoToXY(10,17);
	printf("Student's Mother name :");
	string_print(school[Index].mother.name);
	cmdGoToXY(10,19);
	printf("Student's Mother Phone Number :");
	string_print(school[Index].mother.phone);
	cmdGoToXY(10,21);
	printf("Student's Mother Age : %d",school[Index].mother.age);
		
	/***************** Brothers ***********************/
	Total_bro = school[Index].Brothers_no ;
	for (i=0;i<Total_bro;i++)
	{ 
		cmdGoToXY(10,24+y_axis);
		printf("Student's Brother[%d]name: ",i+1);
		string_print(school[Index].Brother_ptr[i].name);
		
		y_axis+=2 ; 	
		cmdGoToXY(10,24+y_axis);		
		printf("Student's Brother[%d]age: %d",i+1,
						school[Index].Brother_ptr[i].age);
		y_axis+= 3 ;
	}
	cmdGoToXY(10,24+y_axis);
	system("pause");
	y_axis = 0 ;
	cmdClearScreen();		
}
/*************************************************************************/
static void student_edit_data (void)
{
	print_student_data();
	if(0==current_std)
	{
		cmdClearScreen();
		return ; 
	}
	cmdSetConsoleColour(TEXT_Cyan);
	while(1)
	{
		cmdGoToXY(10,4);
		printf("1.Edit Student's phone");
		
		cmdGoToXY(10,5);
		printf("2.Edit father's phone");
		
		cmdGoToXY(10,6);
		printf("3.Edit mother's phone");
		
		cmdGoToXY(10,7);
		printf("4.Edit Student's degree");
		
		cmdGoToXY(10,8);
		printf("5.Edit Student's age");
		
		cmdGoToXY(10,9);
		printf("6.Edit father's age");
		
		cmdGoToXY(10,10);
		printf("7.Edit mother's age");
		cmdGoToXY(10,12);
		printf("==========================");
		cmdGoToXY(10,15);
		printf("Enter Your Edit Choice (From 1 To 10) : ");
		fflush(stdin);
		scanf("%d",&edit_choice);
		if	((edit_choice<8)&&(edit_choice!=0) )
		{
			cmdClearScreen();
			break ;
		}
		else 
		{
			cmdGoToXY(10,20);
			printf("Wrong Choice (From 1 To 7)");
			cmdGoToXY(10,22);
			system("pause");
			cmdClearScreen();
		}
		
	}
	print_student_data_no_asking_for_info();
	switch (edit_choice)
	{
		case edit_std_phone :
			cmdGoToXY(10,3);
			
			printf("Enter New Phone: ");
			fflush(stdin);
			Phone_scan(school[Index].phone,MAX_PHONE_NUMBER);
			fflush(stdin);
			cmdGoToXY(10,6);
			printf(".............");
		break ;
		
		case edit_father_phone :
			cmdGoToXY(10,3);
			printf("Enter New father's phone number: ");
			fflush(stdin);
			Phone_scan(school[Index].father.phone,MAX_PHONE_NUMBER);
			
			fflush(stdin);
			cmdGoToXY(10,6);
			printf(".............");
		break ;
		
		case edit_mother_phone :
			cmdGoToXY(10,3);
			printf("Enter New mother's phone number: ");
			fflush(stdin);
			Phone_scan(school[Index].mother.phone,MAX_PHONE_NUMBER);
		
			fflush(stdin);
			cmdGoToXY(10,6);
			printf(".............");
		break ;
		
		case edit_std_degree :
			cmdGoToXY(10,3);
			printf("Enter New degree: ");
			fflush(stdin);
			scanf("%c",&school[Index].degree);
			fflush(stdin);
			cmdGoToXY(10,6);
			printf(".............");
		break ;
		
		case edit_std_age :
			cmdGoToXY(10,3);
			printf("Enter New age: ");
			fflush(stdin);
			scanf("%d",&school[Index].age);
			fflush(stdin);
			cmdGoToXY(10,6);
			printf(".............");
		break ;
		
		case edit_father_age :
			cmdGoToXY(10,3);
			printf("Enter New father's age: ");
			fflush(stdin);
			scanf("%d",&school[Index].father.age);
			fflush(stdin);
			cmdGoToXY(10,6);
			printf(".............");
		break ;
		
		case edit_mother_age :
			cmdGoToXY(10,3);
			printf("Enter New mother's age: ");
			fflush(stdin);
			scanf("%d",&school[Index].mother.age);
			fflush(stdin);
			cmdGoToXY(10,6);
			printf(".............");
		break ;
		
	}
	
	cmdDelay(5000);
	cmdClearScreen();
	cmdGoToXY(10,1);
	printf("Student's new data : ");
	print_student_data_no_asking_for_info();
	School_store_database();
	
}
/*************************************************************************/
static school_t School_empty(void)
{
	if (0==current_std)
	{
		cmdSetConsoleColour(TEXT_Red);
		cmdGoToXY(10,3);
		printf("No Studentes Yet !!");
		cmdGoToXY(10,5);
		system("pause");
		cmdClearScreen();
		return sch_empty ;
	}
	return sch_not_empty ;
}
/*************************************************************************/
static void print_choices (void)
{
	cmdSetConsoleColour(TEXT_Green);
	cmdGoToXY(20,3);
	printf("1. *** Add Student ****");
	cmdGoToXY(20,4);
	printf("2. *** Edit Student ***");
	cmdGoToXY(20,5);
	printf("3. *** Print Student Data ***");
	cmdGoToXY(20,6);
	printf("4. *** Print All School Data ***");
	cmdGoToXY(20,7);
	printf("5. *** Remove Student ***");
	cmdGoToXY(20,8);
	printf("6. *** Call Student/Father/Mother ***");
	cmdGoToXY(20,9);
	printf("7. *** Sorting Data ***");
	cmdGoToXY(20,10);
	printf("8. *** Exit Programm ***");
	cmdGoToXY(20,11);
	printf("============================================");
	cmdResetConsoleColour();
}
/*************************************************************************/
u8 Get_user_choice (void)
{
	u8 Choice ; 
	cmdClearScreen();
	while (1)
	{
		print_choices();
		cmdGoToXY(20,13);
		printf("Enter Your Choice (From 1 To 8) : ");
		scanf("%d",&Choice);
		if ((Choice>8)||(0==Choice))
		{
			cmdGoToXY(20,15);
			printf("Enter Valid Choiche (From 1 To 8)!!");
			cmdDelay(2000);
			cmdClearScreen();
		}
		else 
		{
			cmdGoToXY(20,17);
			printf("=====================================");
			cmdGoToXY(20,20);
			system("pause");
			cmdClearScreen();
			break ; 
		}
	}
	
	return Choice ;
}
/*************************************************************************/
static void string_scan (u8 *s,u8 max)
{
	u8 i = 0 ; 
	fflush(stdin);
	scanf("%c",&s[i]);
	while (s[i]!='\n')
	{
		i++ ;
		if (i>=max)
		{
			s[max]='\0';
			return  ;
		}
		scanf("%c",&s[i]);
	}
	
		s[i] ='\0' ;
}
/*************************************************************************/
static void Phone_scan (u8 *s,u8 max)
{
	u8 i = 0 ; 
	fflush(stdin);
	scanf("%c",&s[i]);
	
	while (s[i]!='\n')
	{
		i++ ;
		if (i>=max)
		{
			s[max]='\0' ;
			return ;
		}
		scanf("%c",&s[i]);
	}
	
	s[i] = '\0' ;
	
	
}
/*************************************************************************/
static void string_print (u8 *s)
{
	u8 i ;
	for (i=0;s[i];i++)
	{
		printf("%c",s[i]);
	}
	printf("\n");
}
/*************************************************************************/

static void print_student_data (void)
{
	if (School_empty()==sch_empty)
	{
		return ;
	}
	else 
	{
		u16 i ;
		u8 L_Total;
		cmdSetConsoleColour(TEXT_Cyan);
		print_All_school_data();
		school_determine_Student_index();
		
		print_student_data_no_asking_for_info();
		
	}

	cmdClearScreen();
}
/*************************************************************************/
/* Add Student To School */
static void school_add_student (void)
{
	if (current_std<SCHOOL_MAX_SIZE)
	{
		u16 i ;
		u8 L_var ;
		cmdSetConsoleColour(TEXT_Cyan);
		cmdGoToXY(20,3);
		printf("Enter Student Name : ");
		fflush(stdin);
		string_scan(school[current_std].name,MAX_NAME_LENGTH);
		
		
		cmdGoToXY(20,6);
		printf("Enter Student Age : ");
		fflush(stdin);
		scanf("%d",&school[current_std].age);
		
		cmdGoToXY(20,8);
		printf("Enter Student Phone Number : ");
		fflush(stdin);
		Phone_scan(school[current_std].phone,MAX_PHONE_NUMBER);

		cmdGoToXY(20,10);
		printf("Enter Student Degree : ");
		fflush(stdin);
		scanf("%c",&school[current_std].degree);
		
		cmdGoToXY(20,12);
		printf("Enter Father's name : ");
		fflush(stdin);
		string_scan(school[current_std].father.name,MAX_NAME_LENGTH);
		
		cmdGoToXY(20,14);
		printf("Enter Father's age : ");
		fflush(stdin);
		scanf("%d",&school[current_std].father.age);
		cmdGoToXY(20,16);
		printf("Enter Father's phone number : ");
		fflush(stdin);
		Phone_scan(school[current_std].father.phone,MAX_PHONE_NUMBER);
		
		cmdGoToXY(20,18);
		fflush(stdin);
		printf("Enter Mother's name : ");
		fflush(stdin);
		string_scan(school[current_std].mother.name,MAX_NAME_LENGTH);
		
		cmdGoToXY(20,20);
		printf("Enter Mother's age : ");
		fflush(stdin);
		scanf("%d",&school[current_std].mother.age);
		cmdGoToXY(20,22);
		printf("Enter Mother's phone number : ");
		fflush(stdin);
		Phone_scan(school[current_std].mother.phone,MAX_PHONE_NUMBER);

		cmdGoToXY(20,24);
		printf("Enter Number of brothers : ");
		fflush(stdin);
		scanf("%d",&school[current_std].Brothers_no);
		Total_bro = school[current_std].Brothers_no ;
		
		school[current_std].Brother_ptr = malloc(Total_bro * sizeof(person_t));
												
		for (i=0;i<Total_bro;i++)
		{
			cmdGoToXY(20,26+y_axis);
			printf("Enter name of brother[%d]: ",i+1);
			fflush(stdin);
			string_scan(school[current_std].Brother_ptr[i].name,MAX_NAME_LENGTH);
			
			y_axis+=2 ;
			
			cmdGoToXY(20,26+y_axis);
			printf("Enter Age of brother[%d]: ",i+1);
			fflush(stdin);
			scanf("%d",&school[current_std].Brother_ptr[i].age);
			
			y_axis+=3 ;
		}
		cmdGoToXY(20,26+y_axis);
		printf("*************************");
		cmdDelay(5000);
		current_std++ ;
		School_store_database();
		y_axis = 0 ;
	}
	else 
	{
		cmdClearScreen();
		cmdGoToXY(20,8);
		printf("Can't Take Another Student as Maximum Limit Has Been reached");
		cmdGoToXY(20,12);
		printf("***************************************************");
		cmdDelay(8000);
		cmdClearScreen();
		return ; 
	}
	
}
/*************************************************************************/

static void swapp_Two_students (student_t *s1 , student_t *s2)
{
	student_t temp = *s1 ;
	*s1 = *s2 ;
	*s2 = temp ; 
}
/*************************************************************************/

static u8 string_compare_not_case_sensitive (u8 *s1,u8 *s2)
{
	u8 i ;
	
	for (i=0;s1[i]||s2[i];i++)
	{
		if ((s1[i]!=s2[i])&&(s1[i]!=s2[i]+'a'-'A')&&((s1[i]!=s2[i]+'A'-'a')))
		{
			return 0 ;
		}
	}
	return 1 ;
	
} 
/*************************************************************************/

static u8 string_compare_for_sorting (u8 *s1,u8 *s2)
{
	u8 i ;
	u8 c1 , c2;
	
	for (i=0;s1[i]||s2[i];i++)
	{
		c1 = s1[i] ;
		c2 = s2[i] ;
		if ((c1>='A')&&(c1<='Z'))
		{
			c1 = c1 - 'A' + 'a' ;
		}
		if ((c2>='A')&&(c2<='Z'))
		{
			c2 = c2 - 'A' + 'a' ;
		}
		if (c1>c2)
		{
			return 1 ;
		}
		if (c1<c2)
		{
			return -1 ;
		}
	}
	
	return 0 ;
}
/*************************************************************************/
static void print_All_school_data (void)
{
	u16 i , x=3 , y=5 ;
	if (School_empty()==sch_empty)
	{
		return ;
	}
	else 
	{
		
		system ("cls");
		cmdGoToXY(x,y);
		cmdSetConsoleColour(TEXT_LYellow);
		printf("Order|        Name        |Degree|Age|Phone_Number|");
		y+=3;
		for (i=0;i<current_std;i++)
		{
			cmdGoToXY(x,y);
			printf("%-4d |",i+1);
			printf("%-20s|",school[i].name);
			printf(" %c    |",school[i].degree);
			printf("%-2d |",school[i].age);
			printf("%-11s |",school[i].phone);
			y+=3;
		}
	}
		cmdGoToXY(10,y);
		system("pause");
		cmdClearScreen();
		School_store_database();
}
/*************************************************************************/
static void school_Search_student(void)
{
	cmdSetConsoleColour(TEXT_Green);
	while(1)
	{
		cmdGoToXY(10,3);
		printf("1. search By Student Name");
		cmdGoToXY(10,4);
		printf("2. search By Student ID");
		cmdGoToXY(10,6);
		printf("=====================");
		cmdGoToXY(10,8);
		printf("Enter Your Choice : ");
		scanf("%d",&search_choice);
		if ((search_choice<3)&&(search_choice!=0))
		{
			break ;
		}
		else 
		{
			cmdGoToXY(10,12);
			printf("Search Choice has to be 1 Or 2 only !!");
			cmdGoToXY(10,14);
			system("pause");
		}
		cmdClearScreen();
	}
	cmdClearScreen();
}
/*************************************************************************/
void school_determine_Student_index (void)
{
	u16 i ;
	u8 l_ind ;
	school_Search_student();
	cmdSetConsoleColour(TEXT_Green);
	switch (search_choice)
	{
		case name_search :
		
		while(1)
		{
			cmdGoToXY(10,5);
			printf("Enter Student Name: ");
			string_scan(student_name,MAX_NAME_LENGTH);
			
			for(i=0;i<current_std;i++)
			{
				if (1== string_compare_not_case_sensitive(student_name,school[i].name))
				{
					Index = i ;
					break ;
				}
			}
			if (-1!=Index)
			{
				cmdGoToXY(10,10);
				printf("Entered Name is found at order %d",Index+1);
				cmdGoToXY(10,12);
				system("pause");
				cmdClearScreen();
				break ;
			}
			else 
			{
				cmdGoToXY(10,10);
				printf("Entered Name is not Found in school !!");
				cmdGoToXY(10,12);
				system("pause");
				cmdClearScreen();
			}
		}
		
		break ;
		
		case ID_search :
		
			while (1)
			{
				cmdGoToXY(10,3);
				printf("Current Students in school are %d",current_std);
				cmdGoToXY(10,5);
				printf("Enter Student ID less than %d: ",current_std+1);
				scanf("%d",&l_ind);
				Index = l_ind -1 ; 
				if ((l_ind>current_std)||(0==l_ind))
				{
					cmdGoToXY(10,8);
					printf("Enetered ID doen't Exsist!!");
					cmdGoToXY(10,10);
					system("pause");
					cmdClearScreen();
				}
				else 
				{
					break ;
				}
			}
			cmdClearScreen();
		
		
		break ;
		
	}
}
/*************************************************************************/
static void student_call(void)
{
	u8 i ;
	
	cmdSetConsoleColour(TEXT_LYellow);
	cmdGoToXY(10,5);
	printf("student : %s",school[Index].name);
	cmdGoToXY(10,8);
	printf("call %s ",school[Index].phone);
	for(i=0;i<10;i++)
	{
		cmdGoToXY(27,8);
		printf(".........");
		cmdDelay(1000);
		cmdGoToXY(27,8);
		printf("         ");
		cmdDelay(1000);
	}
	
	cmdGoToXY(10,12);
	printf("NO Response");
	cmdGoToXY(10,15);
	system("pause");
	
}
/*************************************************************************/
static void Father_Call(void)
{
	u8 i ;
	
	cmdSetConsoleColour(TEXT_LYellow);
	cmdGoToXY(10,5);
	printf("Student : %s",school[Index].name);
	cmdGoToXY(10,8);
	printf("Father: %s",school[Index].father.name);
	cmdGoToXY(10,10);
	printf("call father : %s ",school[Index].father.phone);
	for(i=0;i<10;i++)
	{
		cmdGoToXY(36,10);
		printf(".........");
		cmdDelay(1000);
		cmdGoToXY(36,10);
		printf("         ");
		cmdDelay(1000);
	}
	
	cmdGoToXY(10,12);
	printf("NO Response");
	cmdGoToXY(10,15);
	system("pause");
	
}
/*************************************************************************/
static void Mother_Call(void)
{
	u8 i ;
	
	cmdSetConsoleColour(TEXT_LYellow);
	cmdGoToXY(10,5);
	printf("Student : %s",school[Index].name);
	cmdGoToXY(10,8);
	printf("Mother : %s",school[Index].mother.name);
	cmdGoToXY(10,10);
	printf("call mother: %s ",school[Index].mother.phone);
	for(i=0;i<10;i++)
	{
		cmdGoToXY(35,10);
		printf(".........");
		cmdDelay(1000);
		cmdGoToXY(35,10);
		printf("         ");
		cmdDelay(1000);
	}
	
	cmdGoToXY(10,12);
	printf("NO Response");
	cmdGoToXY(10,15);
	system("pause");
	
}
/*************************************************************************/
void General_call (void)
{
	if (School_empty()==sch_empty)
	{
		return ;
	}
	else 
	{
		print_All_school_data();
		school_determine_Student_index();
		cmdSetConsoleColour(TEXT_LYellow);
		while(1)
		{
			cmdGoToXY(5,10);
			printf("1.Call Student");
			cmdGoToXY(5,11);
			printf("2.Call father");
			cmdGoToXY(5,12);
			printf("3.Call mother");
			cmdGoToXY(5,14);
			printf("==========================");
			cmdGoToXY(5,17);
			printf("Enter Your Choice : ");
			scanf("%d",&call_choice);
			if ((call_choice<4)&&(0!=call_choice))
			{
				break ;
			}
			else 
			{
				cmdGoToXY(5,20);
				printf("Wrong Choice (from 1 to 3)");
				cmdGoToXY(5,22);
				system("pause");
				cmdClearScreen();
			}
			
		}
			cmdClearScreen();
		switch (call_choice)
		{
			case std_call:
				student_call();
			break ;
			
			case father_call:
				Father_Call();
			break ;
			
			case mother_call:
				Mother_Call();
			break ;
		}
	}
	
}
/*************************************************************************/
void data_opearate_user_choice (u8 choice)
{
	switch (choice)
	{
		case Add :
			school_add_student();
		break ;
		
		case Edit :
			student_edit_data();
		break ;
		
		case Print_student :
			print_student_data();
		break ;
		
		case print_school :
			print_All_school_data();
		break ;
		
		case remove_student :
			school_remove_student();
		break ;
		
		case call_student :
			General_call();
		break ;
		
		case sort :
			school_student_sort_general();
		break ;
		
		case exit_prog :
		
		exit(2) ;
		break ;
	}
	
	cmdClearScreen();
}
/*************************************************************************/
void Welcome_Message (void)
{
	cmdClearScreen();
	cmdSetConsoleColour(TEXT_LYellow);
	cmdGoToXY(40,15);
	printf("******* WELCOME *******");
	cmdDelay(10000);
	cmdClearScreen();
}
/*************************************************************************/