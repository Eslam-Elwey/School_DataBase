#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "cmd_Handler.h"


u8 user_choice ; 

int main()
{
	Welcome_Message();
	
	while (1)
	{
		user_choice = Get_user_choice();
		data_opearate_user_choice (user_choice) ;
		
	}
	
	
	
	return 0 ;
}