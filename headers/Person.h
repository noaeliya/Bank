#pragma once
#include <string>

class Person {
private:
    std::string m_name; // שינוי מ-char* ל-string
    int m_id;

public:
    Person();
    Person(const std::string& name, int id); // שינוי מ-const char* ל-std::string
    
    void SetName(const std::string& newName); // החתימה המדויקת שחסרה לך בקובץ ה-.cpp
    void SetId(int newId);
    
    std::string GetName() const; // שינוי מ-char* ל-string
    int GetId() const;
};