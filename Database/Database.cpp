#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>
#include "../Student/Student.h"
#include "../Course/Course.h"
#include "Database.h"
#include "../CompE/CompE.h"
#include <algorithm>
     
     //vector onto heap, return pointer
     //destructor at main();

vector<Course> Database::list_all;

void Database::create_db()
{
    ifstream file;
    file.open("course_database.txt", ios::in);
    
    if(file.fail())
    {
        std::cout << "Error: course_database.txt not found.\nPress Enter to exit.";
        string temp;
        std::getline(std::cin, temp);
        exit(EXIT_FAILURE);
        return;
    }
    
    while(file.good())
    {
        //Major CourseNum avgGPA creditHours AttributeString
        Course temp;
        file >> temp;
        list_all.push_back(temp);
    }
    file.close();
}

vector<Course> Database::get_vector()
{
    return list_all;
}

void Database::save_data()
{
    ofstream save_file ("course_data_save.txt", ofstream::out);
    save_file << list_all.size() << "\n"; //saves list size into file 
    for(int i = 0; i < list_all.size(); ++i)
    {
        save_file << list_all[i];  //loads database courses into save file
    }
    save_file.close();
}

void Database::load_data() 
{
    int list_all_size; 
    ifstream load_file ("course_data_save.txt", ifstream::in);   
    if(load_file.fail())
    {
        //Student::create_new_student();
    }
    load_file >> list_all_size; //retrieves list size from save file
    for(int x = 0; x < list_all_size; ++x)
    {
        load_file >> list_all[x];  //loads courses into list_all vector
    }
}

 void Database::search_db()
{
    std::cout << "\nEnter the attributes you want to search by: \nAttributes to choose from: major, gpa, coursenum, credhours, libed, gened, humanities, social, western, non-western, minority. \n";
    string s;
    std::getline(std::cin, s);
    vector<Course> vec = list_all;
    if(s.find("major") != string::npos)
    {
        std::cout << "\nWhat course major?\n";
        string maj;
        cin >> maj;
        vec = real_search(vec, "maj", maj);
    }
    if(s.find("libed") != string::npos)
    {
        vec = real_search(vec, "atr", "libed");
    }
    if(s.find("humanities") != string::npos)
    {
        vec = real_search(vec, "atr", "hum");
    }
    if(s.find("social") != string::npos)
    {
        vec = real_search(vec, "atr", "soc");
    }
    if(s.find("western") != string::npos)
    {
        vec = real_search(vec, "atr", "west");
    }
    if(s.find("non-western") != string::npos)
    {
        vec = real_search(vec, "atr", "nwest");
    }
    if(s.find("minority") != string::npos)
    {
        vec = real_search(vec, "atr", "min");
    }
    if(s.find("gpa") != string::npos)
    {
        std::cout << "\nEnter the GPA range to search: (separate by spaces)\n";
        double low, up;
        cin >> low >> up;
        vec = real_search(vec, low, up);
    }
    if(s.find("coursenum") != string::npos)
    {
        int cnum;
        std::cout << "Enter course number: \n";
        std::cin >> cnum;
        vec = real_search(vec, "cnum", cnum);
    }
    if(s.find("credhours") != string::npos)
    {
        int cnum;
        std::cout << "Enter credit hour amount: \n";
        std::cin >> cnum;
        vec = real_search(vec, "chours", cnum);
    }
    std::cout << "\n";
    Course::display(vec);
    
}
vector<Course> Database::real_search(vector<Course> vec, string key, string specific)
{
    vector<Course> ret;
    if(key.compare("maj") == 0)
    {
        for(int i = 0; i < vec.size(); ++i)
        {
            if(vec[i].get_major().compare(specific) == 0)
            {
                ret.push_back(vec[i]);
            }
        }
        return ret;
    }
    else if(key.compare("atr") == 0)
    {
        for(int i = 0; i < vec.size(); ++i)
        {
            if(vec[i].get_attribute().compare(specific) == 0)
            {
                ret.push_back(vec[i]);
            }
        }
        return ret;
    }
    return ret;
}

vector<Course> Database::real_search(vector<Course> vec, double low, double up)
{
    vector<Course> ret;
    if(low < 0)
        low = 0.0;
    if(up > 4.00)
        up = 4.00;
    if(low > up)
    {
        low = up;
    }
    for(int i = 0; i < vec.size(); ++i)
    {
        if(vec[i].get_avgGPA() >= low && vec[i].get_avgGPA() <= up)
        {
            ret.push_back(vec[i]);
        }
    }
    return ret;
}

vector<Course> Database::real_search(vector<Course> vec, string key, int num)
{
    vector<Course> ret;
    if(key.compare("cnum") == 0)
    {
        for(int i = 0; i < vec.size(); ++i)
        {
            if(vec[i].get_course_num() == num)
            {
                ret.push_back(vec[i]);
            }
        }
        return ret;
    }
    else if(key.compare("chours") == 0)
    {
        for(int i = 0; i < vec.size(); ++i)
        {
            if(vec[i].get_credit_hours() == num)
            {
                ret.push_back(vec[i]);
            }
        }
        return ret;
    }
    return ret;
}

Course * Database::find_course(string major, int c_num)
{   
    Course c(major, c_num);
    sort(list_all.begin(), list_all.end());
    Course * found =  bsearch(list_all, c);
    return found;
}

Course * Database::bsearch(vector <Course> & a, Course & x)
{
    int low = 0;
    int high = a.size() -1;

    while(low <= high)
    {
        int mid = (low+high)/2;

        if(x < a[mid])
        high = mid - 1;

        else if(x > a[mid])
        low = mid + 1;
        else

        return &a[mid];
    }
    
    return NULL;
}


