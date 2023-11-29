/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2022
* Author: Vu Van Tien
* Date: 15.02.2022
*/

//The library here is concretely set, students are not allowed to include any other libraries.
#ifndef studyInPink_h
#define studyInPink_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

////////////////////////////////////////////////////////////////////////
///STUDENT'S ANSWER BEGINS HERE
///Complete the following functions
///DO NOT modify any parameters in the functions.
////////////////////////////////////////////////////////////////////////

class Point {
private:
    int x;
    int y;
public:
    Point(int x=0, int y=0);
    string toString() const;

    int distanceTo(const Point & otherPoint) const;
};
Point::Point(int x, int y)
{
   this -> x = x;
   this -> y = y;
}
string Point::toString() const
{
    string a = to_string(x);
    string b = to_string(y);
    return "<Point["+a+","+b+"]>";
}
int Point::distanceTo(const Point & otherPoint) const
{
    return ceil(sqrt((x - otherPoint.x) * (x - otherPoint.x) 
                   + (y - otherPoint.y) * (y - otherPoint.y)));
}
class Node {
private:
    Point point;
    Node * next;

    friend class Path;

public:
    Node(const Point & point=Point(), Node * next=NULL);
    string toString() const;
};
Node::Node(const Point & point, Node * next)
{
    this -> point = point;
    this -> next = next;
}
string Node::toString() const
{
    return "<Node[" + point.toString() + "]>";
}
class Path {
private:
    Node * head;
    Node * tail;
    int count;
    int length;

public:
    Path();
    ~Path();
    void addPoint(int x, int y);
    string toString() const;
    Point getLastPoint() const;
    int getLength();
};
Path::Path()
{
    head = NULL;
    tail = NULL;
    count = 0;
    length = -1;
}
Path::~Path()
{
    Node *tmp; 
    while (head != NULL)
    {
        tmp = head -> next;
        free(head);
        head = tmp;
    }
}
void Path::addPoint(int x, int y)
{
    count++;
    Node *node1 = new Node ;
    node1 -> point = Point(x ,y);
    Node *node2 = tail ;
    if (head == NULL)
    {
        head = tail = node1;
    }
    else
    {
        tail -> next = node1;
        tail = node1;
    }
    if (count == 1) length = 0;
    else
    {
        length += node2 -> point.distanceTo(node1 -> point);
    }    
}
string Path::toString() const
{
    string s;
    string sclone;
    Node *node3 = new Node;
    node3 = head;
    for (int i = 0 ; i < count ; i++)
    {
        sclone += node3 -> toString();
        node3 = node3 -> next;  
        if (i < count -1) sclone += ",";
    }
    s += "<Path[count:" + to_string(count) + ",length:" + to_string(length) + ",[" + sclone +  "]]>";
    return s;
}
Point Path::getLastPoint() const
{
    return tail -> point;
}
int Path::getLength()
{
    return length;
}
class Character {
private:
    string name;
    Path * path;
public:
    Character(const string & name="");
    ~Character();

    string getName() const;
    void setName(const string & name);
    int getLength() const;
    Point getLastPoint() const;
    void moveToPoint(int x, int y);
    string toString() const;
};
Character::Character(const string & name)
{
    this -> name = name;
    Path *p = new Path;
    this -> path = p;
}
Character::~Character()
{
    path -> ~Path();
}
string Character::getName() const
{
    return name;
}
void Character::setName(const string & name)
{
    this -> name = name;
}
void Character::moveToPoint(int x, int y)
{
    path->addPoint(x, y);
}
string Character::toString() const
{
    string l;
    l = "<Character[name:"+name+",path:";
    string k;
    k = path -> toString();
    l += k;
    return l + "]>";
}
int Character::getLength() const
{
    return path -> getLength();
}
Point Character::getLastPoint() const
{
    return path -> getLastPoint();
}
bool rescueSherlock(
        const Character & chMurderer,
        const Character & chWatson,
        int maxLength,
        int maxDistance,
        int & outDistance
        ){
    int l1 = chWatson.getLength();
    int l2 = chMurderer.getLength();
    Point p1 = chWatson.getLastPoint();
    Point p2 = chMurderer.getLastPoint();
    int length = p1.distanceTo(p2);
    if (l1 - l2 <= maxLength)
    {
        outDistance = length;
        if (length <= maxDistance) return true;
        return false;
    }
    else
    {
        outDistance = -1;
        return false;
    }
    return false;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* studyInPink_h */