//
//  main.cpp
//  2016_2_21
//
// Assignment: nextday
//


#include <iostream>
using namespace std;

// functions: get/show date
void GetDate(int &m, int &d, int &y);
void ShowDate(int m, int d, int y);
bool NextDate(int &m, int &d, int &y);

// function: user input validation
bool DateIsValid(int &m, int &d, int &y);
// function: leap year validation
bool IsLeapYear(int y);
// function: calculate number of days in Month
int DaysInMonth (int m, int y);
/*
 *
 */
int main() {
    // initialize variable: month, day, year
    int m, d, y;
    char ans;
    
    do
    {
        GetDate(m, d, y);
        if (!DateIsValid(m, d, y)) {
            cout << "INVALID INPUT!" << endl;
            ans = 'y';
            continue;
        }
        
        cout << "The day after ";
        ShowDate(m, d, y);
        bool errorCode = NextDate(m, d, y);
        if (!errorCode) {
            cout << " is ";
            ShowDate(m, d, y);
        }
        else {
            cout << endl << "ERROR: date is invalid." << endl;
        }
        
        cout << endl << "Test again? (Type y for yes or n for no): ";
        cin >> ans;
        cout << endl;
    } while(ans == 'y' || ans == 'Y');
    
    return 0;
}

// GetDate function: user enter date in m/d/y format
void GetDate(int &m, int &d, int &y) {
    char slash;
    cout << "Enter the calendar date in m/d/y format: ";
    cin >> m >> slash >> d >> slash >> y;
}

// ShowDate function: display date
void ShowDate(int m, int d, int y) {
    cout << m << "/" << d << "/" << y;
}

// NextDate function
// 유저가 입력한 month 을 기반으로 그달의 날짜를 확인합니다
// 유저가 입력한 day 가 그달의 총 날짜수와 같으면 month + 1 하고 day 을 1 로 지정합니다.
// month 가 12 보다 크면 year + 1 하고 month 을 1 로 합니다.
bool NextDate(int &m, int &d, int &y) {
    if (!DateIsValid(m, d, y)) {
        return true;
    }
    else {
        int days_in_month = DaysInMonth(m, y);
        if (d == days_in_month) {
            m++;
            d = 1;
        }
        else {
            d++;
        }
        
        if (m > 12) {
            y++;
            m = 1;
        }
        return false;
    }
}

// DateIsValid function: validate entered month and date
// 유저가 잘못된 date 을 입력할경우 return false
bool DateIsValid(int &m, int &d, int &y) {
    if (d > 0 && d <= DaysInMonth (m, y))
        return true;
    else if (d == 0 || m == 0)
        return false;
    else
        return false;
}

// DaysInMonth function: calculate number of days base on Month user entered
// month: 1, 3, 5, 7, 8, 10, 12 월일경우 날짜수가 31일
// month: 4, 6, 9, 11 월일경우 날짜수가 30일
// month: 2 월일경우 윤달이 있는지 확인 후 윤달이 있을경우 29일 아닐경우 28일
int DaysInMonth (int m, int y) {
    switch (m) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return 31;
            break;
        case 4: case 6: case 9: case 11:
            return 30;
            break;
        case 2:
            if (IsLeapYear(y))
                return 29;
            else
                return 28;
            break;
        default:
            return 0;
            break;
    }
}

// IsLeapYear function: validate leap year
// user entered year 로 윤달 확인 윤달이 있을경우 return true, 아닐결우 return false
// leap year 계산은 text book 에 나와있는 algorithm 사용하였음
bool IsLeapYear(int y) {
    if (y % 4 == 0) {
        if (y % 100 == 0) {
            if (y % 400 == 0)
                return true;
            else
                return false;
        }
        else
            return true;
    }
    else
        return false;
}
