#include <string.h>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#pragma once
using namespace std;

//start of a strcpy_s implementation just to see this thing work
//comment this out for windows implementation
//template<typename C>
//inline int strcpy_s(C* d, const C* s) {
//	unsigned long dmax = strlen(s) + 2;
//	if (dmax <= 1 || !d) {
//		if (!d || !dmax) {
//			return 22;
//		}
//		*d = C(0);
//		return 0;
//	}
//	for (C* de = d + dmax - 1; (d != de || (*d = C(0))) && (*d = *s); ++d, ++s);
//	return 0;
//}
//end of strcpy_s implementation

class CEmployee {
	friend ostream& operator <<(ostream& ls, CEmployee* rs);

private:
	char name[30];
	char id[30];
	//virtual float Pay() { return 0;};  // virtual function
	virtual float Pay() = 0; // pure virtual function
public:
	CEmployee(char n[], char i[])
	{
		strcpy_s(name, n);
		strcpy_s(id, i);
	}
	CEmployee()
	{
		strcpy_s(name, "");
		strcpy_s(id, "");
	}
	void PrintCheck()
	{
		cout << name << "  " << Pay() << endl;
	}
	char* getName() {
		return name;
	}
	char* getID() {
		return id;
	}
};

class CFulltimeEmployee : public CEmployee {
protected:
	float benefitcost;
public:
	CFulltimeEmployee()
	{

	}
	CFulltimeEmployee(char n[], char i[]) : CEmployee(n, i)
	{
		benefitcost = 100;
	}
};

class CHourlyFTEmployee : public CFulltimeEmployee
{
private:
	float rate;
	float hours;
public:
	CHourlyFTEmployee()
	{
		rate = 0;
		hours = 0;
	}
	CHourlyFTEmployee(char n[], char i[], float r, float h) : CFulltimeEmployee(n, i)
	{
		rate = r;
		hours = h;
	}
	float Pay()
	{
		return rate * hours - benefitcost;
	}
	void updatePayData(float rateIn, float hoursIn) {
		rate = rateIn;
		hours = hoursIn;
	}
	float getRate() {
		return rate;
	}
	float getHours() {
		return hours;
	}
};

//placeholder class for parttime employees
class CParttimeEmployee : public CEmployee {
	//implements the constructor accessed by CHourlyPTEmployee
protected:
	//default
	CParttimeEmployee() {}
	//with variables
	CParttimeEmployee(char n[], char i[]) : CEmployee(n, i) {}
};

//implementation of a parttime employee on an hourly basis
class CHourlyPTEmployee : public CParttimeEmployee {
private:
	float rate;
	float hours;
public:
	//default constructor
	CHourlyPTEmployee() {
		hours = 0;
		rate = 0;
	}
	//constructor expecting all four variables
	CHourlyPTEmployee(char n[], char i[], float r, float h) : CParttimeEmployee(n, i) {
		rate = r;
		hours = h;
	}
	//utility function to return a weeks' pay; parttime employees have no benefits cost as they have no benefits
	float Pay() {
		return hours * rate;
	}
	//utility function to update rate and hours
	void updatePayData(float rateIn, float hoursIn) {
		rate = rateIn;
		hours = hoursIn;
	}
	float getRate() {
		return rate;
	}
	float getHours() {
		return hours;
	}
};

//implementation of a fulltime employee on a salary contract
class CSalariedFTEmployee : public virtual CFulltimeEmployee {
private:
	float salary;
public:
	//default constructor
	CSalariedFTEmployee() {
		salary = 0;
	}
	//constructor expecting all four variables
	CSalariedFTEmployee(char n[], char i[], float s) : CFulltimeEmployee(n, i) {
		salary = s;
	}
	//utility function to return a weeks' pay; fulltime employees benefits cost
	float Pay() {
		return (salary / 12) - benefitcost;
	}
	//function to update a salaried employee's salary
	void updatePayData(float salaryIn) {
		salary = salaryIn;
	}
	float getSal() {
		return salary;
	}
};

