/*
 * Code_APP.c
 *
 *  Created on: Jun 25, 2024
 *      Author: ahmed
 */

#include"Code_APP.h"

//Admin
void password_init ()
{

	DIO_setPinDir(DIO_PINA0,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA2,DIO_OUTPUT);

	DIO_setPinDir (DIO_PINA3,DIO_OUTPUT);
}

BOOL flage=FALSE;

BOOL CheckPasswordAdmin(){
	static BOOL EEPROM_flage = FALSE,Save_flage = FALSE;
	static u8 UART_RecevedData = 'x', Entered_Pass[4], InputIndex = 0, EEPROMRecevedData = 0,counter=0;
	static u16 EEPROMAdminLocation = 0;
	/*while (EEPROMAdminLocation<4)
	{
		_delay_ms(100);
		EEPROM_SendByte(4,EEPROMAdminLocation);
		EEPROMAdminLocation++;
	}*/
	while (EEPROMAdminLocation<4)
	{
		EEPROM_ReadByteNACK(&EEPROMRecevedData,EEPROMAdminLocation);
		_delay_ms(100);
		//UART_sendData(EEPROMRecevedData+48);
		if (EEPROMRecevedData!=255)
		{
			EEPROM_flage = TRUE;
		}
		else
		{
			EEPROM_flage = FALSE;
			break;
		}
		EEPROMAdminLocation++;
	}
	UART_RecevedData = UART_NOT_RECEIVE;
	UART_RecevedData = UART_receiveData()-48;
	if (UART_RecevedData!=UART_NOT_RECEIVE)
	{
		Entered_Pass[InputIndex] = UART_RecevedData;
		InputIndex++;
	}
	if (InputIndex==4)
	{
		if (EEPROM_flage==FALSE)
		{
			EEPROMAdminLocation = 0;
			while (EEPROMAdminLocation<4)
			{
				_delay_ms(100);
				EEPROM_SendByte(Entered_Pass[EEPROMAdminLocation],EEPROMAdminLocation);
				EEPROMAdminLocation++;
			}
			Save_flage = TRUE;
		}
		if (EEPROM_flage==TRUE){
			EEPROMAdminLocation = 0;
			while ( EEPROMAdminLocation<4)
			{
				_delay_ms(100);
				EEPROM_ReadByteNACK(&EEPROMRecevedData,EEPROMAdminLocation);
				if (Entered_Pass[EEPROMAdminLocation]==EEPROMRecevedData)
				{
					flage = TRUE;
				}
				else
				{
					flage = FALSE;
					break;
				}
				EEPROMAdminLocation++;
			}
		}

		if (Save_flage==FALSE)
		{
			if (flage==TRUE)
			{
				UART_sendStr("Welcome\r\n");
				InputIndex=0;
				_delay_ms(100);
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
		}
		InputIndex = 0;
	}
	return FALSE;
}

//Temperature
void TEMP_Init(){


	DIO_setPinDir(DIO_PINA1,DIO_INPUT);

	//DC Motor control

	//Enable
	DIO_setPinDir(DIO_PIND4,DIO_OUTPUT);

	//Direction
	DIO_setPinDir(DIO_PIND3,DIO_OUTPUT);
	DIO_setPinDir(DIO_PIND7,DIO_OUTPUT);

}

u16 VDigitalTemp;
f32 VAnalogTemp;

void TEMP_Check(){

	VDigitalTemp = ADC_read(ADC_CH1);
	VAnalogTemp = (ADC_convertAnalog(VDigitalTemp))*100;
	LCD_clearDis();
	LCD_sendStr("Temp = ");
	LCD_sendFloatNum(VAnalogTemp);
	LCD_sendData('C');
	TEMP_ControlAC();
}


void TEMP_ControlAC(){
	if(VAnalogTemp>28){

		//Enable
		DIO_setPinValue(DIO_PIND4,DIO_HIGH);

		//Direction
		DIO_setPinValue(DIO_PIND3,DIO_HIGH);
		DIO_setPinValue(DIO_PIND7,DIO_LOW);
	}
	else if(VAnalogTemp<28){

		//Enable
		DIO_setPinValue(DIO_PIND4,DIO_LOW);

		//Direction
		DIO_setPinValue(DIO_PIND3,DIO_LOW);
		DIO_setPinValue(DIO_PINC6,DIO_LOW);
	}
}
//Lighting
void LIGHTING_init (){
	DIO_setPinDir(DIO_PINC2,DIO_OUTPUT);
	DIO_setPinDir(DIO_PINC7,DIO_OUTPUT);

}

void LIGHTING_Start(u8 Start){
	switch(Start){
			case LIGHTINGROOM:
				 DIO_togglePinValue(DIO_PINC7);
				break;
			case LIGHTINHALL:
				 DIO_togglePinValue(DIO_PINC2);
				break;
			default:
				break ;
	}
}

//Input
u8 INPUT_Read(){
	static u8 Keypad_Press_KPD,UART_Press;
	Keypad_Press_KPD=KPD_read();
	UART_Press=UART_receiveData();
	if (Keypad_Press_KPD!=KPD_UNPRESSED)
	{
		while (KPD_read()!=KPD_UNPRESSED);
		return Keypad_Press_KPD;
	}
	if (UART_Press!=UART_NOT_RECEIVE)
	{
		while (UART_receiveData()!=UART_NOT_RECEIVE);
		return UART_Press;
	}
}

//Servo
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
		TimeOn = TIMER0_getCounts();

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

//Door
void DOORCONTROL_init(){

	//Servo Motor control PIN
	DIO_setPinDir(DIO_PIND5,DIO_OUTPUT);

	//Timer1
	TIMER1_initFastPwmMod14();

	TIMER1_setFrequency(50);
}

BOOL DOORCONTROL_Start(){
	//Open the door
	TIMER1_setOcr(499);

	//Start the Holding process
	HOLD_Start();

	//Wait for the Ultrasonic Sensor to return a distance greater than 30cm
	if(HOLD_Retrun()>30)
	{
		//Close the door
		TIMER1_setOcr(375);
		return TRUE;
	}
}

//User
u8 password[4], username[4], ch;

void AddUser()
{
	u8 EEPROMINDEX = MINEEPROMUSER;
	u8 EEPROMValue;
	BOOL EEPROMReturnFlag = FALSE;

	while(EEPROMINDEX<=MAXEEPROMUSER){

		_delay_ms(100);
		EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
		if(EEPROMValue!=255){
			EEPROMReturnFlag = FALSE;
		}
		else
		{
			EEPROMReturnFlag = TRUE;
			break;
		}
		EEPROMINDEX+=8;
	}
	if(EEPROMReturnFlag==TRUE){
		for(u8 userindex = 0;userindex<=4;userindex++){
			EEPROM_SendByte(username[userindex],EEPROMINDEX);
			EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
			UART_sendData(EEPROMValue);
			EEPROMINDEX++;
		}
		for(u8 passindex = 0;passindex<=4;passindex++){
			EEPROM_SendByte(password[passindex],EEPROMINDEX);
			EEPROM_ReadByteNACK(&EEPROMValue,EEPROMINDEX);
			UART_sendData(EEPROMValue);
			EEPROMINDEX++;
		}
	}
}

BOOL CheckDataForUser(){
	BOOL flage=FALSE,EEPROM_flage = FALSE,Save_flage = FALSE , flag=0 , Check_index = MINEEPROMUSER + 4;
	u8  KPD_RecevedData, Entered_User[4],Entered_Pass[4], Userindex = 0,Passindex=0, i2 = 0, EEPROMRecevedData,counter=0;

	while (i2<4)
	{
		_delay_ms(100);
		EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
		if (EEPROMRecevedData!=255)
		{
			EEPROM_flage = TRUE;
		}
		else
		{
			EEPROM_flage = FALSE;
		}
		i2++;
	}

	KPD_RecevedData = KPD_read();
	if ( KPD_RecevedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);

			LCD_sendNum(KPD_RecevedData-48);
			Entered_User[Userindex] = KPD_RecevedData;


			Userindex++;
	}
	else if ( KPD_RecevedData!=KPD_UNPRESSED)
	{
		while(KPD_read()!=KPD_UNPRESSED);
			LCD_sendNum(KPD_RecevedData-48);
			Entered_Pass[Passindex] = KPD_RecevedData;

			Passindex++;
	}


	if (Userindex==4&&flag==0)
	{
		if (EEPROM_flage==FALSE)
		{
			i2 = MINEEPROMUSER;
			while (i2<Check_index)
			{
				_delay_ms(100);
				EEPROM_SendByte(Entered_User[i2],i2);
				i2++;
			}
			Save_flage = TRUE;
		}
		if (EEPROM_flage==TRUE){
			i2 = MINEEPROMUSER;
			while ( i2<Check_index)
			{
				_delay_ms(100);
				EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
				if (Entered_User[i2]==EEPROMRecevedData)
				{
					flage = TRUE;
				}
				else
				{
					flage = FALSE;
					break;
				}
				i2++;
			}
		}

		if (Save_flage==FALSE)
		{
			if (flage==TRUE)
			{
				LCD_sendStr("Welcome");
				return TRUE;


			}
			else {
				LCD_sendStr("WRONGPASSWORD");
				counter ++ ;
				switch (counter){
				case 1 :
					DIO_setPinValue (DIO_PINA0,DIO_HIGH) ;
					break ;
				case 2 :
					DIO_setPinValue (DIO_PINA2,DIO_HIGH) ;
					break ;
				case 3 :
					DIO_setPinValue (DIO_PINA3,DIO_HIGH) ;
					LCD_clearDis();
					LCD_sendStr("BLOCK");
					_delay_ms(60000);
					break ;
				default:
					break;
				}
			}
		}
		Userindex = 0;
		flag = 1 ;
		Check_index +=4;
	}
else if (Passindex==4 && flag==1)
	{
		if (EEPROM_flage==FALSE)
		{
			i2 = MINEEPROMUSER;
			while (i2<4)
			{
				_delay_ms(100);
				EEPROM_SendByte(Entered_Pass[i2],i2);
				i2++;
			}
			Save_flage = TRUE;
		}
		if (EEPROM_flage==TRUE){
			i2 = MINEEPROMUSER;
			while ( i2<4)
			{
				_delay_ms(100);
				EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
				if (Entered_Pass[i2]==EEPROMRecevedData)
				{
					flage = TRUE;
				}
				else
				{
					flage = FALSE;
					break;
				}
				i2++;
			}
		}

		if (Save_flage==FALSE)
		{
			if (flage==TRUE)
			{
				LCD_sendStr("Welcome");
				return TRUE;
			}
			else {
				LCD_sendStr("WRONGPASSWORD");
				counter ++ ;
				switch (counter){
				case 1 :
					DIO_setPinValue (DIO_PINA0,DIO_HIGH) ;
					break ;
				case 2 :
					DIO_setPinValue (DIO_PINA2,DIO_HIGH) ;
					break ;
				case 3 :
					DIO_setPinValue (DIO_PINA3,DIO_HIGH) ;
					LCD_clearDis();
					LCD_sendStr("BLOCK");
					_delay_ms(60000);
					break ;
				default:
					break;
				}
			}
		}
		Passindex = 0;
		flag=0;
	}
	return FALSE;
}
BOOL DeleteUser(){
	// define flag to delete user
	 u8 deleteuserflag = FALSE , i2 = 0 , EEPROMRecevedData ;
		 while (i2<4)
		 	{
		 		_delay_ms(100);
		 		EEPROM_ReadByteNACK(&EEPROMRecevedData,i2);
		 		if (EEPROMRecevedData!=255)
		 		{
		 			deleteuserflag = TRUE;
		 		}
		 		else
		 		{
		 			deleteuserflag = FALSE;
		 		}
		 		i2++;
		 	}
}

