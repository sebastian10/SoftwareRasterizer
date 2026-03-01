#pragma once

#include "Color.h"
#include "../Model.h"
#include "Vector.h"
#include <array>
#include "Matrix.h"
#include "lighting/Light.h"

using namespace Rasterizer::Graphics::Lighting;

namespace Rasterizer::Graphics::Shaders
{
	struct IShader
	{
		virtual std::pair<bool, Color> fragment( const Vec3 bar ) const = 0;
	};

    struct FlatShader : IShader
    {
    public:
        const Model& model;
        Mat4 ViewMatrix;
        Mat4 ModelView;
        Mat4 Projection;
        const std::vector<std::unique_ptr<ILight>>& lights;
        std::array<Vec3, 3> tri;    // triangle in camera coordinates
    private:
        float ka = 0.1f;            // ambient strength
        float kd = 0.8f;            // diffuse strength
        float ks = 0.4f;            // specular strength
        float shininess = 320.0f;
    public:

        FlatShader( const Model& m, const Mat4& ViewMatrix, const Mat4& Projection, const std::vector<std::unique_ptr<ILight>>& lights )
            :
            model( m ),
            ViewMatrix( ViewMatrix ),
            ModelView( ViewMatrix * model.GetModelMatrix() ),
            Projection( Projection ),
            lights( lights )
        {
        }

        virtual Vec4 vertex( const int face, const int vert )
        {
            Vec3 vertex = model.GetVertex( face, vert );                          
            Vec4 position = ModelView * Vec4{ vertex.x(), vertex.y(), vertex.z(), 1.0f };
            tri[vert] = position.xyz();                            
            return Projection * position;                         // in clip coordinates
        }

        virtual std::pair<bool, Color> fragment( const Vec3 bar ) const
        {
            // compute face normal
            Vec3 normal = ( tri[1] - tri[0] ).Cross( tri[2] - tri[0] ).Normalise();

            // triangle point as surface position for flat shading
            Vec3 point = tri[0];

            Vec3 view = (-point).GetNormalised();

            Vec3 colour(0.0f);
            for ( const auto& light : lights )
            {
                Vec3 lDirection = light->GetLightDirection( point, ViewMatrix.ToMat3() );
                Vec3 lightColour = light->GetColor() * light->GetAttenuation( point ) * light->GetIntensity();

                // ambient
                Vec3 ambient = lightColour * ka;

                // Diffuse
                float diff = max( 0.0f, normal.Dot( lDirection ) );
                Vec3 diffuse = lightColour * diff * kd;

                Vec3 specular( 0.0f );
                if ( diff > 0.0f )
                {
                    // Specular
                    Vec3 halfVector = ( lDirection + view ).Normalise();
                    float spec = std::pow( max( 0.0f, normal.Dot( halfVector ) ), shininess );
                    specular = lightColour * spec * ks;
                }
                
                colour += ambient + diffuse + specular;
            }

            float maxVal = max( colour.x(), max(colour.y(), colour.z()));
            //std::cout << "Max light value: " << maxVal << std::endl;

            Vec3 finalColour(
                min( 1.f, colour.x() ),
                min( 1.f, colour.y() ),
                min( 1.f, colour.z() )
            );

            return { false, Colors::MakeRGB(                    // do not discard the pixel
                (unsigned char) ( finalColour.x() * 255 ), 
                (unsigned char) ( finalColour.y() * 255 ), 
                (unsigned char) ( finalColour.z() * 255 ) ) 
            };         
        }
    };

    struct GouraudShader : IShader
    {
        const Model& model;
        Mat4 ModelMatrix;
        Mat4 ViewMatrix;
        Mat4 ModelView;
        Mat4 Projection;
        const std::vector<std::unique_ptr<ILight>>& lights;
        std::array<Vec3, 3> tri;  // triangle in camera coordinates
        std::array<Vec3, 3> vertexColors;

        Mat3 NormalMatrix;

        float ka = 0.1f;            // ambient strength
        float kd = 0.8f;            // diffuse strength
        float ks = 0.4f;            // specular strength
        float shininess = 320.0f;

        GouraudShader( const Model& m, const Mat4& ViewMatrix, const Mat4& Projection, const std::vector<std::unique_ptr<ILight>>& lights )
            :
            model( m ),
            ModelMatrix( model.GetModelMatrix() ),
            ViewMatrix( ViewMatrix ),
            Projection( Projection ),
            lights( lights )
        {
            ModelView = ViewMatrix * ModelMatrix;

            NormalMatrix = ModelView.ToMat3();
            NormalMatrix = NormalMatrix.Inversed( NormalMatrix.Determinant() ).Transposed();
        }

        virtual Vec4 vertex( const int face, const int vert )
        {
            Vec3 vertex = model.GetVertex( face, vert );
            Vec3 normal = model.GetVertexNormal( face, vert );

            Vec4 position = ModelView * Vec4{ vertex.x(), vertex.y(), vertex.z(), 1.0f };
            tri[vert] = position.xyz();

            Vec3 view = ( -position.xyz() ).GetNormalised();

            normal = NormalMatrix * normal;
            if ( normal.GetLength() > 1e-6f )
                normal.Normalise();
            else
                normal = Vec3( 0, 0, 1.0f ); // fallback

            // for visualising normals
            // Vec3 debugColor = ( normal + Vec3( 1, 1, 1 ) ) * 0.5f;

            Vec3 colour(0.0f);
            for ( const auto& light : lights )
            {
                Vec3 lDirection = light->GetLightDirection( position.xyz(), ViewMatrix.ToMat3() );
                Vec3 lightColour = light->GetColor() * light->GetAttenuation( position.xyz() ) * light->GetIntensity();

                // ambient
                Vec3 ambient = lightColour * ka;

                // Diffuse
                float diff = max( 0.0f, normal.Dot( lDirection ) );
                Vec3 diffuse = lightColour * diff * kd;

                Vec3 specular( 0.0f );
                if ( diff > 0.0f )
                {
                    // Specular
                    Vec3 halfVector = ( lDirection + view ).Normalise();
                    float spec = std::pow( max( 0.0f, normal.Dot( halfVector ) ), shininess );
                    specular = lightColour * spec * ks;
                }

                colour += ambient + diffuse + specular;

                //std::cout << "diff: " << diff << ",\n" <<
                //    "normal: " << normal.x() << ", " << normal.y() << ", " << normal.z() << ",\n" <<
                //    "L: " << lDirection.x() << ", " << lDirection.y() << ", " << lDirection.z() << std::endl;
            }

            Vec3 finalColour(
                min( 1.0f, colour.x() ),
                min( 1.0f, colour.y() ),
                min( 1.0f, colour.z() )
            );

            vertexColors[vert] = finalColour * 255;

            return Projection * position;                         // in clip coordinates
        }

        virtual std::pair<bool, Color> fragment( const Vec3 bar ) const
        {
            float a = bar.x(), b = bar.y(), c = bar.z();

            int rCol = (int) ( a * vertexColors[0].x() + b * vertexColors[1].x() + c * vertexColors[2].x() );
            int gCol = (int) ( a * vertexColors[0].y() + b * vertexColors[1].y() + c * vertexColors[2].y() );
            int bCol = (int) ( a * vertexColors[0].z() + b * vertexColors[1].z() + c * vertexColors[2].z() );

            return { false, Colors::MakeRGB( rCol, gCol, bCol ) };         // do not discard the pixel
        }
    };
}