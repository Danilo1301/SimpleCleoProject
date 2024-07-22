#pragma once

class CVector {
public:
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    CVector(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    CVector operator+(const CVector right)
    {
        CVector result(this->x, this->y, this->z);
        result.x += right.x;
        result.y += right.y;
        result.z += right.z;
        return result;
    }
};