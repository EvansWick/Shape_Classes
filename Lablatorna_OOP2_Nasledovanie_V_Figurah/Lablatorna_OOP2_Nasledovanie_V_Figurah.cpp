
#include <iostream>
#include <string.h>
#include <cmath>
#include <sstream>

//#define WathcConstructorAndDestructorInformation 

using namespace std;
void GlobalInterface();

double P = P;

class shape {

	
protected:
	string name;
	double SideLength;
	int SidesCount; // Количество стороно (ребер)
	int NumOfVertices; // Количество вершин
	double Square;
	double RadiusOfDescribedCircle;
	double RadiusOfInscribedCircle;
	

	static int objectCount;


	virtual ~shape() {// destructor
		objectCount--;
#ifdef WathcConstructorAndDestructorInformation
		cout << "\tShape destroed\n";
#endif // DEBUG
	}


public:
	friend void GlobalInterface();
	friend void DeleteFlatSHapeObject(shape* obj);
	//friend void DeleteFlatSHapeObject(FlatShape* obj);
	shape(double LengthSide_arg) //Конструктор по умолчанию
	{
		if (LengthSide_arg >= 0) {
			name = "Undefined";
			this->SideLength = LengthSide_arg;
			SidesCount = 0;
			NumOfVertices = 0;
			Square = 0;
			RadiusOfInscribedCircle = 0;
			RadiusOfDescribedCircle = 0;
			objectCount++;
#ifdef WathcConstructorAndDestructorInformation
			cout << "\tShape created!";
#endif // DEBUG
		}
		else {
			name = "Undefined";
			this->SideLength = 0;
			SidesCount = 0;
			NumOfVertices = 0;
			Square = 0;
			RadiusOfInscribedCircle = 0;
			RadiusOfDescribedCircle = 0;
			objectCount++;
#ifdef WathcConstructorAndDestructorInformation
			cout << "\tShape created!";
#endif // DEBUG
		}
	}
	shape(const shape& other) // Конструктор копирования
	{
		name = other.name;
		SideLength = other.SideLength;
		SidesCount = other.SidesCount;
		NumOfVertices = other.NumOfVertices;
		Square = other.Square;
		RadiusOfDescribedCircle = other.RadiusOfDescribedCircle;
		RadiusOfInscribedCircle = other.RadiusOfInscribedCircle;
	}
	
	virtual string shapeToString() const { 
		ostringstream ss;
		ss << "\n\tName: " << name << "\n\tLengthOfSide: " << SideLength << "\n\tNumOfSides: " << SidesCount;
		ss << "\n\tNumOfVertices: " << NumOfVertices << "\n\tArea: " << Square;
		return ss.str(); 
	}

	string ReturnShapeName() // 
	{
		return name;
	}

	// Getters
	int GetCountSides()
	{
		return this->SidesCount;
	}
	int GetNumOfVertices()
	{
		return this->NumOfVertices;
	}
	double GetSideLength()
	{
		return this->SideLength;
	}
	double GetRadiusOfInscribedCircle() {
		return RadiusOfInscribedCircle;
	}
	double GetRadiusOfDescribedCircle() {
		return RadiusOfDescribedCircle;
	}

	double GetSquare() {
		return Square;
	}
	
	// Setters
	virtual void SetSquare(double val) {}
	virtual void setSideLength(double val) {}
	virtual void SetRadiusOfInscribedCircle(double val) {}
	virtual void SetRadiusOfDescribedCircle(double val) {}
	
};

class FlatShape : public shape //Плоские фигуры
{
protected:
	virtual ~FlatShape() { // Класс виртуальный, чтобы потом можно было удалять через указатель
#ifdef WathcConstructorAndDestructorInformation
		cout << "\n\tFlatShape destroed\n";
#endif
	}
	double Perimetr;
public:
	FlatShape(double LengthSide_arg) : shape(LengthSide_arg)
	{
		Perimetr = 0;
#ifdef WathcConstructorAndDestructorInformation
		cout << "\n\tFlatShape Created\n";
#endif
	}
	string shapeToString() const override {
		ostringstream ss;
		ss << shape::shapeToString();
		ss << "\n\tPerimetr: " << Perimetr;
		ss << "\n\tRadiusOfDescribedCircle: " << RadiusOfDescribedCircle << "\n\tRadiusOfInscribedCircle: " << RadiusOfInscribedCircle;
		return ss.str();
	}

