
#ifndef _INCLUDE_PIXEL_H_
#define _INCLUDE_PIXEL_H_

#include <iostream.h>
#include <vector>
#define PW 50
#define PH 40

class Pixel
{
public:
    int origin;
    int right;
    int upright;
    int up;
    bool isgood;
    int value;

    vector<int> pixelUpArray;
    vector<int> pixelRightArray;

    vector<int> pixelDownArray;
    vector<int> pixelLeftArray;
    
    vector<int> pixelUpArrayNoValue;
    vector<int> pixelRightArrayNoValue;
    vector<int> pixelDownArrayNoValue;
    vector<int> pixelLeftArrayNoValue;

public:
    Pixel();
    Pixel(int ori, int rig, int uprig, int up);
    Pixel(const Pixel &original);
    ~Pixel();
    bool IsValid();
    bool IsValid2();
    void DoValue();
    bool IsConnectedH(Pixel *right);
    bool IsConnectedV(Pixel *up);
    bool IsEqual(Pixel *pixel);
    void PrintOut();
    const Pixel &operator=(const Pixel &rightSide);
};

Pixel::Pixel(int ori, int rig, int uprig, int u)
{
    origin = ori;
    right = rig;
    upright = uprig;
    up = u;
    value = 0;
    isgood = true;
}

Pixel::Pixel()
{
    origin = 0;
    right = 0;
    upright = 0;
    up = 0;
    value = 0;
    isgood = false;
}

void Pixel::DoValue()
{
    value = 0;
    if (1 == origin)
        ++value;
    if (1 == right)
        ++value;
    if (1 == upright)
        ++value;
    if (1 == up)
        ++value;
}

Pixel::Pixel(const Pixel &original)
{
    origin = original.origin;
    right = original.right;
    upright = original.upright;
    up = original.up;
    value = original.value;
    isgood = original.isgood;
}

Pixel::~Pixel()
{
}

const Pixel &Pixel::operator=(const Pixel &rightSide)
{

    if (this != &rightSide)
    {
        this->origin = rightSide.origin;
        this->right = rightSide.right;
        this->upright = rightSide.upright;
        this->up = rightSide.up;
        this->value = rightSide.value;
        this->isgood = rightSide.isgood;
    }
}

bool Pixel::IsEqual(Pixel *pixel)
{
    return this->origin == pixel->origin && this->right == pixel->right && this->up == pixel->up && this->upright == pixel->upright;
}
void Pixel::PrintOut()
{
    cout << "PrintOut " << origin << "  " << right << "  " << upright << "  " << up << " value " << value << " isgood " << isgood << endl;
}

bool Pixel::IsValid2()
{
    if (value > 1) return false;
  return IsValid();
}

bool Pixel::IsValid()
{

   // if (origin == right && right == upright && upright == up)
    //    return false;

    //  if ( origin == right  && upright == up)  isgood = true;

    if (origin == up && right == upright)
        isgood = false;

    if (origin != 1 && right != 1 && upright != 1 && up != 1)
        isgood = false;

    if (2 == origin)
    {
        if (right != 5 && upright != 4 && up != 3)
        {
            return true;
        }
    }
    else if (5 == right)
    {
        if (origin != 2 && upright != 4 && up != 3)
        {
            return true;
        }
    }
    else if (4 == upright)
    {
        if (right != 5 && origin != 2 && up != 3)
        {
            return true;
        }
    }
    else if (3 == up)
    {
        if (right != 5 && upright != 4 && origin != 2)
        {
            return true;
        }
    }

    return false;
}

bool Pixel::IsConnectedH(Pixel *rig)
{
    if (rig->origin == right && rig->up == upright)
    {
        return true;
    }
    return false;
}

bool Pixel::IsConnectedV(Pixel *upOne)
{

    if (upOne->origin == up && upOne->right == upright)
    {
        return true;
    }
    return false;
}
#endif
