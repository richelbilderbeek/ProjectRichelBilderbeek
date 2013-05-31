/*
 *  ComputerGenerated.cpp
 *  Sim4
 *
 *  Created by Richel Bilderbeek on Thu Jun 30 2005.
 *  Copyright (c) 2005 Richel Bilderbeek. All rights reserved.
 *
 */

#include "Sim4Interpreter.h"
#include "OptionsFile.h"
#include "SimulationFile.h"

//Below, only computer generated code...
//  COMPUTER GENERATED CODE
void Sim4Interpreter::interpretSetDconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setDconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation D's parameter A." << std::endl				
			<< "    e.g. './Sim4 setDconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newDconstA=-1.0;																					
	if (isDouble(nextCommand,newDconstA)==false)															
	{   //User typed 'setDConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation D's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setDconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newDconstA<0.0)																						
	{   //User typed 'setDConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation D's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setDconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setDconstA(newDconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetFconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setFconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation F's parameter A." << std::endl				
			<< "    e.g. './Sim4 setFconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newFconstA=-1.0;																					
	if (isDouble(nextCommand,newFconstA)==false)															
	{   //User typed 'setFConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation F's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setFconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newFconstA<0.0)																						
	{   //User typed 'setFConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation F's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setFconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setFconstA(newFconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetGconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setGconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation G's parameter A." << std::endl				
			<< "    e.g. './Sim4 setGconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newGconstA=-1.0;																					
	if (isDouble(nextCommand,newGconstA)==false)															
	{   //User typed 'setGConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation G's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setGconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newGconstA<0.0)																						
	{   //User typed 'setGConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation G's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setGconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setGconstA(newGconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetMconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setMconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation M's parameter A." << std::endl				
			<< "    e.g. './Sim4 setMconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newMconstA=-1.0;																					
	if (isDouble(nextCommand,newMconstA)==false)															
	{   //User typed 'setMConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation M's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setMconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newMconstA<0.0)																						
	{   //User typed 'setMConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation M's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setMconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setMconstA(newMconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetNconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setNconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation N's parameter A." << std::endl				
			<< "    e.g. './Sim4 setNconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newNconstA=-1.0;																					
	if (isDouble(nextCommand,newNconstA)==false)															
	{   //User typed 'setNConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation N's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setNconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newNconstA<0.0)																						
	{   //User typed 'setNConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation N's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setNconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setNconstA(newNconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetPconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setPconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation P's parameter A." << std::endl				
			<< "    e.g. './Sim4 setPconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newPconstA=-1.0;																					
	if (isDouble(nextCommand,newPconstA)==false)															
	{   //User typed 'setPConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation P's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setPconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newPconstA<0.0)																						
	{   //User typed 'setPConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation P's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setPconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setPconstA(newPconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetQconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setQconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation Q's parameter A." << std::endl				
			<< "    e.g. './Sim4 setQconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newQconstA=-1.0;																					
	if (isDouble(nextCommand,newQconstA)==false)															
	{   //User typed 'setQConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation Q's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setQconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newQconstA<0.0)																						
	{   //User typed 'setQConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation Q's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setQconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setQconstA(newQconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetRconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setRconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation R's parameter A." << std::endl				
			<< "    e.g. './Sim4 setRconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newRconstA=-1.0;																					
	if (isDouble(nextCommand,newRconstA)==false)															
	{   //User typed 'setRConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation R's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setRconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newRconstA<0.0)																						
	{   //User typed 'setRConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation R's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setRconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setRconstA(newRconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetWconstA(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setWconstA' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation W's parameter A." << std::endl				
			<< "    e.g. './Sim4 setWconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newWconstA=-1.0;																					
	if (isDouble(nextCommand,newWconstA)==false)															
	{   //User typed 'setWConstA [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation W's parameter A as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setWconstA 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newWconstA<0.0)																						
	{   //User typed 'setWConstA [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation W's parameter A to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setWconstA 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setWconstA(newWconstA);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetDconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setDconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation D's parameter B." << std::endl				
			<< "    e.g. './Sim4 setDconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newDconstB=-1.0;																					
	if (isDouble(nextCommand,newDconstB)==false)															
	{   //User typed 'setDConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation D's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setDconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newDconstB<0.0)																						
	{   //User typed 'setDConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation D's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setDconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setDconstB(newDconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetFconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setFconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation F's parameter B." << std::endl				
			<< "    e.g. './Sim4 setFconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newFconstB=-1.0;																					
	if (isDouble(nextCommand,newFconstB)==false)															
	{   //User typed 'setFConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation F's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setFconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newFconstB<0.0)																						
	{   //User typed 'setFConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation F's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setFconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setFconstB(newFconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetGconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setGconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation G's parameter B." << std::endl				
			<< "    e.g. './Sim4 setGconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newGconstB=-1.0;																					
	if (isDouble(nextCommand,newGconstB)==false)															
	{   //User typed 'setGConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation G's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setGconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newGconstB<0.0)																						
	{   //User typed 'setGConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation G's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setGconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setGconstB(newGconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetMconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setMconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation M's parameter B." << std::endl				
			<< "    e.g. './Sim4 setMconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newMconstB=-1.0;																					
	if (isDouble(nextCommand,newMconstB)==false)															
	{   //User typed 'setMConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation M's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setMconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newMconstB<0.0)																						
	{   //User typed 'setMConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation M's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setMconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setMconstB(newMconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetNconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setNconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation N's parameter B." << std::endl				
			<< "    e.g. './Sim4 setNconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newNconstB=-1.0;																					
	if (isDouble(nextCommand,newNconstB)==false)															
	{   //User typed 'setNConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation N's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setNconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newNconstB<0.0)																						
	{   //User typed 'setNConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation N's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setNconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setNconstB(newNconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetPconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setPconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation P's parameter B." << std::endl				
			<< "    e.g. './Sim4 setPconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newPconstB=-1.0;																					
	if (isDouble(nextCommand,newPconstB)==false)															
	{   //User typed 'setPConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation P's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setPconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newPconstB<0.0)																						
	{   //User typed 'setPConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation P's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setPconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setPconstB(newPconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetQconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setQconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation Q's parameter B." << std::endl				
			<< "    e.g. './Sim4 setQconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newQconstB=-1.0;																					
	if (isDouble(nextCommand,newQconstB)==false)															
	{   //User typed 'setQConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation Q's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setQconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newQconstB<0.0)																						
	{   //User typed 'setQConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation Q's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setQconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setQconstB(newQconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetRconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setRconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation R's parameter B." << std::endl				
			<< "    e.g. './Sim4 setRconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newRconstB=-1.0;																					
	if (isDouble(nextCommand,newRconstB)==false)															
	{   //User typed 'setRConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation R's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setRconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newRconstB<0.0)																						
	{   //User typed 'setRConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation R's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setRconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setRconstB(newRconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetWconstB(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setWconstB' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation W's parameter B." << std::endl				
			<< "    e.g. './Sim4 setWconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newWconstB=-1.0;																					
	if (isDouble(nextCommand,newWconstB)==false)															
	{   //User typed 'setWConstB [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation W's parameter B as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setWconstB 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newWconstB<0.0)																						
	{   //User typed 'setWConstB [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation W's parameter B to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setWconstB 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setWconstB(newWconstB);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetDconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setDconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation D's parameter C." << std::endl				
			<< "    e.g. './Sim4 setDconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newDconstC=-1.0;																					
	if (isDouble(nextCommand,newDconstC)==false)															
	{   //User typed 'setDConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation D's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setDconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newDconstC<0.0)																						
	{   //User typed 'setDConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation D's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setDconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setDconstC(newDconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetFconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setFconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation F's parameter C." << std::endl				
			<< "    e.g. './Sim4 setFconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newFconstC=-1.0;																					
	if (isDouble(nextCommand,newFconstC)==false)															
	{   //User typed 'setFConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation F's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setFconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newFconstC<0.0)																						
	{   //User typed 'setFConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation F's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setFconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setFconstC(newFconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetGconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setGconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation G's parameter C." << std::endl				
			<< "    e.g. './Sim4 setGconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newGconstC=-1.0;																					
	if (isDouble(nextCommand,newGconstC)==false)															
	{   //User typed 'setGConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation G's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setGconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newGconstC<0.0)																						
	{   //User typed 'setGConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation G's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setGconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setGconstC(newGconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetMconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setMconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation M's parameter C." << std::endl				
			<< "    e.g. './Sim4 setMconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newMconstC=-1.0;																					
	if (isDouble(nextCommand,newMconstC)==false)															
	{   //User typed 'setMConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation M's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setMconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newMconstC<0.0)																						
	{   //User typed 'setMConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation M's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setMconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setMconstC(newMconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetNconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setNconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation N's parameter C." << std::endl				
			<< "    e.g. './Sim4 setNconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newNconstC=-1.0;																					
	if (isDouble(nextCommand,newNconstC)==false)															
	{   //User typed 'setNConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation N's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setNconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newNconstC<0.0)																						
	{   //User typed 'setNConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation N's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setNconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setNconstC(newNconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetPconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setPconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation P's parameter C." << std::endl				
			<< "    e.g. './Sim4 setPconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newPconstC=-1.0;																					
	if (isDouble(nextCommand,newPconstC)==false)															
	{   //User typed 'setPConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation P's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setPconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newPconstC<0.0)																						
	{   //User typed 'setPConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation P's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setPconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setPconstC(newPconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetQconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setQconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation Q's parameter C." << std::endl				
			<< "    e.g. './Sim4 setQconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newQconstC=-1.0;																					
	if (isDouble(nextCommand,newQconstC)==false)															
	{   //User typed 'setQConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation Q's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setQconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newQconstC<0.0)																						
	{   //User typed 'setQConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation Q's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setQconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setQconstC(newQconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetRconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setRconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation R's parameter C." << std::endl				
			<< "    e.g. './Sim4 setRconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newRconstC=-1.0;																					
	if (isDouble(nextCommand,newRconstC)==false)															
	{   //User typed 'setRConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation R's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setRconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newRconstC<0.0)																						
	{   //User typed 'setRConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation R's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setRconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setRconstC(newRconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetWconstC(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setWconstC' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation W's parameter C." << std::endl				
			<< "    e.g. './Sim4 setWconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newWconstC=-1.0;																					
	if (isDouble(nextCommand,newWconstC)==false)															
	{   //User typed 'setWConstC [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation W's parameter C as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setWconstC 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newWconstC<0.0)																						
	{   //User typed 'setWConstC [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation W's parameter C to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setWconstC 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setWconstC(newWconstC);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetDconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setDconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation D's parameter D." << std::endl				
			<< "    e.g. './Sim4 setDconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newDconstD=-1.0;																					
	if (isDouble(nextCommand,newDconstD)==false)															
	{   //User typed 'setDConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation D's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setDconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newDconstD<0.0)																						
	{   //User typed 'setDConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation D's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setDconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setDconstD(newDconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetFconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setFconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation F's parameter D." << std::endl				
			<< "    e.g. './Sim4 setFconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newFconstD=-1.0;																					
	if (isDouble(nextCommand,newFconstD)==false)															
	{   //User typed 'setFConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation F's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setFconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newFconstD<0.0)																						
	{   //User typed 'setFConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation F's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setFconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setFconstD(newFconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetGconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setGconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation G's parameter D." << std::endl				
			<< "    e.g. './Sim4 setGconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newGconstD=-1.0;																					
	if (isDouble(nextCommand,newGconstD)==false)															
	{   //User typed 'setGConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation G's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setGconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newGconstD<0.0)																						
	{   //User typed 'setGConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation G's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setGconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setGconstD(newGconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetMconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setMconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation M's parameter D." << std::endl				
			<< "    e.g. './Sim4 setMconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newMconstD=-1.0;																					
	if (isDouble(nextCommand,newMconstD)==false)															
	{   //User typed 'setMConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation M's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setMconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newMconstD<0.0)																						
	{   //User typed 'setMConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation M's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setMconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setMconstD(newMconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetNconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setNconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation N's parameter D." << std::endl				
			<< "    e.g. './Sim4 setNconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newNconstD=-1.0;																					
	if (isDouble(nextCommand,newNconstD)==false)															
	{   //User typed 'setNConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation N's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setNconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newNconstD<0.0)																						
	{   //User typed 'setNConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation N's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setNconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setNconstD(newNconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetPconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setPconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation P's parameter D." << std::endl				
			<< "    e.g. './Sim4 setPconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newPconstD=-1.0;																					
	if (isDouble(nextCommand,newPconstD)==false)															
	{   //User typed 'setPConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation P's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setPconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newPconstD<0.0)																						
	{   //User typed 'setPConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation P's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setPconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setPconstD(newPconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetQconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setQconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation Q's parameter D." << std::endl				
			<< "    e.g. './Sim4 setQconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newQconstD=-1.0;																					
	if (isDouble(nextCommand,newQconstD)==false)															
	{   //User typed 'setQConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation Q's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setQconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newQconstD<0.0)																						
	{   //User typed 'setQConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation Q's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setQconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setQconstD(newQconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetRconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setRconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation R's parameter D." << std::endl				
			<< "    e.g. './Sim4 setRconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newRconstD=-1.0;																					
	if (isDouble(nextCommand,newRconstD)==false)															
	{   //User typed 'setRConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation R's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setRconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newRconstD<0.0)																						
	{   //User typed 'setRConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation R's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setRconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setRconstD(newRconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetWconstD(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setWconstD' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation W's parameter D." << std::endl				
			<< "    e.g. './Sim4 setWconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newWconstD=-1.0;																					
	if (isDouble(nextCommand,newWconstD)==false)															
	{   //User typed 'setWConstD [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation W's parameter D as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setWconstD 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newWconstD<0.0)																						
	{   //User typed 'setWConstD [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation W's parameter D to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setWconstD 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setWconstD(newWconstD);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetDconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setDconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation D's parameter E." << std::endl				
			<< "    e.g. './Sim4 setDconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newDconstE=-1.0;																					
	if (isDouble(nextCommand,newDconstE)==false)															
	{   //User typed 'setDConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation D's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setDconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newDconstE<0.0)																						
	{   //User typed 'setDConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation D's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setDconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setDconstE(newDconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetFconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setFconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation F's parameter E." << std::endl				
			<< "    e.g. './Sim4 setFconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newFconstE=-1.0;																					
	if (isDouble(nextCommand,newFconstE)==false)															
	{   //User typed 'setFConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation F's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setFconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newFconstE<0.0)																						
	{   //User typed 'setFConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation F's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setFconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setFconstE(newFconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetGconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setGconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation G's parameter E." << std::endl				
			<< "    e.g. './Sim4 setGconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newGconstE=-1.0;																					
	if (isDouble(nextCommand,newGconstE)==false)															
	{   //User typed 'setGConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation G's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setGconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newGconstE<0.0)																						
	{   //User typed 'setGConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation G's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setGconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setGconstE(newGconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetMconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setMconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation M's parameter E." << std::endl				
			<< "    e.g. './Sim4 setMconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newMconstE=-1.0;																					
	if (isDouble(nextCommand,newMconstE)==false)															
	{   //User typed 'setMConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation M's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setMconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newMconstE<0.0)																						
	{   //User typed 'setMConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation M's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setMconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setMconstE(newMconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetNconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setNconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation N's parameter E." << std::endl				
			<< "    e.g. './Sim4 setNconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newNconstE=-1.0;																					
	if (isDouble(nextCommand,newNconstE)==false)															
	{   //User typed 'setNConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation N's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setNconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newNconstE<0.0)																						
	{   //User typed 'setNConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation N's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setNconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setNconstE(newNconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetPconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setPconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation P's parameter E." << std::endl				
			<< "    e.g. './Sim4 setPconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newPconstE=-1.0;																					
	if (isDouble(nextCommand,newPconstE)==false)															
	{   //User typed 'setPConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation P's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setPconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newPconstE<0.0)																						
	{   //User typed 'setPConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation P's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setPconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setPconstE(newPconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetQconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setQconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation Q's parameter E." << std::endl				
			<< "    e.g. './Sim4 setQconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newQconstE=-1.0;																					
	if (isDouble(nextCommand,newQconstE)==false)															
	{   //User typed 'setQConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation Q's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setQconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newQconstE<0.0)																						
	{   //User typed 'setQConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation Q's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setQconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setQconstE(newQconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetRconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setRconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation R's parameter E." << std::endl				
			<< "    e.g. './Sim4 setRconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newRconstE=-1.0;																					
	if (isDouble(nextCommand,newRconstE)==false)															
	{   //User typed 'setRConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation R's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setRconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newRconstE<0.0)																						
	{   //User typed 'setRConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation R's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setRconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setRconstE(newRconstE);																	
}																											
//----------------------------------------------------------------------------------						
void Sim4Interpreter::interpretSetWconstE(const unsigned int& index)										
{																											
	if (index+1==mCommand.size())																			
	{   //User typed 'setWconstE' only																		
		std::cout << std::endl																				
			<< "    Please also specify the VALUE of equation W's parameter E." << std::endl				
			<< "    e.g. './Sim4 setWconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	const std::string nextCommand = mCommand[index+1];														
	double newWconstE=-1.0;																					
	if (isDouble(nextCommand,newWconstE)==false)															
	{   //User typed 'setWConstE [non-double]'																
		std::cout << std::endl																				
			<< "    Please specify the value of equation W's parameter E as a NUMBER." << std::endl		
			<< "    e.g. './Sim4 setWconstE 1.5'"	<< std::endl											
			<< std::endl;																					
		return;																								
	}																										
																											
	if (newWconstE<0.0)																						
	{   //User typed 'setWConstE [non-posive double]'														
		std::cout << std::endl																				
			<< "    Please set the VALUE of equation W's parameter E to a POSITIVE number." << std::endl	
			<< "    e.g. './Sim4 setWconstE 1.5'"	<< std::endl											
			<< std::endl << std::endl;																		
		return;																								
	}																										
	//Success. OptionsFile handles the feedback to the user													
	mOptionsFile.setWconstE(newWconstE);																	
}																											
//----------------------------------------------------------------------------------						
//
// COMPUTER GENERATED CODE
// OptionsFile
//
//----------------------------------------------------------------------------------
//  COMPUTER GENERATED CODE
void OptionsFile::setDconstA(const double& DconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's D constant A to 'DconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setDconstA(DconstA);   
        std::cout << std::endl															
            << "    Set 'equation D's, constant A' of all Simulation Files to "			
            << DconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setDconstA(DconstA);								
        std::cout << std::endl															
                  << "Set 'equation D's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << DconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setFconstA(const double& FconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's F constant A to 'FconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setFconstA(FconstA);   
        std::cout << std::endl															
            << "    Set 'equation F's, constant A' of all Simulation Files to "			
            << FconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setFconstA(FconstA);								
        std::cout << std::endl															
                  << "Set 'equation F's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << FconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setGconstA(const double& GconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's G constant A to 'GconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setGconstA(GconstA);   
        std::cout << std::endl															
            << "    Set 'equation G's, constant A' of all Simulation Files to "			
            << GconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setGconstA(GconstA);								
        std::cout << std::endl															
                  << "Set 'equation G's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << GconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setMconstA(const double& MconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's M constant A to 'MconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setMconstA(MconstA);   
        std::cout << std::endl															
            << "    Set 'equation M's, constant A' of all Simulation Files to "			
            << MconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setMconstA(MconstA);								
        std::cout << std::endl															
                  << "Set 'equation M's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << MconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setNconstA(const double& NconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's N constant A to 'NconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setNconstA(NconstA);   
        std::cout << std::endl															
            << "    Set 'equation N's, constant A' of all Simulation Files to "			
            << NconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setNconstA(NconstA);								
        std::cout << std::endl															
                  << "Set 'equation N's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << NconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setPconstA(const double& PconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's P constant A to 'PconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setPconstA(PconstA);   
        std::cout << std::endl															
            << "    Set 'equation P's, constant A' of all Simulation Files to "			
            << PconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setPconstA(PconstA);								
        std::cout << std::endl															
                  << "Set 'equation P's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << PconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setQconstA(const double& QconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's Q constant A to 'QconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setQconstA(QconstA);   
        std::cout << std::endl															
            << "    Set 'equation Q's, constant A' of all Simulation Files to "			
            << QconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setQconstA(QconstA);								
        std::cout << std::endl															
                  << "Set 'equation Q's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << QconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setRconstA(const double& RconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's R constant A to 'RconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setRconstA(RconstA);   
        std::cout << std::endl															
            << "    Set 'equation R's, constant A' of all Simulation Files to "			
            << RconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setRconstA(RconstA);								
        std::cout << std::endl															
                  << "Set 'equation R's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << RconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setWconstA(const double& WconstA)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's W constant A to 'WconstA'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setWconstA(WconstA);   
        std::cout << std::endl															
            << "    Set 'equation W's, constant A' of all Simulation Files to "			
            << WconstA << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setWconstA(WconstA);								
        std::cout << std::endl															
                  << "Set 'equation W's, constant A' of Simulation File #"				
                  << mUsesSimFile << " to " << WconstA << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setDconstB(const double& DconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's D constant B to 'DconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setDconstB(DconstB);   
        std::cout << std::endl															
            << "    Set 'equation D's, constant B' of all Simulation Files to "			
            << DconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setDconstB(DconstB);								
        std::cout << std::endl															
                  << "Set 'equation D's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << DconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setFconstB(const double& FconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's F constant B to 'FconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setFconstB(FconstB);   
        std::cout << std::endl															
            << "    Set 'equation F's, constant B' of all Simulation Files to "			
            << FconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setFconstB(FconstB);								
        std::cout << std::endl															
                  << "Set 'equation F's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << FconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setGconstB(const double& GconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's G constant B to 'GconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setGconstB(GconstB);   
        std::cout << std::endl															
            << "    Set 'equation G's, constant B' of all Simulation Files to "			
            << GconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setGconstB(GconstB);								
        std::cout << std::endl															
                  << "Set 'equation G's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << GconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setMconstB(const double& MconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's M constant B to 'MconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setMconstB(MconstB);   
        std::cout << std::endl															
            << "    Set 'equation M's, constant B' of all Simulation Files to "			
            << MconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setMconstB(MconstB);								
        std::cout << std::endl															
                  << "Set 'equation M's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << MconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setNconstB(const double& NconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's N constant B to 'NconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setNconstB(NconstB);   
        std::cout << std::endl															
            << "    Set 'equation N's, constant B' of all Simulation Files to "			
            << NconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setNconstB(NconstB);								
        std::cout << std::endl															
                  << "Set 'equation N's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << NconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setPconstB(const double& PconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's P constant B to 'PconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setPconstB(PconstB);   
        std::cout << std::endl															
            << "    Set 'equation P's, constant B' of all Simulation Files to "			
            << PconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setPconstB(PconstB);								
        std::cout << std::endl															
                  << "Set 'equation P's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << PconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setQconstB(const double& QconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's Q constant B to 'QconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setQconstB(QconstB);   
        std::cout << std::endl															
            << "    Set 'equation Q's, constant B' of all Simulation Files to "			
            << QconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setQconstB(QconstB);								
        std::cout << std::endl															
                  << "Set 'equation Q's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << QconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setRconstB(const double& RconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's R constant B to 'RconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setRconstB(RconstB);   
        std::cout << std::endl															
            << "    Set 'equation R's, constant B' of all Simulation Files to "			
            << RconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setRconstB(RconstB);								
        std::cout << std::endl															
                  << "Set 'equation R's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << RconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setWconstB(const double& WconstB)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's W constant B to 'WconstB'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setWconstB(WconstB);   
        std::cout << std::endl															
            << "    Set 'equation W's, constant B' of all Simulation Files to "			
            << WconstB << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setWconstB(WconstB);								
        std::cout << std::endl															
                  << "Set 'equation W's, constant B' of Simulation File #"				
                  << mUsesSimFile << " to " << WconstB << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setDconstC(const double& DconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's D constant C to 'DconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setDconstC(DconstC);   
        std::cout << std::endl															
            << "    Set 'equation D's, constant C' of all Simulation Files to "			
            << DconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setDconstC(DconstC);								
        std::cout << std::endl															
                  << "Set 'equation D's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << DconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setFconstC(const double& FconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's F constant C to 'FconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setFconstC(FconstC);   
        std::cout << std::endl															
            << "    Set 'equation F's, constant C' of all Simulation Files to "			
            << FconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setFconstC(FconstC);								
        std::cout << std::endl															
                  << "Set 'equation F's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << FconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setGconstC(const double& GconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's G constant C to 'GconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setGconstC(GconstC);   
        std::cout << std::endl															
            << "    Set 'equation G's, constant C' of all Simulation Files to "			
            << GconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setGconstC(GconstC);								
        std::cout << std::endl															
                  << "Set 'equation G's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << GconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setMconstC(const double& MconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's M constant C to 'MconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setMconstC(MconstC);   
        std::cout << std::endl															
            << "    Set 'equation M's, constant C' of all Simulation Files to "			
            << MconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setMconstC(MconstC);								
        std::cout << std::endl															
                  << "Set 'equation M's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << MconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setNconstC(const double& NconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's N constant C to 'NconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setNconstC(NconstC);   
        std::cout << std::endl															
            << "    Set 'equation N's, constant C' of all Simulation Files to "			
            << NconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setNconstC(NconstC);								
        std::cout << std::endl															
                  << "Set 'equation N's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << NconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setPconstC(const double& PconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's P constant C to 'PconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setPconstC(PconstC);   
        std::cout << std::endl															
            << "    Set 'equation P's, constant C' of all Simulation Files to "			
            << PconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setPconstC(PconstC);								
        std::cout << std::endl															
                  << "Set 'equation P's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << PconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setQconstC(const double& QconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's Q constant C to 'QconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setQconstC(QconstC);   
        std::cout << std::endl															
            << "    Set 'equation Q's, constant C' of all Simulation Files to "			
            << QconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setQconstC(QconstC);								
        std::cout << std::endl															
                  << "Set 'equation Q's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << QconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setRconstC(const double& RconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's R constant C to 'RconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setRconstC(RconstC);   
        std::cout << std::endl															
            << "    Set 'equation R's, constant C' of all Simulation Files to "			
            << RconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setRconstC(RconstC);								
        std::cout << std::endl															
                  << "Set 'equation R's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << RconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setWconstC(const double& WconstC)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's W constant C to 'WconstC'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setWconstC(WconstC);   
        std::cout << std::endl															
            << "    Set 'equation W's, constant C' of all Simulation Files to "			
            << WconstC << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setWconstC(WconstC);								
        std::cout << std::endl															
                  << "Set 'equation W's, constant C' of Simulation File #"				
                  << mUsesSimFile << " to " << WconstC << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setDconstD(const double& DconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's D constant D to 'DconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setDconstD(DconstD);   
        std::cout << std::endl															
            << "    Set 'equation D's, constant D' of all Simulation Files to "			
            << DconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setDconstD(DconstD);								
        std::cout << std::endl															
                  << "Set 'equation D's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << DconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setFconstD(const double& FconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's F constant D to 'FconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setFconstD(FconstD);   
        std::cout << std::endl															
            << "    Set 'equation F's, constant D' of all Simulation Files to "			
            << FconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setFconstD(FconstD);								
        std::cout << std::endl															
                  << "Set 'equation F's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << FconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setGconstD(const double& GconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's G constant D to 'GconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setGconstD(GconstD);   
        std::cout << std::endl															
            << "    Set 'equation G's, constant D' of all Simulation Files to "			
            << GconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setGconstD(GconstD);								
        std::cout << std::endl															
                  << "Set 'equation G's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << GconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setMconstD(const double& MconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's M constant D to 'MconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setMconstD(MconstD);   
        std::cout << std::endl															
            << "    Set 'equation M's, constant D' of all Simulation Files to "			
            << MconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setMconstD(MconstD);								
        std::cout << std::endl															
                  << "Set 'equation M's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << MconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setNconstD(const double& NconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's N constant D to 'NconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setNconstD(NconstD);   
        std::cout << std::endl															
            << "    Set 'equation N's, constant D' of all Simulation Files to "			
            << NconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setNconstD(NconstD);								
        std::cout << std::endl															
                  << "Set 'equation N's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << NconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setPconstD(const double& PconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's P constant D to 'PconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setPconstD(PconstD);   
        std::cout << std::endl															
            << "    Set 'equation P's, constant D' of all Simulation Files to "			
            << PconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setPconstD(PconstD);								
        std::cout << std::endl															
                  << "Set 'equation P's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << PconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setQconstD(const double& QconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's Q constant D to 'QconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setQconstD(QconstD);   
        std::cout << std::endl															
            << "    Set 'equation Q's, constant D' of all Simulation Files to "			
            << QconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setQconstD(QconstD);								
        std::cout << std::endl															
                  << "Set 'equation Q's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << QconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setRconstD(const double& RconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's R constant D to 'RconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setRconstD(RconstD);   
        std::cout << std::endl															
            << "    Set 'equation R's, constant D' of all Simulation Files to "			
            << RconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setRconstD(RconstD);								
        std::cout << std::endl															
                  << "Set 'equation R's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << RconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setWconstD(const double& WconstD)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's W constant D to 'WconstD'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setWconstD(WconstD);   
        std::cout << std::endl															
            << "    Set 'equation W's, constant D' of all Simulation Files to "			
            << WconstD << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setWconstD(WconstD);								
        std::cout << std::endl															
                  << "Set 'equation W's, constant D' of Simulation File #"				
                  << mUsesSimFile << " to " << WconstD << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setDconstE(const double& DconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's D constant E to 'DconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setDconstE(DconstE);   
        std::cout << std::endl															
            << "    Set 'equation D's, constant E' of all Simulation Files to "			
            << DconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setDconstE(DconstE);								
        std::cout << std::endl															
                  << "Set 'equation D's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << DconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setFconstE(const double& FconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's F constant E to 'FconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setFconstE(FconstE);   
        std::cout << std::endl															
            << "    Set 'equation F's, constant E' of all Simulation Files to "			
            << FconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setFconstE(FconstE);								
        std::cout << std::endl															
                  << "Set 'equation F's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << FconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setGconstE(const double& GconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's G constant E to 'GconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setGconstE(GconstE);   
        std::cout << std::endl															
            << "    Set 'equation G's, constant E' of all Simulation Files to "			
            << GconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setGconstE(GconstE);								
        std::cout << std::endl															
                  << "Set 'equation G's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << GconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setMconstE(const double& MconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's M constant E to 'MconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setMconstE(MconstE);   
        std::cout << std::endl															
            << "    Set 'equation M's, constant E' of all Simulation Files to "			
            << MconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setMconstE(MconstE);								
        std::cout << std::endl															
                  << "Set 'equation M's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << MconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setNconstE(const double& NconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's N constant E to 'NconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setNconstE(NconstE);   
        std::cout << std::endl															
            << "    Set 'equation N's, constant E' of all Simulation Files to "			
            << NconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setNconstE(NconstE);								
        std::cout << std::endl															
                  << "Set 'equation N's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << NconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setPconstE(const double& PconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's P constant E to 'PconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setPconstE(PconstE);   
        std::cout << std::endl															
            << "    Set 'equation P's, constant E' of all Simulation Files to "			
            << PconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setPconstE(PconstE);								
        std::cout << std::endl															
                  << "Set 'equation P's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << PconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setQconstE(const double& QconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's Q constant E to 'QconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setQconstE(QconstE);   
        std::cout << std::endl															
            << "    Set 'equation Q's, constant E' of all Simulation Files to "			
            << QconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setQconstE(QconstE);								
        std::cout << std::endl															
                  << "Set 'equation Q's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << QconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setRconstE(const double& RconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's R constant E to 'RconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setRconstE(RconstE);   
        std::cout << std::endl															
            << "    Set 'equation R's, constant E' of all Simulation Files to "			
            << RconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setRconstE(RconstE);								
        std::cout << std::endl															
                  << "Set 'equation R's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << RconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setWconstE(const double& WconstE)										
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));  
																							
    if (mUsesSimFile==-1)																	
    {   //Set all equation's W constant E to 'WconstE'									
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setWconstE(WconstE);   
        std::cout << std::endl															
            << "    Set 'equation W's, constant E' of all Simulation Files to "			
            << WconstE << std::endl << std::endl;											
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setWconstE(WconstE);								
        std::cout << std::endl															
                  << "Set 'equation W's, constant E' of Simulation File #"				
                  << mUsesSimFile << " to " << WconstE << std::endl << std::endl;		
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setD(const EnumD& enumD)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation D to 'enumD'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setD(enumD);			
        std::cout << std::endl															
            << "    Set equation D of all Simulation Files to "							
            << enumDtoString(enumD) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setD(enumD);										
        std::cout << std::endl															
            << "    Set equation D of Simulation File #"								
            << mUsesSimFile << " to " << enumDtoString(enumD)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setF(const EnumF& enumF)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation F to 'enumF'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setF(enumF);			
        std::cout << std::endl															
            << "    Set equation F of all Simulation Files to "							
            << enumFtoString(enumF) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setF(enumF);										
        std::cout << std::endl															
            << "    Set equation F of Simulation File #"								
            << mUsesSimFile << " to " << enumFtoString(enumF)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setG(const EnumG& enumG)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation G to 'enumG'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setG(enumG);			
        std::cout << std::endl															
            << "    Set equation G of all Simulation Files to "							
            << enumGtoString(enumG) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setG(enumG);										
        std::cout << std::endl															
            << "    Set equation G of Simulation File #"								
            << mUsesSimFile << " to " << enumGtoString(enumG)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setM(const EnumM& enumM)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation M to 'enumM'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setM(enumM);			
        std::cout << std::endl															
            << "    Set equation M of all Simulation Files to "							
            << enumMtoString(enumM) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setM(enumM);										
        std::cout << std::endl															
            << "    Set equation M of Simulation File #"								
            << mUsesSimFile << " to " << enumMtoString(enumM)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setN(const EnumN& enumN)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation N to 'enumN'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setN(enumN);			
        std::cout << std::endl															
            << "    Set equation N of all Simulation Files to "							
            << enumNtoString(enumN) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setN(enumN);										
        std::cout << std::endl															
            << "    Set equation N of Simulation File #"								
            << mUsesSimFile << " to " << enumNtoString(enumN)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setP(const EnumP& enumP)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation P to 'enumP'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setP(enumP);			
        std::cout << std::endl															
            << "    Set equation P of all Simulation Files to "							
            << enumPtoString(enumP) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setP(enumP);										
        std::cout << std::endl															
            << "    Set equation P of Simulation File #"								
            << mUsesSimFile << " to " << enumPtoString(enumP)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setQ(const EnumQ& enumQ)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation Q to 'enumQ'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setQ(enumQ);			
        std::cout << std::endl															
            << "    Set equation Q of all Simulation Files to "							
            << enumQtoString(enumQ) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setQ(enumQ);										
        std::cout << std::endl															
            << "    Set equation Q of Simulation File #"								
            << mUsesSimFile << " to " << enumQtoString(enumQ)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setR(const EnumR& enumR)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation R to 'enumR'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setR(enumR);			
        std::cout << std::endl															
            << "    Set equation R of all Simulation Files to "							
            << enumRtoString(enumR) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setR(enumR);										
        std::cout << std::endl															
            << "    Set equation R of Simulation File #"								
            << mUsesSimFile << " to " << enumRtoString(enumR)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
void OptionsFile::setW(const EnumW& enumW)												
{																							
    assert(mUsesSimFile>=-1 && mUsesSimFile < static_cast<int>(mSimulationFile.size()));	
																							
    if (mUsesSimFile==-1)																	
    {   //Set all SimFile's equation W to 'enumW'											
        const unsigned int nSimFile = mSimulationFile.size();								
        for (unsigned int i=0; i<nSimFile; ++i) mSimulationFile[i].setW(enumW);			
        std::cout << std::endl															
            << "    Set equation W of all Simulation Files to "							
            << enumWtoString(enumW) << std::endl << std::endl;							
    }																						
    else																					
    {																						
        mSimulationFile[mUsesSimFile].setW(enumW);										
        std::cout << std::endl															
            << "    Set equation W of Simulation File #"								
            << mUsesSimFile << " to " << enumWtoString(enumW)							
            << std::endl << std::endl;													
    }																						
}																							
//----------------------------------------------------------------------------------		
//----------------------------------------------------------------------------------
//
// COMPUTER GENERATED CODE
// SimulationFile
//
//----------------------------------------------------------------------------------
//  COMPUTER GENERATED CODE
void SimulationFile::setDconstA(const double& DconstA)									
{																						
	mParameters.paramsD.A = DconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setFconstA(const double& FconstA)									
{																						
	mParameters.paramsF.A = FconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setGconstA(const double& GconstA)									
{																						
	mParameters.paramsG.A = GconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setMconstA(const double& MconstA)									
{																						
	mParameters.paramsM.A = MconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setNconstA(const double& NconstA)									
{																						
	mParameters.paramsN.A = NconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setPconstA(const double& PconstA)									
{																						
	mParameters.paramsP.A = PconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setQconstA(const double& QconstA)									
{																						
	mParameters.paramsQ.A = QconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setRconstA(const double& RconstA)									
{																						
	mParameters.paramsR.A = RconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setWconstA(const double& WconstA)									
{																						
	mParameters.paramsW.A = WconstA;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setDconstB(const double& DconstB)									
{																						
	mParameters.paramsD.B = DconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setFconstB(const double& FconstB)									
{																						
	mParameters.paramsF.B = FconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setGconstB(const double& GconstB)									
{																						
	mParameters.paramsG.B = GconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setMconstB(const double& MconstB)									
{																						
	mParameters.paramsM.B = MconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setNconstB(const double& NconstB)									
{																						
	mParameters.paramsN.B = NconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setPconstB(const double& PconstB)									
{																						
	mParameters.paramsP.B = PconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setQconstB(const double& QconstB)									
{																						
	mParameters.paramsQ.B = QconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setRconstB(const double& RconstB)									
{																						
	mParameters.paramsR.B = RconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setWconstB(const double& WconstB)									
{																						
	mParameters.paramsW.B = WconstB;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setDconstC(const double& DconstC)									
{																						
	mParameters.paramsD.C = DconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setFconstC(const double& FconstC)									
{																						
	mParameters.paramsF.C = FconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setGconstC(const double& GconstC)									
{																						
	mParameters.paramsG.C = GconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setMconstC(const double& MconstC)									
{																						
	mParameters.paramsM.C = MconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setNconstC(const double& NconstC)									
{																						
	mParameters.paramsN.C = NconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setPconstC(const double& PconstC)									
{																						
	mParameters.paramsP.C = PconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setQconstC(const double& QconstC)									
{																						
	mParameters.paramsQ.C = QconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setRconstC(const double& RconstC)									
{																						
	mParameters.paramsR.C = RconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setWconstC(const double& WconstC)									
{																						
	mParameters.paramsW.C = WconstC;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setDconstD(const double& DconstD)									
{																						
	mParameters.paramsD.D = DconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setFconstD(const double& FconstD)									
{																						
	mParameters.paramsF.D = FconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setGconstD(const double& GconstD)									
{																						
	mParameters.paramsG.D = GconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setMconstD(const double& MconstD)									
{																						
	mParameters.paramsM.D = MconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setNconstD(const double& NconstD)									
{																						
	mParameters.paramsN.D = NconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setPconstD(const double& PconstD)									
{																						
	mParameters.paramsP.D = PconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setQconstD(const double& QconstD)									
{																						
	mParameters.paramsQ.D = QconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setRconstD(const double& RconstD)									
{																						
	mParameters.paramsR.D = RconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setWconstD(const double& WconstD)									
{																						
	mParameters.paramsW.D = WconstD;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setDconstE(const double& DconstE)									
{																						
	mParameters.paramsD.E = DconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setFconstE(const double& FconstE)									
{																						
	mParameters.paramsF.E = FconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setGconstE(const double& GconstE)									
{																						
	mParameters.paramsG.E = GconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setMconstE(const double& MconstE)									
{																						
	mParameters.paramsM.E = MconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setNconstE(const double& NconstE)									
{																						
	mParameters.paramsN.E = NconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setPconstE(const double& PconstE)									
{																						
	mParameters.paramsP.E = PconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setQconstE(const double& QconstE)									
{																						
	mParameters.paramsQ.E = QconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setRconstE(const double& RconstE)									
{																						
	mParameters.paramsR.E = RconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
void SimulationFile::setWconstE(const double& WconstE)									
{																						
	mParameters.paramsW.E = WconstE;													
	writeToFile();																		
}																						
//----------------------------------------------------------------------------------   