	double GetPerimetr() {
		return Perimetr;
	}

	virtual void SetPerimetr(double val) {}
	friend void DeleteFlatSHapeObject(FlatShape* obj);
};


class VolumeShape : public shape // Объемные фигуры
{
protected:
	double volume;
	int numOfFaces;
	int NumOfFacesThroughVertices; // Количество граней сумижных с вершиной
	int numOfSidesInFace;

	 virtual ~VolumeShape() {
#ifdef WathcConstructorAndDestructorInformation
		 cout << "\n\tVolumeShape Destroed!\n";
#endif
	}

public:
	VolumeShape(double LengthSide_arg) : shape(LengthSide_arg)
	{
			volume = 0;
			numOfFaces = 0;
			NumOfFacesThroughVertices = 0;
			numOfSidesInFace = 0;
#ifdef WathcConstructorAndDestructorInformation
			cout << "\n\tVolumeShape Created\n";
#endif

	}
	string shapeToString() const override {
		ostringstream ss;
		ss << shape::shapeToString();
		ss << "\n\tVolume: " << volume << "\n\tNumOfFaces: " << numOfFaces;
		ss << "\n\tNumOfFasecThroughVertices: " << NumOfFacesThroughVertices << "\n\tnumOfSidesInFace: " << numOfSidesInFace;	
		return ss.str();
	}

