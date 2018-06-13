#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

typedef std::vector<int> ArrayType;

static void printArray(const ArrayType& arr)
{
    std::for_each(arr.begin(), arr.end(), [](ArrayType::value_type val){
        std::cout << val << ' ';
    });
}

static bool isNormalNumber(int val)
{
    return val > 0;
}

class SubArray {
    public:
        SubArray()
        :_max(0), _min(0)
        {}

        bool operator<(const SubArray& rhs) const
        {
            return _data.size() < rhs._data.size();
        }

        void add(int value)
        {
            _data.push_back(value);

            auto it = std::max_element(_data.begin(), _data.end());
            _max = *it;
            it = std::min_element(_data.begin(), _data.end());
            _min = *it;
        }

        bool contain(int value) const
        {
            bool result = false;

            for (auto cur : _data)
            {
                if (cur == value)
                {
                    result = true;
                    break;
                }
            }

            return result;
        }

        bool match() const 
        {
            return _data.size() > 1 && _data.size() == (_max - _min + 1);
        }

        void print() const
        {
            std::cout << this << " = ";
            printArray(_data);
            std::cout << std::endl;;
        }

    private:
        ArrayType _data;
        int _max;
        int _min;
};

class ArrayParser {
    public:
        ArrayParser(ArrayType array);

        void parse();
        void printResult();

    private:
        ArrayType _array;
        std::multiset<SubArray> _resultSubArray;
};

ArrayParser::ArrayParser(ArrayType array)
: _array(array)
{}

void ArrayParser::parse()
{
    for (int i = 0; i < _array.size(); ++i)
    {
        SubArray subArray;

        for (int j = i; j < _array.size(); ++j)
        {
            if (isNormalNumber(_array[j]) && !subArray.contain(_array[j]))
            {
#ifdef DEBUG
                std::cout << "Adding val=" << _array[j] << std::endl;
#endif
                subArray.add(_array[j]);
#ifdef DEBUG
                std::cout << "Current subarray:";
                subArray.print();
                std::cout << std::endl;
#endif
                if (subArray.match())
                {
#ifdef DEBUG
                    std::cout << "Array matches:";
                    subArray.print();
                    std::cout << std::endl;
                    std::cout << "inserted!!! size=" << _resultSubArray.size() << std::endl;
#endif
                    _resultSubArray.insert(subArray);
                }
            }
            else
            {
#ifdef DEBUG
                std::cout << "discarding " << _array[j] << ", index=" << j << std::endl;
#endif
                break;
            }
        }
    }
}

void ArrayParser::printResult()
{
    if (_resultSubArray.empty())
    {
        std::cout << "No matches found..." << std::endl;
        return;
    }

    std::for_each(_resultSubArray.begin(), _resultSubArray.end(), [](const SubArray& val)
    {
        val.print();
    });

    auto bestMatches = _resultSubArray.lower_bound(*_resultSubArray.rbegin());

    std::cout << "Best match(es):" << std::endl;
    std::for_each(bestMatches, _resultSubArray.end(), [](const SubArray& val)
    {
        val.print();
    });
}


int main()
{
    ArrayType array0{1, 2, 0, 3, 4, 5, -2, -4, 0, 4, 5, 6, 3, 2, 7, 6, 8, 5, 4};
    ArrayType array1{1, 3, 4, 2, -1, 5, 7, 6};

    std::cout << "Processing array: ";
    printArray(array1);
    std::cout << std::endl;

    ArrayParser parser{array1};
    parser.parse();
    parser.printResult();

    return 0;
}