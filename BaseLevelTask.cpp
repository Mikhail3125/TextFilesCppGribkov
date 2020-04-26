#include "Stdafx.h"
using namespace std;
//#define MAX_Patients 10

#ifndef _Patients
#define _Patients
struct DateBorn
{
	int day;
	int month;
	int year;
	bool IsCorect();
public: void ShowDate();

};
void DateBorn::ShowDate()
{
	cout << day << "." << month << "." << year << endl;
}
bool DateBorn::IsCorect()
{
	bool result = false;
	switch (month)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
	{
		if ((day <= 31) && (day > 0))
			result = true;
		break;
	}

	case 4:
	case 6:
	case 9:
	case 11:
	{
		if ((day <= 30) && (day > 0))
			result = true;
		break;
	}

	case 2:
	{
		if (year % 4 != 0)
		{
			if ((day <= 28) && (day > 0))
				result = true;
		}
		else
			if (year % 400 == 0)
			{
				if ((day <= 29) && (day > 0))
					result = true;
			}
			else
				if ((year % 100 == 0) && (year % 400 != 0))
				{
					if ((day == 28) && (day > 0))
						result = true;
				}
				else
					if ((year % 4 == 0) && (year % 100 != 0))
						if ((day <= 29) && (day > 0))
							result = true;
		break;
	}

	default:
		result = false;
	}

	return result;

}
struct HomeAdress
{
	//почтовый индекс, страна, область, район, город, улица, дом, квартира
	string mail_index;
	string country;
	string region;
	string district;//район
	string city;
	string street;
	string house_number;
	string flat_num;
};
struct Person
{
	string		 fio;
	string		 sex;
	DateBorn	 date;
	string		 nation;
	unsigned int weigth; // вес
	unsigned int height;// rost
	string		 telephone_num;
	HomeAdress	 home_adress;

};
struct Patient
{
	//номер больницы; отделение; номер медицинской карты; диагноз; группа крови.
	Person       person;
	unsigned int number_hospital;//
	int		 hospital_department;//
	unsigned int number_medical_record;
	string       diagnoses;
	enum         blood_type{ I, II, III, IV};
			
} ;
#endif // !_Patients

void BaseLevelTask()
{
	/*
Задание:
	создать текстовый файл с произвольной информацией. Организовать  просмотр содержимого файла.
	Организовать чтение и обработку данных из файла в соответствии с индивидуальным заданием. Сохранить полученные
	результаты в новый текстовый файл.
 «Пациент»:
	фамилия; имя; отчество; пол; национальность; рост; вес; дата рождения (год, месяц число); номер телефона;
	 домашний адрес (почтовый индекс, страна, область, район, город, улица, дом, квартира); номер больницы; отделение;
	номер медицинской карты; диагноз; группа крови.
 Вывести данные про пациентов с 18 отделения
	*/

	cout << "\nBase level task:\n";
	Patient* p = new Patient[2];
	p[0].person.fio = "Вячеслав Городецкий Андреевис";
	p[1].person.fio = "Галкин Артем Владиславович";

	for (size_t i = 0; i < 2; i++)
	{
		p[i].hospital_department = 15 + rand() % 4;
	}
	FILE* f_out, * f_in;
	f_out = fopen("patientdate", "wb");
	fwrite(p, sizeof(Patient), 2, f_out);
	fclose(f_out);
	cout << "\nДанные хранящиеся в файле <<patientdate.dat>>: \n";
	f_in = fopen("patientdate", "rb");
	Patient* buffer = new Patient[2];
	fread(buffer, sizeof(Patient), 2, f_in);
	f_out = fopen("patientfrom18depart", "wb");
	int counter = 0;
	for (size_t i = 0; i < 2; i++)
	{
		cout << "\t" << buffer[i].person.fio << " " << buffer[i].hospital_department << "\n";
		if (buffer[i].hospital_department == 18)
		{
			fwrite(&buffer[i], sizeof(Patient), 1, f_out); counter++;
		}

	}
	fclose(f_out);
	fclose(f_in);
	cout << "\nДанные о пациентах с 18 отделения(записанны/прочитанны отдельным бинарным файлом): \n";
	f_in = fopen("patientfrom18depart", "rb");
	Patient* buf = (Patient*)malloc(counter * sizeof(Patient));
	fread(buf, sizeof(Patient), counter, f_in);
	for (size_t i = 0; i < counter; i++)
	{
		cout << "\t" << buf[i].person.fio << " " << buf[i].hospital_department << "\n";
	}
	fclose(f_in);
}