	double GetVolume() {
		return volume;
	}
	int GetNumOfFacesThroughVertices() {
		return NumOfFacesThroughVertices;
	}
	int GetNumOfSidesInFace() {
		return SidesCount;
	}
	virtual FlatShape* GetShapeOfSide() = 0;
	//setters
	virtual void SetVolume(double val) = 0;

	
};
class Rectangle : public FlatShape
{

public:
	Rectangle(double LengthSide_arg) : FlatShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Rectangle";
			this->SidesCount = 4;
			this->NumOfVertices = 4;
			this->Square = pow(LengthSide_arg, 2);
			this->Perimetr = LengthSide_arg * SidesCount;
			this->RadiusOfInscribedCircle = SideLength / 2;
			this->RadiusOfDescribedCircle = SideLength * (sqrt(2) / 2);
		}
		else {
			this->name = "Rectangle";
			this->SidesCount = 4;
			this->NumOfVertices = 4;
			this->Square = 0;
			this->Perimetr = 0;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
		}
		// методы вписаного круга........................................................
	}
	Rectangle() : FlatShape(0) {

	}
	void SetRadiusOfInscribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(val * 2);
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetRadiusOfDescribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(val * sqrt(2));
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetSquare(double val) override
	{
		if (val >= 0) {
			this->Square = val;
			setSideLength(sqrt(val));
		}
		else {
			cout << "\n\tError! Area must be > 0!";
		}
	}
	void SetPerimetr(double val) override {
		if (val >= 0) {
			setSideLength(val / SidesCount);
		}
	}
	
	void setSideLength(double val) override
	{
		if (val >= 0) {
			SideLength = val;
			this->name = "Rectangle";
			this->SidesCount = 4;
			this->NumOfVertices = 4;
			this->Square = pow(val, 2);
			this->Perimetr = val * SidesCount;
			this->RadiusOfInscribedCircle = SideLength / 2;
			this->RadiusOfDescribedCircle = SideLength * (sqrt(2) / 2);
		}
		else {
			cout << "\n\tError, legth of side can't be < 0!";
		}
	}

	
}; // Сделать радиусы вписаных кругов
class Triangle : public FlatShape
{

public:
	Triangle(double LengthSide_arg) : FlatShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Triangle";
			this->SidesCount = 3;
			this->NumOfVertices = 3;
			this->Square = (LengthSide_arg * LengthSide_arg * sqrt(3)) / 4.0;
			this->Perimetr = LengthSide_arg * SidesCount;
			this->RadiusOfInscribedCircle = LengthSide_arg / (2.0 * sqrt(3.0));
			this->RadiusOfDescribedCircle = LengthSide_arg / sqrt(3.0);
		}
		else {
			this->name = "Triangle";
			this->SidesCount = 3;
			this->NumOfVertices = 3;
			this->Square = 0;
			this->Perimetr = 0;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
		}
		// методы вписаного круга........................................................
	}
	Triangle() : FlatShape(0) {

	}
	void SetRadiusOfInscribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(val * (2.0 * sqrt(3.0)));
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetRadiusOfDescribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(val * sqrt(3.0));
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetSquare(double val) override
	{
		if (val >= 0) {
			this->Square = val;
			setSideLength(sqrt((0.25*val)/sqrt(3)));
		}
		else {
			cout << "\n\tError! Area must be > 0!";
		}
	}
	void SetPerimetr(double val) override {
		if (val >= 0) {
			setSideLength(val / SidesCount);
		}
	}

	void setSideLength(double val) override
	{
		if (val >= 0) {
			SideLength = val;
			this->name = "Triangle";
			this->SidesCount = 3;
			this->NumOfVertices = 3;
			this->Square = (val * val * sqrt(3)) / 4.0;
			this->Perimetr = val * SidesCount;
			this->RadiusOfInscribedCircle = val / (2.0 * sqrt(3.0));
			this->RadiusOfDescribedCircle = val / sqrt(3.0);
			
		}
		else {
			cout << "\n\tError, legth of side can't be < 0!";
		}
	}
};
class Pentagon : public FlatShape
{

public:
	Pentagon(double LengthSide_arg) : FlatShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Pentagon";
			this->SidesCount = 5;
			this->NumOfVertices = 5;
			this->Square = (5 * pow(LengthSide_arg, 2)) / 4 * sqrt(1+(2/sqrt(5)));
			this->Perimetr = LengthSide_arg * SidesCount;
			this->RadiusOfInscribedCircle = LengthSide_arg / 2 * sqrt(1 + (2 / sqrt(5)));
			this->RadiusOfDescribedCircle = LengthSide_arg / 2 * sqrt((5 + sqrt(5)) / 2);
		}
		else {
			this->name = "Pentagon";
			this->SidesCount = 5;
			this->NumOfVertices = 5;
			this->Square = 0;
			this->Perimetr = 0;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
		}
		// методы вписаного круга........................................................
	}
	Pentagon() : FlatShape(0) {

	}
	void SetRadiusOfInscribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength((2 / val) / sqrt(1 + (2 / sqrt(5))));
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetRadiusOfDescribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength((2 * val) / sqrt((5 + sqrt(5))/2));
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetSquare(double val) override
	{
		if (val >= 0) {
			this->Square = val;
			setSideLength((4*val)/(5*sqrt(1+(2/sqrt(5)))));
		}
		else {
			cout << "\n\tError! Area must be > 0!";
		}
	}
	void SetPerimetr(double val) override {
		if (val >= 0) {
			setSideLength(val / SidesCount);
		}
	}

	void setSideLength(double val) override
	{
		if (val >= 0) {
			SideLength = val;
			this->name = "Pentagon";
			this->SidesCount = 5;
			this->NumOfVertices = 5;
			this->Square = (5 * pow(val, 2)) / 4 * sqrt(1 + (2 / sqrt(5)));
			this->Perimetr = val * SidesCount;
			this->RadiusOfInscribedCircle = val / 2 * sqrt(1 + (2 / sqrt(5)));
			this->RadiusOfDescribedCircle = val / 2 * sqrt((5 + sqrt(5)) / 2);

		}
		else {
			cout << "\n\tError, legth of side can't be < 0!";
		}
	}
};
class Hexagon : public FlatShape
{

public:
	Hexagon(double LengthSide_arg) : FlatShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Hexagon";
			this->SidesCount = 6;
			this->NumOfVertices = 6;
			this->Square = (3 * sqrt(3) * pow(LengthSide_arg, 2)) / 2;
			this->Perimetr = LengthSide_arg * SidesCount;
			this->RadiusOfInscribedCircle = (sqrt(3) * LengthSide_arg) / 2;
			this->RadiusOfDescribedCircle = LengthSide_arg;
		}
		else {
			this->name = "Hexagon";
			this->SidesCount = 6;
			this->NumOfVertices = 6;
			this->Square = 0;
			this->Perimetr = 0;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
		}
		// методы вписаного круга........................................................
	}
	Hexagon() : FlatShape(0) {

	}
	void SetRadiusOfInscribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(2 * val / sqrt(3));
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetRadiusOfDescribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(val);
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetSquare(double val) override
	{
		if (val >= 0) {
			this->Square = val;
			setSideLength(sqrt((2 * val) / (3 * sqrt(3))));
		}
		else {
			cout << "\n\tError! Area must be > 0!";
		}
	}
	void SetPerimetr(double val) override {
		if (val >= 0) {
			setSideLength(val / SidesCount);
		}
	}

	void setSideLength(double val) override
	{
		if (val >= 0) {
			SideLength = val;
			this->name = "Hexagon";
			this->SidesCount = 6;
			this->NumOfVertices = 6;
			this->Square = (3 * sqrt(3) * pow(val , 2)) / 2;
			this->Perimetr = val * SidesCount;
			this->RadiusOfInscribedCircle = (sqrt(3) * val) / 2;
			this->RadiusOfDescribedCircle = val;
		}
		else {
			cout << "\n\tError, legth of side can't be < 0!";
		}
	}
};
class Circle : public shape
{
protected:
	double PerimetrOfCircle;
	double Radius;
public:
	Circle(double Radius_arg) : shape(0)
	{
		if (Radius_arg >= 0) {// Написание круга
			this->name = "Circle";
			this->SidesCount = 0;
			this->NumOfVertices = 0;
			this->Square = Radius_arg * Radius_arg * P;
			this->PerimetrOfCircle = (P * Radius_arg)*2;
			this->Radius = Radius_arg;
		}
		else {
			this->name = "Circle";
			this->SidesCount = 0;
			this->NumOfVertices = 0;
			this->Square = 0;
			this->PerimetrOfCircle = 0;
			this->Radius = 0;
		}
		// методы вписаного круга........................................................
	}
	Circle() : shape(0) {
		Radius = 0;
		PerimetrOfCircle = 0;
	}
	void SetRadius(double val)
	{
		if (val >= 0) {
			Radius = val;
			this->Square = P * Radius * Radius;
			this->PerimetrOfCircle = (P * val)*2;
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetSquare(double val) override
	{
		if (val >= 0) {
			SetRadius(sqrt(val/P));
		}
		else {
			cout << "\n\tError! Area must be > 0!";
		}
	}
	void SetPerimetr(double val) {
		if (val >= 0) {
			SetRadius(val / (P)*2);
		}
	}

		string shapeToString() const {
		ostringstream ss;
		ss << "\n\tName: " << name;
		ss << "\n\tArea: " << Square;
		ss << "\n\tRadius: " << Radius << "\n\tLengthOfCircle: " << PerimetrOfCircle;
		return ss.str();
		}
};


////////////////////////////////////// 3D SHapes!!!

class Cube : public VolumeShape
{
public:
	Cube(double LengthSide_arg) : VolumeShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Cube";
			this->SidesCount = 12;
			this->NumOfVertices = 8;
			numOfFaces = 6;
			this->Square = pow(LengthSide_arg, 2) * numOfFaces;
			volume = pow(LengthSide_arg, 3);
			NumOfFacesThroughVertices = 3;
			numOfSidesInFace = 4;
			this->RadiusOfInscribedCircle = SideLength / 2;
			this->RadiusOfDescribedCircle = SideLength * (sqrt(2) / 2);
#ifdef WathcConstructorAndDestructorInformation
			cout << "\tCube created";
#endif
		}
		else {
			this->name = "Cube";
			this->SidesCount = 12;
			this->NumOfVertices = 8;
			this->Square = 0;
			volume = 0;
			numOfFaces = 6;
			NumOfFacesThroughVertices = 3;
			numOfSidesInFace = 4;
#ifdef WathcConstructorAndDestructorInformation
			cout << "\tVolumeSHape created";
#endif
		}

		
	}
	// setters
	void setSideLength(double val) override {
		this->SideLength = val;
		this->Square = pow(SideLength, 2) * numOfFaces;
		this->volume = pow(SideLength, 3);
		this->RadiusOfInscribedCircle = SideLength / 2;
		this->RadiusOfDescribedCircle = SideLength * (sqrt(2) / 2);
		return;
	}
	void SetVolume(double val) override {
		if (val >= 0) {
			setSideLength(cbrt(val));
		}
		return;
	}
	void SetSquare(double val) override {
		setSideLength(sqrt(val / 6));
	}
	void SetRadiusOfInscribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(val * 2);
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetRadiusOfDescribedCircle(double val) override
	{
		if (val >= 0) {
			setSideLength(val * sqrt(2));
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}
	// getters
	FlatShape* GetShapeOfSide() override{
		Rectangle* R = new Rectangle(SideLength); // 
		return R;
	}
};
class Tetraeder : public VolumeShape
{
protected:
	
public:
	Tetraeder(double LengthSide_arg) : VolumeShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Tetraeder";
			this->SidesCount = 6;
			this->NumOfVertices = 4;
			numOfFaces = 4;
			this->Square = ((LengthSide_arg * LengthSide_arg * sqrt(3)) / 4.0) * numOfFaces;
			volume = ((pow(LengthSide_arg, 3) * sqrt(2)))/12;
			NumOfFacesThroughVertices = 3;
			numOfSidesInFace = 3;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
			cout << "\tTetraeder created";
		}
		else {
			this->name = "Tetraeder";
			this->SidesCount = 6;
			this->NumOfVertices = 4;
			this->Square = 0;
			volume = 0;
			numOfFaces = 6;
			NumOfFacesThroughVertices = 3;
			numOfSidesInFace = 3;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
			cout << "\tVolumeSHape created";
		}

	}
	// setters
	void setSideLength(double val) override {
		this->SideLength = val;
		this->name = "Tetraeder";
		this->SidesCount = 6;
		this->NumOfVertices = 4;
		numOfFaces = 4;
		this->Square = ((val * val * sqrt(3)) / 4.0) * numOfFaces;
		volume = ((pow(val, 3) * sqrt(2))) / 12;
		NumOfFacesThroughVertices = 3;
		numOfSidesInFace = 3;
		return;
	}
	void SetVolume(double val) override {
		if (val >= 0) {
			setSideLength(cbrt((12 * val / sqrt(2))));
		}
		return;
	}
	void SetSquare(double val) override {
		setSideLength(sqrt(val / sqrt(3)));
	}
	
	// getters
	FlatShape* GetShapeOfSide() override {
		Triangle* R = new Triangle(SideLength); // 
		return R;
	}
	friend void DeleteFlatSHapeObject(FlatShape* obj);
};
class Oktaeder : public VolumeShape
{
protected:

public:
	Oktaeder(double LengthSide_arg) : VolumeShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Oktaeder";
			this->SidesCount = 12;
			this->NumOfVertices = 6;
			numOfFaces = 8;
			this->Square = 2 * pow(LengthSide_arg, 2) * sqrt(3);
			volume = (pow(LengthSide_arg, 3) * sqrt(2)) / 3;
			NumOfFacesThroughVertices = 4;
			numOfSidesInFace = 3;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
			cout << "\tTetraeder created";
		}
		else {
			this->name = "Oktaeder";
			this->SidesCount = 12;
			this->NumOfVertices = 6;
			this->Square = 0;
			volume = 0;
			numOfFaces = 6;
			NumOfFacesThroughVertices = 4;
			numOfSidesInFace = 3;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
			cout << "\tVolumeSHape created";
		}

	}
	// setters
	void setSideLength(double val) override {
		this->SideLength = val;
		this->name = "Oktaeder";
		this->SidesCount = 12;
		this->NumOfVertices = 6;
		numOfFaces = 8;
		this->Square = 2 * pow(val, 2) * sqrt(3);
		volume = (pow(val, 3) * sqrt(2)) / 3;
		NumOfFacesThroughVertices = 4;
		numOfSidesInFace = 3;
		this->RadiusOfInscribedCircle = 0;
		this->RadiusOfDescribedCircle = 0;
		return;
	}
	void SetVolume(double val) override {
		if (val >= 0) {
			setSideLength(cbrt(3 * val / sqrt(2)));
		}
		return;
	}
	void SetSquare(double val) override {
		setSideLength(sqrt(val / (2*sqrt(3))));
	}

	// getters
	FlatShape* GetShapeOfSide() override {
		Triangle* R = new Triangle(SideLength); // 
		return R;
	}
	friend void DeleteFlatSHapeObject(FlatShape* obj);
};
class Dodekaeder : public VolumeShape
{
protected:

public:
	Dodekaeder(double LengthSide_arg) : VolumeShape(LengthSide_arg)
	{
		if (LengthSide_arg >= 0) {
			this->name = "Dodekaeder";
			this->SidesCount = 30;
			this->NumOfVertices = 20;
			numOfFaces = 12;
			this->Square = 3 * pow(LengthSide_arg, 2) * sqrt((25 + 10 * sqrt(5)));
			volume = (pow(LengthSide_arg, 3)/4)*(15+7*sqrt(5));
			NumOfFacesThroughVertices = 3;
			numOfSidesInFace = 5;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
			cout << "\Dodekaeder created";
		}
		else {
			this->name = "Dodekaeder";
			this->SidesCount = 30;
			this->NumOfVertices = 20;
			this->Square = 0;
			volume = 0;
			numOfFaces = 12;
			NumOfFacesThroughVertices = 3;
			numOfSidesInFace = 5;
			this->RadiusOfInscribedCircle = 0;
			this->RadiusOfDescribedCircle = 0;
			cout << "\tVolumeSHape created";
		}

	}
	// setters
	void setSideLength(double val) override {
		this->SideLength = val;
		this->name = "Dodekaeder";
		this->SidesCount = 30;
		this->NumOfVertices = 20;
		numOfFaces = 12;
		this->Square = 3 * pow(val, 2) * sqrt((25 + 10 * sqrt(5)));
		volume = (pow(val, 3) / 4) * (15 + 7 * sqrt(5));
		NumOfFacesThroughVertices = 3;
		numOfSidesInFace = 5;
		this->RadiusOfInscribedCircle = 0;
		this->RadiusOfDescribedCircle = 0;
		return;
	}
	void SetVolume(double val) override {
		if (val >= 0) {
			setSideLength(cbrt((4*val)/(15+7*sqrt(5))));
		}
		return;
	}
	void SetSquare(double val) override {
		setSideLength(sqrt(val / (3*sqrt(25+10*sqrt(5)))));
	}

