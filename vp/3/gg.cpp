#include <bits/stdc++.h>
using namespace std;
const int N = 310;
const int p[9][9]= {
  1,1,1,1,1,1,1,0,0,
  1,0,0,0,0,0,0,0,0,
  1,0,0,0,0,0,0,0,0,
  1,1,1,0,0,0,0,0,0,
  1,1,1,0,0,0,0,0,0,
  1,1,1,0,0,0,0,0,0,
  1,1,1,1,1,1,1,0,0,
  1,1,1,1,1,1,1,1,1,
  1,1,1,1,1,1,1,1,1
};

string s;
char str[N];
map<string, string> mp;

string init(string s) {
  string ans = "";
  for(int i = 0; i < s.length(); ++i) {
    if(s[i] >= 'A' && s[i] <= 'Z') ans += s[i] - 'A' + 'a';
    else if(s[i] != ' ') ans += s[i];
  }
  return ans;
}

string findfa(string s) {
  if(mp.find(s) == mp.end()) return s;
  mp[s] = findfa(mp[s]);
  return mp[s];
}

void go(string s) {
  string s1 = "", s2 = "";
  int i = 0;
  while(s[i] == ' ') i++;
  while(s[i] != ' ') s1 += s[i++];
  while(s[i] == ' ') i++;
  while(i < s.length() && s[i] != ' ') s2 += s[i++];
  s1 = init(s1);
  s2 = init(s2);
  if(mp.find(s1) != mp.end() || s1 == s2) return ;
  if(findfa(s2) != s1) mp[s1] = s2;
}

bool check(char x) {
  return x >= 'a' && x <= 'z';
}

string pre(string s) {
  string ans = "";
  int flag = 1;
  for(int i = 0; i < s.length(); ++i) {
    if(isdigit(s[i])) ans += s[i], flag = 0;
    else if(check(s[i])) ans += s[i], flag = 0;
    else if(s[i] == '(') ans += s[i], flag = 1;
    else if(s[i] == ')') ans += s[i], flag = 0;
    else if(s[i] == '%' || s[i] == '*' || s[i] == '/' || s[i] == '^') ans += s[i], flag = 1;
    else if(s[i] == '+') {
      if(!flag) ans += s[i], flag = 1;
      else ans += '$';
    }
    else if(s[i] == '-') {
      if(!flag) ans += s[i], flag = 1;
      else ans += '#';
    }
  }
  return ans;
}

int get(char c) {
  if(c == '(') return 0;
  if(c == '+') return 1;
  if(c == '-') return 2;
  if(c == '*') return 3;
  if(c == '/') return 4;
  if(c == '%') return 5;
  if(c == '^') return 6;
  if(c == '$') return 7;
  if(c == '#') return 8;
  if(c == ')') return 9;
  return 10;
}

stack<int> st1, st2;
int sgn(int x) {
  if(x < 0) return -1;
  if(x > 0) return 1;
  return 0;
}

int pow(int x, int y) {
  int ans = 1;
  for(; y; y >>= 1) {
    if(y & 1) ans = ans * x;
    x = x * x;
  }
  return ans;
}

void pop() {
  int x, y, op = st1.top();
  st1.pop();
  if(op == 8) {
    x = st2.top(); st2.pop();
    st2.push(-x); 
  } else if(op >= 1 && op <= 6) {
    y = st2.top(); st2.pop();
    x = st2.top(); st2.pop();
    if(op == 1) x += y;
    if(op == 2) x -= y;
    if(op == 3) x *= y;
    if(op == 4) x = sgn(x) * sgn(y) * abs(x) / abs(y);
    if(op == 5) x = sgn(x) * sgn(y) * (abs(x) % abs(y));
    if(op == 6) x = pow(x,y);
    st2.push(x);
  }
}

int cal(string s, int pos, string &s1) {
  int i;
  s1 = "";
  for(i = pos; i < s.length() && (isdigit(s[i]) || check(s[i])); ++i) 
    s1 += s[i];
  return i;
}

string replace(string s) {
  if(mp.find(s) != mp.end()) return findfa(s);
  return s;
}

int zh(string s) {
  int ans = 0;
  for(int i = 0; i < s.length(); ++i) {
    if(isdigit(s[i])) ans = ans * 10 + s[i] - '0';
    else return 0;
  }
  return ans;
}

void print(string s) {
  s = pre(s);
  string s1, s2;
  for(int i = 0; i < s.length(); ++i) {
    int k = get(s[i]), j;
    if(k == 0 || k == 7 || k == 8) st1.push(k);
    else if(k <= 6) {
      while(!st1.empty() && !p[k][st1.top()]) {
        pop();
      }
      st1.push(k);
    }
    else if(k == 9) {
      while(st1.top() != 0) {
        pop();
      }
      st1.pop();
    }
    else {
      j = cal(s, i, s1);
      i = j-1;
      s1 = replace(s1);
      st2.push(zh(s1));
    }
  }
  while(!st1.empty())pop();
  printf("%d\n", st2.top());
}

int main() {
  freopen("plcool.in", "r", stdin);
  freopen("plcool.out", "w", stdout);
  while(gets(str)) {
    s = str;
    while(!st1.empty()) st1.pop();
    while(!st2.empty()) st2.pop();
    if(s[0] == 'p' || s[0] == 'P') {
      s = s.substr(5, s.length() - 5);
      s = init(s);
      print(s);
    } else {
      s = s.substr(6, s.length() - 6);
      go(s);
    }
  }
  return 0;
}