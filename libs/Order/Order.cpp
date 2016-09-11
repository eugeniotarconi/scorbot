/** 
* 
*  
*/

#include "Order.h"

/** Default constructor*/
Order::Order(){
	this->cmdType = "";
	this->cmd = "";
	this->who = -1;		
	this->args = "";
}


// -------------------- SETTERS GETTERS & PRINTS --------------------


// --------------------      FUNCTIONALITIES     --------------------


/** New funtion */
Order::CMD_TYPE Order::recognizeCmdType(string CmdType){
	
	Order::CMD_TYPE recognizedCmdType;
	if(!strcmp(CmdType.c_str(),"AXES")){	
		recognizedCmdType = AXES;
	}else if(!strcmp(CmdType.c_str(),"ARD")){
		recognizedCmdType = ARD;
	}else{	
		recognizedCmdType = NO_RECONIZED_CMD_TYPE;
	} 
	return recognizedCmdType;
	
}

/** New funtion */
Order::ARG_TYPE Order::recognizeArgType(string ArgType){
		
	Order::ARG_TYPE recognizedArgType;
	if(!strcmp(ArgType.c_str(),"ALL")){	
		recognizedArgType = ALL;
	}else{	
		recognizedArgType = NO_RECONIZED_ARGS_TYPE;
	} 
	return recognizedArgType;
	
	
}


// --------------------    SUPPORT FUNCTIONS     --------------------





