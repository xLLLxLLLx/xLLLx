[TOC]

## Set

#### 前言

> 不会数据结构选手 
>
> 当几乎没写过什么数据结构的菜鸡遇上了毒瘤的splay和treap 时间正一点一点地被续走TAT
>
> 听说set有时候可以替代treap和splay 
>
> 那么菜鸡LLL就来学习一下set的神奇操作

#### 简单的介绍==没介绍TAT

> `set` `multiset` `map` `multimap` 等内部采用的就是一种非常高效的平衡检索二叉树

**tips:**

- `set`中元素都是排好序的
- `set`中没有重复的元素（`multiset` 可以有

#### set中常用的方法

```c++
begin() //返回set中第一个元素的迭代器
end() //返回指向当前set末尾元素的下一位置的迭代器
clear() //删除set容器里的所有元素
empty() //判断set容器是否为空
max_size() //返回set容器可能包含的元素个数
rbegin() //返回的值和end()相同
rend() //返回的值和begin()相同
count() //用来查找set中某个键值出现的次数
erase(iterator) //删除定位器iterator指向的值
erase(first,second) //删除定位器first和second之间的值
erase(key_value) // 删除键值key_value的值
equal_range() //返回一堆定位器 分别表示第一个大于或等于给定关键值的元素和第一个大于给定关键值的元素 这个返回值是一个pair类型 如果这一对定位器中哪个返回失败 就会等于end()值 
find() //返回给定值的定位器 如果没有找到则返回end()
```

```c++
#include <iostream>
#include <set>
 
using namespace std;
 
int main(){
     set<int> s;
     set<int>::iterator iter;
     for(int i = 1 ; i <= 5; ++i)
     {
         s.insert(i);
     }
     for(iter = s.begin() ; iter != s.end() ; ++iter)
     {
         cout<<*iter<<" ";
     }
     cout<<endl;
     pair<set<int>::const_iterator,set<int>::const_iterator> pr;
     pr = s.equal_range(3);
     cout<<"第一个大于等于 3 的数是 ："<<*pr.first<<endl;
     cout<<"第一个大于 3的数是 ： "<<*pr.second<<endl;
     return 0;
}
```

#### 自定义比较函数



- 元素不是结构体

  //自定义比较函数myComp 重载`()`操作符

  ```c++
  struct myComp{
      bool operator () (const your_type &a,const your type &b){
          return a.data-b.data>0;
      }
  }
  set<int,myComp>s;
  set<int,myComp>:: iterator it;
  ```

  

- 结构题

  ```c++
  struct Info{
      string name;
      double score;
      bool operator < (const Info &a) const{
          return a.score < score;
      }
  }
  set<Info>s;
  set<Info>:: iterator it;
  ```



#### 补充

```c++
lower_bound(elem) //返回元素值为elem的第一个可安插的位置 也就是元素值>=elem的第一个元素的位置
upper_bound(elem) //返回元素值为elem的最后一个可安插的位置 也就是元素值>elem的第一个元素位置

```

```c++
// cont/set1.cpp

    #include <iostream>
    #include <set>
    using namespace std;

    int main()
    {

       /*type of the collection:
        *-no duplicates
        *-elements are integral values
        *-descending order
        */
       typedef set<int,greater<int> > IntSet;

       IntSet coll1;         // empty set container

       //insert elements in random order
       coll1.insert(4);
       coll1.insert(3);
       coll1.insert(5);
       coll1.insert(1);
       coll1.insert(6);
       coll1.insert(2);
       coll1.insert(5);

       //iterate over all elements and print them
       IntSet::iterator pos;
       for (pos = coll1.begin(); pos != coll1.end(); ++pos) {
           cout << *pos << ' ';
       }
       cout << endl;

       //insert 4 again and process return value
       pair<IntSet::iterator,bool> status = coll1.insert(4);
       if (status.second) {
           cout << "4 inserted as element "
                << distance (coll1.begin(),status. first) + 1
                << endl;
       }
       else {
           cout << "4 already exists" << endl;
       }

       //assign elements to another set with ascending order
       set<int> coll2(coll1.begin(),
                      coll1.end());

       //print all elements of the copy
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;

       //remove all elements up to element with value 3
       coll2.erase (coll2.begin(), coll2.find(3));

       //remove all elements with value 5
       int num;
       num = coll2.erase (5);
       cout << num << " element(s) removed" << endl;

       //print all elements
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;
    }
```

```c++
   6 5 4 3 2 1
   4 already exists
   1 2 3 4 5 6
   1 element(s) removed
   3 4 6
```

```c++
// cont/mset1.cpp

   #include <iostream>
   #include <set>
   using namespace std;

   int main()
   {

       /*type of the collection:
        *-duplicates allowed
        *-elements are integral values
        *-descending order
        */
       typedef multiset<int,greater<int> > IntSet;

       IntSet coll1,        // empty multiset container

       //insert elements in random order
       coll1.insert(4);
       coll1.insert(3);
       coll1.insert(5);
       coll1.insert(l);
       coll1.insert(6);
       coll1.insert(2);
       coll1.insert(5);

       //iterate over all elements and print them
       IntSet::iterator pos;
       for (pos = coll1.begin(); pos != coll1.end(); ++pos) {
           cout << *pos << ' ';
       }
       cout << endl;

       //insert 4 again and process return value
       IntSet::iterator ipos = coll1.insert(4);
       cout << "4 inserted as element "
            << distance (coll1.begin(),ipos) + 1
            << endl;

       //assign elements to another multiset with ascending order
       multiset<int> coll2(coll1.begin(),
                              coll1.end());

       //print all elements of the copy
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;

       //remove all elements up to element with value 3
       coll2.erase (coll2.begin(), coll2.find(3));

       //remove all elements with value 5
       int num;
       num = coll2.erase (5);
       cout << num << " element(s) removed" << endl;

       //print all elements
       copy (coll2.begin(), coll2.end(),
             ostream_iterator<int>(cout," "));
       cout << endl;
   }
```



```c++
6 5 5 4 3 2 1
4 inserted as element 5
1 2 3 4 4 5 5 6
2 element(s) removed
3 4 4 6
```

