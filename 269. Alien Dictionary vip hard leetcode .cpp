class Solution {
public:
    string alienOrder(vector<string>& words) {
        set<pair<char, char>> st; //TreeSet 来保存这些 pair
        unordered_set<char> ch; //HashSet 来保存所有出现过的字母 
        vector<int> in(256);
        queue<char> q;
        string res;
        for (auto a : words) ch.insert(a.begin(), a.end()); //先遍历单词集，把所有字母先存入 HashSet
        for (int i = 0; i < (int)words.size() - 1; ++i) {
            int mn = min(words[i].size(), words[i + 1].size()), j = 0;
            //每两个相邻的单词比较，找出顺序 pair，然后我们根据这些 pair 来赋度，我们把 HashSet 中入度为0的字母都排入 queue 中
            for (; j < mn; ++j) { 
                if (words[i][j] != words[i + 1][j]) {
                    st.insert(make_pair(words[i][j], words[i + 1][j]));
                    break;
                }
            }
            if (j == mn && words[i].size() > words[i + 1].size()) return "";
        }
        
        for (auto a : st) ++in[a.second]; //我们根据这些 pair 来赋度
        
        for (auto a : ch) {
            if (in[a] == 0) {
                q.push(a);
                res += a;
            } 
        }
        
        //然后开始遍历，如果字母在 TreeSet 中存在，则将其 pair 中对应的字母的入度减1，若此时入度减为0了，则将对应的字母排入 queue 中并且加入结果 res 中，直到遍历完成，
        while (!q.empty()) {
            char c = q.front(); q.pop();
            for (auto a : st) {
                if (a.first == c) {
                    --in[a.second];
                    if (in[a.second] == 0) {
                        q.push(a.second);
                        res += a.second;
                    }
                }
            }
        }
        return res.size() == ch.size() ? res : "";
    }
};