	// getters
	FlatShape* GetShapeOfSide() override {
		Pentagon* R = new Pentagon(SideLength); // 
		return R;
	}
	friend void DeleteFlatSHapeObject(FlatShape* obj);
};
class Sphere : public shape
{
protected:
	double PerimetrOfCircle;
	double Radius;
	double volume;
public:
	Sphere(double Radius_arg) : shape(0)
	{
		if (Radius_arg >= 0) {// Написание круга
			this->name = "Sphere";
			this->SidesCount = 0;
			this->NumOfVertices = 0;
			this->Square = Radius_arg * Radius_arg * P * 4;
			this->PerimetrOfCircle = (P * Radius_arg) * 2;
			this->Radius = Radius_arg;
			this->volume = (4 / 3) * P * pow(Radius_arg, 3);
		}
		else {
			this->name = "Sphere";
			this->SidesCount = 0;
			this->NumOfVertices = 0;
			this->Square = 0;
			this->PerimetrOfCircle = 0;
			this->Radius = 0;
			this->volume = 0;
		}
		// методы вписаного круга........................................................
	}
	Sphere() : shape(0) {
		Radius = 0;
		PerimetrOfCircle = 0;
		volume = 0;
	}
	void SetRadius(double val)
	{
		if (val >= 0) {
			Radius = val;
			this->Square = P * Radius * Radius * 4;
			this->PerimetrOfCircle = (P * val) * 2;
			this->volume = (4 / 3) * P * pow(val, 3);
		}
		else {
			cout << "\n\tError! Radius must be > 0!";
		}
	}

