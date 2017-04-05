// ..................................................  
// CDate class definitions
// Adapted from Hagit Schechter, Jan 2007 for 2014W2 
// ..................................................

#include <iostream>
#include <string>
#include "CDate.h"

CDate::CDate(void){
	// init y/m/d to 0
	m_year = m_month = m_day = 0;
}

CDate::CDate(int year, int month, int day){
	setDate( year, month, day );        
}

CDate::CDate(int year, std::string month, int day){
	setDate( year, monthStr2Num(month), day );
}

// validate the entire date by making sure year & month are correct
bool CDate::isValidDate(int year, int month, int day){
	return (isValidDay(year, month, day) && year > 0 && month > 0 && month < 13);
}

// validate the entire date by making sure year & month are correct
bool CDate::isValidDate(int year, std::string month, int day){
	int monthNum = monthStr2Num(month);
	return (isValidDay(year, monthNum, day) && year > 0 && monthNum > 0 && monthNum < 13);
}

/*
monthStr2Num
@param: string month
@ret: numerical representation of the month 
*/
int CDate::monthStr2Num(std::string month){
	int monthNum;
	
	if (month.compare("January") == 0) { monthNum = 1; }
	else if (month.compare("February") == 0) { monthNum = 2; }
	else if (month.compare("March") == 0) { monthNum = 3; }
	else if (month.compare("April") == 0) { monthNum = 4; }
	else if (month.compare("May") == 0) { monthNum = 5; }
	else if (month.compare("June") == 0) { monthNum = 6; }
	else if (month.compare("July") == 0) { monthNum = 7; }
	else if (month.compare("August") == 0) { monthNum = 8; }
	else if (month.compare("September") == 0) { monthNum = 9; }
	else if (month.compare("October") == 0) { monthNum = 10; }
	else if (month.compare("November") == 0) { monthNum = 11; }
	else if (month.compare("December") == 0) { monthNum = 12; }
	else { monthNum = -1; }
	
	return monthNum;
}

// validate the day to ensure it is correct for the month & leap year month
bool CDate::isValidDay(int year, int month, int day){
	if ((day < 1) || (day > 31)) return false;

	bool valid;
	switch (month) {
		case 1: valid = (day <= 31); break;
		case 3: valid = (day <= 31); break;
		case 5: valid = (day <= 31); break;
		case 7: valid = (day <= 31); break;
		case 8: valid = (day <= 31); break;
		case 10: valid = (day <= 31); break;
		case 12: valid = (day <= 31); break;
		case 2:
			// Don't worry about this code too much.
			// It handles all the leap year rules for February.
			if ((year % 4) != 0) {
				valid = (day <=28);
			} else if ((year % 400) == 0) {
				valid = (day <= 29);
			} else if ((year % 100) == 0) {
				valid = (day <= 28);
			} else {
				valid = (day <= 29);
			}
			break;
		case 4: valid = (day <= 30); break;
		case 6: valid = (day <= 30); break;
		case 9: valid = (day <= 30); break;
		case 11: valid = (day <= 30); break;
		default: valid = false; break;
	}
	return valid;
}

void CDate::setDate(int year, int month, int day){
	if(isValidDate(year, month, day)){    
		m_year = year;
		m_month = month;
		m_day = day;
	}
	else {
		m_year = m_month = m_day = 0;
	}
}

void CDate::setDate(int year, std::string month, int day){
	if (isValidDate(year, monthStr2Num(month), day)) {
		m_year = year;
		m_month = monthStr2Num(month);
		m_day = day;
	}
	else {
		m_year = m_month = m_day = 0;
	}
}

void CDate::print(void){
	std::cout << m_year << "/" << m_month << "/" << m_day << std::endl;
}

int CDate::getDate(void){
	return (m_year * 10000) + (m_month * 100) + m_day;
}
