#include <string>
#include <vector>

using namespace std;

class Candlestick {
public:
  string date;
  float open;
  float high;
  float close;
  Candlestick(string _date, float _open, float _high, float _close) : date(_date), open(_open), high(_high), close(_close) {}
};

class DataPoint {
    private:
        int x;
        int y;
    public: 
        DataPoint(float _x, float _y) : x(_x), y(_y) {}
};

class CandlestickProcessor {
public:
  static float get_average_mean(const vector<DataPoint> &candlesticks);
  static float get_lowest(const vector<DataPoint> &candlesticks);
  static float get_highest(const vector<DataPoint> &candlesticks);
};

class Plotter {

public: 
    static void plot(const vector<DataPoint> &candlesticks);
};
