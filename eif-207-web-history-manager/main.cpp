#include "main.h"
#include "Tab.h"

int main()
{
	WebPage w1("1", "2", "3");
	WebPage w2("4", "5", "6");
	WebPage w3("7", "8", "9");
	std::list<WebPage> l1;
	l1.push_back(w1);
	l1.push_back(w2);
	l1.push_back(w3);
	History h1(l1, 1);
	Tab t1(h1);
	t1.goBackward();
	return 0;
}