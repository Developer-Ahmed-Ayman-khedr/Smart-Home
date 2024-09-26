/*
 * Code_APP.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#include "Code_APP.h"

//InitializeEEPROM
u8 EEPROMValues[24];

BOOL EEPROMInitialize(){
	u16 EEPROMINDEX = 0;
	BOOL ReturnFlag = FALSE;
	//Read the EEPROM an put it into the EEPROMValues Array
	//Admin       ,User1          ,User2              ,User3               ,User4
	//[0][1][2][3],[4][5][6][7][8],[9][10][11][12][13],[14][15][16][17][18],[19][20][21][22][23]
	while (EEPROMINDEX<=MAXEEPROMUSER)
	{
		_delay_ms(50);
		EEPROMValues[EEPROMINDEX] = INTERNALEEPROM_Read(EEPROMINDEX);
		EEPROMINDEX++;
		ReturnFlag = TRUE;
	}
	return ReturnFlag;
}

//Admin
void password_init ()
{
	DIO_setPinDir(DIO_PINA0,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA2,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA3,DIO_OUTPUT);
}


BOOL CheckPasswordAdmin(){
	static u8 UART_RecevedData = UART_NOT_RECEIVE, Entered_Pass[4], InputIndex = 0, counter=0;
	static BOOL AccessFlag = TRUE;	
	UART_RecevedData = UART_receiveData();
	if (UART_RecevedData!=UART_NOT_RECEIVE)
	{	
		Entered_Pass[InputIndex] = UART_RecevedData-48;
		UART_sendData(UART_RecevedData);
		UART_sendStr("\r\n");
		InputIndex++;
		UART_RecevedData = UART_NOT_RECEIVE;
	}
		
	//Check if the user entered 4 Numbers
	if (InputIndex==4)
	{
		InputIndex = 0;
		//Check if the entered Array is equal to the first 4 Elements in the EEPROMValues Array
		while (InputIndex<4)
		{
			if (Entered_Pass[InputIndex]==EEPROMValues[InputIndex])
			{
				AccessFlag = TRUE;
			}
			else
			{
				AccessFlag = FALSE;
				break;
			}
			InputIndex++;
		}
		if (AccessFlag==TRUE)
		{
			UART_sendStr("Welcome\r\n");
			InputIndex=0;
			return TRUE;
		}
		else {
			UART_sendStr("WRONGPASSWORD");
			counter++;
			switch (counter){
				case 1:
				DIO_setPinValue (DIO_PINA0,DIO_HIGH);
				break;
				case 2:
				DIO_setPinValue (DIO_PINA2,DIO_HIGH);
				break;
				case 3:
				DIO_setPinValue (DIO_PINA3,DIO_HIGH);
				UART_sendStr("BLOCK");
				_delay_ms(60000);
				break;
				default:
				break;
			}
		}
		InputIndex = 0;
	}
	return FALSE;
}

//Temperature
void TEMP_Check(u8 Platform){
	
	//Temperature read pin
	DIO_setPinDir(DIO_PINA1,DIO_INPUT);

	//DC Motor control

	//Enable
	DIO_setPinDir(DIO_PIND4,DIO_OUTPUT);

	//Direction
	DIO_setPinDir(DIO_PIND3,DIO_OUTPUT);
	DIO_setPinDir(DIO_PIND7,DIO_OUTPUT);
	
	//Read the ADC 
	
	u16 VDigitalTemp;
	f32 VAnalogTemp;
	
	VDigitalTemp = ADC_read(ADC_CH1);
	VAnalogTemp = ADC_convertAnalog(VDigitalTemp)*100;
	
	if (Platform==OUTPUTLCD)
	{
		//LCD_clearDis();
		LCD_sendStr("Temp = ");
		LCD_sendFloatNum(VAnalogTemp);
		LCD_sendData('C');
	}
	
	//Start the Cooling Motor
	if(VAnalogTemp>28){

		//Enable
		DIO_setPinValue(DIO_PIND4,DIO_HIGH);

		//Direction
		DIO_setPinValue(DIO_PIND3,DIO_HIGH);
		DIO_setPinValue(DIO_PIND7,DIO_LOW);
	}
	//Stop the Cooling Motor
	else if(VAnalogTemp<28){

		//Enable
		DIO_setPinValue(DIO_PIND4,DIO_LOW);

		//Direction
		DIO_setPinValue(DIO_PIND3,DIO_LOW);
		DIO_setPinValue(DIO_PINC6,DIO_LOW);
	}
	_delay_ms(1000);
}

//Lighting
void LIGHTING_Start(u8 Start){
	
	DIO_setPinDir(DIO_PINC2,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINC7,DIO_OUTPUT);
	
	if (Start==LIGHTINGENTRANCE)
	{
		DIO_togglePinValue(DIO_PINC7);
	} 
	else if (Start==LIGHTINHALL)
	{
		DIO_togglePinValue(DIO_PINC2);
	}
}

//Hold
//UltraSonic using Timer0 and INT0
f32 Ttick = 0.004, TONTime=0; //ms
u32 dis;
u32 OvCounter=0, TimeOn=0;
u8 edge = 0;

void Timer0OvFunc(){
	OvCounter++;
}

void UltrasonicFunc(){
	//rising
	if (edge==0){

		TIMER0_setPreload(0);
		TIMER0_start(TIMER0_DIV64);

		OvCounter = 0;

		EXT_int0Int(EXT_FALLING);

		edge++;

	}
	//falling
	else if (edge==1){
		TIMER0_start(TIMER0_STOP);
		TimeOn = TIMER0_getCounter();

		TONTime = Ttick*(TimeOn+(256*OvCounter));
		dis = 17 * TONTime;

		EXT_int0Int(EXT_RISING);

		edge = 0;
	}
}

void HOLD_init(){
	//TR
	DIO_setPinDir(DIO_PINC6,DIO_OUTPUT);

	//ECHO
	DIO_setPinDir(DIO_PIND2,DIO_INPUT);

	//Timer0
	TIMER0_initNormal();

	TIMER0_setCallbackOv(Timer0OvFunc);

	//External Interrupt
	EXT_int0Int(EXT_RISING);

	EXT_setcallbackInt0(UltrasonicFunc);
}

void HOLD_Start(){
	DIO_setPinValue(DIO_PINC6,DIO_HIGH);
	_delay_us(11);
	DIO_setPinValue(DIO_PINC6,DIO_LOW);
}

u32 HOLD_Retrun(){
	return dis;
}

//Door using Servo
void DOORCONTROL_init(){

	//Servo Motor control PIN
	DIO_setPinDir(DIO_PIND5,DIO_OUTPUT);

	//Timer1
	TIMER1_initFastPwmMod14();

	TIMER1_setFrequency(50);
	
	//Close the door
	TIMER1_setOcr(374);
	
}

void DOORCONTROL_Start(){
	//Start the Holding process
	HOLD_Start();
	
	if(HOLD_Retrun()<30)
	{
		//Open the door
		TIMER1_setOcr(499);
	}
	
	//Wait for the Ultrasonic Sensor to return a distance greater than 30cm
	
	while(HOLD_Retrun()<=30){
		HOLD_Start();
	}
	if (HOLD_Retrun()>30)
	{
		//Close the door
		TIMER1_setOcr(374);
	}
}

//User
void AddUser(){
	 // temp array to put pass in the main array
	 u8 TEMPArr [5] ;
	 u8 UARTResevedData = UART_NOT_RECEIVE;

	 UART_sendStr("Enter pass:\r\n");
	 u8 index1 = 0;
	 while (index1<5)
	 {
		 UARTResevedData = UART_NOT_RECEIVE;
		 UARTResevedData = UART_receiveData();
		 if (UARTResevedData!=UART_NOT_RECEIVE)
		 {
			 TEMPArr[index1] = UARTResevedData-48;
			 index1++;
			 UARTResevedData = UART_NOT_RECEIVE;
		 }
	 }
	 if (index1==5)
	 {
		 UART_sendStr("Saving\r\n");
		 for (u8 Arrayindex=4 ;Arrayindex<24 ; Arrayindex+=5)
		 {
			 if ( EEPROMValues[Arrayindex] == 255 )
			 {
				 u8 INDEX1 = 0;
				 for (u8 EEPROMIndex= Arrayindex ;EEPROMIndex<(Arrayindex+5) ;EEPROMIndex++)
				 {
					 // will put the pass from temp array in EEPROMValues
					 EEPROMValues [EEPROMIndex] = TEMPArr [INDEX1];
					 INDEX1++;
				 }
				 break;
			 }
		 }

		 for (u16 EEPROMIndex=4 ;EEPROMIndex<=23;EEPROMIndex++)
		 {
			 _delay_ms(50) ;
			 INTERNALEEPROM_SendByte(EEPROMValues[EEPROMIndex],EEPROMIndex);
		 }
	 }
	 EEPROMInitialize();
}

BOOL UserLogin(){
	static BOOL AccessResult = FALSE;
	static u8 User_Data[5];
	u8 KPD_ReceivedData = KPD_UNPRESSED;
	static u8 index = 0;
	static u8 counter = 0;
	
	AccessResult = FALSE;
	
	KPD_ReceivedData = KPD_read();
	if (KPD_ReceivedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
		LCD_sendData(KPD_ReceivedData);
		User_Data[index] = KPD_ReceivedData-48;
		index++;
	}
	//if the user entered five digits
	if (index>4)
	{
		u8 i2 = 4;
		while(i2<24)
		{
			
			//Check if the first digit is equal to a place in the EEPROMValues array in the addresses (4,9,14,19)
			if (User_Data[0]==EEPROMValues[i2])
			{
				index = 0;
				for (u16 index2 = i2; index2<(i2+5); index2++)
				{
					if (User_Data[index]==EEPROMValues[index2])
					{
						LCD_sendData('w');
						AccessResult = TRUE;
					}
					else
					{
						AccessResult = FALSE;
						break;
					}
					index++;
				}
				break;
			}
			else{
				AccessResult = FALSE;
			}
			i2+=5;
		}

		LCD_clearDis();
		if (AccessResult==TRUE)
		{
			LCD_sendStr("Welcome");
			index = 0;
			_delay_ms(300);
			return AccessResult;
		}
		else{
			LCD_sendStr("WrongData");
			counter++;
			switch (counter){
				case 1:
				DIO_setPinValue (DIO_PINA0,DIO_HIGH);
				break;
				case 2:
				DIO_setPinValue (DIO_PINA2,DIO_HIGH);
				break;
				case 3:
				DIO_setPinValue (DIO_PINA3,DIO_HIGH);
				LCD_sendStr("BLOCK");
				_delay_ms(60000);
				break;
				default:
				break;
			}
		}
		index = 0;
		
	}
	return AccessResult;
}

void DeleteUser(u8 userID){
	switch (userID)
	{
		case 1:
			for (u8 i = 4; i<9; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		case 2:
			for 
			(u8 i = 9; i<14; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		case 3:
			for (u8 i =14 ; i<19; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		case 4:
			for (u8 i = 19; i<=24; i++){
				_delay_ms(50);
				INTERNALEEPROM_SendByte(255,i);
			}
			break;
		default:
			break;	
	}
	UART_sendStr("Deleted\r\n");
	EEPROMInitialize();
}

//Main
void Code_APPInitDriversTask(void *pvParameters){
	while(1){
		//Initialize the system Drivers
		GI_enable();
		ADC_init();
		KPD_init();
		LCD_init();
		UART_init();
		
		//Initialize the program features
		HOLD_init();
		password_init();
		DOORCONTROL_init();
		EEPROMInitialize();
		
		vTaskResume(LoginTaskHandle);		
		vTaskDelete(NULL);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}

void LoginTask(void * pvParameters ){
	while(1)
	{		
		if(CheckPasswordAdmin()==TRUE)
		{			
			xTaskCreate(AdminOptionsTask,NULL,100,NULL,2,&AdminOptionsTaskHandle);
			vTaskSuspend(NULL);
		}
		if(UserLogin() == TRUE){			
			xTaskCreate(UserOptionsTask,NULL,100,NULL,2,&UserOptionsTaskHandle);
			vTaskSuspend(NULL);
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

void AdminOptionsTask(void * pvParameters ){
	u8 AdminControlCounter = 0;
	u8 Adminrecieve = UART_NOT_RECEIVE;
	while(1){		
		
		//Admin Section
		if (AdminControlCounter==0)
		{
			//Correct password show options
			UART_sendStr("1.Light 2.Temp 3.Enter 4.Add User 5.Delete User 6.logout\r\n");
			AdminControlCounter = 1;
		}
		if (AdminControlCounter==1)
		{
			//UART read
			Adminrecieve = UART_receiveDataWait();
				
			if(Adminrecieve==INPUT_Light){
				//lighting
				UART_sendStr("1.Entrance 2.Hall\r\n");
					
				Adminrecieve = UART_receiveDataWait();
					
				if (Adminrecieve ==LIGHTINGENTRANCE)
				{
					LIGHTING_Start(LIGHTINGENTRANCE);
				}
				else if (Adminrecieve == LIGHTINHALL)
				{
					LIGHTING_Start(LIGHTINHALL);
				}
			}
			else if(Adminrecieve ==INPUT_Temp){
				//Temperature check
				TEMP_Check(OUTPUTUART);
			}
			else if (Adminrecieve ==INPUT_ENTERANCE)
			{
				UART_sendStr("\r\n");
				DOORCONTROL_Start();
			}

			else if (Adminrecieve ==INPUT_ADDUSER)
			{
				AddUser();
			}
			else if (Adminrecieve == INPUT_DELETEUSER)
			{
				// show the saved users for admin to delete from them
				UART_sendStr("\r\n");
				for (u8 i=4 ; i<24 ; i++)
				{
					UART_sendData(EEPROMValues[i]+48);
					if (i==8||i==13||i==18||i==23)
					{
						UART_sendData('*');
					}
				}
				UART_sendStr("\r\nEnter user id\r\n");
				Adminrecieve = UART_receiveDataWait()-48;
				DeleteUser(Adminrecieve);
				//ControlCounter = 0;
			}
			else if (Adminrecieve == INPUT_LOGOUTADMIN)
			{
				vTaskResume(LoginTaskHandle);
				vTaskDelete(NULL);
			}
			AdminControlCounter = 0;
		}
		vTaskDelay(5/portTICK_PERIOD_MS);
	}	
}
	
void UserOptionsTask(void * pvParameters ){
	u8 UserControlCounter = 0;
	u8 UserRecieve = KPD_UNPRESSED;
	
	u8 lcdsend[20] = "1.Li2.T3.E4.log"; //1.Light 2.Temp 3.Enter 4.logout
	while(1){
		switch (UserControlCounter)
		{
			case 0:
				//Correct password Show the options
				LCD_clearDis();
				LCD_sendStr(lcdsend);
				LCD_GoTo(0,1);
				UserControlCounter = 1;
				break;
			case 1:			
				//Keypad read
				UserRecieve = KPD_read();
			
				if (UserRecieve!=KPD_UNPRESSED)
				{
					while(KPD_read()!=KPD_UNPRESSED);
				
					LCD_sendData(UserRecieve);
				
					//lighting
					if(UserRecieve==INPUT_Light){
						//lighting
						LCD_clearDis();
						//1.Hall 2.Entrance
						LCD_sendData('E');
						LCD_sendData(' ');
						LCD_sendData('H');
						LCD_GoTo(0,1);
						UserControlCounter = 2;
					}
					//else 
					if(UserRecieve ==INPUT_Temp){
						//Temperature check
						LCD_clearDis();
						TEMP_Check(OUTPUTLCD);
						UserControlCounter = 0;
					}
					//else 
					if (UserRecieve ==INPUT_ENTERANCE)
					{
						//Yes to open the door and no to keep it closed
						UART_sendData('y');
						UART_sendData('n');
						UserRecieve = UART_receiveDataWait();
						if (UserRecieve=='y')
						{
							DOORCONTROL_Start();
						}
						UserControlCounter = 0;
					}
					//Logout for the user
					else if (UserRecieve == INPUT_LOGOUTUSER)
					{
						LCD_clearDis();
						vTaskResume(LoginTaskHandle);
						vTaskDelete(NULL);
					}
				}
				break;
			case 2:
				//lighting
				//Keypad read
				UserRecieve = KPD_read();
			
				if (UserRecieve!=KPD_UNPRESSED)
				{
					while(KPD_read()!=KPD_UNPRESSED);
				
					LCD_sendData(UserRecieve);
				
					//lighting
					if (UserRecieve ==LIGHTINGENTRANCE)
					{
						LIGHTING_Start(LIGHTINGENTRANCE);
						UserControlCounter = 0;
					}
					else if (UserRecieve == LIGHTINHALL)
					{
						LIGHTING_Start(LIGHTINHALL);
						UserControlCounter = 0;
				}
			}
				break;
			default:
			break;
		}
	vTaskDelay(5/portTICK_PERIOD_MS);
	}
}

//Source Code
int source_code()
{		
	xTaskCreate(Code_APPInitDriversTask,NULL,100,NULL,3,&Code_APPInitDriversTaskHandle);
	
	xTaskCreate(LoginTask,NULL,100,NULL,3,&LoginTaskHandle);
	
	vTaskSuspend(LoginTaskHandle);
	
	vTaskStartScheduler();
	
	while (1)
	{
		
	}
	return 0;
}
