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

            // position in view space
            Vec4 position = ModelView * Vec4{ vertex.x(), vertex.y(), vertex.z(), 1.0f };

            // save a copy for further fragment calculations
            tri[vert] = position.xyz();                     

            // return vertex in clip space, after projection
            return Projection * position;                         
        }

        virtual std::pair<bool, Color> fragment( const Vec3 bar ) const
        {
            // compute face normal
            Vec3 normal = ( tri[2] - tri[0] ).Cross( tri[1] - tri[0] ).Normalise();

            // triangle point as surface position for flat shading
            Vec3 point = tri[0];

            // view vector for specular light calculation 
            Vec3 view = (-point).GetNormalised();

            Vec3 colour(0.0f);
            for ( const auto& light : lights )
            {
                // light direction, either
                //      direction in case of directional light
                //      light position - point in case of point light
                Vec3 lDirection = light->GetLightDirection( point, ViewMatrix.ToMat3() );

                // attenuation based on distance to light for point lights
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

            // clamping of final colour so it won't exceed values of 255
            Vec3 finalColour(
                min( 1.f, colour.x() ),
                min( 1.f, colour.y() ),
                min( 1.f, colour.z() )
            );

            // returns the final colour
            // going from values [0,1] to [0,255]
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
        std::array<float, 3> clipW;

        bool skip = false;

        Mat3 NormalMatrix;

        float ka = 0.2f;            // ambient strength
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
            skip = false;

            Vec3 vertex = model.GetVertex( face, vert );
            Vec3 normal = model.GetVertexNormal( face, vert );

            Vec4 position = ModelView * Vec4{ vertex.x(), vertex.y(), vertex.z(), 1.0f };
            tri[vert] = position.xyz();

            Vec3 view = ( -position.xyz() ).GetNormalised();

            normal = NormalMatrix * normal;

            if ( normal.GetLength() > Rasterizer::Maths::epsilon )
                normal.Normalise();
            else
                skip = true;

            // for visualising normals
            Vec3 debugColor = ( normal + Vec3( 1, 1, 1 ) ) * 0.5f;

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
            }

            Vec3 finalColour(
                min( 1.0f, colour.x() ),
                min( 1.0f, colour.y() ),
                min( 1.0f, colour.z() )
            );

            vertexColors[vert] = finalColour * 255;

            Vec4 clip = Projection * position;
            clipW[vert] = clip.w();
            return clip;                         // in clip coordinates
        }

        virtual std::pair<bool, Color> fragment( const Vec3 bar ) const
        {
            float a = bar.x(), b = bar.y(), c = bar.z();
             
            float rcol = a * vertexColors[0].x() + b * vertexColors[1].x() + c * vertexColors[2].x();

            float gcol = a * vertexColors[0].y() + b * vertexColors[1].y() + c * vertexColors[2].y();

            float bcol = a * vertexColors[0].z() + b * vertexColors[1].z() + c * vertexColors[2].z();

            return { skip, Colors::MakeRGB( (int) rcol, (int) gcol, (int) bcol ) };
        }
    };
}