//implementation of a fulltime employee on a commission basis
class CCommissionedFTEmployee : public virtual CFulltimeEmployee {
private:
	float salesVolume;
	float commissionPercent;
public:
	//default constructor
	CCommissionedFTEmployee() {
		salesVolume = 0;
		commissionPercent = 0;
	}
	//constructor expecting all four variables
	CCommissionedFTEmployee(char n[], char i[], float c, float v) : CFulltimeEmployee(n, i) {
		salesVolume = v;
		commissionPercent = c;
	}
	//utility function to return a weeks' pay; fulltime employees have  benefits cost
	float Pay() {
		return (salesVolume * commissionPercent) - benefitcost;
	}
	//function to update commissioned employee percentage and sales volume
	void updatePayData(float percentIn, float volumeIn) {
		salesVolume = volumeIn;
		commissionPercent = percentIn;
	}
	float getVol() {
		return salesVolume;
	}
	float getComm() {
		return commissionPercent;
	}
};

//implementation of a fulltime employee on a salary contract with commission
class CSalariedCommissionedFTEmployee : public CSalariedFTEmployee, CCommissionedFTEmployee {
public:
	//default constructor
	CSalariedCommissionedFTEmployee() {
	}
	//constructor expecting all five variables
	CSalariedCommissionedFTEmployee(char n[], char i[], float s, float c, float v) : CSalariedFTEmployee(n, i, s), CCommissionedFTEmployee(n, i, c, v), CFulltimeEmployee(n, i) {
	}
	//utility function to return a weeks' pay; benefitcost has already been deducted twice from commission and salary so it is added once more to prevent logic error
	float Pay() {
		return CSalariedFTEmployee::Pay() + CCommissionedFTEmployee::Pay() + benefitcost;
	}
	//function to update salaried commissioned employee salary, percentage, and volume 
	void updatePayData(float salaryIn, float percentIn, float volumeIn) {
		CSalariedFTEmployee::updatePayData(salaryIn);
		CCommissionedFTEmployee::updatePayData(percentIn, volumeIn);
	}
	float getVol() {
		return this->CCommissionedFTEmployee::getVol();
	}
	float getComm() {
		return this->CCommissionedFTEmployee::getComm();
	}
};

ostream& operator <<(ostream& ls, CEmployee* rs)
{
	CHourlyFTEmployee* hfe;
	hfe = dynamic_cast<CHourlyFTEmployee*>(rs);
	if (hfe) {
		ls << fixed << setprecision(2) << hfe->getName() << "\t" << hfe->getID() << "\t" << hfe->getRate() << "\t" << hfe->getHours() << " Hourly Fulltime Employee";
		return ls;
	}
	CSalariedFTEmployee* sfe;
	sfe = dynamic_cast<CSalariedFTEmployee*>(rs);
	CCommissionedFTEmployee* cfe;
	cfe = dynamic_cast<CCommissionedFTEmployee*>(rs);
	CSalariedCommissionedFTEmployee* scfe;
	scfe = dynamic_cast<CSalariedCommissionedFTEmployee*>(rs);
	if (scfe) {
		ls << fixed << setprecision(2) << scfe->getName() << "\t" << scfe->getID() << "\t" << scfe->getSal() << "\t" << scfe->getComm() << "\t" << scfe->getVol() << " Salaried Commissioned Fulltime Employee";
		return ls;
	}
	else if (cfe) {
		ls << fixed << setprecision(2) << cfe->getName() << "\t" << cfe->getID() << "\t" << cfe->getComm() << "\t" << cfe->getVol() << " Commissioned Fulltime Employee";
		return ls;
	}
	else if (sfe) {
		ls << fixed << setprecision(2) << sfe->getName() << "\t" << sfe->getID() << "\t" << sfe->getSal() << " Salaried Fulltime Employee";
		return ls;
	}
	CHourlyPTEmployee* pfe;
	pfe = dynamic_cast<CHourlyPTEmployee*>(rs);
	if (pfe) {
		ls << fixed << setprecision(2) << pfe->getName() << "\t" << pfe->getID() << "\t" << pfe->getRate() << "\t" << pfe->getHours() << " Hourly Parttime Employee";
		return ls;
	}
	return ls;
}
