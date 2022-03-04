#include <iostream>
#include <map>
#include <fstream>
//#include <cstdlib>
using namespace std;

class ArithmeticEncodingTable
{
  private:
    double low;
    double high;
    double delta;
  public:
    ArithmeticEncodingTable();
    ~ArithmeticEncodingTable();
    double get_low();
    double get_high();
    double get_delta();
    void set_low(double low);
    void set_high(double high);
    void set_delta(double delta);
};

class ArithmeticEncoding
{
  private:
    std::map<char, ArithmeticEncodingTable> CodeTable;

  public:
    ArithmeticEncoding(/* args */);
    ~ArithmeticEncoding();
    void CreateTable();
    double Encoding(string encode);
    string Decoding(double decode);
};

ArithmeticEncodingTable::ArithmeticEncodingTable(/* args */)
{
    low = 0.0;
    high = 1.0;
    delta = 1.0;
}

ArithmeticEncodingTable::~ArithmeticEncodingTable()
{
}

double ArithmeticEncodingTable::get_low()
{
    return low;
}

double ArithmeticEncodingTable::get_high()
{
    return high;
}

double ArithmeticEncodingTable::get_delta()
{
    return delta;
}

void ArithmeticEncodingTable::set_low(double low)
{
    this->low = low;
}

void ArithmeticEncodingTable::set_high(double high)
{
    this->high = high;
}

void ArithmeticEncodingTable::set_delta(double delta)
{
    this->delta = delta;
}

ArithmeticEncoding::ArithmeticEncoding(/* args */)
{
}

ArithmeticEncoding::~ArithmeticEncoding()
{
}

void ArithmeticEncoding::CreateTable()
{
    ofstream in("table.txt");
    if (!in)
    {
        cout << "error" << endl;
        return;
    }

    int codenum;
    char code;
    double delta;
    double low = 0.0;
    double high = 0.0;

    cout << "please input number of the char:" << endl;
    cin >> codenum;
    in << codenum;
    for (int i = 0; i < codenum; i++)
    {
        cout << "please input " << i << "th char:";
        cin>> code;
        in << code;
        cout << "please input " << i << "th probability:";
        cin >> delta;
        in << delta;
        ArithmeticEncodingTable table;
        table.set_delta(delta);
        low = high;
        table.set_low(low);
        high = low + delta;
        table.set_high(high);
        CodeTable.insert(std::pair<char, ArithmeticEncodingTable>(code, table));
    }
}
double ArithmeticEncoding::Encoding(string encode)
{

    double low = 0.0;
    double high = 1.0;
    for (string::iterator it = encode.begin(); it != encode.end(); it++)
    {
        double delta = high - low;
        high = low + delta * CodeTable[*it].get_high();
        low = low + delta * CodeTable[*it].get_low();
    }
    return low;
}

string ArithmeticEncoding::Decoding(double value)
{
    double low, high;
    double prelow = 0.0, prehigh = 1.0;
    string symbol = "";
    while (true)
    {
        low = prelow;
        high = prehigh;
        for (std::map<char, ArithmeticEncodingTable>::iterator i = CodeTable.begin(); i != CodeTable.end(); ++i)
        {
            double delta = high - low;
            high = low + delta * (i->second).get_high();
            low = low + delta * (i->second).get_low();

            if (low < value && high > value)
            {
                prelow = low;
                prehigh = high;
                symbol += (i->first);
                break;
            }
            else if (low == value)
            {
                symbol += (i->first);
                return symbol;
            }
            else
            {
                low = prelow;
                high = prehigh;
            }
        }

    }
}

int main()
{

    ArithmeticEncoding AE;
    string s;
    cout<<"Enter the string: "<<endl;
    cin>>s;
    AE.CreateTable();

    double out = AE.Encoding(s);
    //cout << endl;
    cout << "Encoded value: "<< out << endl;

    cout<<"Decoded string:"<<endl;
    cout << AE.Decoding(out)<<endl;
    system("pause");

    return 0;
}
