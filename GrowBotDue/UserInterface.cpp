// 
// 
// 

#include "UserInterface.h"

void UserInterfaceElement::draw() {
	//Overwrite
}

UserInterfaceElement::UserInterfaceElement() {
	//Overwrite
}
UserInterfaceElement::~UserInterfaceElement() {

}
void UserInterfaceElement::executeAction() {

}

bool UserInterfaceElement::checkHit(int x, int y) {
	//Current Navpoints, need to be stored temporaley while objects are destroyed
	int navmenue, navframe;

	if (x >= this->x1 && x <= this->x2 && y >= this->y1 && y <= this->y2 && this->active == true) {
		return true;
	}
	else return false;
}


MenueItem::MenueItem(String value, word frame_color, word fill_color, word text_color, uint8_t row, TouchInterface *touchmenue, bool active, int navmenue, int navframe) {
	//Look and Feel
	this->value = value;
	this->row = row;
	this->frame_color = frame_color;
	this->fill_color = fill_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;

	this->x1 = 0;
	this->y1 = Y_DIVIDER + row * MENUE_HEIGHT;
	this->x2 = X_DIVIDER;
	this->y2 = y1 + MENUE_HEIGHT;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	this->draw();

}
void MenueItem::draw() {
	myGLCD.setColor(this->fill_color);
	myGLCD.fillRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setColor(this->frame_color);
	myGLCD.drawRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.setFont(SmallFont);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

TextLabel::TextLabel(String value, uint8_t row, uint8_t column, uint8_t column_spread, word fill_color, word text_color, TouchInterface *touchmenue, bool active, int navmenue, int navframe) {
	//Look and feel
	this->value = value;
	this->row = row;
	this->column = column;
	this->row_spread = column_spread;
	this->column_spread = column_spread;
	this->fill_color = fill_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;
	this->x1 = X_DIVIDER + column * COLUMN_WIDTH + PADDING;
	this->y1 = Y_DIVIDER + row * ROW_HEIGHT + PADDING;
	this->x2 = x1 + column_spread * COLUMN_WIDTH - PADDING;
	this->y2 = y1 + ROW_HEIGHT - PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	this->draw();

}
void TextLabel::draw() {
	myGLCD.setFont(SmallFont);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

TextBox::TextBox(String value, uint8_t row, uint8_t column, uint8_t column_spread, word frame_color, word text_color, TouchInterface *touchmenue, bool active, int navmenue, int navframe) {
	//Look and Feel
	this->value = value;
	this->row = row;
	this->column = column;
	this->column_spread = column_spread;
	this->frame_color = frame_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;
	this->x1 = X_DIVIDER + column * COLUMN_WIDTH + PADDING;
	this->y1 = Y_DIVIDER + row * ROW_HEIGHT + PADDING;
	this->x2 = x1 + column_spread * COLUMN_WIDTH - PADDING;
	this->y2 = y1 + ROW_HEIGHT - PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	this->draw();

}
void TextBox::draw() {
	myGLCD.setFont(SmallFont);
	myGLCD.setColor(this->frame_color);
	myGLCD.drawRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(BACKGROUNDCOLOR);
	myGLCD.setColor(this->text_color);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

template <class T>
ControlButton<T>::ControlButton(String value, uint8_t row, uint8_t column, uint8_t row_spread, uint8_t column_spread, word fill_color, word text_color, TouchInterface *touchmenue, T *actionObj, void (T::*actionFunc)(), bool active, int navmenue, int navframe) {
	//Look and Feel
	this->value = value;
	this->row = row;
	this->column = column;
	this->row_spread = row_spread;
	this->column_spread = column_spread;
	this->fill_color = fill_color;
	this->text_color = text_color;

	//Dimensions
	this->active = active;
	this->x1 = X_DIVIDER + column * COLUMN_WIDTH + PADDING;
	this->y1 = Y_DIVIDER + row * ROW_HEIGHT + PADDING;
	this->x2 = x1 + column_spread * COLUMN_WIDTH - PADDING;
	this->y2 = y1 + row_spread * ROW_HEIGHT - PADDING;

	//Container
	this->touchmenue = touchmenue;
	this->navmenue = navmenue;
	this->navframe = navframe;

	draw();

	//Action Handler
	this->actionObject = actionObj;
	this->callback = actionFunc;
	this->active = active;
}

template <class T>
void ControlButton<T>::draw() {
	myGLCD.setColor(this->fill_color);
	myGLCD.fillRoundRect(this->x1, this->y1, this->x2, this->y2);
	myGLCD.setBackColor(this->fill_color);
	myGLCD.setColor(this->text_color);
	myGLCD.setFont(SmallFont);
	myGLCD.print(this->value, this->x1 + 3, this->y1 + 3);
}

template <class T>
void ControlButton<T>::executeAction() {
	if (this->active == true && this->actionObject != NULL) {
		(actionObject->*callback)();
	}
	else Serial.println("FAIL: Button has no action");
}

TouchInterface::TouchInterface() {

}

void TouchInterface::drawBackground() {
	myGLCD.clrScr();
	myGLCD.setBackColor(BACKGROUNDCOLOR);
	myGLCD.setColor(VGA_WHITE);
	myGLCD.drawLine(X_DIVIDER, Y_DIVIDER, X_DIVIDER, 239);
	myGLCD.drawLine(X_DIVIDER, Y_DIVIDER, 319, Y_DIVIDER);

	myGLCD.setFont(SmallFont);


	myGLCD.print(currenttime.createDate(), 2, 4);
	myGLCD.print(currenttime.createTime(), 90, 4);
	myGLCD.print(sensors[0]->getValue(), 215, 4);
	myGLCD.print(sensors[1]->getValue(), 270, 4);

	
}

void TouchInterface::drawMenue(int nav) {
	current_menue = nav;

	switch (nav) {

		//Menu Page 1
	case 1:
		menueElements[0] = new MenueItem("Info", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 11, 110);
		menueElements[1] = new MenueItem("Manual", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 12, 120);
		menueElements[2] = new MenueItem("Settings", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 13, 130);
		menueElements[3] = new MenueItem("<Page 2>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[4] = NULL;
		break;

		//Sub Menue Page 1:Info
	case 11:
		menueElements[0] = new MenueItem("Internal", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 11, 110);
		menueElements[1] = new MenueItem("Front", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 11, 111);
		menueElements[2] = new MenueItem("Relais", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 11, 112);
		menueElements[3] = new MenueItem("Top", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 11, 113);
		menueElements[4] = new MenueItem("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 1, 1);
		menueElements[5] = NULL;
		break;

		//Sub Menue Page 2: Manual
	case 12:
		menueElements[0] = new MenueItem("Relais", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 12, 120);
		menueElements[1] = new MenueItem("Water", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 12, 121);
		menueElements[2] = new MenueItem("Height", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 12, 122);
		menueElements[3] = new MenueItem("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 1, 1);
		menueElements[4] = NULL;
		break;

		//Sub Menue Page 3: Settings
	case 13:
		menueElements[0] = new MenueItem("RTC", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 13, 130);
		menueElements[1] = new MenueItem("Func 2", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 13, 131);
		menueElements[2] = new MenueItem("Func 3", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 13, 132);
		menueElements[3] = new MenueItem("Func 4", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 13, 133);
		menueElements[4] = new MenueItem("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 1, 1);
		menueElements[5] = NULL;
		break;

		//Page 2
	case 2:
		menueElements[0] = new MenueItem("<Page 1>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 0, this, true, 1, 1);
		menueElements[1] = new MenueItem("Intern", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 21, 210);
		menueElements[2] = new MenueItem("Analog", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 22, 220);
		menueElements[3] = new MenueItem("Digital", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 23, 230);
		menueElements[4] = new MenueItem("<Page 3>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 3, 1);
		menueElements[5] = NULL;
		break;

		//Time Trigger
	case 21:
		menueElements[0] = new MenueItem("Time", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 21, 210);
		menueElements[1] = new MenueItem("Temp.", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 21, 211);
		menueElements[2] = new MenueItem("Humid.", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 21, 212);
		menueElements[3] = new MenueItem("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[4] = NULL;
		break;


		//Analog Trigger
	case 22:
		menueElements[0] = new MenueItem("Analog 1", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 22, 220);
		menueElements[1] = new MenueItem("Analog 2", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 22, 221);
		menueElements[2] = new MenueItem("Analog 3", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 22, 222);
		menueElements[3] = new MenueItem("Analog 4", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 22, 223);
		menueElements[4] = new MenueItem("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[5] = NULL;
		break;
	case 23:
		menueElements[0] = new MenueItem("Digi. 1", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 23, 230);
		menueElements[1] = new MenueItem("Digi. 2", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 23, 231);
		menueElements[2] = new MenueItem("Digi. 3", VGA_WHITE, VGA_BLACK, VGA_WHITE, 2, this, true, 23, 232);
		menueElements[3] = new MenueItem("Digi. 4", VGA_WHITE, VGA_BLACK, VGA_WHITE, 3, this, true, 23, 233);
		menueElements[4] = new MenueItem("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 2, 1);
		menueElements[5] = NULL;
		break;

		//Page 3
	case 3:
		menueElements[0] = new MenueItem("<Page 2>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 0, this, true, 2, 1);
		menueElements[1] = new MenueItem("Rules Set", VGA_WHITE, VGA_BLACK, VGA_WHITE, 1, this, true, 31, 310);
		menueElements[2] = NULL;
		break;
		//Digital Sensors
		//Rules Set
	case 31:
		menueElements[0] = new MenueItem("Rules Set", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 31, 310);
		menueElements[1] = new MenueItem("<back>", VGA_WHITE, VGA_TEAL, VGA_WHITE, 4, this, true, 3, 1);
		menueElements[2] = NULL;
		break;

	case 999:
		menueElements[0] = new MenueItem("<Back>", VGA_WHITE, VGA_BLACK, VGA_WHITE, 0, this, true, 1, 1);
		menueElements[1] = NULL;
		break;
	}
}
void TouchInterface::drawFrame(int nav) {
	current_frame = nav;


	switch (nav) {
		// Home
	case 1:
		frameElements[0] = new TextLabel("Welcome to GrowRobot V0.5", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("(c) Oliver Gass - 2016", 1, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextLabel(debug, 3, 0, 5, BACKGROUNDCOLOR, VGA_RED, this);
		frameElements[3] = NULL;
		break;
		// Internal Sensors
	case 110:
		frameElements[0] = new TextLabel("Interal Sensor Values:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("Temperature:", 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(sensors[0]->getValue()), 2, 5, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("Humidity:", 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(sensors[1]->getValue()), 3, 5, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = NULL;
		break;
		// Analog / Front
	case 111:
		frameElements[0] = new TextLabel("Analog Front Sensors:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("A1:", 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(sensors[2]->readValue()), 2, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("A2:", 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(sensors[3]->getValue()), 3, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TextLabel("A3:", 4, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(sensors[4]->getValue()), 4, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextLabel("A4:", 5, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[8] = new TextBox(String(sensors[5]->getValue()), 5, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = NULL;
		break;
		//Relais Status
	case 112: //
		bool r1, r2, r3, r4;

		r1 = (digitalRead(RELAY1) == 1) ? false : true;
		r2 = (digitalRead(RELAY2) == 1) ? false : true;
		r3 = (digitalRead(RELAY3) == 1) ? false : true;
		r4 = (digitalRead(RELAY4) == 1) ? false : true;

		frameElements[0] = new TextLabel("Relais Status:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("R1:", 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(r1), 2, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("R2:", 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(r2), 3, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TextLabel("R3:", 4, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(r3), 4, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextLabel("R4:", 5, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[8] = new TextBox(String(r4), 5, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = NULL;
		break;
		//Digital Status
	case 113:
		frameElements[0] = new TextLabel("Digital Top Sensors:", 0, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("T1:", 2, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new TextBox(String(sensors[6]->getValue()), 2, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new TextLabel("T2:", 3, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[4] = new TextBox(String(sensors[7]->getValue()), 3, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new TextLabel("T3:", 4, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(sensors[8]->getValue()), 4, 4, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextLabel("T4:", 5, 0, 0, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[8] = new TextBox(String(sensors[9]->getValue()), 5, 4, 3, VGA_WHITE, VGA_WHITE, this, true);
		frameElements[9] = NULL;
		break;

		//Switch Relais
	case 120:
		frameElements[0] = new TextLabel("Relais", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new ControlButton<RelaisBoard>("R1", 2, 1, 2, 2, VGA_BLUE, VGA_BLACK, this, &relaisboard, &RelaisBoard::switchR1, true, 12, 120);
		frameElements[2] = new TextBox(String(relaisboard.getStatusR1()), 4, 1, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[3] = new ControlButton<RelaisBoard>("R2", 2, 5, 2, 2, VGA_BLUE, VGA_BLACK, this, &relaisboard, &RelaisBoard::switchR2, true, 12, 120);
		frameElements[4] = new TextBox(String(relaisboard.getStatusR2()), 4, 5, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<RelaisBoard>("R3", 7, 1, 2, 2, VGA_BLUE, VGA_BLACK, this, &relaisboard, &RelaisBoard::switchR3, true, 12, 120);
		frameElements[6] = new TextBox(String(relaisboard.getStatusR3()), 9, 1, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new ControlButton<RelaisBoard>("R4", 7, 5, 2, 2, VGA_BLUE, VGA_BLACK, this, &relaisboard, &RelaisBoard::switchR4, true, 12, 120);
		frameElements[8] = new TextBox(String(relaisboard.getStatusR4()), 9, 5, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = NULL;
		break;
		//Switch Water Pump 
	case 121:
		frameElements[0] = new TextLabel("Water", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;
		//Change Height
	case 122:
		frameElements[0] = new TextLabel("Height", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;
		//Set RTC
	case 130:
		frameElements[0] = new TextLabel("Settings", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = new TextLabel("Date", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[2] = new ControlButton<CurrentTime>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incDay, true, 13, 130);
		frameElements[3] = new ControlButton<CurrentTime>("+", 1, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incMonth, true, 13, 130);
		frameElements[4] = new ControlButton<CurrentTime>("+", 1, 6, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incYear, true, 13, 130);
		frameElements[5] = new TextBox(String(currenttime.getDay()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[6] = new TextBox(String(currenttime.getMonth()), 2, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextBox(String(currenttime.getYear()), 2, 6, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[8] = new ControlButton<CurrentTime>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decDay, true, 13, 130);
		frameElements[9] = new ControlButton<CurrentTime>("-", 3, 4, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decMonth, true, 13, 130);
		frameElements[10] = new ControlButton<CurrentTime>("-", 3, 6, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decYear, true, 13, 130);
		frameElements[11] = new TextLabel("Time", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[12] = new ControlButton<CurrentTime>("+", 5, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incHour, true, 13, 130);
		frameElements[13] = new ControlButton<CurrentTime>("+", 5, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, &currenttime, &CurrentTime::incMinute, true, 13, 130);
		frameElements[14] = new TextBox(String(currenttime.getHours()), 6, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[15] = new TextBox(String(currenttime.getMinutes()), 6, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[16] = new ControlButton<CurrentTime>("-", 7, 2, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decHour, true, 13, 130);
		frameElements[17] = new ControlButton<CurrentTime>("-", 7, 4, 1, 2, VGA_RED, VGA_BLACK, this, &currenttime, &CurrentTime::decMinute, true, 13, 130);
		frameElements[18] = new ControlButton<CurrentTime>("Default", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, &currenttime, &CurrentTime::updateRTCdefault, true, 13, 130);
		frameElements[19] = NULL;
		break;
	case 131:
		frameElements[0] = new TextLabel("Settings Func 1", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;
	case 132:
		frameElements[0] = new TextLabel("Settings Func 2", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;
	case 133:
		frameElements[0] = new TextLabel("Settings Func 3", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;


		//Time
	case 210:
		actionhandler->setTriggerCatPointer(0);
		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String(actionhandler->getCurrentTitle()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("From", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 1, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentStartDay, true, 21, 210);
		frameElements[4] = new ControlButton<ActionHandler>("+", 1, 3, 1, 1, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentStartMonth, true, 21, 210);
		frameElements[5] = new ControlButton<ActionHandler>("+", 1, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentStartYear, true, 21, 210);
		frameElements[6] = new TextBox(String((actionhandler->getCurrentStartDay)()), 2, 2, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[7] = new TextBox(String((actionhandler->getCurrentStartMonth)()), 2, 3, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentStartYear)()), 2, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 2, 1, 1, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentStartDay, true, 21, 210);
		frameElements[10] = new ControlButton<ActionHandler>("-", 3, 3, 1, 1, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentStartMonth, true, 21, 210);
		frameElements[11] = new ControlButton<ActionHandler>("-", 3, 4, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentStartYear, true, 21, 210);

		frameElements[12] = new TextLabel("to", 2, 6, 1, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("+", 1, 7, 1, 1, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentEndDay, true, 21, 210);
		frameElements[14] = new ControlButton<ActionHandler>("+", 1, 8, 1, 1, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentEndMonth, true, 21, 210);
		frameElements[15] = new ControlButton<ActionHandler>("+", 1, 9, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentEndYear, true, 21, 210);
		frameElements[16] = new TextBox(String((actionhandler->getCurrentEndDay)()), 2, 7, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[17] = new TextBox(String((actionhandler->getCurrentEndMonth)()), 2, 8, 1, VGA_WHITE, VGA_WHITE, this);
		frameElements[18] = new TextBox(String((actionhandler->getCurrentEndYear)()), 2, 9, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[19] = new ControlButton<ActionHandler>("-", 3, 7, 1, 1, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentEndDay, true, 21, 210);
		frameElements[20] = new ControlButton<ActionHandler>("-", 3, 8, 1, 1, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentEndMonth, true, 21, 210);
		frameElements[21] = new ControlButton<ActionHandler>("-", 3, 9, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentEndYear, true, 21, 210);

		frameElements[22] = new TextLabel("Time", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[23] = new ControlButton<ActionHandler>("+", 5, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentStartHour, true, 21, 210);
		frameElements[24] = new ControlButton<ActionHandler>("+", 5, 4, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentStartMinute, true, 21, 210);
		frameElements[25] = new TextBox(String((actionhandler->getCurrentStartHour)()), 6, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[26] = new TextBox(String((actionhandler->getCurrentStartMinute)()), 6, 4, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[27] = new ControlButton<ActionHandler>("-", 7, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentStartHour, true, 21, 210);
		frameElements[28] = new ControlButton<ActionHandler>("-", 7, 4, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentStartMinute, true, 21, 210);

		frameElements[29] = new TextLabel("Int.", 6, 6, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[30] = new ControlButton<ActionHandler>("+", 5, 8, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 21, 210);
		frameElements[31] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 8, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[32] = new ControlButton<ActionHandler>("-", 7, 8, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 21, 210);

		frameElements[33] = new TextLabel("Stat.", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[34] = new ControlButton<ActionHandler>((actionhandler->getCurrentActive)(), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 21, 210);

		frameElements[35] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 21, 210);
		frameElements[36] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 21, 210);

		frameElements[37] = NULL;
		break;


		//Temp. Trigger
	case 211:
		actionhandler->setTriggerCatPointer(1);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 21, 211);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 21, 211);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 21, 211);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 21, 211);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 21, 211);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 21, 211);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 21, 211);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 21, 211);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 21, 211);

		frameElements[18] = NULL;
		break;

		//Hum. Trigger
	case 212:
		actionhandler->setTriggerCatPointer(2);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 21, 212);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 21, 212);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 21, 212);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 21, 212);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 21, 212);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 21, 212);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 21, 212);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 21, 212);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 21, 212);

		frameElements[18] = NULL;
		break;


		//Analog Trigger 1
	case 220:
		actionhandler->setTriggerCatPointer(3);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 22, 220);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 22, 220);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 22, 220);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 22, 220);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 22, 220);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 22, 220);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 22, 220);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 22, 220);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 22, 220);

		frameElements[18] = NULL;
		break;

		//Analog Trigger 2
	case 221:
		actionhandler->setTriggerCatPointer(4);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 22, 221);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 22, 221);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 22, 221);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 22, 221);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 22, 221);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 22, 221);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 22, 221);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 22, 221);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 22, 221);

		frameElements[18] = NULL;
		break;

		//Analog Trigger 3
	case 222:
		actionhandler->setTriggerCatPointer(5);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 22, 222);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 22, 222);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 22, 222);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 22, 222);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 22, 222);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 22, 222);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 22, 222);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 22, 222);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 22, 222);

		frameElements[18] = NULL;
		break;

		//Analog Trigger 4
	case 223:
		actionhandler->setTriggerCatPointer(6);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 22, 223);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 22, 223);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 22, 223);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 22, 223);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 22, 223);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 22, 223);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 22, 223);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 22, 223);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 22, 223);

		frameElements[18] = NULL;
		break;

		//Digital Trigger 1
	case 230:
		actionhandler->setTriggerCatPointer(7);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 23, 230);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 23, 230);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 23, 230);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 23, 230);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 23, 230);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 23, 230);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 23, 230);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 23, 230);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 23, 230);

		frameElements[18] = NULL;
		break;
		//Digital Trigger 2
	case 231:
		actionhandler->setTriggerCatPointer(8);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 23, 231);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 23, 231);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 23, 231);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 23, 231);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 23, 231);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 23, 231);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 23, 231);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 23, 231);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 23, 231);

		frameElements[18] = NULL;
		break;
		//Digital Trigger 3
	case 232:
		actionhandler->setTriggerCatPointer(9);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 23, 232);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 23, 232);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 23, 232);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 23, 232);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 23, 232);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 23, 232);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 23, 232);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 23, 232);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 23, 232);

		frameElements[18] = NULL;
		break;
		//Digital Trigger 4
	case 233:
		actionhandler->setTriggerCatPointer(10);

		frameElements[0] = new TextLabel("ID", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[1] = new TextLabel(String((actionhandler->getCurrentTitle)()), 0, 2, 6, BACKGROUNDCOLOR, VGA_WHITE, this);

		frameElements[2] = new TextLabel("Temp.", 2, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[3] = new ControlButton<ActionHandler>("+", 1, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentBoolOp, true, 23, 233);
		frameElements[4] = new TextBox(String((actionhandler->getCurrentBoolOp)()), 2, 2, 2, VGA_WHITE, VGA_WHITE, this);
		frameElements[5] = new ControlButton<ActionHandler>("-", 3, 2, 1, 2, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentBoolOp, true, 23, 233);

		frameElements[6] = new TextLabel("Celcius", 2, 4, 3, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[7] = new ControlButton<ActionHandler>("+", 1, 7, 1, 3, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentThresh, true, 23, 233);
		frameElements[8] = new TextBox(String((actionhandler->getCurrentThresh)()), 2, 7, 3, VGA_WHITE, VGA_WHITE, this);
		frameElements[9] = new ControlButton<ActionHandler>("-", 3, 7, 1, 3, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentThresh, true, 23, 233);

		frameElements[10] = new TextLabel("Int.", 6, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[11] = new ControlButton<ActionHandler>("+", 5, 2, 1, 5, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::incCurrentInterval, true, 23, 233);
		frameElements[12] = new TextBox(String((actionhandler->getCurrentInterval)()), 6, 2, 5, VGA_WHITE, VGA_WHITE, this);
		frameElements[13] = new ControlButton<ActionHandler>("-", 7, 2, 1, 5, VGA_RED, VGA_BLACK, this, actionhandler, &ActionHandler::decCurrentInterval, true, 23, 233);


		frameElements[14] = new TextLabel("Stat", 9, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[15] = new ControlButton<ActionHandler>(String((actionhandler->getCurrentActive)()), 9, 2, 1, 2, VGA_GREEN, VGA_BLACK, this, actionhandler, &ActionHandler::changeCurrentActive, true, 23, 233);

		frameElements[16] = new ControlButton<ActionHandler>("<<Prev", 9, 5, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::decTriggerPointer, true, 23, 233);
		frameElements[17] = new ControlButton<ActionHandler>("Next>>", 9, 8, 1, 3, VGA_YELLOW, VGA_BLACK, this, actionhandler, &ActionHandler::incTriggerPointer, true, 23, 233);

		frameElements[18] = NULL;
		break;
		//Rules Set
	case 310:
		frameElements[0] = new TextLabel("Define Rules Set", 0, 0, 2, BACKGROUNDCOLOR, VGA_WHITE, this);
		frameElements[1] = NULL;
		break;

	case 999:
		frameElements[0] = new TextLabel("No Navigation Point defined for this UI Element", 0, 0, 0, VGA_RED, VGA_BLACK, this);
		frameElements[1] = NULL;
		break;
	}
}
void TouchInterface::checkEvent(int x, int y) {
	int i = 0, targetmenue = 1, targetframe = 1, hit = false;

	//Check if Menue Element was hit
	while (menueElements[i] != NULL && hit == false) {
		if (menueElements[i]->checkHit(x, y) == true) {
			targetmenue = menueElements[i]->navmenue;
			targetframe = menueElements[i]->navframe;
			hit = true;
			break;
		}
		else i++;
	}
	i = 0;
	//Check if Frame Element was hit
	while (frameElements[i] != NULL && hit == false) {
		if (frameElements[i]->checkHit(x, y) == true) {

			frameElements[i]->executeAction();
			targetmenue = frameElements[i]->navmenue;
			targetframe = frameElements[i]->navframe;
			hit = true;
			break;
		}
		else {
			i++;
		}
	}

	if (hit == true) {
		//Destory old UI Elements
		cleanup();

		//Update BackgroundFacebook
		drawBackground();

		//Draw new Menue 
		drawMenue(targetmenue);
		drawFrame(targetframe);
	}
}

void TouchInterface::cleanup() {
	//Iterator
	int i;

	i = 0;
	//Delete Old Menue Buttons
	while (menueElements[i] != NULL) {
		delete menueElements[i];
		i++;
	}
	//Delete Frame User Interface
	i = 0;
	while (frameElements[i] != NULL) {
		delete frameElements[i];
		i++;
	}

}
