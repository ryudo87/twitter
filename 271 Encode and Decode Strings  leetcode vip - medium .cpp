Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings.

Machine 1 (sender) has the function:

string encode(vector<string> strs) {
  // ... your code
  return encoded_string;
}
Machine 2 (receiver) has the function:

vector<string> decode(string s) {
  //... your code
  return strs;
}
 

So Machine 1 does:

string encoded_string = encode(strs);
 

and Machine 2 does:

vector<string> strs2 = decode(encoded_string);
 

strs2 in Machine 2 should be the same as strs in Machine 1.

Implement the encode and decode methods.

Note:

The string may contain any possible characters out of 256 valid ascii characters. Your algorithm should be generalized enough to work on any possible characters.
Do not use class member/global/static variables to store states. Your encode and decode algorithms should be stateless.
Do not rely on any library method such as eval or serialize methods. You should implement your own encode/decode algorithm.
 

这道题让我们给字符加码再解码，先有码再无码，然后题目中并没有限制我们加码的方法，那么我们的方法只要能成功的把有码变成无码就行了，具体变换方法我们自己设计。由于我们需要把一个字符串集变成一个字符串，然后把这个字符串再还原成原来的字符串集，最开始我想能不能在每一个字符串中间加个空格把它们连起来，然后再按空格来隔开，但是这种方法的问题是原来的一个字符串中如果含有空格，那么还原的时候就会被分隔成两个字符串，所以我们必须还要加上长度的信息，我们的加码方法是长度+"/"+字符串，比如对于"a","ab","abc"，我们就变成"1/a2/ab3/abc"，那么我们解码的时候就有规律可寻，先寻找"/"，然后之前的就是要取出的字符个数，从“/"后取出相应个数即可，以此类推直至没有"/"了，这样我们就得到高清无码的字符串集了

class Codec {
public:
    // Encodes a list of strings to a single string.
    string encode(vector<string>& strs) {
        string res = "";
        for (auto a : strs) {
            res.append(to_string(a.size())).append("/").append(a);
        }
        return res;
    }
    // Decodes a single string to a list of strings.
    vector<string> decode(string s) {
        vector<string> res;
        int i = 0;
        while (i < s.size()) {
            auto found = s.find("/", i);
            int len = stoi(s.substr(i, found - i));
            res.push_back(s.substr(found + 1, len));
            i = found + len + 1;
        }
        return res;
    }
};
