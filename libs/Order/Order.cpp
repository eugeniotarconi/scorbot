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
	
	Order::CMD_TYPE recognizedCmdType = this->recognizeCmdType(this->cmdType);
	return recognizedCmdType;
	
}

/** Recognize is a input string is a valid cmd */
Order::CMD Order::recognizeCmd(string Cmd){
	
	Order::CMD recognizedCmd;
	if(!strcmp(Cmd.c_str(),"BRAKE")){	
		recognizedCmd = BRAKE;
	}else if(!strcmp(cmd.c_str(),"LOG_MODE")){	
		recognizedCmd = LOG_MODE;
	}else if(!strcmp(cmd.c_str(),"SET_BRAKE_PIN")){	
		recognizedCmd = SET_BRAKE_PIN;
	}
	else{	
		recognizedCmd = NO_RECONIZED_CMD;
	} 
	return recognizedCmd;
	
}

/** Pass a self string type to his enum value */
Order::CMD Order::recognizeCmd(){	
	Order::CMD recognizedCmd = this->recognizeCmd(this->cmd);
	return recognizedCmd;
	
}


/** New funtion */
Order::ARG Order::recognizeArg(string Arg){
		
	Order::ARG recognizedArg;
	if(!strcmp(Arg.c_str(),"ALL")){	
		recognizedArg = ALL;
	}else if(!strcmp(Arg.c_str(),"ON")){
		recognizedArg = ON;
	}else if(!strcmp(Arg.c_str(),"OFF")){
		recognizedArg = OFF;
	}else{		
		recognizedArg = NO_RECONIZED_ARG;
	} 
	return recognizedArg;
	
	
}

/** New funtion */
Order::ARG Order::recognizeArg(){	
	return this->recognizeArg(this->args);	
}


// --------------------    SUPPORT FUNCTIONS     --------------------





