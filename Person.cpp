#include "Person.h"

// בנאי ברירת מחדל
Person::Person() : m_name("NULL"), m_id(0) {}

// בנאי עם פרמטרים
Person::Person(const std::string& name, int id) : m_name(name), m_id(id) {}

void Person::SetName(const std::string& newName) { 
    m_name = newName; // ה-string מנהל את הקצאת הזיכרון בעצמו!
}

void Person::SetId(int newId) {
    m_id = newId;
}

std::string Person::GetName() const { 
    return m_name; 
}

int Person::GetId() const { 
    return m_id;
}