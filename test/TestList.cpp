
#include "gtest/gtest.h"

#include "base_types.h"
#include "list.h"
#include "stack.h"

struct datum {
    String name;
    unsigned int age;
    datum(String n, unsigned int a): name(n),age(a) {}
    datum() {};

    datum &operator = (const datum &d) {
        name = d.name;
        age = d.age;
    }

    void show() const {
        std::cout << name << " " << age << std::endl;
    }
};



template <class Iter>
void print_iter(Iter begin, Iter end) {
  for(Iter it = begin; it != end; ++it) {
    it->show();
  }

}


// Write tests for the list
TEST(TestList, Test1) {
    dst::List2<datum> l;
    Strings names = {"javi","pedro","garineh", "maria"};
    Ints ages = {1,2,3,4};
    for(unsigned int i = 0; i < names.size(); ++i) {
        l.push_back(datum(names[i], ages[i]));
        l.push_front(datum(names[i], ages[i]));
    }
    EXPECT_EQ(l.size(), 8);

    print_iter(l.begin(),l.end());
    l.insert(datum("marcelino",68),1);
    //print_iter(l.begin(),l.end());
    for(unsigned int i = 0; i < l.size(); ++i) {
        l[i].age++;
    }
    l.remove(1);
    l.remove(3);
    l.remove(5);
    EXPECT_EQ(l.size(), 6);

}

TEST(TestStack, Test1) {
    dst::Stack<int> stack;
    Ints ages = {1,2,3,4};
    for(auto i : ages) stack.push(i);

    EXPECT_EQ(stack.pop(), 4);
    EXPECT_EQ(stack.pop(), 3);
    EXPECT_EQ(stack.pop(), 2);
    EXPECT_EQ(stack.pop(), 1);
    EXPECT_EQ(stack.size(), 0);

}