	void SetSquare(double val) override
	{
		if (val >= 0) {
			SetRadius(sqrt(val / (P*4)));
		}
		else {
			cout << "\n\tError! Area must be > 0!";
		}
	}
	void SetPerimetr(double val) {
		if (val >= 0) {
			SetRadius(cbrt(3*val/(4*P)));
		}
	}

	string shapeToString() const {
		ostringstream ss;
		ss << "\n\tName: " << name;
		ss << "\n\tArea: " << Square;
		ss << "\n\tRadius: " << Radius << "\n\tLength of circle: " << PerimetrOfCircle;
		ss << "\n\tVolumeOfSphere: " << volume;
		return ss.str();
	}


	shape* GetShapeOfSide() {
		Circle* R = new Circle(SideLength); // 
		return R;
	}
};
void GlobalInterface(); // Глобальный интерфейс
int ShapeProcessing(FlatShape* Shape, double val);
int ShapeProcessing(VolumeShape* Shape, double val);
int ShapeProcessing(Circle* Shape, double val);
int ShapeProcessing(Sphere* Shape, double val);

int shape::objectCount = 0;
int main()
{
	GlobalInterface();
	return 0;
}

void GlobalInterface()
{
	while (true)
	{
		string ShapeName;
		string Variables[10] = { "Square", "Triangle", "Pentagon", "Hexagon", "Circle", "Tetraeder", "Cube", "Oktaeder", "Dodekaeder" , "Sphere" };
		double LengthVal;
		cout << "\n\tEnter shape you want explore and her side length: ";
		cin >> ShapeName >> LengthVal;
		int id;
		for (id = 0; id < 10; id++) {
			if (ShapeName == Variables[id]) {
				break;
			}
		}
		if (id == 10 || LengthVal <= 0) {
			cout << "\n\tIncorrect Shape params!";
			continue;
		}
		else {
			cout << "\n\tSuccess! You have shape \"" << ShapeName << "\" her side length: " << LengthVal;
		}

		if (ShapeName == "Square") {
			Rectangle A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Triangle") {
			Triangle A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Pentagon") {
			Pentagon A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Hexagon") {
			Hexagon A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Circle") {
			Circle A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}

		if (ShapeName == "Cube") {
			Cube A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Tetraeder") {
			Tetraeder A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Oktaeder") {
			Oktaeder A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Dodekaeder") {
			Dodekaeder A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}
		if (ShapeName == "Sphere") {
			Sphere A(LengthVal);
			ShapeProcessing(&A, LengthVal);
		}

	}

}
void DeleteFlatSHapeObject(FlatShape* obj) { // Дружественная функция для удаления FlatShape
	delete obj;
	obj = nullptr;
}
void DeleteFlatSHapeObject(shape* obj) { // Дружественная функция для удаления FlatShape
	delete obj;
	obj = nullptr;
}
int ShapeProcessing(FlatShape* Shape, double val) {
	string select;

	while (true)
	{
		cout << "\n\tYou created your shape! Now, you can apply a few modification.";
		cout << endl << endl << "\tEnter \"/SetArea (value)\" to set area for your shape\n\t";
		cout << "Enter \"/SetPerimetr (value)\" to set perimetr for your shape\n\t";
		cout << "Enter \"/SetPerimetr (value)\" to set perimetr for your shape\n\t";
		cout << "Enter \"/SetSideLength (value)\" to set length of side for your shape\n\t";
		cout << "Enter \"/SetRadiusOfDescribedCircle (value)\" to setradius of described circle for your shape\n\t";
		cout << "Enter \"/SetRadiusOfInscribedCircle (value)\" to setradius of inscribed circle for your shape\n\t";
		
	
	}

	return 0;
}
int ShapeProcessing(VolumeShape* Shape, double val) {
	cout << Shape->shapeToString();

	return 0;
}
int ShapeProcessing(Circle* Shape, double val) {
	cout << Shape->shapeToString();

	return 0;
}
int ShapeProcessing(Sphere* Shape, double val) {
	cout << Shape->shapeToString();

	return 0;
}