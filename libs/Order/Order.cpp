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


/** Recognize is a input string is a valid cmd type */
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

/** Pass a self string type to his enum value */
Order::CMD_TYPE Order::recognizeCmdType(){
	
	Order::CMD_TYPE recognizedCmdType;
	if(!strcmp(this->cmdType.c_str(),"AXES")){	
		recognizedCmdType = AXES;
	}else if(!strcmp(this->cmdType.c_str(),"ARD")){
		recognizedCmdType = ARD;
	}else{	
		recognizedCmdType = NO_RECONIZED_CMD_TYPE;
	} 
	return recognizedCmdType;
	
}

/** Recognize is a input string is a valid cmd */
Order::CMD Order::recognizeCmd(string Cmd){
	
	Order::CMD recognizedCmd;
	if(!strcmp(Cmd.c_str(),"BREAK")){	
		recognizedCmd = BREAK;
	}else if(!strcmp(cmd.c_str(),"LOG_MODE")){	
		recognizedCmd = LOG_MODE;
	}
	else{	
		recognizedCmd = NO_RECONIZED_CMD;
	} 
	return recognizedCmd;
	
}

/** Pass a self string type to his enum value */
Order::CMD Order::recognizeCmd(){
	
	Order::CMD recognizedCmd;
	if(!strcmp(this->cmd.c_str(),"BREAK")){	
		recognizedCmd = BREAK;
	}else if(!strcmp(cmd.c_str(),"LOG_MODE")){	
		recognizedCmd = LOG_MODE;
	}else{	
		recognizedCmd = NO_RECONIZED_CMD;
	} 
	return recognizedCmd;
	
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