//Main
void Code_APPInitDriversTask(void *pvParameters){
	while(1){
		GI_enable();
		KPD_init();
		LCD_init();
		UART_init();
		EEPROM_Init();
		vTaskSuspend(NULL);
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}
void UARTInputTask(void *pvParameters){
	u8 var = UART_NOT_RECEIVE;
	while(1){
		var = UART_receiveData();
		if(var!=UART_NOT_RECEIVE){
			xQueueSend(xQueue,&var,0);
		}
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}
void LoginTask(void * pvParameters ){
	while(1)
	{
		if(CheckPasswordAdmin()==TRUE){

			xEventGroupSetBits(LoginEventGroup, BIT_0 );
		}
		else if(CheckDataForUser() == TRUE){
			 xEventGroupClearBits( LoginEventGroup, BIT_0 );
		}
	}
}
void OptionsTask(void *pvParameters){
	u8 var2, read = 0;
	while(1){
		if (xQueueReceive( xQueue, &var2, 0) == pdPASS)
		{
			uxBits = xEventGroupWaitBits(LoginEventGroup, BIT_0, pdTRUE, pdFALSE, 0 );
			if(( uxBits & BIT_0 ) != 0){
				//Correct password Welcome
				UART_sendStr("1.Light 2.Temp 3.Enter\r\n");

				//UART read
				if(UART_receiveData()==INPUT_Light){
					//lighting
					UART_sendStr("1.Hall 2.Entrance\r\n");
					//Go to UART read part for Lighting Section
				}
				else if(UART_receiveData()==INPUT_Temp){
					//Temperature check
					TEMP_Check();
					UART_sendStr("\r\n1 to return:  ");
				}
			}
			else if(( uxBits & BIT_0 ) != 1){
				LCD_sendStr("1.Light 2.Temp 3.Enter");
				LCD_Goto(0,1);
				if(INPUT_Read()==INPUT_Light){
					LCD_sendData('1');
				}
				else if(INPUT_Read()==INPUT_Temp){
					LCD_sendData('2');
				}
				else if(INPUT_Read()==INPUT_ENTERANCE){
					LCD_sendData('3');
				}
				LCD_clearDis();
				LCD_Goto(0,0);
				LCD_sendStr("1.Hall 2.Entrance");
				LCD_Goto(0,1);
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_LIGHTINGROOM);
					LIGHTING_Start(LIGHTINGROOM);
				}
				else if(INPUT_Read()=='2'){
					LCD_sendData(INPUT_LIGHTINHALL);
					LIGHTING_Start(LIGHTINHALL);
				}
				LCD_Goto(0,0);
				TEMP_Check();
				LCD_Goto(0,1);
				LCD_sendStr("1 to return:  ");
				read = INPUT_Read();
				if(INPUT_Read()=='1'){
					LCD_sendData(INPUT_return);
				}
			}
		}
		vTaskDelay(500/portTICK_PERIOD_MS);
	}
}
void DoorControlTask (void * pvParameters ){
u8 DoorKey ;
	while(1)
	{
		if (xQueueReceive(xQueue,&DoorKey,0)== pdPASS)
		{
			if(DoorKey==1)
			{
				DOORCONTROL_Start();
			}
		}
		vTaskDelay(250/portTICK_PERIOD_MS);
	}
}
