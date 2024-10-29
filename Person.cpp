#include "Person.h"
using namespace std;
#include <string.h>

Person::Person() {
	SetName("NULL");
	SetId(0);
}
Person::Person(const char* name, int id) {
	SetName(name);
	SetId(id);
}
Person::Person(const Person& other) {
	SetName(other.m_name);
	SetId(other.m_id);
}
void Person :: SetName(const char* newName) { 
	m_name = new char[strlen(newName) + 1];// הקצאת זיכרון למערך דינמי והגדרתו
	strcpy(m_name, newName);
}
void Person:: SetId(int newId) {
	m_id = newId;
}
char* Person::GetName() const { return m_name; }

int	Person::GetId() const{ 
		return m_id;
}

Person::~Person() {
	delete[] m_name;
}