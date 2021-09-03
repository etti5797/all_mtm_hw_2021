#ifndef EXAMDETAILS_H_
#define EXAMDETAILS_H_

#include <iostream>

using std::string;


namespace mtm
{
    /*consts used in the class ExamDetails*/
    static const double MATAM_TIME = 13.0;   
    static const string MATAM_LINK = "https://tinyurl.com/59hzps6m";
    static const string DEFAULT_LINK="";

    class ExamDetails
    {

        private:
        static const int MATAM_NUMBER=234124;
        static const int MATAM_MONTH = 7;
        static const int MATAM_DAY = 28;
        static const int MATAM_LENGTH = 3;
        const int NUM_DAYS=30;
        const int MIN_DAY=1;
        const int MAX_DAY=30;
        const int MIN_MONTH=1;
        const int MAX_MONTH=12;
        const double HALF_HOUR=0.5;

        int course_num;
        int month;
        int day;
        double exam_time;
        int length;
        string exam_link;

        bool checkIfDateValid(int day, int month);  
        bool checkIfHourIsValid(double exam_time);   

        public:                 
        ExamDetails(int course_num,int month,int day,double exam_time,int length,string exam_link = DEFAULT_LINK);
        ~ExamDetails()=default;
        ExamDetails(const ExamDetails& exam)= default;
        ExamDetails& operator=(const ExamDetails& exam) = default; 
        string getLink() const;                                          
        void setLink(const string new_link);                            
        int operator-(const ExamDetails& exam) const;    
        bool operator<(const ExamDetails& exam)const;
        static ExamDetails makeMatamExam()  
        {
            return ExamDetails(MATAM_NUMBER,MATAM_MONTH,MATAM_DAY,MATAM_TIME,MATAM_LENGTH,MATAM_LINK);  
        }

        friend std::ostream& operator<<(std::ostream& os, const ExamDetails& exam); 
        class InvalidDateException{};    
        class InvalidTimeException{};      
        
    };

}


#endif