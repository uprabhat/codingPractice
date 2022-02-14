#include <iostream>
#include <cmath>
using namespace std;

#if 0
void printLogarithm (double x) {
    if (x <= 0.0) {
        cout << "Positive numbers only, please." << endl;
        return;
    }
    double result = log (x);
    cout << "The log of x is " << result;
}

double distance (double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double dsquared = dx*dx + dy*dy;
    double result = sqrt (dsquared);
    return result;
}
//Overloading//
double area (double radius) {
    return acos(-1.0) * radius * radius;
}
double area (double xc, double yc, double xp, double yp) {
    return area (distance (xc, yc, xp, yp));
}
// main: generate some simple output
int main ()
{
    cout << "Hello, world." << endl;

    int hour, minute;
    hour = 11;
    minute = 59;
    cout << "Number of minutes since midnight: ";
    cout << hour*60 + minute << endl;
    cout << "Fraction of the hour that has passed: ";
    cout << minute/60 << endl;
    printLogarithm(1024);
    double result;
    result=area(2.3);
    cout << endl << result << " : ";
    result=area(1.0, 2.0, 4.0, 6.0);
    cout << result;
    cout << endl;
    return 0;
}
#endif

#if 0
//// Strings ////
int main () {
    string myStr="Utkarsh";
    cout << myStr << endl;
    int len=myStr.length();
    int index=myStr.find('a');
    cout << myStr.find('ar');
    myStr=(string)"Utkarsh" + (string)"Prabhat";
    cout << myStr << endl;
    string newStr=myStr.substr(0,7);
    if (newStr == "Utkarsh") {
        cout << "Yup that's me\n";
    }
}
#endif

#if 0
/// Vectors ///
#include <vector>

void printVector (const vector<int>& vec) { //pass reference//
    for (int i = 0; i<vec.size(); i++) {
        cout << vec[i] << " ";
    }
}
int main() {
    vector<int> ct(4); //uninitialized
    vector<int> cnt(4,0);
    vector<int> cpCnt=cnt; //copy with the same elements & size
    for(int i=0;i<cpCnt.size();i++) {
        cpCnt[i]=i;
        cout << i << ":" << cpCnt[i]<<endl;
    }
    //Resizing//
    vector<int> inCnt;
    int num;
    //getline(cin,num); //Error : only for strings?
    cout << "Enter integers ending on -1\n";
    cin>>num;
    if (cin.good()==false) { cout << "Not an int"; return -1;}
    while(num!=-1) {
        cout << "Got:" << num << endl;
        inCnt.push_back(num);
        cin >> num;
    }
    cout<<"Array  has "<<inCnt.size()<<" Numbers\n";
    printVector(inCnt);

    cout << endl;
}
#endif

#if 0
/// Member functions ///
struct Time {
  int hour, minute;
  double second;
    
  //Constructor
  Time (int hour, int min, double secs);
  Time (double secs);

  void print () const;
  void increment (double secs);
  bool after (const Time& time2) const;
  Time add (const Time& t2) const;

  double convertToSeconds () const;
};
Time::Time (int h, int m, double s)
{
  hour = h;  minute = m;  second = s;
}

Time::Time (double secs)
{
  hour = (int) (secs / 3600.0);
  secs -= hour * 3600.0;
  minute = (int) (secs / 60.0);
  secs -= minute * 60.0;
  second = secs;
}

void Time::print () const
{
  cout << hour << ":" << minute << ":" << second << endl; //implicit members
}

void Time::increment (double secs)
{
  second += secs;

  while (second >= 60.0) {
    second -= 60.0;
    minute += 1;
  }
  while (minute >= 60) {
    minute -= 60;
    hour += 1;
  }
}

int main() {
    //Time currentTime = { 9, 14, 30.0 };
    Time currentTime (9,14,30);
    currentTime.increment(500.0);
    currentTime.print();
    return 0;
}
#endif

#if 0
//Class//
class Complex
{
  double real, imag;
  double mag, theta;
  bool cartesian, polar;

  public:
    Complex () { cartesian = false; polar = false; }
    Complex (double r, double i) { real = r; imag = i; cartesian = true; polar = false;}
    double getReal();
    void calculateCartesian();
    void calculatePolar();
    void printCartesian();
    void printPolar();
    double getImag();
    double getMag();
    double getTheta();
};

void Complex::printCartesian ()
{
cout << getReal() << " + " << getImag() << "i" << endl;
}
void Complex::printPolar ()
{
cout << getMag() << " e^ " << getTheta() << "i" << endl;
}
double Complex::getReal ()
{
  if (cartesian == false) calculateCartesian ();
  return real;
}

double Complex::getImag ()
{
  if (cartesian == false) calculateCartesian ();
  return imag;
}

double Complex::getMag ()
{
  if (polar == false) calculatePolar ();
  return mag;
}

double Complex::getTheta ()
{
  if (polar == false) calculatePolar ();
  return theta;
}

void Complex::calculateCartesian ()
{
  real = mag * cos (theta);
  imag = mag * sin (theta);
  cartesian = true;
}

void Complex::calculatePolar ()
{
  assert (cartesian);
  mag = sqrt (real* real + imag * imag);
  theta = atan2 (imag, real);
  polar = true;
}

int main() {
  Complex cmp(2,3);
  cmp.printPolar();

  return 0;
}
#endif

#if 1
void increment(int& val) { //takes reference - could use pointer as well
  val++;
}

int main() {
  //Pointers//
  //int* b =new int[2];
  //char * buf= new(b) char[8]; //specify address target as well
  char * buf= new char[8]; //allocation of memory 8 times of the char memory -> calls constructor
  memcpy(buf,"Utkarsh\n",8);
  cout << buf;
  delete[] buf; //also calls destructor

  //Pass by reference //
  int a=8;
  int& b=a;
  increment(b);
  cout << b << endl;


  return 0;
}
#endif