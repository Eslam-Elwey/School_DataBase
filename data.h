#ifndef _DATA_H_
#define _DATA_H_

/************************* Includes Section ************************/
#include "STD_Types.h"
#include "cmd_Handler.h"
#include <windows.h>
#include <stdio.h>

/************************ Macro Section ****************************/

#define SCHOOL_MAX_SIZE 		500
#define MAX_PHONE_NUMBER 		11
#define MAX_NAME_LENGTH 		19

/***************** Defined Data Types Section **********************/

typedef enum 
{
	Add=1,
	Edit,
	Print_student,
	print_school,
	remove_student,
	call_student,
	sort,
	exit_prog
}choice_t;

typedef enum 
{
	alphabet=1 ,
	std_age,
	std_degree
}sort_t;

typedef enum 
{
	edit_std_phone=1,
	edit_father_phone,
	edit_mother_phone,
	edit_std_degree,
	edit_std_age,
	edit_father_age,
	edit_mother_age,
	
}edit_t;

typedef enum 
{
	name_search=1 , 
	ID_search
}search_t;

typedef enum
{
	std_call =1 ,
	father_call ,
	mother_call
}call_t ;

typedef enum 
{
	sch_empty ,
	sch_not_empty
}school_t;



typedef struct 
{
	u8 name[20];
	u8 phone[12];
	u32 age ;
}person_t;

typedef struct 
{
	u8 name[20];
	u8 phone[12];
	u32 age ;
	u8 degree ; 
	person_t father ;
	person_t mother ;
	u8 Brothers_no ;
	person_t *Brother_ptr ;
}student_t;

/*********************** Functions Prototypes Section *************/

u8 Get_user_choice (void) ;
void data_opearate_user_choice (u8 choice);
void Welcome_Message (void) ;


#endif //_DATA_H_