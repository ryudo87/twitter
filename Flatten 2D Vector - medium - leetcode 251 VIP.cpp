251.Flatten 2D Vector
Design and implement an iterator to flatten a 2d vector. It should support the following operations: next and hasNext.

Example:

Vector2D iterator = new Vector2D([[1,2],[3],[4]]);

iterator.next(); // return 1
iterator.next(); // return 2
iterator.next(); // return 3
iterator.hasNext(); // return true
iterator.hasNext(); // return true
iterator.next(); // return 4
iterator.hasNext(); // return false
 

Notes:

Please remember to RESET your class variables declared in Vector2D, as static/class variables are persisted across multiple test cases. 
Please see here for more details.
You may assume that next() call will always be valid, that is, 
there will be at least a next element in the 2d vector when next() is called.

那么最简单的方法就是将二维数组按顺序先存入到一个一维数组里，然后此时只要维护一个变量i来记录当前遍历到的位置，
hasNext 函数看当前坐标是否小于元素总数，next 函数即为取出当前位置元素，坐标后移一位
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d) {
        for (auto a : vec2d) {
            v.insert(v.end(), a.begin(), a.end());
        }    
    }
    int next() {
        return v[i++];
    }
    bool hasNext() {
        return i < v.size();
    }
private:
    vector<int> v;
    int i = 0;
};


下面我们来看另一种解法，不直接转换为一维数组，而是维护两个变量x和y，我们将x和y初始化为0，
对于 hasNext 函数，我们检查当前x是否小于总行数，y是否和当前行的列数相同，如果相同，说明要转到下一行，则x自增1，y初始化为0，
若此时x还是小于总行数，说明下一个值可以被取出来，那么在 next 函数就可以直接取出行为x，列为y的数字，并将y自增1，
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d): data(vec2d), x(0), y(0) {}

    int next() {
        hasNext();
        return data[x][y++];
    }
    bool hasNext() {
        while (x < data.size() && y == data[x].size()) {
            ++x; 
            y = 0;
        }
        return x < data.size();
    }    
private:
    vector<vector<int>> data;
    int x, y;
};



题目中的 Follow up 让我们用 interator 来做，C++中 iterator 不像 Java 中的那么强大，自己本身并没有包含 next 和 hasNext 函数，所以我们得自己来实现，我们将x定义为行的 iterator，再用个 end 指向二维数组的末尾，定义一个整型变量y来指向列位置，实现思路和上一种解法完全相同，只是写法略有不同，参见代码如下：

 

解法三：
class Vector2D {
public:
    Vector2D(vector<vector<int>>& vec2d): x(vec2d.begin()), end(vec2d.end()) {}
    
    int next() {
        hasNext();
        return (*x)[y++];
    }
    bool hasNext() {
        while (x != end && y == (*x).size()) {
            ++x; 
            y = 0;
        }
        return x != end;
    }
private:
    vector<vector<int>>::iterator x, end;
    int y = 0;
};

