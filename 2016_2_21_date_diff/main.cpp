//
//  main.cpp
//  2016_2_21
//
// Assignment: date difference
//

#include <iostream>
using namespace std;

// functions: get/show date
void GetDate(int &m, int &d, int &y);
void ShowDate(int m, int d, int y);

// function: date calculation
int DateDiff(int &m1, int &d1, int &y1, int &m2, int &d2, int &y2);
int DayNo(int m, int d, int y);
void DayNoToDate(int dayNumber, int m, int d, int y);
int DaysInYear(int y);

// function: user input validation
bool DateIsValid(int m, int d, int y);
// function: leap year validation
bool IsLeapYear(int y);
// function: calculate number of days in Month
int DaysInMonth (int m, int y);
/*
 *
 */
int main() {
    // initialize variable: month, day, year, number of days to add
    int m1, d1, y1, m2, d2, y2;
    char ans;
    
    do
    {
        cout << "Enter the start date in m/d/y format: ";
        GetDate(m1, d1, y1);
        cout << "Enter the end date in m/d/y format: ";
        GetDate(m2, d2, y2);
        
        int n_date_diff = DateDiff(m1, d1, y1, m2, d2, y2);
        cout << "Difference between the dates in days: " << n_date_diff << endl;
        cout << "Convert a day number: " << n_date_diff << " to a start date: ";
        DayNoToDate(n_date_diff, m1, d1, y1);
        
        cout << endl << "Test again? (Type y for yes or n for no): ";
        cin >> ans;
        cout << endl;
    } while(ans == 'y' || ans == 'Y');
    
    return 0;
}

// GetDate function: user enter date in m/d/y format
void GetDate(int &m, int &d, int &y) {
    char slash;
    cin >> m >> slash >> d >> slash >> y;
}

// ShowDate function: display date
void ShowDate(int m, int d, int y) {
    cout << m << "/" << d << "/" << y;
}

// DateDiff function
// return total number of days between start and end date
// 참조: 총날짜수를 계산함에 있으서 instructor 가 DayNo function parameters 을 지정하였기예 날짜계산이 많이 복잡합니다.
// 예를들어 2016 이면 0 부터 시작인데 0 AD (BC 까지는 계산하지 않음 년도를 minus 표시하지 않기때문임) 는 윤달이 있는년도이기에
// start/end date 을 기본으로 계산할경우 1 day 을 더해주어야 합니다. 다만 start/end year 둘다 윤달이 있는경우에는 DaysInYear function
// 윤달에 따른 날짜를 계산하기때문에 1 day 을 더할필요는 없습니다.
int DateDiff(int &m1, int &d1, int &y1, int &m2, int &d2, int &y2) {
    int n_first_date = DayNo(m1, d1, y1);
    int n_second_date = DayNo(m2, d2, y2);
    int n_days_diff = n_second_date - n_first_date;
    
    // start/end year 가 틀릴경우 end year 가 start year 보다 클경우 y1, y2 모두다 윤달이 아니면 1 day 를 더해줌
    // y1, y2 가 모두 윤달이 있는 년도에는 DaysInYear function 에서 모두다 계산이 되지만 y1, y2 둘중 하나만 윤달이 있는경우에 해당됨
    if (y2 > y1) {
        if (!IsLeapYear(y1) || !IsLeapYear(y2)) {
            n_days_diff += 1;
        }
    }
    // start/end year 가 틀릴경우 end year 가 start year 보다 작을경우 y1, y2 모두다 윤달이 아니면 1 day 를 빼줌
    // y1, y2 가 모두 윤달이 있는 년도에는 DaysInYear function 에서 모두다 계산이 되지만 y1, y2 둘중 하나만 윤달이 있는경우에 해당됨
    else if (y2 < y1) {
        if (!IsLeapYear(y1) || !IsLeapYear(y2)) {
            n_days_diff -= 1;
        }
    }
    
    return n_days_diff;
}

// DayNo function
// calculate total number of days
// parameter date 에 마춰 1월1일 부터 input date 까지 총 몇일인지 계산함
int DayNo(int m, int d, int y) {
    int m_start = 1;
    int days_month = 0;
    // parameter year 에따라 총날짜수를 계산함
    int days_yr = DaysInYear(y);
    
    // 1월1일부터 parameter month, day 까지의 날짜수를 총계산함
    while (m_start < m) {
        days_month += DaysInMonth(m_start, y);
        m_start ++;
    }
    
    return days_yr + days_month + d;
}

// days in year function
// calculate total number of days in year
// 윤달이 있는 년도를 확인 후 윤달이 있는 년도는 366일 없는 년도는 365 로 계산함
// 시작년도는 0 에서 시작하므로 차후 추가적으로 1 day 을 add/substract 해야함
// 예: 16년도는 윤달이 있는년도가 4미여 없는 년도는 11 이므로
// 4 * 366 + 11 * 355
int DaysInYear(int y) {
    int leap_count = y / 4;
    int no_leap_count = (y-1) - leap_count;
    
    return (leap_count * 366) + no_leap_count * 365;
}

// DayNoToDate function
// number of days to add/substract from parameter month, day, year
void DayNoToDate(int dayNumber, int m, int d, int y) {
    if (!DateIsValid(m, d, y)) {
        return;
    }
    else {
        int new_day = d + dayNumber;
        bool flag;
        
        do
        {
            // start date 이 end date 보다 클경우
            if(new_day > DaysInMonth(m, y)) {
                new_day -= DaysInMonth(m, y);
                m++;
                flag = true;
            }
            // start date 이 end date 보다 작을경우
            else if (new_day < 0) {
                new_day += DaysInMonth(m-1, y);
                m--;
                if (new_day < 0) {
                    flag = true;
                }
                else {
                    flag = false;
                }
            }
            else {
                flag = false;
            }
            
            // start date 이 end date 보다 클경우
            if (m > 12) {
                y++;
                m = 1;
            }
            // start date 이 end date 보다 작을경우
            else if (m == 0) {
                y--;
                m = 13;
            }
            
        } while(flag);
        d = new_day;
        
        cout << m << "/" << d << "/" << y;
    }
}


// DateIsValid function: validate entered month and date
// 유저가 잘못된 date 을 입력할경우 return false
bool DateIsValid(int m, int d, int y) {
    if (d > 0 && d <= DaysInMonth (m, y))
        return true;
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