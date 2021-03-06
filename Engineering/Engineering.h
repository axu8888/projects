#pragma once
#include <iostream>
#include <vector>
#include "../Course/Course.h"


//Class contains general courses overlapping between ECE and CS
class Engineering{   //ABSTRACT CLASS
protected:
    static const int tot_hours;
    //interacts with Student Class
    //lib ed requirements
        //gened categories
   static vector <Course> pos_geneds;
   static vector <Course> pos_lang;
   static vector <Course> pos_compos;
   
   
   //geneds
    vector <Course> west_comp = vector<Course>(2);
    vector <Course> non_west = vector<Course>(2);
    vector <Course> US_min = vector<Course>(2);
    vector <Course> hum_and_arts = vector<Course>(2);
    vector <Course> soc_and_behav = vector<Course>(2);
    vector <Course> libed = vector<Course>(2);
    
    //3 language courses
    vector <Course> language = vector<Course>(3);
    //Composition 1 and Advanced Composition
    vector <Course> compos = vector<Course>(2);
    vector <Course> misc; //ENG 100 + whatever extra bs you need
   

public:
    //constructors

    
    //getters
    
    //other functions
    
    static vector<Course> get_geneds();
    static int get_tot_hours();
    static Engineering * choose_major(string maj);
    static bool search_req(pair<vector<Course>, int> vec, Course c); //helper function for add_to_degree
    static void fill_pos_vec();
    static int search_req_index(pair<vector<Course>, int> vec, Course c); //helper function for add_to_degree
    static int search_req2(vector<Course> vec, Course c);
    
    
    virtual void add_to_degree(Course& c)=0;  //pure virtual function to make class virtual
    virtual bool remove_from_degree(Course &c) = 0;
    virtual void save_deg_vec(Engineering * major) = 0;
    virtual void load_deg_vec(Engineering * major) = 0;

    virtual pair<vector<Course>, int>* get_foundations() = 0;
    virtual pair<vector<Course>, int>* get_core() = 0;
    virtual pair<vector<Course>, int>* get_gen_electives() = 0;
    virtual pair<vector<Course>, int>* get_EE_foundation() = 0;
    virtual pair<vector<Course>, int>* get_adv_computing() = 0;
    virtual pair<vector<Course>, int>* get_capstone() = 0;
};