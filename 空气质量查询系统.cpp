#define _CRT_SECURE_NO_WARNINGS  1
#include <iostream>
#include <fstream>
#include<sstream>
#include <vector>
#include <algorithm>
#include<string>
#include <chrono>
#include<map>
using namespace std;

struct airquality {
    int citycode;
    string cityname;
    string object;
    int index;
    string level;
    string condition;
    int year;
    int month;
    int day;
};
bool compare(const pair<string,int> s1, const pair<string,int> s2) {
    return s1.second < s2.second; 
}
pair<chrono::system_clock::time_point, chrono::system_clock::time_point> getDateRangeFromWeek(int year, int week) {
    chrono::system_clock::time_point first_day = chrono::system_clock::from_time_t(0);
    time_t tt = chrono::system_clock::to_time_t(first_day);
    tm* timeinfo = localtime(&tt);
    timeinfo->tm_year = year - 1900;
    timeinfo->tm_mon = 0;  // 一月
    timeinfo->tm_mday = 1;  // 第一天
    mktime(timeinfo);
    first_day = chrono::system_clock::from_time_t(mktime(timeinfo));

    // 移动到目标周的第一天
    chrono::hours hours_in_a_day(24);
    chrono::system_clock::time_point start_of_week = first_day + chrono::hours(24 * 7 * (week - 1));
    while (start_of_week.time_since_epoch().count() % hours_in_a_day.count() != 0) {
        start_of_week -= chrono::hours(1);
    }

    // 计算周日的日期
    chrono::system_clock::time_point end_of_week = start_of_week + chrono::hours(24 * 6);

    return make_pair(start_of_week, end_of_week);
}
vector<airquality> searchcity(vector<airquality>& data,string city, int citycode) {
    vector<airquality> result;
    for (const auto& entry : data) {
        if (entry.cityname == city || entry.citycode == citycode) {
            result.push_back(entry);
        }
    }
    return result;
}
vector<airquality> searchtime(vector<airquality>& city,int year,int month=0,int day=0) {
    vector<airquality> result;
    for (const auto& entry : city) {
        if (month == 0)
        {
            result.push_back(entry);
        }
        else if (day == 0)
        {
            if (entry.month == month) {
                result.push_back(entry);
            }
        }
        else {
            if (entry.month == month && entry.day == day) {
                result.push_back(entry);
            }
        }
    }
    for (const auto& entry : result) {
    cout << entry.citycode << "\t" << entry.cityname << "\t" << entry.object << "\t"
    << entry.index << "\t" << entry.level << "\t" << entry.condition << "\t"
    << entry.year << "\t" << entry.month << "\t" << entry.day << endl;
       
    }
    return result;
}
vector<airquality> searchtimex(vector<airquality>& city, int year, int month = 0, int day = 0) {
    vector<airquality> result;
    for (const auto& entry : city) {
        if (month == 0)
        {
            result.push_back(entry);
        }
        else if (day == 0)
        {
            if (entry.month == month) {
                result.push_back(entry);
            }
        }
        else {
            if (entry.month == month && entry.day == day) {
                result.push_back(entry);
            }
        }
    }
    return result;
}
void counting(vector<airquality>& result, int& a, int& b, int& c, int& d, int& e)
{

    for (const auto& entry : result)
    {
        if (entry.condition == "优")
        {
            a++;
        }
        if (entry.condition == "良")
        {
            b++;
        }
        if (entry.condition == "轻微污染")
        {
            c++;
        }
        if (entry.condition == "轻度污染")
        {
            d++;
        }
        if (entry.condition == "重污染")
        {
            e++;
        }
    }
    cout << "优：" << a << "天" << endl;
    cout << "良：" << b << "天" << endl;
    cout << "轻微污染：" << c << "天" << endl;
    cout << "轻度污染：" << d << "天" << endl;
    cout << "重污染：" << e << "天" << endl;
}
void sortx(vector<airquality> result1,int n)
{
    map<string, int> map;
    vector<airquality> city;
    vector<vector<airquality>> city1;
    string cityname= result1[0].cityname;

    for (const auto& entry : result1)
    {
        if (entry.cityname != cityname)
        {
            city1.push_back(city);
            city.clear();
            cityname = entry.cityname;
       }
        city.push_back(entry);
    }
    
    for (const auto& entry : city1)
    {
        int sum = 0;
        int count = 0;
        string q;
        for (const auto& x : entry)
        {
            q = x.cityname;
            sum += x.index;
            count++;
        }
        map[q] = sum / count;
    }
    vector<pair<string, int>>v(map.begin(), map.end());
    sort(v.begin(), v.end(), compare);
    for (int i = 0; i < n; i++)
    {
        cout << i + 1 << ":" << v[i].first << endl;
    }

}
void countx(vector<airquality> result1, int n,int l)
{
    map<string, int> map;
    vector<airquality> city;
    vector<vector<airquality>> city1;
    string cityname = result1[0].cityname;

    for (const auto& entry : result1)
    {
        if (entry.cityname != cityname)
        {
            city1.push_back(city);
            city.clear();
            cityname = entry.cityname;
        }
        city.push_back(entry);
    }

    for (const auto& entry : city1)
    {
        int sum = 0;
        int count = 0;
        string q;
     
        for (const auto& x : entry)
        {
            string q = x.cityname;
            
            switch (n)
            {
            case 1:
                if (x.condition == "优")
                {
                    count++;
                }
                break;
            case 2:
                if (x.condition == "良")
                {
                    count++;
                }
                break;
            case 3:
                if (x.condition == "轻微污染")
                {
                    count++;
                }
                break;
            case 4:
                if (x.condition == "轻度污染")
                {
                    count++;
                }
                break;
            case 5:
                if (x.condition == "重度污染")
                {
                    count++;
                }
                break;
            }
           if (count >= l)
        {
            cout << q << endl;
            break;
        }
        }
        
    }
   
}
vector<airquality> searchtime1(vector<airquality>& city, int year, int month = 0, int day = 0) {
    vector<airquality> result;
    for (const auto& entry : city) {
        if (entry.month == month && entry.day >= day&&entry.day<day+7)
        {
           result.push_back(entry);
        }
    }
    for (const auto& entry : result) {
        cout << entry.citycode << "\t" << entry.cityname << "\t" << entry.object << "\t"
            << entry.index << "\t" << entry.level << "\t" << entry.condition << "\t"
            << entry.year << "\t" << entry.month << "\t" << entry.day << endl;
    }
    return result;
}
int main() {
    vector<airquality> data,result1,result2,result3;
    ifstream file("data.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            airquality entry;
            istringstream iss(line);
            iss >> entry.citycode >> entry.cityname >> entry.object >> entry.index
                >> entry.level >> entry.condition >> entry.year >> entry.month >> entry.day;
            data.push_back(entry);
        }
        file.close();
    }
    else {
        cout << "Unable to open file." << endl;
        return 1;
    }
    int citycode;
    string city;
    int op;
    int op1;
    int op2;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0; 
    int e = 0;
    int week_number;
    int n;
    int x;
    cout << "请选择操作：" << endl;
    cout << "1：普通查询" << endl;
    cout << "2：统计查询" << endl;
    cout << "3：排序查询" << endl;
    cin >> op;
    if (op == 1)
    {
        cout << "请输入城市代码和城市名称：" << endl;
        cin >> citycode >> city;
        vector<airquality> result = searchcity(data, city, citycode);
        cout << "请选择操作：" << endl;
        cout << "1：日" << endl;
        cout << "2：月" << endl;
        cout << "3：季度" << endl;
        cout << "4：年" << endl;
        cout << "5：周" << endl;
        cin >> op1;
        switch (op1)
        {
          case 1:
              cout << "输入月 日：" << endl;
              cin >> a >> b;
              searchtime(result, 2006, a, b);
              break;
          case 2:
              cout << "输入月：" << endl;
              cin >> a;
              searchtime(result, 2006, a);
              break;
          case 3:
              cout << "输入季度：" << endl;
              cin >> a;
              if (a == 1)
              {
                  result1=searchtime(result, 2006, 1);
                  result2=searchtime(result, 2006, 2);
                  result3=searchtime(result, 2006, 3);
                
              }
              if (a == 2)
              {
                  result1=searchtime(result, 2006, 4);
                  result2=searchtime(result, 2006, 5);
                  result3=searchtime(result, 2006, 6);
                 
              }
              if (a == 3)
              {
                  result1=searchtime(result, 2006, 7);
                  result2=searchtime(result, 2006, 8);
                  result3=searchtime(result, 2006, 9);
                 
              }
              if (a == 4)
              {
                  result1=searchtime(result, 2006, 10);
                  result2=searchtime(result, 2006, 11);
                  result3=searchtime(result, 2006, 12);
  
              }
              break;
          case 4:
              cout << "输入年：" << endl;
              cin >> a;
              searchtime(result, 2006);
              break;
          case 5:
              cout << "输入周数：" << endl;
              cin >> week_number;
              auto date_range = getDateRangeFromWeek(2006, week_number);
              auto start_time = chrono::system_clock::to_time_t(date_range.first);
              tm* start_timeinfo = localtime(&start_time);
              int month = start_timeinfo->tm_mon + 1;
              int day = start_timeinfo->tm_mday;
              searchtime1(result, 2006, month, day);
              break;
        
        }
    }
    if (op == 2)
    {
        cout << "请选择操作：" << endl;
        cout << "1：按城市查询" << endl;
        cout << "2：按空气质量和时间查询" << endl;
        cin >> op1;
        if (op1 == 1)
        {
            cout << "请输入城市代码和城市名称：" << endl;
            cin >> citycode >> city;
            vector<airquality> result = searchcity(data, city, citycode);
            cout << "请选择操作：" << endl;
            cout << "1：日" << endl;
            cout << "2：月" << endl;
            cout << "3：季度" << endl;
            cout << "4：年" << endl;
            cout << "5：周" << endl;
            cin >> op2;
            switch (op2)
            {
            case 1:
                cout << "输入月 日：" << endl;
                cin >> a >> b;
                searchtime(result, 2006, a, b);
                break;
            case 2:
                cout << "输入月：" << endl;
                cin >> a;
                result1=searchtimex(result, 2006, a);
                a = 0;
                counting(result1, a, b, c, d, e);
                break;
            case 3:
                cout << "输入季度：" << endl;
                cin >> a;
                if (a == 1)
                {
                    result1 = searchtimex(result, 2006, 1);
                    result2 = searchtimex(result, 2006, 2);
                    result3 = searchtimex(result, 2006, 3);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    a = 0;
                    counting(result1, a, b, c, d, e);
                   
                }
                if (a == 2)
                {
                    result1 = searchtimex(result, 2006, 4);
                    result2 = searchtimex(result, 2006, 5);
                    result3 = searchtimex(result, 2006, 6);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    a = 0;
                    counting(result1, a, b, c, d, e);
                }
                if (a == 3)
                {
                    result1 = searchtimex(result, 2006, 7);
                    result2 = searchtimex(result, 2006, 8);
                    result3 = searchtimex(result, 2006, 9);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    a = 0;
                    counting(result1, a, b, c, d, e);
                }
                if (a == 4)
                {
                    result1 = searchtimex(result, 2006, 10);
                    result2 = searchtimex(result, 2006, 11);
                    result3 = searchtimex(result, 2006, 12);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    a = 0;
                    counting(result1, a, b, c, d, e);
                }
                break;
            case 4:
                cout << "输入年：" << endl;
                cin >> a;
                result1=searchtimex(result, 2006);
                a = 0;
                counting(result1, a, b, c, d, e);
                break;
            case 5:
                cout << "输入周数：" << endl;
                cin >> week_number;
                auto date_range = getDateRangeFromWeek(2006, week_number);
                auto start_time = chrono::system_clock::to_time_t(date_range.first);
                tm* start_timeinfo = localtime(&start_time);
                int month = start_timeinfo->tm_mon + 1;
                int day = start_timeinfo->tm_mday;
                result1=searchtime1(result, 2006, month, day);
                counting(result1, a, b, c, d, e);
                break;

            }
        }
        if (op1 == 2)
        {
            
            cout << "请选择操作：" << endl;
            cout << "1：日" << endl;
            cout << "2：月" << endl;
            cout << "3：季度" << endl;
            cout << "4：年" << endl;
            cout << "5：周" << endl;
            cin >> op2;
            cout << "请选择污染级别：" << endl;
            cout << "1：优" << endl;
            cout << "2：良" << endl;
            cout << "3：轻微污染" << endl;
            cout << "4：轻度污染" << endl;
            cout << "5：重度污染" << endl;
            cin >> n;
            cout << "请输入最低影响天数：" << endl;
            cin >> x;
            switch (op2)
            {
            case 1:
                cout << "输入月 日：" << endl;
                cin >> a >> b;
                result1 = searchtimex(data, 2006, a, b);
                countx(result1, n, x);
                break;
            case 2:
                cout << "输入月：" << endl;
                cin >> a;
                result1 = searchtimex(data, 2006, a);
                
                countx(result1, n, x);

                break;
            case 3:
                cout << "输入季度：" << endl;
                cin >> a;
                if (a == 1)
                {
                    result1 = searchtimex(data, 2006, 1);
                    result2 = searchtimex(data, 2006, 2);
                    result3 = searchtimex(data, 2006, 3);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    countx(result1, n, x);

                }
                if (a == 2)
                {
                    result1 = searchtimex(data, 2006, 4);
                    result2 = searchtimex(data, 2006, 5);
                    result3 = searchtimex(data, 2006, 6);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    countx(result1, n, x);
                }
                if (a == 3)
                {
                    result1 = searchtimex(data, 2006, 7);
                    result2 = searchtimex(data, 2006, 8);
                    result3 = searchtimex(data, 2006, 9);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    countx(result1, n, x);
                }
                if (a == 4)
                {
                    result1 = searchtimex(data, 2006, 10);
                    result2 = searchtimex(data, 2006, 11);
                    result3 = searchtimex(data, 2006, 12);
                    result1.insert(result1.end(), result2.begin(), result2.end());
                    result1.insert(result1.end(), result3.begin(), result3.end());
                    countx(result1, n, x);
                }
                break;
            case 4:
                cout << "输入年：" << endl;
                cin >> a;
                result1 = searchtimex(data, 2006);
                countx(result1, n, x);
                break;
            case 5:
                cout << "输入周数：" << endl;
                cin >> week_number;
                auto date_range = getDateRangeFromWeek(2006, week_number);
                auto start_time = chrono::system_clock::to_time_t(date_range.first);
                tm* start_timeinfo = localtime(&start_time);
                int month = start_timeinfo->tm_mon + 1;
                int day = start_timeinfo->tm_mday;
                result1 = searchtime1(data, 2006, month, day);
                countx(result1, n, x);
                break;

            }
        }
    }
   
    if (op == 3)
    {
        cout << "请选择操作：" << endl;
        cout << "1：日" << endl;
        cout << "2：月" << endl;
        cout << "3：季度" << endl;
        cout << "4：年" << endl;
        cout << "5：周" << endl;
        cin >> op2;
        cout << "输入排序前多少个城市：" << endl;
        cin >> n;
        switch (op2)
        {
        case 1:
            cout << "输入月 日：" << endl;
            cin >> a >> b;
            result1=searchtimex(data, 2006, a, b);
            sortx(result1, n);
            break;
        case 2:
            cout << "输入月：" << endl;
            cin >> a;
            result1 = searchtimex(data, 2006, a);
            sortx(result1,n);
           
            
            break;
        case 3:
            cout << "输入季度：" << endl;
            cin >> a;
            if (a == 1)
            {
                result1 = searchtimex(data, 2006, 1);
                result2 = searchtimex(data, 2006, 2);
                result3 = searchtimex(data, 2006, 3);
                result1.insert(result1.end(), result2.begin(), result2.end());
                result1.insert(result1.end(), result3.begin(), result3.end());
                sortx(result1, n);

            }
            if (a == 2)
            {
                result1 = searchtimex(data, 2006, 4);
                result2 = searchtimex(data, 2006, 5);
                result3 = searchtimex(data, 2006, 6);
                result1.insert(result1.end(), result2.begin(), result2.end());
                result1.insert(result1.end(), result3.begin(), result3.end());
                sortx(result1, n);
            }
            if (a == 3)
            {
                result1 = searchtimex(data, 2006, 7);
                result2 = searchtimex(data, 2006, 8);
                result3 = searchtimex(data, 2006, 9);
                result1.insert(result1.end(), result2.begin(), result2.end());
                result1.insert(result1.end(), result3.begin(), result3.end());
                sortx(result1, n);
            }
            if (a == 4)
            {
                result1 = searchtimex(data, 2006, 10);
                result2 = searchtimex(data, 2006, 11);
                result3 = searchtimex(data, 2006, 12);
                result1.insert(result1.end(), result2.begin(), result2.end());
                result1.insert(result1.end(), result3.begin(), result3.end());
                sortx(result1, n);
            }
            break;
        case 4:
            cout << "输入年：" << endl;
            cin >> a;
            result1 = searchtimex(data, 2006);
            sortx(result1, n);
            break;
        case 5:
            cout << "输入周数：" << endl;
            cin >> week_number;
            auto date_range = getDateRangeFromWeek(2006, week_number);
            auto start_time = chrono::system_clock::to_time_t(date_range.first);
            tm* start_timeinfo = localtime(&start_time);
            int month = start_timeinfo->tm_mon + 1;
            int day = start_timeinfo->tm_mday;
            result1 = searchtime1(data, 2006, month, day);
            sortx(result1, n);
            break;

        }
    }
   
    return 0;
}




    

 