
// COS30008, Tutorial 2, 2023

#include "Polygon.h"

#include <cassert>

Polygon::Polygon() noexcept :
    fNumberOfVertices()
{}

void Polygon::readData( std::istream& aIStream )
{
    // read input file containing 2D vector data
    // if no data can be read, then exit loop
    // lInput >> lVectors[lIndex] evaluates to false on EOF
    while ( aIStream >> fVertices[fNumberOfVertices] )
    {
        fNumberOfVertices++;
    }
}

size_t Polygon::getNumberOfVertices() const noexcept
{
    return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex( size_t aIndex ) const
{
    assert( aIndex < fNumberOfVertices );

    return fVertices[aIndex];
}

float Polygon::getPerimeter() const noexcept
{
    float Result = 0.0f;

    // There have to be at least three vertices
    if ( fNumberOfVertices > 2 )
    {
        // solution without modulus and explicit temporary variables
        for ( size_t i = 1; i < fNumberOfVertices; i++ )
        {
            Result += (fVertices[i] - fVertices[i - 1]).length();
        }

        Result += (fVertices[0] - fVertices[fNumberOfVertices - 1]).length();
    }

    return Result;
}

Polygon Polygon::scale( float aScalar ) const noexcept
{
    Polygon Result = *this;
    
    for ( size_t i = 0; i < fNumberOfVertices; i++ )
    {
        Result.fVertices[i] = fVertices[i] * aScalar;
    }
    
    return Result;
}

float Polygon::getSignedArea() const noexcept
{
    if (getNumberOfVertices() > 2)
    {
        float lVal = 0;
        float lFirstLastVal = 0;
        for (int i = 0; i < getNumberOfVertices(); i++)
        {
            int j = (i + 1) % getNumberOfVertices();
            lVal += 0.5 * (getVertex(i).x() * getVertex(j).y() 
                - getVertex(j).x() * getVertex(i).y());
        }
        return lVal;
    }
}


// Take in rotational matrix and apply it to Polygon
Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept
{   
    Polygon lResPolygon = *this;
    Vector3D result;
    for (int i = 0; i < getNumberOfVertices(); i++)
    {
        Vector3D lVec3D = Vector3D(getVertex(i));
        Vector3D result = aMatrix * lVec3D;
        lResPolygon.fVertices[i] = static_cast<Vector2D>(result);
    }
    return lResPolygon;
}
